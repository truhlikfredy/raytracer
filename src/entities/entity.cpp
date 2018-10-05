/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 12/01/2018
 */

#include "entity.h"

Entity::Entity(Vector3 centerInit): center(centerInit), isEnabled(true)  {
  //evaluateObjFn = nullptr;
}

Entity::Entity(std::function<Entity(float frame)> evaluateFnInit): isEnabled(true) {
  evaluateFn = evaluateFnInit;
}

Entity::Entity(): isEnabled(true) {
}

