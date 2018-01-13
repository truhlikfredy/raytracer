/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 12/01/2018
 */

#ifndef RAYTRACER_ENTITY_H
#define RAYTRACER_ENTITY_H

#include <functional>
#include "../types/vector3.h"

class Entity {
private:
  float frame;

public:
  Vector3 center;

  std::function<Entity(float frame)> evaluateFn;

  Entity(std::function<Entity(float frame)> evaluateFnInit);

  Entity();
};

#endif //RAYTRACER_ENTITY_H
