//
// Created by fredy on 03/08/2019.
//

#ifndef RAYTRACER_SCENEGENERATOR_H
#define RAYTRACER_SCENEGENERATOR_H

#include "../types/color.h"
#include "scene.h"
#include "../entities/objects/objectGenerator.h"

class SceneGenerator {
public:
  std::vector<LightGenerator*>      *lightGenerators;
  std::vector<ObjectGenerator*>     *objectGenerators;
  Color                             ambientStatic;
  std::function<Color(float frame)> ambientFn;
  float                             frame;
  float                             frameFirst;
  float                             frameLast;
  float                             lightStep;
  float                             lightEnd;

  /* TODO: Make cameras generic */
  struct {
    Vector3 position;     // Position of the camera
    Vector3 lookAt;       // Location where the camera is looking
    float   aperture;     // Affects strength of the depth of field, 0 = disabled DOF
    float   shutterBlur;  // Affects motion blur, 0 = disabled blur
  } camera;

  SceneGenerator();

  explicit SceneGenerator(float frameEndInit);

  ~SceneGenerator();

  Scene* generateScene();

  Scene* generateScene(float frame);
};
#endif //RAYTRACER_SCENEGENERATOR_H
