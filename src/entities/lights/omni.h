/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_LIGHT_OMNI_H
#define RAYTRACER_LIGHT_OMNI_H

#include "../../types/vector3.h"
#include "../../types/color.h"
#include "../entity.h"

class LightOmni: public Vector3, public Entity {
public:
  LightOmni(std::function<LightOmni(float frame)> propertiesInit);
  LightOmni(Vector3 centerInit, Color colorInit);
  LightOmni();
  Color color;
};


#endif //RAYTRACER_LIGHT_OMNI_H
