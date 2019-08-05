//
// Created by fredy on 04/08/2019.
//

#include "light.h"

Light::Light(const Vector3 &centerInit, const Color &colorInit) : Entity(centerInit), color(colorInit) {}

Light::Light(): Entity(), color() {
}
