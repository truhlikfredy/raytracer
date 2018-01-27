/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include <cmath>
#include <thread>
#include <vector>
#include <float.h>
#include "render.h"
#include "../entities/objects/sphere.h"


Render::Render(int widthInit, int heightInit) {
  scene         = nullptr;
  width         = widthInit;
  height        = heightInit;
  dynamicPixels = new Color[widthInit * heightInit];
  threadsMax    = std::thread::hardware_concurrency();
}


windowType Render::getThreadWindow(int thread) {
  // Having 4 cores and 2 segments, will cause to create 4 threads which will together compute half of the screen and
  // then run another 4 threads to finish second segment. Setting segments to 1 will cause all threads to calculate
  // everything in one pass. At the moment the load balancing between the cores is fairly simple and instead of creating
  // small rectangles, this is just creating horizontal slits.

  return {
    .xStart = 0,
    .xEnd   = width,
    .yStart = ( thread    * height) / (threadsMax * SEGMENTS),
    .yEnd   = ((thread+1) * height) / (threadsMax * SEGMENTS)
  };
}



Color Render::rayStart(Ray ray, Sphere* objects, LightOmni* light, float frame) {
  //scene->evaluateLights(light, frame);
  scene->evaluateObjects(objects, frame);

  return rayFollow(ray, objects, light, frame, 1, false);
}


void Render::refract(Vector3 &incidentVec, Vector3 &normal, float refractionIndex, Vector3 &refractionRay) {
  float cosi = fmax(-1, fmin(1, (incidentVec % normal)));
  float etai = 1, etat = refractionIndex;
  Vector3 n = normal;
  if (cosi < 0) { cosi = -cosi; } else { std::swap(etai, etat); n= normal * -1.0; }
  float eta = etai / etat;
  float k = 1 - eta * eta * (1 - cosi * cosi);
  refractionRay = k < 0 ? 0 : incidentVec * eta  + n * (eta * cosi - sqrtf(k));
}

Color Render::rayFollow(Ray ray, Sphere* objects, LightOmni* light, float frame, int iteration, bool inside) {

  if (iteration > MAX_BOUNCES) {
    return Color();
  }

  // https://stackoverflow.com/questions/9893316/how-do-i-combine-phong-lighting-with-fresnel-dielectric-reflection-transmission
  float smallestHitDistance = FLT_MAX;  // set it to maximum at first
  int smallestObjectIndex = -1;
  Vector3 smallestHitPoint;

  // Find closest collision
  for (int i = 0; i< scene->nObjects; i++){
    Vector3 hitPoint;
    Sphere object = objects[i];
    float hitDistance;

    if (inside) {
      hitDistance = object.detectHitMax(ray, hitPoint);
    }
    else {
      hitDistance = object.detectHit(ray, hitPoint);
    }

    if (hitDistance != -1.0f) {
      if (smallestHitDistance > hitDistance) {
        // It's the shortest hit yet, let's save it, if it will win then calculate it's color by shading it depending on the bounce angle
        smallestObjectIndex = i;
        smallestHitDistance = hitDistance;
        smallestHitPoint = hitPoint;
      }
    }
  }

  // Only shade the closes collision
  if (smallestObjectIndex >= 0) {
    Sphere object = objects[smallestObjectIndex];

    // https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
    Vector3 hitNormal = object ^smallestHitPoint;
    Vector3 hitReflected = ray.direction - (hitNormal * 2 * (ray.direction % hitNormal));
    Vector3 hitLight = ~Vector3(light->center - smallestHitPoint);
    //Vector3 hitLight = ~Vector3(smallestHitPoint - light->center);

    materialStatic hitMaterial = object.materialFn(smallestHitPoint, frame);

    float diffuse = fmaxf(0, hitLight % hitNormal); // how similar are they?
    float specular = fmaxf(0, hitLight % hitReflected);


    Color colorBase = Color();
    Color colorRefract = Color();
    Color colorReflect = Color();

    //if (iteration ==1)
    if (hitMaterial.transparency != 0.0f) {
      Vector3 hitRefracted;
      refract(ray.direction, hitNormal, hitMaterial.refractiveIndex, hitRefracted);

      colorRefract = rayFollow(Ray(smallestHitPoint, hitRefracted), objects, light, frame, iteration +1, !inside) * hitMaterial.transparency;
    }
    if (hitMaterial.reflectivity != 0.0f && inside == false) {
      colorReflect = rayFollow(Ray(smallestHitPoint, hitReflected), objects, light, frame, iteration +1, false) * hitMaterial.reflectivity;
    }
    // diffuse = similarity (dot product) of hitLight and hitNormal
    // https://youtu.be/KDHuWxy53uM
    // And use the diffuse / specular only when they are positive
    // shadeOfTheRay = specular + diffuse + ambient
    // https://qph.ec.quoracdn.net/main-qimg-dbc0172ecc9127a3a6b36c4d7f634277

    //http://www.paulsprojects.net/tutorials/simplebump/simplebump.html
    Color emmision(0.0f, 0.0f, 0.0f);
    Color globalAmbient(0.0f, 0.0f, 0.0f);
    float atenuate = 1.0f;

    colorBase = light->color * powf(specular, hitMaterial.shininess) + hitMaterial.diffuse * diffuse + hitMaterial.ambient;

    for (int j = 0; j < scene->nObjects; j++) {
      // test all objects if they are casting shadow from this light
      if (j != smallestObjectIndex) {
        // can't cast shadow on yourself through bounded rays, at least not yet with simple shapes
        Sphere shadow = objects[j];
        if (shadow.detectHit(Ray(smallestHitPoint, hitLight)) != -1) {
          if (shadow.materialFn(hitLight,frame).castsShadows) {
            colorBase = Color(hitMaterial.ambient);
            break;
          }
        }
      }
    }

    //return colorBase;
    return Color(colorBase + colorRefract + colorReflect);
  }

  return Color();
}

