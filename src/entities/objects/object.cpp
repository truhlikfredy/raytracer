/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 11/01/2018
 */

#include "object.h"

Object::Object(Vector3 centerInit,
               std::function<materialStatic(Vector3 point, float frame)> materialFnInit):
               Entity(centerInit), materialFn(materialFnInit), material(Materials::lightGray) {
}

Object::Object(Vector3 centerInit, materialStatic materialInit): Entity(centerInit),
  material(materialInit), materialFn(nullptr) {
}

Object::Object(Vector3 centerInit): Object(centerInit, Materials::lightGray) {
}

Object::Object(): Object(Vector3()) {
}


Vector3 Object::operator ^ (Vector3 pointOnSurface) {
  return Vector3();
}

float Object::detectHit(Ray ray) {
  return -1;
}

float Object::detectHit(Ray ray, Vector3 &hitPoint) {
  return -1;
}

float Object::detectHitMax(Ray ray, Vector3 &hitPoint) {
  return -1;
}

uv Object::toUv(Vector3 point) {
  return uv();
}
