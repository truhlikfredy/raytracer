//
// Created by fredy on 03/08/2019.
//

#include "entityGenerator.h"

EntityGenerator::EntityGenerator(Vector3 centerInit): center(centerInit)  {
}

// Move to OBJECT, LIGHT
EntityGenerator::EntityGenerator(std::function<Entity*(float frame)> evaluateFnInit) {
  evaluateFn = evaluateFnInit;
}

//Entity *EntityGenerator::eval(float frame) {
//  if (evaluateFn) {
//    return evaluateFn(frame);
//  }
//}

/* So the derived classes do not have to call me explicitly */
//EntityGenerator::EntityGenerator() {
//
//}
