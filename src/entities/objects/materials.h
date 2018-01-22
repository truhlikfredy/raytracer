/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 11/01/2018
 */

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include <functional>
#include "../../types/vector3.h"
#include "../../types/color.h"

struct MaterialStatic {
  bool  castsShadows;
  Color ambient;
  Color diffuse;
  Color specular;
  Color emission;
  float shininess;
  float reflectivity;
  float transparency;
  float refractiveIndex;
};

struct uv {
  float u;
  float v;
};

class Materials {

public:
  // colors
  static MaterialStatic red;
  static MaterialStatic yellow;
  static MaterialStatic white;
  static MaterialStatic green;
  static MaterialStatic indigo;
  static MaterialStatic blue;
  static MaterialStatic violet;
  static MaterialStatic black;
  static MaterialStatic mediumGray;
  static MaterialStatic lightGray;


  // materials
  static MaterialStatic mirror;
  static MaterialStatic brass;
  static MaterialStatic pollishedCopper;
  static MaterialStatic glass;
};

// Allow dynamic materials made on the fly

#endif //RAYTRACER_MATERIAL_H
