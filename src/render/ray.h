/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "../entities/objects/object.h"
#include "../types/vector3.h"
#include "../render/settings.h"

class Object; // https://stackoverflow.com/questions/2133250/x-does-not-name-a-type-error-in-c/2133260

struct Ray {
  Vector3 source;
  Vector3 direction;
  Object *inside[MAX_BOUNCES];
#ifdef AABB
  Vector3 directionFraction;
#endif
  float   directionDot;
  float   directionDotInverse;

  Ray();

  Ray(Vector3 sourceInit, Vector3 directionInit);

  Ray(Vector3 sourceInit, Vector3 directionInit, Ray *originalRay, Object *enteringObject);

  void getOutsideObject();
};


#endif //RAYTRACER_RAY_H
