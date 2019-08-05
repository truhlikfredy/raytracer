/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 11/01/2018
 */

#ifndef RAYTRACER_OBJECT_H
#define RAYTRACER_OBJECT_H

#include <functional>
#include "../../types/color.h"
#include "../../render/ray.h"
#include "../entity.h"
#include "materials.h"

class Object: public Entity {

public:
  std::function<materialStatic(Vector3 point, float frame)> materialFn;
  materialStatic material;

  Object(Vector3 centerInit, std::function<materialStatic(Vector3 point, float frame)> materialFnInit);

  Object(Vector3 centerInit, materialStatic materialInit);

  Object(Vector3 centerInit);

  Object();

  std::function<Object(float frame)> evaluateObjFn;

  //virtual uv toUv(Vector3 point) = 0;

  virtual float detectHit(Ray ray);

  virtual float detectHit(Ray ray, Vector3 &hitPoint);

  virtual float detectHitMax(Ray ray, Vector3 &hitPoint);

  Vector3 operator ^ (Vector3 pointOnSurface);


};

// TODO: Material should take time, uv as input as well, not just the point

#endif //RAYTRACER_OBJECT_H
