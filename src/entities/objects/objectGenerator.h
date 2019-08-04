//
// Created by fredy on 03/08/2019.
//

#ifndef RAYTRACER_OBJECTGENERATOR_H
#define RAYTRACER_OBJECTGENERATOR_H

#include "../../types/vector3.h"
#include "materials.h"
#include "object.h"

class ObjectGenerator: public Object {

public:
  std::function<Object*(float frame)> evaluateFn;

  ObjectGenerator(Vector3 centerInt);

  ObjectGenerator(Vector3 centerInt, std::function<materialStatic(Vector3 point, float frame)> materialFnInit);

  ObjectGenerator(std::function<Object*(float frame)> evaluateFnInit);

  virtual Object * eval(float frame);
};
#endif //RAYTRACER_OBJECTGENERATOR_H
