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

  //virtual Object(std::function<Entity(float frame)> propertiesFnInit);

  //Object(Vector3 centerInit, Materials materialInit);
  Object(Vector3 centerInit, std::function<MaterialStatic(Vector3 point, float frame)> materialFnInit);

  Object(Vector3 centerInit, MaterialStatic materialStaticInit);

  Object();

  uv toUv(Vector3 point);

  virtual bool detectHit(Ray ray, Vector3 &hitPoint) = 0;

  virtual Vector3 operator ^ (Vector3 pointOnSurface) = 0;

};

// TODO: Material should take time, uv as input as well, not just the point

#endif //RAYTRACER_OBJECT_H
