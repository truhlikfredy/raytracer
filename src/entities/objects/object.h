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

class Ray; // https://stackoverflow.com/questions/2133250/x-does-not-name-a-type-error-in-c/2133260

class Object: public Entity {

public:
  std::function<materialStatic(Vector3 point, float frame)> materialFn;
  materialStatic material;

  Object(Vector3 centerInit, std::function<materialStatic(Vector3 point, float frame)> materialFnInit);

  Object(Vector3 centerInit, materialStatic materialInit);

  // https://rules.sonarsource.com/cpp/RSPEC-1709
  explicit Object(Vector3 centerInit);

  Object();

  std::function<Object(float frame)> evaluateObjFn;

  materialStatic evalMaterial(Vector3 point, float frame);

  virtual uv toUv(Vector3 point);

  virtual float detectHit(Ray *ray);

  virtual float detectHitPoint(Ray *ray, Vector3 &hitPoint, bool isMin);

  virtual Vector3 operator ^ (Vector3 pointOnSurface);

protected:
#ifdef AABB
  bool detectHitBB(Ray *ray);
#endif

};

// TODO: Material should take time, uv as input as well, not just the point

#endif //RAYTRACER_OBJECT_H
