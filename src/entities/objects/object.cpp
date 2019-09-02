/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 11/01/2018
 */

#include "object.h"
#include <math.h>

Object::Object(Vector3 centerInit,
               std::function<materialStatic(Vector3 point, float frame)> materialFnInit):
               Entity(centerInit), materialFn(materialFnInit), material(Materials::lightGray) {
}

Object::Object(Vector3 centerInit, materialStatic materialInit): Entity(centerInit),
  material(materialInit), materialFn(nullptr) {
}

Object::Object(Vector3 centerInit): Object(centerInit, Materials::lightGray) {
}

Object::Object(): Object(Vector3()) {
}

/* TODO: do virtual need implementations? */

Vector3 Object::operator ^ (Vector3 pointOnSurface) {
  return Vector3();
}

float Object::detectHit(Ray *ray) {
  return -1;
}

float Object::detectHitMin(Ray *ray, Vector3 &hitPoint) {
  return -1;
}

float Object::detectHitMax(Ray *ray, Vector3 &hitPoint) {
  return -1;
}

uv Object::toUv(Vector3 point) {
  return uv();
}

bool Object::detectHitBB(Ray *ray) {
  Vector3 tMin = (aabbMin - ray->source) * ray->directionFraction;
  Vector3 tMax = (aabbMax - ray->source) * ray->directionFraction;

  Vector3 t1 = tMin.min(tMax);
  Vector3 t2 = tMin.max(tMax);

  float tNear = t1.max();
  float tFar  = t2.min();

  // Ray is intersecting bounding box, it's behind us, or ray doesn't intersect bounding box
  if (tFar < 0 || tNear > tFar)
  {
    return false;
  }

  return true;
}
