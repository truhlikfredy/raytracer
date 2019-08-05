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

  float detectHit(Ray ray) override;

  float detectHit(Ray ray, Vector3 &hitPoint) override;

  float detectHitMax(Ray ray, Vector3 &hitPoint) override;

  uv toUv(Vector3 point);

  Vector3 operator ^ (Vector3 pointOnSurface);


};


#endif //RAYTRACER_SPHERE_H
