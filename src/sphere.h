//
// Created by fredy on 07/01/18.
//

#ifndef RAYCASTER_SPHERE_H
#define RAYCASTER_SPHERE_H

#include "vector3.h"
#include "ray.h"

class Sphere {
  Vector3 center;
  float   radius;

public:
  Sphere(Vector3 centerInt, float radiusInit);

  // Get normalized normal vector from sphere's surface point
  Vector3 operator ^ (Vector3 pointOnSurface);

  bool detectHit(Ray ray, Vector3 &hitPoint);
};


#endif //RAYCASTER_SPHERE_H
