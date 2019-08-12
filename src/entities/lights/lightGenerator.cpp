//
// Created by fredy on 04/08/2019.
//

#include "lightGenerator.h"

LightGenerator::LightGenerator(std::function<Light *(float frame)> evaluateFnInit): evaluateFn(evaluateFnInit) {
}

LightGenerator::LightGenerator(const Vector3 &centerInit, const Color &colorInit, const float distanceInit,
                               const float burnInit) : Light(centerInit, colorInit, distanceInit, burnInit) {

}

LightGenerator::LightGenerator(Vector3 centerInit, Color colorInit): Light(centerInit, colorInit) {
}

LightGenerator::LightGenerator(): Light() {
}

// https://stackoverflow.com/questions/3065154/undefined-reference-to-vtable
Light *LightGenerator::eval(float frame) {
  return nullptr;
}


