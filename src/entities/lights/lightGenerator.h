//
// Created by fredy on 04/08/2019.
//

#ifndef RAYTRACER_LIGHTGENERATOR_H
#define RAYTRACER_LIGHTGENERATOR_H

#include "functional"
#include "../entity.h"
#include "../../types/color.h"
#include "light.h"

class LightGenerator: public Light {
public:
  std::function<Light*(float frame)> evaluateFn;

  LightGenerator(const Vector3 &centerInit, const Color &colorInit, const float distanceInvInit, const float burnInit);

  LightGenerator(Vector3 centerInit, Color colorInit); //TODO: const arguments

  LightGenerator(std::function<Light*(float frame)> evaluateFnInit);

  LightGenerator();

  virtual Light* eval(float frame);
};
#endif //RAYTRACER_LIGHTGENERATOR_H
