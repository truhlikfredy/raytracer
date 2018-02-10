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
  std::function<Sphere(float frame)> evaluateFn;

  Sphere(Vector3 centerInt, float radiusInit, std::function<materialStatic(Vector3 point, float frame)> materialFnInit);

  Sphere(Vector3 centerInt, float radiusInit);

  Sphere(std::function<Sphere(float frame)> evaluateFnInit);


  Sphere();

  float detectHit(Ray ray);

  float detectHit(Ray ray, Vector3 &hitPoint);

  float detectHitMax(Ray ray, Vector3 &hitPoint);

  uv toUv(Vector3 point);

  Vector3 operator ^ (Vector3 pointOnSurface);


};


#endif //RAYTRACER_SPHERE_H
