/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include "omni.h"

LightOmni::LightOmni(std::function<LightOmni(float frame)> propertiesInit): Entity(propertiesInit) {
}

LightOmni::LightOmni(Vector3 centerInit, Color colorInit): color(colorInit), Entity(nullptr) {
  center = centerInit;
}

