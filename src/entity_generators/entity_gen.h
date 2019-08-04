
#ifndef RAYTRACER_ENTITY_H
#define RAYTRACER_ENTITY_H

#include <functional>
#include "../types/vector3.h"
#include "../render/ray.h"

class EntityGen {

public:
  std::function<Entity(float frame)> evaluateFn;


  Entity(std::function<Entity(float frame)> evaluateFnInit);

  virtual ~Entity() = default;

};

#endif //RAYTRACER_ENTITY_H
