/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include "lightOmni.h"

LightOmni::LightOmni(std::function<Entity(float frame)> propertiesInit): Entity(propertiesInit) {
}

LightOmni::LightOmni(Vector3 centerInit, Color colorInit): color(colorInit), Entity(centerInit) {
}

LightOmni::LightOmni() {
}

