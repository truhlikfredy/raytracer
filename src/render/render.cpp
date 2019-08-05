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
#include "../scenes/sceneGenerator.h"


Render::Render(int widthInit, int heightInit): width(widthInit), height(heightInit) {
  dynamicPixels = new Color[widthInit * heightInit];
//  threadsMax    = std::thread::hardware_concurrency();
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


colors Render::rayStart(Ray ray, Scene *scene) {

  return rayFollow(ray, scene, 1, nullptr);
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


colors Render::rayFollow(Ray ray, Scene *scene, int iteration, Object *inside) {
  colors ret = {.average = Color(), .sum = Color() };

  if (iteration > MAX_BOUNCES) {
    return ret;
  }

  // https://stackoverflow.com/questions/9893316/how-do-i-combine-phong-lighting-with-fresnel-dielectric-reflection-transmission
  float shortestHitDistance = FLT_MAX;  // set it to maximum at first
  Object *shortestObject = nullptr;
  Vector3 shortestHitPoint;

  // Find closest collision
  for (Object *object: *scene->objects) {
    Vector3 hitPoint;
//    Object* objectUpcast = objects[i];
//    Sphere object = dynamic_cast<Sphere &>(objects[i]);
    float hitDistance;

    if (inside) {
      //hitDistance = object.detectHitMax(ray, hitPoint);
      if (inside == object) {
        // if we are testing the collision with itslef (inside the object) then find the furtherst point
        hitDistance = object->detectHitMax(ray, hitPoint);
      }
      else {
        // but for all other objects even including intersecting object do detect closest collision
        hitDistance = object->detectHit(ray, hitPoint);
      }
    }
    else {
      hitDistance = object->detectHit(ray, hitPoint);
    }

    if (hitDistance != -1.0f) {
      if (shortestHitDistance > hitDistance) {
        // It's the shortest hit yet, let's save it, if it will win then calculate it's color by shading it depending on the bounce angle
        shortestObject      = object;
        shortestHitDistance = hitDistance;
        shortestHitPoint    = hitPoint;
      }
    }
  }

  // Only shade the closes collision
  if (shortestObject) {
    // https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
    Vector3 hitNormal    = *shortestObject ^shortestHitPoint;
    Vector3 hitReflected = ray.direction - (hitNormal * 2 * (ray.direction % hitNormal));

    materialStatic hitMaterial = shortestObject->material;
//    materialStatic hitMaterial = shortestObject->materialFn(shortestHitPoint, scene->frame);

    colors colorRefract = {.average = Color(), .sum = Color() };
    colors colorReflect = {.average = Color(), .sum = Color() };

    if (hitMaterial.transparency != 0.0f) {
      // If transparency is enabled then handle refraction
      Vector3 hitRefracted;
      refract(ray.direction, hitNormal, hitMaterial.refractiveIndex, hitRefracted);

      colorRefract = rayFollow(Ray(shortestHitPoint, hitRefracted), scene, iteration + 1, (inside) ? nullptr : shortestObject);
      colorRefract.average *= hitMaterial.transparency;
      colorRefract.sum     *= hitMaterial.transparency;
    }

    if (hitMaterial.reflectivity != 0.0f) {
      // If the material is reflective then handle reflection
      colorReflect = rayFollow(Ray(shortestHitPoint, hitReflected), scene, iteration + 1, inside);
      colorReflect.average *= hitMaterial.reflectivity;
      colorReflect.sum     *= hitMaterial.reflectivity;
    }

    for (std::vector<Light*> lightSet : *scene->lights) {

      Vector3 hitLight = Vector3(lightSet[0]->center - shortestHitPoint);
      float diffuse    = fmaxf(0, hitLight % hitNormal); // how similar are they?
      float specular   = fmaxf(0, hitLight % hitReflected);

      // calculate length from the collision point to light source and then normalize the vector pointing to it
      float hitLightLen    = hitLight.lenght();
      hitLight = ~hitLight;

      // diffuse = similarity (dot product) of hitLight and hitNormal
      // https://youtu.be/KDHuWxy53uM
      // And use the diffuse / specular only when they are positive
      // shadeOfTheRay = specular + diffuse + ambientStatic
      // https://qph.ec.quoracdn.net/main-qimg-dbc0172ecc9127a3a6b36c4d7f634277
      // http://www.paulsprojects.net/tutorials/simplebump/simplebump.html

      ret.average = scene->ambientStatic * hitMaterial.ambient;
      ret.sum     = (( hitMaterial.diffuse * diffuse + powf(specular, hitMaterial.shininess)) * lightSet[0]->color) / fmax(0.8f, powf((hitLightLen + shortestHitDistance) / 300.0f, 2));

//    for (int j = 0; j < scene->nObjects; j++) {
//      // test all objects if they are casting shadow from this light
//      Object objectCausingShadow = objects[j];
//      if (j != smallestObjectIndex &&
//        objectCausingShadow.detectHit(Ray(shortestHitPoint, hitLight)) != -1 &&
//        objectCausingShadow.materialFn(hitLight,frame).castsShadows &&
//        hitLightLen > (objectCausingShadow.center - shortestHitPoint).lenght() ) {
//
//        // If the following are meet:
//        // 1) can't cast shadow on yourself through bounded rays, at least not yet with simple shapes
//        // 2) ray needs to hit the object which is causing shadows (if it's not hit then it couldn't cause shadow)
//        // 3) object's material needs to have property to cast shadows
//        // 4) object needs to be between the light source and the collision point and not behind the light source
//        // Then do the following:
//
//        ret.sum = Color();    // null the summing factor, leave only average factor ok which is the ambientStatic part
//        break;
//      }
//    }

      ret.average += colorRefract.average + colorReflect.average;
      ret.sum     += colorRefract.sum     + colorReflect.sum;
    }
  }

  return ret;
}


void Render::renderPartialWindow(windowType &window) {
  // this will be executed by multiple different threads,
  // things needs to be in local stack or globally synchronize to be safe

  Sampler sampler((*scenes)[0], SAMPLING_MIN, SAMPLING_MAX);

  Camera  camera(width,height);

  sampleTuple sample;
  Ray         rayForThisPixel;

  for (int y = window.yStart; y < window.yEnd; y++) {
    for (int x = window.xStart; x < window.xEnd; x++) {
      unsigned int colorsCount = 0;
      colors totalColor = {.average = Color(), .sum = Color() };
      colors lastColor;

      sampler.nextPixel();
      unsigned int count = 0;
      while (sampler.isNext()) {
        auto scene = (*scenes)[count];

        sampler.getNextSample(&sample);

        camera.getRay(x, y, sample, scene, rayForThisPixel);
        lastColor = rayStart(rayForThisPixel, scene);

        totalColor.average += ~lastColor.average;
        totalColor.sum     += ~lastColor.sum;
        colorsCount++;

        if (sampler.index == sampler.indexMinimum) {
          // detect black parts of the scene after few sample rays
          if (Color((totalColor.average + totalColor.sum)/ colorsCount).sum() == 0) {
            sampler.finish();
          }
        }

        count++;
      }
      dynamicPixels[x + (y * width)] = ~Color(totalColor.sum / colorsCount);
    }
  }

}


void Render::clearDynamicPixels() {
  for (int i = 0; i < height * width; i++) {
    dynamicPixels[i] = Color();
  }
}


void Render::renderFullWindow(SceneGenerator *sceneGenerator) {
  std::vector<std::thread> workers;

  clearDynamicPixels();

  /* Create scenes in all the time samples */
  Sampler sampler(sceneGenerator, SAMPLING_MIN, SAMPLING_MAX);
  int timeSamples = (sceneGenerator->camera.shutterBlur == 0.0f) ? 1 : sampler.indexMaximum;
  scenes = new std::vector<Scene*>(timeSamples);
  for (int i = 0; i < timeSamples; i++) {
    sampleTuple sample;
    sampler.getNextSample(&sample);

    (*scenes)[i] = sceneGenerator->generateScene(sceneGenerator-> frame + sample.time);
  }

  /* Give work to all threads to render part of the screen */
  for (int segment = 0; segment < SEGMENTS; segment++) {
    for (int thread = 0; thread < threadsMax; thread++) {
      workers.emplace_back([this, thread] {
        windowType partialWindow;
        this->getThreadWindow(thread, partialWindow);
        this->renderPartialWindow(partialWindow);
      });
    }
    for (auto& worker: workers) worker.join();
  }

  /* Delete scenes in all the motion blur time samples */
  for (int i = 0; i < timeSamples; i++) {
    delete (*scenes)[i];
  }
  delete scenes;
}
