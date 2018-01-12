/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 11/01/2018
 */

#ifndef RAYTRACER_OBJECT_H
#define RAYTRACER_OBJECT_H

#include <functional>
#include "materials.h"
#include "../../render/ray.h"
#include "../../types/color.h"

class Object {

public:
  Vector3 center;
  std::function<materialStatic(Vector3 point)> material;

  Object(Vector3 center, std::function<materialStatic(Vector3 point)> materialInit);

  uv toUv(Vector3 point);

  virtual bool detectHit(Ray ray, Vector3 &hitPoint) = 0;

  virtual Vector3 operator ^ (Vector3 pointOnSurface) = 0;


};

// TODO: Material should take time, uv as input as well, not just the point

#endif //RAYTRACER_OBJECT_H
