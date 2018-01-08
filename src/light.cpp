/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include "light.h"

Light::Light(Vector3 source, Color colorInit): Vector3(source) {
  color = colorInit;
}
