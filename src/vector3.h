/*
 * vector.h
 *
 *  Created on: 22 Dec 2017
 *      Author: fredy
 */

#ifndef RAYCASTER_VECTOR3_H_
#define RAYCASTER_VECTOR3_H_

#include "triple.h"

class Vector3: public Triple {

public:
  Vector3();

  Vector3(float xInit, float yInit, float zInit);

  Vector3(const Triple& base);

  float operator%(Vector3 secondVector);

  Vector3 operator~();
};

#endif /* VECTOR_H_ */
