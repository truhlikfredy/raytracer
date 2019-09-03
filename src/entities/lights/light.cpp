//
// Created by fredy on 04/08/2019.
//

#include "light.h"

Light::Light(const Vector3 &centerInit, const Color &colorInit, const float distanceInit, const float burnInit):
  Entity(centerInit), color(colorInit), distance(distanceInit), burn(burnInit) {
}

Light::Light(const Vector3 &centerInit, const Color &colorInit): Light(centerInit, colorInit, 350.0f, 0.8f) {}

Light::Light(): Entity(), color() {
}

