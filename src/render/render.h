/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_RENDER_H
#define RAYTRACER_RENDER_H

#define SEGMENTS 1  // how many partitions the screen should be split
#define ANTI_ALIASING 2

#include "../entities/lights/omni.h"
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


struct DynamicPixel {
  Color    color;
  unsigned count;
};


class Render {
private:
  unsigned int width;
  unsigned int height;
  Scene        scene;

  windowType getThreadWindow(int thread);

  Color rayFollow(Ray ray, LightOmni light);

  Color rayStart(Ray ray, LightOmni light, float frame);

  void renderPartial(float frame, windowType window);

  void clearDynamicPixels();

public:
  unsigned int threadsMax = 1;
  DynamicPixel* dynamicPixels;

  Render(int width, int height);

  void renderFull(Scene sceneInit, float frame);
};
#endif //RAYTRACER_RENDER_H
