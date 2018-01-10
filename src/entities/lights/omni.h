/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_LIGHT_OMNI_H
#define RAYTRACER_LIGHT_OMNI_H

#include "../../types/vector3.h"
#include "../../types/color.h"

class Light: public Vector3 {
public:
  Light(Vector3 source, Color colorInit);
  Color color;
};


#endif //RAYTRACER_LIGHT_OMNI_H
