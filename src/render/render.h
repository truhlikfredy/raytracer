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


struct DynamicPixel {
  Color    color;
  unsigned count;
};


class Render {
private:
  unsigned int width;
  unsigned int height;

  windowType getThreadWindow(int thread);

  Color calculateShadeOfTheRay(Ray ray, Light light);

  void renderPartial(float frame, windowType window);

  void clearDynamicPixels();

public:
  unsigned int threadsMax = 1;
  DynamicPixel* dynamicPixels;

  Render(int width, int height);

  void renderFull(float frame);
};
#endif //RAYTRACER_RENDER_H
