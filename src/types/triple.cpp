/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */


#include <float.h>
#include <cmath>

#include "triple.h"


Triple::Triple() {
  x = y = z = 0.0f;
}

Triple::Triple(float init) {
  x = init;
  y = init;
  z = init;
}

Triple::Triple(float xInit, float yInit, float zInit) {
  x = xInit;
  y = yInit;
  z = zInit;
}

//Triple::Triple(Triple &triple) {
//  x = triple.x;
//  y = triple.y;
//  z = triple.z;
//}

Triple Triple::operator+(Triple secondTriple) {
  return Triple(this->x + secondTriple.x, this->y + secondTriple.y, this->z + secondTriple.z);
}

Triple Triple::operator-(Triple secondTriple) {
  return Triple(this->x - secondTriple.x, this->y - secondTriple.y, this->z - secondTriple.z);
}

Triple Triple::operator*(float scalar) {
  return Triple(this->x * scalar, this->y * scalar, this->z * scalar);
}

Triple Triple::operator/(float scalar) {
  return Triple(this->x / scalar, this->y / scalar, this->z / scalar);
}

float Triple::sum() {
  return this->x + this->y + this->z;
}


Triple Triple::operator*(Triple secondTriple) {
  return Triple(this->x * secondTriple.x, this->y * secondTriple.y, z * secondTriple.z);
}

//Triple Triple::operator=(Triple& secondTriple) {
//  return Triple(secondTriple->x, secondTriple->y, secondTriple->z);
//}