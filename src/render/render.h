/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_RENDER_H
#define RAYTRACER_RENDER_H

#define SEGMENTS 1  // how many partitions the screen should be split
#define SAMPLING_MIN 4
#define SAMPLING_MAX 9
#define MAX_BOUNCES 5

#include "../entities/lights/lightOmni.h"
#include "ray.h"


//#include <tuple>
//typedef std::tuple<int, int, int, int> windowType;

struct windowType {
  unsigned int xStart;
  unsigned int xEnd;
  unsigned int yStart;
  unsigned int yEnd;
};

#include "../types/color.h"
#include "sampler.h"
#include "../scenes/scene.h"


class Render {
private:
  unsigned int width;
  unsigned int height;
  Scene        *scene;

  windowType getThreadWindow(int thread);

  void refract(Vector3 &incidentVec, Vector3 &normal, float refractionIndex, Vector3 &refractionRay);

  Color rayStart(Ray ray, Sphere* objects, LightOmni* light, float frame);

  Color rayFollow(Ray ray, Sphere* objects, LightOmni* light, float frame, int iteration, bool inside);

  void renderPartialWindow(float frame, windowType window);

  void clearDynamicPixels();

public:
  unsigned int threadsMax = 1;
  Color* dynamicPixels;

  Render(int width, int height);

  void renderFullWindow(Scene *sceneInit);
};
#endif //RAYTRACER_RENDER_H
