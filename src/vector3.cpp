/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include <float.h>
#include <cmath>

#include "vector3.h"

Vector3::Vector3(): Triple() {}

Vector3::Vector3(float x, float y, float z): Triple(x, y, z) { }

Vector3::Vector3(const Triple& base): Triple(base) { }

float Vector3::operator%(Vector3 secondVector) {
  return (x * secondVector.x + y * secondVector.y + z * secondVector.z);
}

Vector3 Vector3::operator~() {
  const float magnitude = sqrt(x * x + y * y + z * z);
  return Vector3(x / magnitude, y / magnitude, z / magnitude);
}
