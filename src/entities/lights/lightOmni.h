/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_LIGHT_OMNI_H
#define RAYTRACER_LIGHT_OMNI_H

#include "../../types/vector3.h"
#include "../../types/color.h"
#include "../entity.h"
#include "light.h"

class LightOmni: public Light {
public:
  LightOmni(const Vector3 &centerInit, const Color &colorInit, const float distanceInvInit, const float burnInit);

  LightOmni(Vector3 centerInit, Color colorInit);
};


#endif //RAYTRACER_LIGHT_OMNI_H
