/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include <cmath>
#include <thread>
#include <vector>
#include <float.h>
#include "render.h"
#include "../entities/camera.h"
#include "../scenes/scene.h"


Render::Render(int widthInit, int heightInit): width(widthInit), height(heightInit), scene(nullptr) {
  dynamicPixels = new Color[widthInit * heightInit];
  threadsMax    = std::thread::hardware_concurrency();
}


void Render::getThreadWindow(int thread, windowType &ret) {
  // Having 4 cores and 2 segments, will cause to create 4 threads which will together compute half of the screen and
  // then run another 4 threads to finish second segment. Setting segments to 1 will cause all threads to calculate
  // everything in one pass. At the moment the load balancing between the cores is fairly simple and instead of creating
  // small rectangles, this is just creating horizontal slits.

  ret.xStart = 0;
  ret.xEnd   = width;
  ret.yStart = ( thread    * height) / (threadsMax * SEGMENTS);
  ret.yEnd   = ((thread+1) * height) / (threadsMax * SEGMENTS);
}


colors Render::rayStart(Ray ray, Sphere* objects, LightOmni* light, float frame) {
  if (scene->camera.shutterBlur != 0.0f) {
    scene->evaluateObjects(objects, frame);
  }

  return rayFollow(ray, objects, light, frame, 1, -1);
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


colors Render::rayFollow(Ray ray, Sphere* objects, LightOmni* light, float frame, int iteration, int inside) {
  colors ret = {.average = Color(), .sum = Color() };

  if (iteration > MAX_BOUNCES) {
    return ret;
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

    if (inside >= 0) {
      //hitDistance = object.detectHitMax(ray, hitPoint);
      if (inside == i) {
        // if we are testing the collision with itslef (inside the object) then find the furtherst point
        hitDistance = object.detectHitMax(ray, hitPoint);
      }
      else {
        // but for all other objects even including intersecting object do detect closest collision
        hitDistance = object.detectHit(ray, hitPoint);
      }
    }
    else {
      hitDistance = object.detectHit(ray, hitPoint);
    }

    if (hitDistance != -1.0f) {
      if (smallestHitDistance > hitDistance) {
        // It's the shortest hit yet, let's save it, if it will win then calculate it's color by shading it depending on the bounce angle
        smallestObjectIndex = i;
        smallestHitDistance = hitDistance;
        smallestHitPoint    = hitPoint;
      }
    }
  }

  // Only shade the closes collision
  if (smallestObjectIndex >= 0) {
    Sphere object = objects[smallestObjectIndex];

    // https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
    Vector3 hitNormal    = object ^smallestHitPoint;
    Vector3 hitReflected = ray.direction - (hitNormal * 2 * (ray.direction % hitNormal));
    Vector3 hitLight     = Vector3(light->center - smallestHitPoint);

    // calculate lenght from the collision point to light source and then normalize the vector pointing to it
    float hitLightLen    = hitLight.lenght();
    hitLight = ~hitLight;

    materialStatic hitMaterial = object.materialFn(smallestHitPoint, frame);

    float diffuse  = fmaxf(0, hitLight % hitNormal); // how similar are they?
    float specular = fmaxf(0, hitLight % hitReflected);


    colors colorRefract = {.average = Color(), .sum = Color() };
    colors colorReflect = {.average = Color(), .sum = Color() };

    if (hitMaterial.transparency != 0.0f) {
      // If transparency is enabled then handle refraction
      Vector3 hitRefracted;
      refract(ray.direction, hitNormal, hitMaterial.refractiveIndex, hitRefracted);

      colorRefract = rayFollow(Ray(smallestHitPoint, hitRefracted), objects, light, frame, iteration +1, (inside == -1) ? smallestObjectIndex : -1 );
      colorRefract.average *= hitMaterial.transparency;
      colorRefract.sum     *= hitMaterial.transparency;
    }

    if (hitMaterial.reflectivity != 0.0f) {
      // If the material is reflective then handle reflection
      colorReflect = rayFollow(Ray(smallestHitPoint, hitReflected), objects, light, frame, iteration +1, inside);
      colorReflect.average *= hitMaterial.reflectivity;
      colorReflect.sum     *= hitMaterial.reflectivity;
    }

    // diffuse = similarity (dot product) of hitLight and hitNormal
    // https://youtu.be/KDHuWxy53uM
    // And use the diffuse / specular only when they are positive
    // shadeOfTheRay = specular + diffuse + ambient
    // https://qph.ec.quoracdn.net/main-qimg-dbc0172ecc9127a3a6b36c4d7f634277
    // http://www.paulsprojects.net/tutorials/simplebump/simplebump.html

    ret.average = scene->ambient * hitMaterial.ambient;
    ret.sum     = (( hitMaterial.diffuse * diffuse + powf(specular, hitMaterial.shininess)) * light->color) / fmax(0.8f, powf((hitLightLen + smallestHitDistance)/300.0f, 2));

    for (int j = 0; j < scene->nObjects; j++) {
      // test all objects if they are casting shadow from this light
      Sphere objectCausingShadow = objects[j];
      if (j != smallestObjectIndex &&
        objectCausingShadow.detectHit(Ray(smallestHitPoint, hitLight)) != -1 &&
        objectCausingShadow.materialFn(hitLight,frame).castsShadows &&
        hitLightLen > (objectCausingShadow.center - smallestHitPoint).lenght() ) {

        // If the following are meet:
        // 1) can't cast shadow on yourself through bounded rays, at least not yet with simple shapes
        // 2) ray needs to hit the object which is causing shadows (if it's not hit then it couldn't cause shadow)
        // 3) object's material needs to have property to cast shadows
        // 4) object needs to be between the light source and the collision point and not behind the light source
        // Then do the following:

        ret.sum = Color();    // null the summing factor, leave only average factor ok which is the ambient part
        break;
      }
    }

    ret.average += colorRefract.average + colorReflect.average;
    ret.sum     += colorRefract.sum     + colorReflect.sum;
  }

  return ret;
}


void Render::renderPartialWindow(float frame, windowType &window) {
  // this will be executed by multiple different threads,
  // things needs to be in local stack or globaly synchronize to be safe

  Sampler sampler(SAMPLING_MIN * scene->nLights, SAMPLING_MAX * scene->nLights,
                  scene->camera.shutterBlur, scene->camera.apeture, scene->nLights, frame);

  Camera  camera(width,height);

  Sphere      *objects = new Sphere[scene->nObjects];
  LightOmni   light;
  sampleTuple sample;
  Ray         rayForThisPixel;

  if (scene->camera.shutterBlur == 0.0f) {
    // if there is no blurness due to animation do not evaluate scene per each ray
    scene->evaluateObjects(objects, frame);
  }

  for (int y = window.yStart; y < window.yEnd; y++) {
    for (int x = window.xStart; x < window.xEnd; x++) {
      unsigned int colorsCount = 0;
      colors totalColor = {.average = Color(), .sum = Color() };
      colors lastColor;

      sampler.nextPixel();
      while (sampler.isNext()) {

        sampler.getNextSample(&sample);

        camera.getRay(x, y, sample, scene, rayForThisPixel);
        light = scene->lights[sample.light].evaluateFn(frame);
        lastColor = rayStart(rayForThisPixel, objects, &light, frame + sample.time);

        totalColor.average += ~lastColor.average;
        totalColor.sum     += ~lastColor.sum;
        colorsCount++;

        if (sampler.index == sampler.indexMinimum) {
          // detect black parts of the scene after few sample rays
          if (Color((totalColor.average + totalColor.sum)/ colorsCount).sum() == 0) {
            sampler.finish();
          }
        }

      }
      const float raysPerLight = ((float)colorsCount/scene->nLights);
      dynamicPixels[x + (y * width)] = ~Color( (totalColor.sum     / raysPerLight) +
                                               (totalColor.average / colorsCount));
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
        windowType partialWindow;
        this->getThreadWindow(thread, partialWindow);
        this->renderPartialWindow(scene->frame, partialWindow);
      });
    }
    for (auto& worker: workers) worker.join();
  }
}
