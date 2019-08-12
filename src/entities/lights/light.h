//
// Created by fredy on 04/08/2019.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include "../entity.h"
#include "../../types/color.h"

class Light: public Entity {
public:
  Color color;
  float burn;
  float distance;

  Light(const Vector3 &centerInit, const Color &colorInit, const float distanceInit, const float burnInit);

  Light(const Vector3 &centerInit, const Color &colorInit);

  Light();
};


#endif //RAYTRACER_LIGHT_H
