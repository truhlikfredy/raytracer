/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 17/01/2018
 */

#ifndef RAYTRACER_SCENES_MANDELBROT_H
#define RAYTRACER_SCENES_MANDELBROT_H

#include "scene.h"

class Mandelbrot: public Scene {
private:
  Color mandelbrot(float lookAtX, float lookAtY, float width, float height, float gamma, uv pixel);

public:
  Mandelbrot();
};


#endif //RAYTRACER_SCENES_MANDELBROT_H
