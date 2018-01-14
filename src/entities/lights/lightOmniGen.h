//
// Created by fredy on 14/01/18.
//

#ifndef RAYTRACER_OMNIGEN_H
#define RAYTRACER_OMNIGEN_H

#include "lightOmni.h"

class LightOmniGen {
public:
  std::function<LightOmni(float frame)> evaluateFn;

  LightOmniGen(std::function<LightOmni(float frame)> evaluateFnInit);
  LightOmniGen();
};
#endif //RAYTRACER_OMNIGEN_H
