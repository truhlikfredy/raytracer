/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "../types/vector3.h"

struct Ray {
  Vector3 source;
  Vector3 direction;
  Vector3 directionFraction;
  float   directionDot;
  float   directionDotInverse;

  Ray();

  Ray(Vector3 sourceInit, Vector3 directionInit);
};


#endif //RAYTRACER_RAY_H
