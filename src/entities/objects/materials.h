/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 11/01/2018
 */

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include <functional>
#include "../../types/vector3.h"
#include "../../types/color.h"

struct materialStatic {
  Color ambient;
  Color diffuse;
  Color specular;
  Color emission;
  float shininess;
};

struct uv {
  float u;
  float v;
};

class Materials {

public:
  static materialStatic red;
  static materialStatic mirror;
};

#endif //RAYTRACER_MATERIAL_H
