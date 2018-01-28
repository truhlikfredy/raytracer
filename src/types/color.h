/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include "triple.h"

class Color : public Triple {

public:
  Color();
  Color(float r, float g, float b);
  Color(const Triple& base);

  Color operator~();
  Color toLab();
  float labDifference(Color secondColor);
};



#endif //RAYTRACER_COLOR_H
