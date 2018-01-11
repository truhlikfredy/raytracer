//
// Created by fredy on 11/01/18.
//

#ifndef RAYTRACER_OBJECT_H
#define RAYTRACER_OBJECT_H

#include "../../render/ray.h"

class Object {
public:

  virtual bool detectHit(Ray ray, Vector3 &hitPoint) = 0;

  virtual Vector3 operator ^ (Vector3 pointOnSurface) = 0;

};

#endif //RAYTRACER_OBJECT_H
