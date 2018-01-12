/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include <cmath>
#include <thread>
#include <vector>
#include "render.h"
#include "../entities/objects/sphere.h"
#include "../entities/objects/materials.h"


Render::Render(int widthInit, int heightInit) {
  width = widthInit;
  height = heightInit;
  dynamicPixels = new DynamicPixel[widthInit * heightInit];
  threadsMax = std::thread::hardware_concurrency();
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

Color Render::calculateShadeOfTheRay(Ray ray, Light light) {
  Sphere  sphere(Vector3(0, 0, 100), 25, [](Vector3 point) {
//    if ((int)point.x/5 % 2 ^ (int)point.y/5 % 2 ^ (int)point.z/5 % 2) {
//      return Materials::red;
//    }
//    else {
//      return Materials::mirror;
//    }
    return materialStatic{
      .ambient = Color(0.0f, 0.0f, 0.2f),
      .diffuse = Color((sinf(point.x/2+point.y+point.z)+0.2)*0.5),
      .specular = Color(0.2f),
      .emission = Color(0.0),
      .shininess = point.z
    };
  });
  Sphere  sphere2(Vector3(15, 10, 60), 7, [](Vector3 point) { return Materials::mirror; });
  Color   color;
  Vector3 hitPoint;

  // https://stackoverflow.com/questions/9893316/how-do-i-combine-phong-lighting-with-fresnel-dielectric-reflection-transmission

  if (sphere.detectHit(ray, hitPoint)) {
    // The ray hit the sphere, let's find the bounce angle and shade it
    // https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
    Vector3 hitNormal    = sphere ^ hitPoint;
    Vector3 hitReflected = ray.direction - (hitNormal * 2 *(ray.direction % hitNormal));
    Vector3 hitLight     = ~Vector3(light - hitPoint);
    float   diffuse      = fmaxf(0, hitLight % hitNormal); // how similar are they?
    float   specular     = fmaxf(0, hitLight % hitReflected);

    materialStatic hitMaterial = sphere.material(hitPoint);

    // diffuse = similarity (dot product) of hitLight and hitNormal
    // https://youtu.be/KDHuWxy53uM
    // And use the diffuse / specular only when they are positive
    // shadeOfTheRay = specular + diffuse + ambient
    // https://qph.ec.quoracdn.net/main-qimg-dbc0172ecc9127a3a6b36c4d7f634277
    color = Color(light.color * powf(specular, 10) + hitMaterial.diffuse * diffuse + hitMaterial.ambient);
  }
  if (sphere2.detectHit(ray, hitPoint)) {
    // The ray hit the sphere, let's find the bounce angle and shade it
    // https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
    Vector3 hitNormal    = sphere2 ^ hitPoint;
    Vector3 hitReflected = ray.direction - (hitNormal * 2 *(ray.direction % hitNormal));
    Vector3 hitLight     = ~Vector3(light - hitPoint);
    float   diffuse      = fmaxf(0, hitLight % hitNormal); // how similar are they?
    float   specular     = fmaxf(0, hitLight % hitReflected);

    materialStatic hitMaterial = sphere2.material(hitPoint);

    // diffuse = similarity (dot product) of hitLight and hitNormal
    // https://youtu.be/KDHuWxy53uM
    // And use the diffuse / specular only when they are positive
    // shadeOfTheRay = specular + diffuse + ambient
    // https://qph.ec.quoracdn.net/main-qimg-dbc0172ecc9127a3a6b36c4d7f634277
    color = Color(light.color * powf(specular, 10) + hitMaterial.diffuse * diffuse + hitMaterial.ambient);
  }
  return color;
}

void Render::renderPartial(float frame, windowType window) {
  const int zoom=2;
  const float lightRotate = (M_PI * frame) / 11;
  Sampler sampler(ANTI_ALIASING, 1, 0.1f, 0, frame);

  Light light(Vector3(1.0*width  * cosf(lightRotate),
                      0.6*height * (sinf(lightRotate)-0.5), 20), Color(0.2f, 0.7f, 0.3f));


  for (int y = window.yStart; y < window.yEnd; y++) {
    for (int x = window.xStart; x < window.xEnd; x++) {
      sampler.nextPixel();
      while (sampler.isNext()) {
        sampleTuple sample = sampler.getNextSample();

        Ray rayForThisPixel(Vector3(0, 0, 0),
                            ~Vector3(x + sample.spaceX - width / 2.0f, y + sample.spaceY - height / 2.0f, width * 1.0f));
        Color shade = calculateShadeOfTheRay(rayForThisPixel, light);
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

void Render::renderFull(float frame) {
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