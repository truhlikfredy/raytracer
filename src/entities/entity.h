/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 12/01/2018
 */

#ifndef RAYTRACER_ENTITY_H
#define RAYTRACER_ENTITY_H

#include <functional>
#include "../types/vector3.h"
#include "../render/ray.h"

class Entity {

public:
  Vector3 center;

// TODO : enabled/disabled bool

  std::function<Entity(float frame)> evaluateFn;

  Entity(Vector3 centerInit);

  Entity(std::function<Entity(float frame)> evaluateFnInit);

  Entity();

  virtual ~Entity() = default;

};

#endif //RAYTRACER_ENTITY_H