void Render::renderPartialWindow(float frame, windowType window) {
  Sampler sampler(SAMPLING_MIN, SAMPLING_MAX, scene->camera.shutterSpeed, scene->camera.apeture, scene->nLights, frame);

  Sphere    *objects = new Sphere[scene->nObjects];
  LightOmni light;
  sampleTuple sample;

  for (int y = window.yStart; y < window.yEnd; y++) {
    for (int x = window.xStart; x < window.xEnd; x++) {
      unsigned int colors = 0;
      Color totalColor(0.0f);
      Color lastColor;

      sampler.nextPixel();
      while (sampler.isNext()) {


        sampler.getNextSample(&sample);

        Vector3 start = scene->camera.possition + Vector3(sample.lensX, sample.lensY, 0);
        Vector3 lookAt = scene->camera.lookAt;
        Vector3 down(0.0f, -1.0f, 0.0f);
        Vector3 right = (~Vector3(lookAt & down))*320;
        Vector3 up2 = (~Vector3(lookAt & right))*200;

        float recenterX = ( x + sample.spaceX - width/2.0f) / ( 2.0 * width);
        float recenterY = ( y + sample.spaceY - height/2.0f) / ( 2.0 * height);

        Vector3 dest3 = ~Vector3((right * recenterX) + (up2 * recenterY) + lookAt - start);

        Ray rayForThisPixel(start,dest3);
        light = scene->lights[sample.light].evaluateFn(frame);
        lastColor = ~rayStart(rayForThisPixel, objects, &light, frame + sample.time);

        totalColor = totalColor + lastColor;    // TODO
        colors++;

        if (sampler.index == sampler.indexMinimum) {
          // detect black parts of the scene after few sample rays
          Color currentAverage(totalColor/ colors);
          if (currentAverage.sum() == 0) {
            sampler.finish();
          }
        }

      }
      dynamicPixels[x + (y * width)] = totalColor / colors;

    }
  }

  delete[] objects;
}

void Render::clearDynamicPixels() {
  for (int i = 0; i < height * width; i++) {
    dynamicPixels[i] = Color();
  }
}

void Render::renderFullWindow(Scene *sceneInit) {
  scene = sceneInit;
  std::vector<std::thread> workers;

  clearDynamicPixels();

  for (int segment = 0; segment < SEGMENTS; segment++) {
    for (int thread = 0; thread < threadsMax; thread++) {
      workers.emplace_back([this, thread] {
        this->renderPartialWindow(scene->frame, this->getThreadWindow(thread));
      });
    }
    for (auto& worker: workers) worker.join();
  }
}