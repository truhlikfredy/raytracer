/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include <math.h>
#include "vector3.h"
#include "color.h"

Color::Color(): Triple() { }

Color::Color(float r, float g, float b): Triple(r, g, b) { }

Color::Color(const Triple& base): Triple(base) { }

// Normalize
Color Color::operator ~() {
  this->x = fmaxf(0, fminf(1, this->x));
  this->y = fmaxf(0, fminf(1, this->y));
  this->z = fmaxf(0, fminf(1, this->z));

  return *this;
}


