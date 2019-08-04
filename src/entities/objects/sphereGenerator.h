/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_SPHERE_GENERATOR_H
#define RAYTRACER_SPHERE_GENERATOR_H

#include "objectGenerator.h"
#include "sphereGenerator.h"
#include "../entityGenerator.h"

class SphereGenerator: public ObjectGenerator {

public:
  float radius;

  SphereGenerator(Vector3 centerInt, float radiusInit);

  SphereGenerator(Vector3 centerInt, float radiusInit, std::function<materialStatic(Vector3 point, float frame)> materialFnInit);

  SphereGenerator(std::function<Object*(float frame)> evaluateFnInit);

  Object* eval(float frame) override;
};


#endif //RAYTRACER_SPHERE_GENERATOR_H
