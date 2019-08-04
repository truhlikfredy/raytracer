//
// Created by fredy on 14/01/18.
//

#ifndef RAYTRACER_OMNIGEN_H
#define RAYTRACER_OMNIGEN_H

#include "lightGenerator.h"
#include "light.h"

class LightOmniGenerator: public LightGenerator {
public:
  LightOmniGenerator(std::function<Light*(float frame)> evaluateFnInit);
  LightOmniGenerator(Vector3 centerInit, Color colorInit);

  Light * eval(float frame) override;
};
#endif //RAYTRACER_OMNIGEN_H
