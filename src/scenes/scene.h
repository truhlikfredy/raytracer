/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 13/01/2018
 */

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include "../types/vector3.h"
#include "../entities/entity.h"
#include "../entities/objects/object.h"
#include "../entities/objects/sphere.h"
#include "../entities/lights/lightOmni.h"
#include "../entities/lights/lightOmniGen.h"

class Scene {
public:
  int           nLights;
  int           nObjects;
  LightOmniGen* lights;
  Sphere*    objects;
  float         frame;
  float         lastFrame;
  Color         ambient;

  struct {
    Vector3 possition;    // Possition of the camera
    Vector3 lookAt;       // Loacation where the camera is looking
    float   apeture;      // Affects strenght of the depth of field, 0 = disabled DOF
    float   shutterBlur; // Affects motion blur, 0 = disabled blur
  } camera;

  Scene(int nlightsInit, int nObjectsInit, float lastFrame);

  Scene(int nlightsInit, int nObjectsInit);

  ~Scene();

  void evaluateLights(LightOmni* result, float frame);
  void evaluateObjects(Sphere* result, float frame);

};

#endif //RAYTRACER_SCENE_H
