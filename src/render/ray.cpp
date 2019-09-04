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

Ray::Ray(Vector3 sourceInit, Vector3 directionInit): source(sourceInit), direction(directionInit)
#ifdef AABB
, directionFraction(1.0f / directionInit.x, 1.0f / directionInit.y, 1.0f / directionInit.z)
#endif
, directionDot(directionInit % directionInit) {
  directionDotInverse = 1.0f / directionDot;
}

Ray::Ray(Vector3 sourceInit, Vector3 directionInit, Ray *originalRay, Object *enteringObject): source(sourceInit), direction(directionInit)
#ifdef AABB
  , directionFraction(1.0f / directionInit.x, 1.0f / directionInit.y, 1.0f / directionInit.z)
#endif
  , directionDot(directionInit % directionInit) {
  directionDotInverse = 1.0f / directionDot;
  if (enteringObject == nullptr) {
    for (int i = 0; i < MAX_BOUNCES; ++i) {
      inside[i] = originalRay->inside[i];
    }
  } else {
    for (int i = 0; i < MAX_BOUNCES-1; ++i) {
      inside[i+1] = originalRay->inside[i];
    }
    inside[0] = enteringObject;
  }
}

void Ray::getOutsideObject() {
  for (int i = 0; i < MAX_BOUNCES-1; ++i) {
    inside[i] = inside[i+1];
  }
  inside[MAX_BOUNCES] = nullptr;
}

