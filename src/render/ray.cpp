/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include "ray.h"

Ray::Ray(Vector3 sourceInit, Vector3 directionInit) {
  source    = sourceInit;
  direction = directionInit;
}
