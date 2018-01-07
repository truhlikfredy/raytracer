//
// Created by fredy on 23/12/17.
//

#ifndef RAYCASTER_COLOR_H
#define RAYCASTER_COLOR_H

#include "triple.h"

class Color : public Triple {

public:
  Color();
  Color(float r, float g, float b);
  Color(const Triple& base);

  Color operator~();
};



#endif //RAYCASTER_COLOR_H
