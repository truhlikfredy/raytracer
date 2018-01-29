/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_RENDER_H
#define RAYTRACER_RENDER_H

#define SEGMENTS 1  // how many partitions the screen should be split
#define SAMPLING_MIN 2  // Samples per light, the final sampling will change depending on the lights present in the scene
#define SAMPLING_MAX 4
#define MAX_BOUNCES 4

#include "../types/color.h"
#include "../entities/lights/lightOmni.h"
#include "../scenes/scene.h"
#include "sampler.h"
#include "ray.h"


struct windowType {
  unsigned int xStart;
  unsigned int xEnd;
  unsigned int yStart;
  unsigned int yEnd;
};


struct colors {
  Color average;
  Color sum;
};


class Render {
private:
  unsigned int width;
  unsigned int height;
  Scene        *scene;

  void getThreadWindow(int thread, windowType &ret);

  void refract(Vector3 &incidentVec, Vector3 &normal, float refractionIndex, Vector3 &refractionRay);

  colors rayStart(Ray ray, Sphere* objects, LightOmni* light, float frame);

  colors rayFollow(Ray ray, Sphere* objects, LightOmni* light, float frame, int iteration, int inside);

  void renderPartialWindow(float frame, windowType &window);

  void clearDynamicPixels();

public:
  unsigned int threadsMax = 1;
  Color* dynamicPixels;

  Render(int width, int height);

  void renderFullWindow(Scene *sceneInit);
};


#endif //RAYTRACER_RENDER_H
