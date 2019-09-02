/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include "ray.h"

Ray::Ray(): source(Vector3()), direction(Vector3()), directionFraction(Vector3(1)),directionDot(0.0f), directionDotInverse(1.0f) {
}

Ray::Ray(Vector3 sourceInit, Vector3 directionInit): source(sourceInit), direction(directionInit),
directionFraction(1.0f / directionInit.x, 1.0f / directionInit.y, 1.0f / directionInit.z), directionDot(directionInit % directionInit) {
  directionDotInverse = 1.0f / directionDot;
}

