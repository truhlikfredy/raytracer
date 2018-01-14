/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 12/01/2018
 */

#include "entity.h"

Entity::Entity(Vector3 centerInit): center(centerInit)  {
  evaluateFn = nullptr;
}

Entity::Entity(std::function<Entity(float frame)> evaluateFnInit) {
  evaluateFn = evaluateFnInit;
}

Entity::Entity() {
}

