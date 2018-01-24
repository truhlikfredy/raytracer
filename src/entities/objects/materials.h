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

struct mandelbrotSet {
  float lookAtX;
  float lookAtY;
  float width;
  float height;
  float gamma;
};

class Materials {

public:
  // colors
  static materialStatic red;
  static materialStatic yellow;
  static materialStatic white;
  static materialStatic green;
  static materialStatic indigo;
  static materialStatic blue;
  static materialStatic violet;
  static materialStatic black;
  static materialStatic mediumGray;
  static materialStatic lightGray;


  // materials
  static materialStatic mirror;
  static materialStatic brass;
  static materialStatic pollishedCopper;
  static materialStatic glass;

  // textures
  static Color mandelbrot(mandelbrotSet &set, uv &pixel);
};

// Allow dynamic materials made on the fly

#endif //RAYTRACER_MATERIAL_H
