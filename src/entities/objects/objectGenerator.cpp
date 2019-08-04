//
// Created by fredy on 03/08/2019.
//

#include "objectGenerator.h"

ObjectGenerator::ObjectGenerator(Vector3 centerInt) : Object(centerInt) {
}

ObjectGenerator::ObjectGenerator(Vector3 centerInt, std::function<materialStatic(Vector3 point, float frame)> materialFnInit): Object(centerInt, materialFn) {

}

ObjectGenerator::ObjectGenerator(std::function<Object *(float frame)> evaluateFnInit) : evaluateFn(evaluateFnInit) {
}

// https://stackoverflow.com/questions/3065154/undefined-reference-to-vtable
Object *ObjectGenerator::eval(float frame) {
  return nullptr;
}

