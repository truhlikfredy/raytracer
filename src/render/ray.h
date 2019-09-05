/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "../entities/objects/object.h"
#include "../entities/objects/materials.h"
#include "../types/vector3.h"
#include "../render/settings.h"

class Object; // https://stackoverflow.com/questions/2133250/x-does-not-name-a-type-error-in-c/2133260

struct Ray {
  Vector3 source;
  Vector3 direction;
  Ray *parentRay;
  Object *inside;
  materialStatic *hitMaterial;
#ifdef AABB
  Vector3 directionFraction;
#endif
  float   directionDot;
  float   directionDotInverse;

  Ray();

  Ray(Vector3 sourceInit, Vector3 directionInit);

  Ray(Vector3 sourceInit, Vector3 directionInit, Ray *parentRayInit, Object *enteringObject);

  void updatePreCalculatedValues();

  // TODO: make direction a private field and use method to update it and recalculate the cached data as well
};


#endif //RAYTRACER_RAY_H
