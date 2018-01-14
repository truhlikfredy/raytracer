/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 11/01/2018
 */

#include "object.h"

// Object::Object(std::function<Object(float frame)> propertiesFnInit): Entity(propertiesFnInit), materialFn(nullptr) {

Object::Object(Vector3 centerInit,
               std::function<MaterialStatic(Vector3 point, float frame)> materialFnInit):
               materialFn(materialFnInit), Entity() {
  center = centerInit;
}

Object::Object(Vector3 centerInit, MaterialStatic materialStaticInit):
  materialStatic(materialStaticInit), materialFn(nullptr), Entity() {
  center = centerInit;
}

Object::Object() {
}

/*bool Object::detectHit(Ray ray, Vector3 &hitPoint) {
  return false;
}*/

//Vector3 Object::operator ^ (Vector3 pointOnSurface) {
//  return pointOnSurface;
//}

uv Object::toUv(Vector3 point) {
  return {
    .u = point.x,
    .v = point.y,
  };
}
