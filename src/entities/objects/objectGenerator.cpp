//
// Created by fredy on 03/08/2019.
//

#include "objectGenerator.h"

ObjectGenerator::ObjectGenerator(Vector3 centerInt) : EntityGenerator(centerInt) {
}

ObjectGenerator::ObjectGenerator(Vector3 centerInt, std::function<materialStatic(Vector3 point, float frame)> materialFnInit): EntityGenerator(centerInt) {
  materialFn = materialFnInit;
}

ObjectGenerator::ObjectGenerator(std::function<Object *(float frame)> evaluateFnInit) : EntityGenerator(evaluateFnInit) {

}

