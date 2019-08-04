//
// Created by fredy on 14/01/18.
//

#include "lightOmniGenerator.h"
#include "lightOmni.h"

LightOmniGenerator::LightOmniGenerator(std::function<Entity *(float frame)> evaluateFnInit): LightGenerator(evaluateFnInit) {
}

LightOmniGenerator::LightOmniGenerator(Vector3 centerInit, Color colorInit) : LightGenerator(centerInit, colorInit) {
}

Light *LightOmniGenerator::eval(float frame) {
  if (evaluateFn) {
    return evaluateFn(frame);
  } else {
    return new LightOmni(center, color);
  }
}


