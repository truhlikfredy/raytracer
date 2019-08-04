/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 11/01/2018
 */

#include "object.h"

Object::Object(Vector3 centerInit,
               std::function<materialStatic(Vector3 point, float frame)> materialFnInit):
               materialFn(materialFnInit), Entity(centerInit) {
}

Object::Object(Vector3 centerInit, materialStatic materialInit):
  material(materialInit), materialFn(nullptr), Entity(centerInit) {
}

Object::Object(Vector3 centerInit): Entity(centerInit) {
}

Object::Object() {
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