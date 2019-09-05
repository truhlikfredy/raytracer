/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_RENDER_H
#define RAYTRACER_RENDER_H

#include "settings.h"
#include "../types/color.h"
#include "../entities/lights/lightOmni.h"
#include "../scenes/scene.h"
#include "sampler.h"
#include "ray.h"


struct windowType {
  unsigned int xStart;
  unsigned int xEnd;
  unsigned int yStart;
  unsigned int yEnd;
};


class Render {
private:
  unsigned int width;
  unsigned int height;
  std::vector<Scene*> *scenes;

  void getThreadWindow(int thread, windowType &ret);

  bool refract(Object  *closestHitObject, Ray *incidentRay, Vector3 *normal, Ray *refractionRayOut);

  Color rayStart(Ray *ray, Scene *scene);

  Color rayFollow(Ray *ray, Scene *scene, int iteration);

  void renderPartialWindow(windowType &window);

  void clearDynamicPixels();

public:
  unsigned int threadsMax = 1;
  Color* dynamicPixels;

  Render(int width, int height);

  void renderFullWindow(SceneGenerator *scene);
};


#endif //RAYTRACER_RENDER_H
