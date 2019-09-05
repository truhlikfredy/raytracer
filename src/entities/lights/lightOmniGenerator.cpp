//
// Created by fredy on 14/01/18.
//

#include "lightOmniGenerator.h"
#include "lightOmni.h"

LightOmniGenerator::LightOmniGenerator(std::function<Light *(float frame)> evaluateFnInit): LightGenerator(evaluateFnInit) {
}

LightOmniGenerator::LightOmniGenerator(const Vector3 &centerInit, const Color &colorInit, const float distanceInvInit,
                                       const float burnInit) : LightGenerator(centerInit, colorInit, distanceInvInit, burnInit) {
}

LightOmniGenerator::LightOmniGenerator(Vector3 centerInit, Color colorInit)  {
}

Light *LightOmniGenerator::eval(float frame) {
  if (evaluateFn) {
    return evaluateFn(frame);
  } else {
    return new LightOmni(center, color);
  }
}



