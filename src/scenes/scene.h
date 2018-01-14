/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 13/01/2018
 */

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <vector>
#include "../entities/entity.h"
#include "../entities/objects/object.h"
#include "../entities/objects/sphereGen.h"
#include "../entities/lights/lightOmni.h"
#include "../entities/lights/lightOmniGen.h"

class Scene {
public:
  int nLights;
  int nObjects;
  LightOmniGen* lights;
  SphereGen*    objects;

  Scene(int nlightsInit, int nObjectsInit);
  ~Scene();

  void evaluateLights(LightOmni* result, float frame);
  void evaluateObjects(Sphere* result, float frame);

};

#endif //RAYTRACER_SCENE_H
