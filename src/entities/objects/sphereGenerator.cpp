
#include "sphereGenerator.h"
#include "sphere.h"

SphereGenerator::SphereGenerator(Vector3 centerInt, float radiusInit): ObjectGenerator(centerInt) {
  radius = radiusInit;
}

SphereGenerator::SphereGenerator(Vector3 centerInt, float radiusInit, std::function<materialStatic(Vector3 point, float frame)> materialFnInit): ObjectGenerator(centerInt, materialFnInit) {
  radius = radiusInit;
}

SphereGenerator::SphereGenerator(std::function<Object*(float frame)> evaluateFnInit): ObjectGenerator(evaluateFnInit) {
}

Object *SphereGenerator::eval(float frame) {
  if (evaluateFn) {
    return evaluateFn(frame);
  } else {
    return new Sphere(center, radius, materialFn);
  }
}
