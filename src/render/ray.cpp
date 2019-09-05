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

Ray::Ray(Vector3 sourceInit, Vector3 directionInit): Ray(sourceInit, directionInit, nullptr, nullptr) {
}

Ray::Ray(Vector3 sourceInit, Vector3 directionInit, Ray *parentRayInit, Object *enteringObject): source(sourceInit), direction(directionInit)
#ifdef AABB
  , directionFraction(1.0f / directionInit.x, 1.0f / directionInit.y, 1.0f / directionInit.z)
#endif
  , directionDot(directionInit % directionInit), parentRay(parentRayInit), inside(enteringObject) {
  directionDotInverse = 1.0f / directionDot;
}

