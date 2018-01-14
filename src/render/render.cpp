/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include <cmath>
#include <thread>
#include <vector>
#include "render.h"
#include "../entities/objects/sphere.h"


Render::Render(int widthInit, int heightInit) {
  scene = nullptr;
  width = widthInit;
  height = heightInit;
  dynamicPixels = new DynamicPixel[widthInit * heightInit];
  //threadsMax = std::thread::hardware_concurrency();
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



Color Render::rayStart(Ray ray, float frame) {
//  Scene staticScene = Scene();
//  scene.evaluate(&staticScene, frame);
  //LightOmni *lithts;
  //scene->evaluateLights()

  Sphere *objects = new Sphere[scene->nObjects];
  scene->evaluateObjects(objects, frame);

  //Sphere  sphere2(Vector3(15, 10, 60), 7, [](Vector3 point, float frame) { return Materials::red; });
  Color   color;
  Vector3 hitPoint;

//  Entity* item = &staticScene.lights.front();

  LightOmni light = LightOmni(Vector3(50,50,50),Color(0.7f));


  // https://stackoverflow.com/questions/9893316/how-do-i-combine-phong-lighting-with-fresnel-dielectric-reflection-transmission

  for (int i = 0; i< scene->nObjects; i++){
    Sphere object = objects[i];
    //Object* object = (Object*)(&item);
    //Entity* it = &item;

    //Sphere *object = static_cast<Sphere *>(it);

    if (object.detectHit(ray, hitPoint)) {
      // The ray hit the sphere, let's find the bounce angle and shade it
      // https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
      Vector3 hitNormal    = object ^ hitPoint;
      Vector3 hitReflected = ray.direction - (hitNormal * 2 *(ray.direction % hitNormal));
      Vector3 hitLight     = ~Vector3(light - hitPoint);
      float   diffuse      = fmaxf(0, hitLight % hitNormal); // how similar are they?
      float   specular     = fmaxf(0, hitLight % hitReflected);

      MaterialStatic hitMaterial = object.materialFn(hitPoint, frame);

      // diffuse = similarity (dot product) of hitLight and hitNormal
      // https://youtu.be/KDHuWxy53uM
      // And use the diffuse / specular only when they are positive
      // shadeOfTheRay = specular + diffuse + ambient
      // https://qph.ec.quoracdn.net/main-qimg-dbc0172ecc9127a3a6b36c4d7f634277
      color = Color(light.color * powf(specular, 10) + hitMaterial.diffuse * diffuse + hitMaterial.ambient);
    }
  }

  return color;
}

void Render::renderPartial(float frame, windowType window) {
  const int zoom=2;
  Sampler sampler(ANTI_ALIASING, 1, 0.1f, 0, frame);

  printf("%f \r\n",frame);
  for (int y = window.yStart; y < window.yEnd; y++) {
    for (int x = window.xStart; x < window.xEnd; x++) {
      sampler.nextPixel();
      while (sampler.isNext()) {
        sampleTuple sample = sampler.getNextSample();

        Ray rayForThisPixel(Vector3(0, 0, 0),
                            ~Vector3(x + sample.spaceX - width / 2.0f, y + sample.spaceY - height / 2.0f, width * 1.0f));
        Color shade = rayStart(rayForThisPixel, frame);
        shade = ~shade;

        dynamicPixels[x + (y * width)].color = dynamicPixels[x + (y * width)].color + shade;
        dynamicPixels[x + (y * width)].count++;
      }
    }
  }
}

void Render::clearDynamicPixels() {
  for (int i = 0; i < height * width; i++) {
    dynamicPixels[i].color = Color();
    dynamicPixels[i].count = 0;
  }
}

void Render::renderFull(Scene *sceneInit, float frame) {
  scene = sceneInit;
  std::vector<std::thread> workers;

  clearDynamicPixels();

  for (int segment = 0; segment < SEGMENTS; segment++) {
    for (int thread = 0; thread < threadsMax; thread++) {
      workers.emplace_back([this, frame, thread] {
        this->renderPartial(frame, this->getThreadWindow(thread));
      });
    }
    for (auto& worker: workers) worker.join();
  }
}