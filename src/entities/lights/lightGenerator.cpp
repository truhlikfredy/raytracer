//
// Created by fredy on 04/08/2019.
//

#include "lightGenerator.h"

LightGenerator::LightGenerator(std::function<Light *(float frame)> evaluateFnInit) : EntityGenerator(evaluateFnInit) {
}

LightGenerator::LightGenerator(Vector3 centerInit, Color colorInit): EntityGenerator(centerInit), color(colorInit) {

}

