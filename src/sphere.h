/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "vector3.h"
#include "ray.h"

class Sphere {
  Vector3 center;
  float   radius;

public:
  Sphere(Vector3 centerInt, float radiusInit);

  // Get normalized normal vector from sphere's surface point
  Vector3 operator ^ (Vector3 pointOnSurface);

  bool detectHit(Ray ray, Vector3 &hitPoint);
};


#endif //RAYTRACER_SPHERE_H
