/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include <cmath>

#include "vector3.h"


Vector3::Vector3(): Triple() {}


Vector3::Vector3(float x, float y, float z): Triple(x, y, z) { }


Vector3::Vector3(const Triple& base): Triple(base) { }


float Vector3::operator%(Vector3 secondVector) {
  // dot product
  return (x * secondVector.x + y * secondVector.y + z * secondVector.z);
}


Vector3 Vector3::operator~() {
  const float magnitude = sqrt(x * x + y * y + z * z);
  return Vector3(x / magnitude, y / magnitude, z / magnitude);
}


Vector3 Vector3::operator&(Vector3 secondVector) {
  // x   https://steveharveynz.wordpress.com/2012/12/20/ray-tracer-part-two-creating-the-camera/
  return Vector3( (x * secondVector.z) - (z * secondVector.y),
                  (z * secondVector.x) - (x * secondVector.z),
                  (x * secondVector.y) - (y * secondVector.x));
}


float Vector3::lenght() {
  return sqrt(x * x + y * y + z * z);
}

