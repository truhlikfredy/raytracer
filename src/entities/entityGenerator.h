//
// Created by fredy on 03/08/2019.
//

#ifndef RAYTRACER_ENTITYGENERATOR_H
#define RAYTRACER_ENTITYGENERATOR_H

#include <functional>
#include "../types/vector3.h"
#include "entity.h"

class EntityGenerator {

public:
  Vector3 center;
  std::function<Entity*(float frame)> evaluateFn;

  EntityGenerator(Vector3 centerInit);

  EntityGenerator(std::function<Entity*(float frame)> evaluateFnInit);

  /* So the derived classes do not have to call me explicitly */
//  EntityGenerator();

  virtual Entity * eval(float frame);
};

#endif //RAYTRACER_ENTITYGENERATOR_H
