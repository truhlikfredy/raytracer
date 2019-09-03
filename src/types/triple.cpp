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


void Triple::operator+=(Triple secondTriple) {
  this->x += secondTriple.x;
  this->y += secondTriple.y;
  this->z += secondTriple.z;
}


Triple Triple::operator-(Triple secondTriple) {
  return Triple(this->x - secondTriple.x, this->y - secondTriple.y, this->z - secondTriple.z);
}


void Triple::operator-=(Triple secondTriple) {
  this->x -= secondTriple.x;
  this->y -= secondTriple.y;
  this->z -= secondTriple.z;
}


Triple Triple::operator-(float scalar) {
  return Triple(this->x - scalar, this->y - scalar, this->z - scalar);
}


void Triple::operator-=(float scalar) {
  this->x -= scalar;
  this->y -= scalar;
  this->z -= scalar;
}


Triple Triple::operator*(float scalar) {
  return Triple(this->x * scalar, this->y * scalar, this->z * scalar);
}


void Triple::operator*=(float scalar) {
  this->x *= scalar;
  this->y *= scalar;
  this->z *= scalar;
}


Triple Triple::operator*(Triple secondTriple) {
  return Triple(this->x * secondTriple.x, this->y * secondTriple.y, z * secondTriple.z);
}


void Triple::operator*=(Triple secondTriple) {
  this->x *= secondTriple.x;
  this->y *= secondTriple.y;
  this->z *= secondTriple.z;
}


Triple Triple::operator/(float scalar) {
  return Triple(this->x / scalar, this->y / scalar, this->z / scalar);
}


void Triple::operator/=(float scalar) {
  this->x /= scalar;
  this->y /= scalar;
  this->z /= scalar;
}


float Triple::sum() {
  return this->x + this->y + this->z;
}


float Triple::distance(Triple secondTriple) {
  return sqrtf(powf(this->x - secondTriple.x, 2) +
               powf(this->y - secondTriple.y, 2) +
               powf(this->z - secondTriple.z, 2));
}


float Triple::lenght() {
  return sqrt(this->x * this->x +
              this->y * this->y +
              this->z * this->z);
}


Triple Triple::min(Triple secondTriple) {
  return Triple(fminf(this->x, secondTriple.x), fminf(this->y, secondTriple.y), fminf(this->z, secondTriple.z));
}


Triple Triple::max(Triple secondTriple) {
  return Triple(fmax(this->x, secondTriple.x), fmax(this->y, secondTriple.y), fmax(this->z, secondTriple.z));
}


float Triple::min() {
  return fminf(fminf(x, y),z);
}


float Triple::max() {
  return fmaxf(fmaxf(x, y),z);
}


//Triple Triple::operator=(Triple& secondTriple) {
//  return Triple(secondTriple->x, secondTriple->y, secondTriple->z);
//}