/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 13/01/2018
 */

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <memory>
#include <vector>
#include "../types/vector3.h"
#include "../entities/entity.h"
#include "../entities/objects/object.h"
#include "../entities/objects/sphere.h"
#include "../entities/lights/lightOmni.h"
#include "../entities/lights/lightOmniGenerator.h"

class Scene {
public:
  std::vector<Light*> *lights;
//  LightOmniGen* lights[];
//  Object*    objects;
  std::vector<Object*> *objects;
  float         frame;
  int           lightVariations;
  Color         ambientStatic;
  std::function<Color(float frame)> ambientFn;


  struct {
    Vector3 position;    // Position of the camera
    Vector3 lookAt;      // Location where the camera is looking
    float   aperture;    // Affects strength of the depth of field, 0 = disabled DOF
    float   shutterBlur; // Affects motion blur, 0 = disabled blur
  } camera;

  Scene();

  Scene(Color ambientStaticInit);

  ~Scene();

//  void evaluateLights(LightOmni* result, float frame);
//  void evaluateObjects(std::vector<std::shared_ptr<Object>> result, float frame);

};

#endif //RAYTRACER_SCENE_H
