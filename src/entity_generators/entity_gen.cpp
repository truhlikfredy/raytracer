/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 12/01/2018
 */

#include "entity.h"
#include "entity_gen.h"


Entity::Entity(std::function<Entity(float frame)> evaluateFnInit) {
  evaluateFn = evaluateFnInit;
}

Entity::Entity(): isEnabled(true) {
}

