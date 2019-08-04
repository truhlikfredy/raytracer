//
// Created by fredy on 04/08/2019.
//

#ifndef RAYTRACER_LIGHTGENERATOR_H
#define RAYTRACER_LIGHTGENERATOR_H

#include "functional"
#include "../entity.h"
#include "../entityGenerator.h"
#include "../../types/color.h"
#include "light.h"

class LightGenerator: public EntityGenerator {
public:
  Color color;

  std::function<Light*(float frame)> evaluateFn;

  LightGenerator(Vector3 centerInit, Color colorInit);

  LightGenerator(std::function<Light*(float frame)> evaluateFnInit);

  LightGenerator();

  virtual Light* eval(float frame);
};
#endif //RAYTRACER_LIGHTGENERATOR_H
