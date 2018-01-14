//
// Created by fredy on 14/01/18.
//

#include "lightOmniGen.h"

LightOmniGen::LightOmniGen(std::function<LightOmni(float frame)> evaluateFnInit): evaluateFn(evaluateFnInit) {
}

LightOmniGen::LightOmniGen() {
}