/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include "lightOmni.h"

LightOmni::LightOmni(Vector3 centerInit, Color colorInit): Light(centerInit, colorInit) {
}

LightOmni::LightOmni(const Vector3 &centerInit, const Color &colorInit, const float distanceInit, const float burnInit)
  : Light(centerInit, colorInit, distanceInit, burnInit) {
}


