//
// Created by fredy on 07/01/18.
//

#ifndef RAYCASTER_RENDER_H
#define RAYCASTER_RENDER_H

#define SEGMENTS 1  // how many partitions the screen should be split
#define ANTI_ALIASING 2

#include "color.h"
#include "ray.h"
#include "light.h"


//#include <tuple>
//typedef std::tuple<int, int, int, int> windowType;

struct windowType {
  unsigned int xStart;
  unsigned int xEnd;
  unsigned int yStart;
  unsigned int yEnd;
};

#include "color.h"


struct DynamicPixel {
  Color    color;
  unsigned count;
};


class Render {
private:
  unsigned int width;
  unsigned int height;

public:
  unsigned int threadsMax = 1;
  DynamicPixel* dynamicPixels;

  Render(int width, int height);
  void clearDynamicPixels();
  windowType getThreadWindow(int thread);
  Color calculateShadeOfTheRay(Ray ray, Light light);
  void renderPartial(int frame, windowType window);
  void renderFull();
};
#endif //RAYCASTER_RENDER_H
