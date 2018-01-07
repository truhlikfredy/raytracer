//
// Created by fredy on 23/12/17.
//

#ifndef RAYCASTER_LIGHT_H
#define RAYCASTER_LIGHT_H

#include "vector3.h"
#include "color.h"

class Light: public Vector3 {
public:
  Light(Vector3 source, Color colorInit);
  Color color;
};


#endif //RAYCASTER_LIGHT_H
