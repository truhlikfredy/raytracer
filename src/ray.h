//
// Created by fredy on 07/01/18.
//

#ifndef RAYCASTER_RAY_H
#define RAYCASTER_RAY_H

#include "vector3.h"

struct Ray {
  Vector3 source;
  Vector3 direction;

  Ray(Vector3 sourceInit, Vector3 directionInit);
};


#endif //RAYCASTER_RAY_H
