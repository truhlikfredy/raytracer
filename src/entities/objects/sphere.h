/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "object.h"

class Sphere: public Object {

public:
  float   radius;

  Sphere(Vector3 centerInt, float radiusInit, std::function<materialStatic(Vector3 point, float frame)> materialFnInit);

  Sphere(Vector3 centerInt, float radiusInit, materialStatic material);

  Sphere(Vector3 centerInt, float radiusInit);

  Sphere();

  float detectHit(Ray *ray) override;

  float detectHitPoint(Ray *ray, Vector3 &hitPoint, bool isMin) override;

  uv toUv(Vector3 point) override;

  Vector3 operator ^ (Vector3 pointOnSurface) override;

private:
#ifdef AABB
  void setAabb();
#endif

};


#endif //RAYTRACER_SPHERE_H
