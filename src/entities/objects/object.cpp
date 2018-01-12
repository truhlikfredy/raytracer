/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 11/01/2018
 */

#include "object.h"

Object::Object(Vector3 centerInit, std::function<materialStatic(Vector3 point)> materialInit):
  center(centerInit), material(materialInit) {

}

uv Object::toUv(Vector3 point) {
  return {
    .u = point.x,
    .v = point.y,
  };
}
