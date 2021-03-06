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
#ifdef NDEBUG
  threadsMax    = std::thread::hardware_concurrency();
#endif
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


Color Render::rayStart(Ray *ray, Scene *scene) {
  return rayFollow(ray, scene, 1);
}


bool Render::refract(
  Object      *closestHitObject,
  Ray         *incidentRay,
  Vector3     *normal,
  const float chromaticTweak,
  Ray         *refractionRayOut) {

  // https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
  // https://stackoverflow.com/questions/42218704/how-to-properly-handle-refraction-in-raytracing
  // https://stackoverflow.com/questions/26087106/refraction-in-raytracing
  // https://en.wikipedia.org/wiki/Fresnel_equations
  // http://hyperphysics.phy-astr.gsu.edu/hbase/Tables/indrf.html
  // https://en.wikipedia.org/wiki/Total_internal_reflection

  Vector3 incidentVec   = incidentRay->getDirection();
  float   dotNormalized = fmax(-1, fmin(1, (incidentVec % *normal)));
  float   indexCurrent;
  float   indexNew;
  Vector3 normalVector;

  if (dotNormalized < 0) {
    // We are outside the object's volume going inside
    indexCurrent                  = incidentRay->inside->material.refractiveIndex;
    indexNew                      = incidentRay->hitMaterial->refractiveIndex * chromaticTweak;

    normalVector                  = *normal;
    dotNormalized                 = -dotNormalized;

    refractionRayOut->parentRay   = incidentRay;
    refractionRayOut->inside      = closestHitObject;
    refractionRayOut->hitMaterial = incidentRay->hitMaterial;
  } else {
    // We are leaving this object, set our new parent to ours parent's parent, and restore the inside object
    indexCurrent                  = incidentRay->hitMaterial->refractiveIndex; // We hit the inside part of the object
    indexNew                      = incidentRay->parentRay->inside->material.refractiveIndex * chromaticTweak;

    normalVector                  = normal->invert();

    refractionRayOut->parentRay   = incidentRay->parentRay->parentRay;
    refractionRayOut->inside      = incidentRay->parentRay->inside;
    refractionRayOut->hitMaterial = incidentRay->parentRay->hitMaterial;
  }

  float indexRatio  = indexCurrent / indexNew;
  float coefficient2 = 1 - indexRatio * indexRatio * (1 - dotNormalized * dotNormalized);

  if (coefficient2 < 0) {
    return false;
  }

  refractionRayOut->setDirection(
    incidentVec * indexRatio +
    normalVector * (indexRatio * dotNormalized - sqrtf(coefficient2)));

  return true;
}


