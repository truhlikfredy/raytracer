/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 11/01/2018
 */

#include "object.h"

// Object::Object(std::function<Object(float frame)> propertiesFnInit): Entity(propertiesFnInit), materialFn(nullptr) {

Object::Object(std::function<Object(float frame)> evaluateFnInit): evaluateObjFn(evaluateFnInit) {
}

Object::Object(Vector3 centerInit,
               std::function<materialStatic(Vector3 point, float frame)> materialFnInit):
               materialFn(materialFnInit), Entity() {
  center = centerInit;
}

Object::Object(Vector3 centerInit, materialStatic materialInit):
  material(materialInit), materialFn(nullptr), Entity() {
  center = centerInit;
}

Object::Object(Vector3 centerInit) {
  center = centerInit;
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