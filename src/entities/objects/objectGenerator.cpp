//
// Created by fredy on 24/02/18.
//

#include "sphere.h"

Sphere::Sphere(Vector3 centerInt, float radiusInit, std::function<materialStatic(Vector3 point, float frame)> materialFnInit):
  Object(centerInt, materialFnInit) {
  radius = radiusInit;
}


class objectGenerator {
  static Sphere makeSphere
};