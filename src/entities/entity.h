/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 12/01/2018
 */

#ifndef RAYTRACER_ENTITY_H
#define RAYTRACER_ENTITY_H

#include <functional>
#include "../types/vector3.h"

class Entity {

public:
  Vector3 center;

  // https://rules.sonarsource.com/cpp/RSPEC-1709
  explicit Entity(Vector3 centerInit);

  Entity();

  virtual ~Entity() = default;

};

#endif //RAYTRACER_ENTITY_H
