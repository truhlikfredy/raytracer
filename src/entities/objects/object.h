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
#include "../entity.h"

class Object: public Entity {

public:
  std::function<MaterialStatic(Vector3 point, float frame)> materialFn;
  MaterialStatic materialStatic;

  Object(std::function<Object(float frame)> propertiesFnInit);

  //Object(Vector3 centerInit, Materials materialInit);
  Object(Vector3 centerInit, std::function<MaterialStatic(Vector3 point, float frame)> materialFnInit);

  Object(Vector3 centerInit, MaterialStatic materialStaticInit);

  uv toUv(Vector3 point);

  bool detectHit(Ray ray, Vector3 &hitPoint);

  Vector3 operator ^ (Vector3 pointOnSurface);

};

// TODO: Material should take time, uv as input as well, not just the point

#endif //RAYTRACER_OBJECT_H
