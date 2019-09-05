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

class Ray {
public:
  Vector3        source;
  Ray            *parentRay;
  Object         *inside;
  materialStatic *hitMaterial;
  float          directionDot;
  float          directionDotInverse;
#ifdef AABB
  Vector3        directionFraction;
#endif

  Ray();

  Ray(Vector3 sourceInit);

  Ray(Vector3 sourceInit, Vector3 directionInit);

  Ray(Vector3 sourceInit, Vector3 directionInit, Ray *parentRayInit, Object *enteringObject);

  void setDirection(Vector3 directionInit);

  Vector3 getDirection();

private:
  Vector3 direction_;
};


#endif //RAYTRACER_RAY_H
