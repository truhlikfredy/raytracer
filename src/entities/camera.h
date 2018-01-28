/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 28/01/2018
 */

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "../render/ray.h"
#include "../render/sampler.h"
#include "../scenes/scene.h"

class Camera {
private:
  unsigned int width;
  unsigned int height;
  static Vector3 down;

public:

  Camera(int widthInit, int heightInit);

  void getRay(int x, int y, sampleTuple &sample, Scene *scene, Ray &ray);
};

#endif //RAYTRACER_CAMERA_H
