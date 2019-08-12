/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include <math.h>
#include "vector3.h"
#include "color.h"

Color::Color(): Triple() { }

Color::Color(float r, float g, float b): Triple(r, g, b) { }

Color::Color(const Triple& base): Triple(base) { }

// Normalize
Color Color::operator ~() {
  this->x = fmaxf(0, fminf(1, this->x));
  this->y = fmaxf(0, fminf(1, this->y));
  this->z = fmaxf(0, fminf(1, this->z));

  return *this;
}

Color Color::toLab() {
  // Will convert RGB to LAB colorspace http://www.brucelindbloom.com

  float r = x;
  float g = y;
  float b = z;
  float X, Y, Z, fx, fy, fz, xr, yr, zr;
  float Ls, as, bs;
  float eps = 216.f / 24389.f;
  float k = 24389.f / 27.f;

  float Xr = 0.964221f;  // reference white D50
  float Yr = 1.0f;
  float Zr = 0.825211f;

  // assuming sRGB (D65)
  if (r <= 0.04045)
    r = r / 12;
  else
    r = powf((r + 0.055) / 1.055, 2.4);

  if (g <= 0.04045)
    g = g / 12;
  else
    g = powf((g + 0.055) / 1.055, 2.4);

  if (b <= 0.04045)
    b = b / 12;
  else
    b = powf((b + 0.055) / 1.055, 2.4);


  X = 0.436052025f * r + 0.385081593f * g + 0.143087414f * b;
  Y = 0.222491598f * r + 0.71688606f * g + 0.060621486f * b;
  Z = 0.013929122f * r + 0.097097002f * g + 0.71418547f * b;

  // XYZ to Lab
  xr = X / Xr;
  yr = Y / Yr;
  zr = Z / Zr;

  if (xr > eps)
    fx = powf(xr, 1 / 3.);
  else
    fx = (float) ((k * xr + 16.) / 116.);

  if (yr > eps)
    fy = powf(yr, 1 / 3.);
  else
    fy = (float) ((k * yr + 16.) / 116.);

  if (zr > eps)
    fz = powf(zr, 1 / 3.);
  else
    fz = (float) ((k * zr + 16.) / 116);

  Ls = (116 * fy) - 16;
  as = 500 * (fx - fy);
  bs = 200 * (fy - fz);

  return Color((2.55 * Ls + .5), (as + .5), (bs + .5));
}


float Color::labDifference(Color secondColor) {
  // return distance between the colors after converting them to lab
  return this->toLab().distance(secondColor.toLab());
}

bool Color::isBlack() {
  return x == 0.0f && y == 0.0f && z == 0.0f;
}

