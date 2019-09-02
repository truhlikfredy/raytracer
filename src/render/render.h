/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_RENDER_H
#define RAYTRACER_RENDER_H

#define SEGMENTS 1  // how many partitions the screen should be split
#define SAMPLING_MIN 2  // Samples per light, the final sampling will change depending on the lights present in the scene
#define SAMPLING_MAX 5
#define SAMPLING_DELTA 0.03f
#define MAX_BOUNCES 4
//#define CHROMATIC_ABERRATION_REFRACTION // Comment out to disable
#define CHROMATIC_ABERRATION_STRENGTH 0.02f

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

  void refract(Vector3 &incidentVec, Vector3 &normal, float refractionIndex, Vector3 &refractionRay);

  Color rayStart(Ray *ray, Scene *scene);

  Color rayFollow(Ray *ray, Scene *scene, int iteration, Object *inside);

  void renderPartialWindow(windowType &window);

  void clearDynamicPixels();

public:
  unsigned int threadsMax = 1;
  Color* dynamicPixels;

  Render(int width, int height);

  void renderFullWindow(SceneGenerator *scene);
};


#endif //RAYTRACER_RENDER_H
