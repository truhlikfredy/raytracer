/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include "ray.h"

Ray::Ray(): source(Vector3()), direction(Vector3())
#ifdef AABB
, directionFraction(Vector3(1))
#endif
,directionDot(0.0f), directionDotInverse(1.0f) {
}


Ray::Ray(Vector3 sourceInit): source(sourceInit)
#ifdef AABB
, directionFraction(Vector3(1))
#endif
{
}


Ray::Ray(Vector3 sourceInit, Vector3 directionInit): Ray(sourceInit, directionInit, nullptr, nullptr) {
}


Ray::Ray(Vector3 sourceInit, Vector3 directionInit, Ray *parentRayInit, Object *enteringObject): source(sourceInit), direction(directionInit)
  , parentRay(parentRayInit), inside(enteringObject) {
  updatePreCalculatedValues();
}


void Ray::updatePreCalculatedValues() {
  // TODO: Verify if direction has to be normalized
  directionDot = direction % direction;
  directionDotInverse = 1.0f / directionDot;
#ifdef AABB
  directionFraction = Vector3(1.0f / direction.x, 1.0f / direction.y, 1.0f / direction.z);
#endif
}


