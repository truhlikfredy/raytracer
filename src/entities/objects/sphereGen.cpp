/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 14/01/2018
 */

#include "sphereGen.h"

SphereGen::SphereGen(std::function<Sphere(float frame)> evaluateFnInit): evaluateFn(evaluateFnInit) {
}

SphereGen::SphereGen() {
}