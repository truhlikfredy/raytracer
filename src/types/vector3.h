/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_VECTOR3_H_
#define RAYTRACER_VECTOR3_H_

#include "triple.h"

class Vector3: public Triple {

public:
  Vector3();

  Vector3(float xInit, float yInit, float zInit);

  Vector3(const Triple& base);

  float operator%(Vector3 secondVector);

  Vector3 operator~();

  Vector3 operator&(Vector3 secondVector);

  float lenght();
};

#endif /* VECTOR_H_ */
