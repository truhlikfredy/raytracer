/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include "ray.h"

Ray::Ray(): source(Vector3()) {
}


Ray::Ray(Vector3 sourceInit): source(sourceInit) {
}


Ray::Ray(Vector3 sourceInit, Vector3 directionInit): Ray(sourceInit, directionInit, nullptr, nullptr) {
}


Ray::Ray(Vector3 sourceInit, Vector3 directionInit, Ray *parentRayInit, Object *enteringObject):
source(sourceInit), parentRay(parentRayInit), inside(enteringObject) {
  setDirection(directionInit);
}


void Ray::setDirection(Vector3 directionInit) {
  /* Changed the direction, recalculated the pre-cached values */
  // TODO: Verify if direction has to be normalized
  direction_ = directionInit;
  directionDot = direction_ % direction_;
  directionDotInverse = 1.0f / directionDot;
#ifdef AABB
  directionFraction = Vector3(1.0f / direction.x, 1.0f / direction.y, 1.0f / direction.z);
#endif
}

Vector3 Ray::getDirection() {
  return direction_;
}


