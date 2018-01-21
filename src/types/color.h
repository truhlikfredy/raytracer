/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include "triple.h"

struct lab {
  int x;
  int y;
  int z;
};

class Color : public Triple {

public:
  Color();
  Color(float r, float g, float b);
  Color(const Triple& base);

  Color operator~();
  lab toLab();
  float difference(Color secondColor);
};



#endif //RAYTRACER_COLOR_H
