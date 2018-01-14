//
// Created by fredy on 14/01/18.
//

#include "sphereGen.h"

SphereGen::SphereGen(std::function<Sphere(float frame)> evaluateFnInit): evaluateFn(evaluateFnInit) {
}

SphereGen::SphereGen() {
}