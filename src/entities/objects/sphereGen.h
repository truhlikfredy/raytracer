//
// Created by fredy on 14/01/18.
//

#ifndef RAYTRACER_SPHEREGEN_H
#define RAYTRACER_SPHEREGEN_H

#include "sphere.h"

class SphereGen {
public:
  std::function<Sphere(float frame)> evaluateFn;

  SphereGen(std::function<Sphere(float frame)> evaluateFnInit);
  SphereGen();
};

#endif //RAYTRACER_SPHEREGEN_H