Color Render::rayFollow(Ray *ray, Scene *scene, int iteration) {
  // https://stackoverflow.com/questions/9893316/how-do-i-combine-phong-lighting-with-fresnel-dielectric-reflection-transmission
  float   closestHitDistance = FLT_MAX;  // set it to maximum at first
  Object  *closestHitObject  = nullptr;
  Vector3 closestHitPoint;
  Color   ret;

  if (iteration > MAX_BOUNCES) {
    return ret;
  }

  // Find closest collision
  for (Object *object: *scene->objects) {
    Vector3 hitPoint;
    float hitDistance;

    if (ray->inside == object) {
      // If we are not in the ether object, then we must be in other objects and
      // if we are testing the collision with itself (inside the object) then find the furthest point
      hitDistance = object->detectHitPoint(ray, hitPoint, false);
    } else {
      // But for all other objects, being in ether or even including intersecting object do detect closest collision
      hitDistance = object->detectHitPoint(ray, hitPoint, true);
    }

    if (hitDistance > 0.0f) {
      if (closestHitDistance > hitDistance) {
        // It's the shortest hit yet, let's save it, if it will win then calculate it's color by shading it depending on the bounce angle
        closestHitObject   = object;
        closestHitDistance = hitDistance;
        closestHitPoint    = hitPoint;
      }
    }
  }

  /* Only shade the closes collision */
  if (closestHitObject) {
    /* https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector */
    Vector3 hitNormal    = *closestHitObject ^closestHitPoint;
    Vector3 hitReflected = ray->getDirection() - (hitNormal * 2 * (ray->getDirection() % hitNormal));

    materialStatic hitMaterial = closestHitObject->evalMaterial(closestHitPoint, scene->frame);
    ray->hitMaterial = &hitMaterial;  /* Populate the ray with the evaluated material as well */

    Color colorRefract;
    Color colorReflect;

    if (hitMaterial.transparency != 0.0f) {
      /* If material is transparent then handle refraction */

#ifdef CHROMATIC_ABERRATION_REFRACTION
      Ray refractRayR(closestHitPoint);
      Ray refractRayG(closestHitPoint);
      Ray refractRayB(closestHitPoint);
      if (refract(closestHitObject, ray, &hitNormal, 1.0f, &refractRayG)) {
        refract(closestHitObject, ray, &hitNormal, (1.0f - CHROMATIC_ABERRATION_STRENGTH), &refractRayR);
        refract(closestHitObject, ray, &hitNormal, (1.0f + CHROMATIC_ABERRATION_STRENGTH), &refractRayB);

        colorRefract = Color(
          rayFollow(&refractRayR, scene, iteration + 1).x,
          rayFollow(&refractRayG, scene, iteration + 1).y,
          rayFollow(&refractRayB, scene, iteration + 1).z);
      }
#else
      /* At this moment we do not know the direction of the refraction, the pre-calculated cached values will be
       * populated with wrong values, after the refract is done, call the updatePreCalculatedValues(); method */
      Ray refractRay(closestHitPoint);

      if (refract(closestHitObject, ray, &hitNormal, 1.0f, &refractRay)) {
        colorRefract = rayFollow(&refractRay, scene, iteration + 1);
      }
#endif
    }

    if (hitMaterial.reflectivity != 0.0f && ray->inside != closestHitObject  ) {
      // If the material is reflective then handle reflection, but do not calculate reflection from the inside objects
      Ray reflectRay(closestHitPoint, hitReflected, ray, ray->inside);
      colorReflect = rayFollow(&reflectRay, scene, iteration + 1);
    }

    for (std::vector<Light*> lightSet : *scene->lights) {
      // Calculate color for each light source
      static int lightSeed   = lightSeed + scene->frame;
      Light      *hitLight   = lightSet[lightSeed % scene->lightVariations];
      Vector3    hitLightRel = Vector3(hitLight->center - closestHitPoint);

      /* Calculate length from the collision point to light source and then normalize the vector pointing to it */
      float hitLightLen = hitLightRel.lenght();
            hitLightRel = ~hitLightRel; /* After we got the distance, then normalize it for angle calculation */

      float diffuse     = fmaxf(0, hitLightRel % hitNormal);    // how similar are they?
      float specular    = fmaxf(0, hitLightRel % hitReflected);

      // diffuse = similarity (dot product) of hitLightRel and hitNormal
      // https://youtu.be/KDHuWxy53uM
      // And use the diffuse / specular only when they are positive
      // shadeOfTheRay = specular + diffuse + ambientStatic
      // https://qph.ec.quoracdn.net/main-qimg-dbc0172ecc9127a3a6b36c4d7f634277
      // http://www.paulsprojects.net/tutorials/simplebump/simplebump.html

      Color colorAmbient = scene->ambientStatic * hitMaterial.ambient;
      Color colorLight;

      bool inShadow = false;
      for (Object *oCS: *scene->objects) {
        Ray shadowRay(closestHitPoint, hitLightRel);
        // test all objects if they are casting shadow from this light
        if (oCS != closestHitObject &&
            oCS->detectHit(&shadowRay) != -1 &&
            hitLightLen > (oCS->center - closestHitPoint).lenght() &&
            oCS->evalMaterial(hitLightRel, scene->frame).castsShadows) {
          // If the following are meet:
          // 1) can't cast shadow on yourself through bounded rays, at least not yet with simple shapes (so test only all other objects)
          // 2) ray needs to hit the object which is causing shadows (if it's not hit then it couldn't cause shadow)
          // 3) object needs to be between the light source and the collision point and not behind the light source
          // 4) object's material needs to have property to cast shadows (either a function or static material)
          // Then do the following:

          inShadow = true;
          break;
        }
      }

      if (!inShadow) {
        /* Do not calculate color unless they are going to be used (i.e. not in the shadow) */

        auto lightStrength = fmax(
          hitLight->burnInv,
          powf((hitLightLen + closestHitDistance) * hitLight->distanceInv, 2));

        colorLight = ((hitMaterial.diffuse * diffuse + powf(specular, hitMaterial.shininess)) *
          lightSet[0]->color / lightStrength);
      }

      ret += colorAmbient + colorLight;
    }

    /* Combine the current result with the reflective and refractive results */
    ret += (~colorReflect * hitMaterial.reflectivity) + (~colorRefract * hitMaterial.transparency);
  }

  return ret;
}


void Render::renderPartialWindow(windowType &window) {
  /* This will be executed by multiple different threads,
   * things needs to be in local stack or globally synchronize to be safe */

  Sampler sampler((*scenes)[0], SAMPLING_MIN, SAMPLING_MAX);

  Camera  camera(width,height);

  sampleTuple sample;
  Ray         rayForThisPixel;

  for (int y = window.yStart; y < window.yEnd; y++) {
    for (int x = window.xStart; x < window.xEnd; x++) {
      unsigned int sampleCount = 0;
      Color currentColor;
      Color totalColor;

      sampler.nextPixel();
      while (sampler.isNext()) {
        auto scene = (*scenes)[sampleCount];

        sampler.getNextSample(&sample);

        camera.getRay(x, y, sample, scene, rayForThisPixel);
        rayForThisPixel.parentRay = scene->etherRay;
        rayForThisPixel.inside = scene->etherObject;
        rayForThisPixel.hitMaterial = &scene->etherObject->material;
        currentColor = ~rayStart(&rayForThisPixel, scene);
        totalColor += currentColor;

        if (sampler.index == sampler.indexMinimum) {
          /* Detect black parts of the scene after few sample rays */
          /* TODO: When background is used different algorithm has to be used */
          if (totalColor.isZero()) {
            sampler.finish();
          }
        } else if (sampler.index > sampler.indexMinimum) {
          Color diff = Color(totalColor / sampleCount) - currentColor;
          if ( fabsf(diff.sum()) < SAMPLING_DELTA ) {
            sampler.finish();
            /* TODO: save stats so I know which settings are worth doing */
          }
        }

        sampleCount++;
      }
      dynamicPixels[x + (y * width)] = Color(totalColor / sampleCount);
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
  scenes = new std::vector<Scene*>(sampler.indexMaximum);
  for (int i = 0; i < sampler.indexMaximum; i++) {
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
  for (int i = 0; i < sampler.indexMaximum; i++) {
    delete (*scenes)[i];
  }
  delete scenes;
}
