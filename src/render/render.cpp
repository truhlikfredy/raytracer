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
  dynamicPixels = new DynamicPixel[widthInit * heightInit];
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



Color Render::rayStart(Ray ray, Sphere* objects, LightOmni* lights, float frame) {
  scene->evaluateLights(lights, frame);
  scene->evaluateObjects(objects, frame);

  return rayFollow(ray, objects, lights, frame, 1);
}

Color Render::rayFollow(Ray ray, Sphere* objects, LightOmni* lights, float frame, int iteration) {
  Color   color;
  Vector3 hitPoint;

  if (iteration > MAX_BOUNCES) {
    return Color(0.0f);
  }

//  Entity* item = &staticScene.lights.front();

  LightOmni light = lights[0];
  // https://stackoverflow.com/questions/9893316/how-do-i-combine-phong-lighting-with-fresnel-dielectric-reflection-transmission
  float smallestHitDistance = FLT_MAX;  // set it to maximum at first
  //int smallestObject = 0;

  for (int i = 0; i< scene->nObjects; i++){
    Sphere object = objects[i];
    //Object* object = (Object*)(&item);
    //Entity* it = &item;

    //Sphere *object = static_cast<Sphere *>(it);
    float hitDistance = object.detectHit(ray, hitPoint);

    if (hitDistance != -1.0f) {
      // The ray hit the sphere
      if (smallestHitDistance > hitDistance) {
        // It's the shortest hit yet, let's calculate it's color by shading it depending on the bounce angle
        smallestHitDistance = hitDistance;
        // https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
        Vector3 hitNormal    = object ^ hitPoint;
        Vector3 hitReflected = ray.direction - (hitNormal * 2 *(ray.direction % hitNormal));
        Vector3 hitLight     = ~Vector3(light.center - hitPoint);
        Vector3 hitLight2     = ~Vector3(hitPoint - light.center);

        MaterialStatic hitMaterial = object.materialFn(hitPoint, frame);

        float   diffuse      = fmaxf(0, hitLight % hitNormal); // how similar are they?
        float   specular     = fmaxf(0, hitLight % hitReflected);


        // diffuse = similarity (dot product) of hitLight and hitNormal
        // https://youtu.be/KDHuWxy53uM
        // And use the diffuse / specular only when they are positive
        // shadeOfTheRay = specular + diffuse + ambient
        // https://qph.ec.quoracdn.net/main-qimg-dbc0172ecc9127a3a6b36c4d7f634277
        color = Color(light.color * powf(specular, hitMaterial.shininess) + hitMaterial.diffuse * diffuse + hitMaterial.ambient);

        for (int j = 0; j< scene->nObjects; j++) {
          // test all objects if they are casting shadow from this light
          if (j != i) {  // can't cast shadow on yourself through bounded rays, at least not yet with simple shapes
            Sphere shadow = objects[j];
            if (shadow.detectHit(Ray(hitPoint, hitLight)) != -1) {
              color = Color(hitMaterial.ambient);
              break;
            }
          }
        }

      }
    }
  }

  return color;

}

void Render::renderPartialWindow(float frame, windowType window) {
  Sampler sampler(ANTI_ALIASING, ANTI_ALIASING * ANTI_ALIASING, scene->camera.shutterSpeed, 0, frame, scene->camera.apeture);

  Sphere    *objects = new Sphere[scene->nObjects];
  LightOmni *lights  = new LightOmni[scene->nLights];

  // printf("%f \r\n",frame);
  for (int y = window.yStart; y < window.yEnd; y++) {
    for (int x = window.xStart; x < window.xEnd; x++) {
      sampler.nextPixel();
      while (sampler.isNext()) {
        sampleTuple sample = sampler.getNextSample();

        Vector3 start = scene->camera.possition + Vector3(sample.lensX, sample.lensY, 0);
        Vector3 lookAt = scene->camera.lookAt;
        //float focalDistance = Vector3(lookAt - start).lenght();
        //float halfWidth = focalDistance * tanf((90.0f/180)*3.14/2);
        //Vector3 up(0.0f, 1.0f, 0.0f);
        Vector3 down(0.0f, -1.0f, 0.0f);
        Vector3 right = (~Vector3(lookAt & down))*320;
        Vector3 up2 = (~Vector3(lookAt & right))*200;
        //Vector3 U = Vector3(~lookAt & up);
        //Vector3 V = ~Vector3(U & ~lookAt);
        //U = ~U;
        //float aspectRatio = (float)height/width;
        //float viewPlaneHalfHeight = aspectRatio * halfWidth;
        //Vector3 viewBottomLeft = lookAt - V*viewPlaneHalfHeight - U*halfWidth;
        //Vector3 xInc = (U * 2 * halfWidth) / width;
        //Vector3 yInc = (U * 2 * viewPlaneHalfHeight) / height;
        //Vector3 dest2 = viewBottomLeft + xInc * x + yInc * y;

        float recenterX = ( x + sample.spaceX - width/2.0f) / ( 2.0 * width);
        float recenterY = ( y + sample.spaceY - height/2.0f) / ( 2.0 * height);

        Vector3 dest3 = ~Vector3((right * recenterX) + (up2 * recenterY) + lookAt - start);


        //Vector3 dest  = ~Vector3(x + sample.spaceX - width / 2.0f, y + sample.spaceY - height / 2.0f, 90);

        Ray rayForThisPixel(start,dest3);
//        Ray rayForThisPixel(start,~Vector3(dest3-start));
        Color shade = rayStart(rayForThisPixel, objects, lights, frame + sample.time);
        shade = ~shade;

        dynamicPixels[x + (y * width)].color = dynamicPixels[x + (y * width)].color + shade;
        dynamicPixels[x + (y * width)].count++;
      }
    }
  }

  delete[] objects;
}

void Render::clearDynamicPixels() {
  for (int i = 0; i < height * width; i++) {
    dynamicPixels[i].color = Color();
    dynamicPixels[i].count = 0;
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