/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 11/01/2018
 *
 * Predefined materials inspired with values from:
 *
 * https://globe3d.sourceforge.io/g3d_html/gl-materials__ads.htm
 */

#include "materials.h"

MaterialStatic Materials::red = {
  .ambient   = Color(0.0f),
  .diffuse   = Color(1.0f, 0.0f, 0.0f),
  .specular  = Color(0.0225f),
  .emission  = Color(0.0f),
  .shininess = 12.8f
};

MaterialStatic Materials::mirror = {
  .ambient   = Color(0.1f),
  .diffuse   = Color(0.1f),
  .specular  = Color(0.8f),
  .emission  = Color(0.0f),
  .shininess = 77.0f
};

