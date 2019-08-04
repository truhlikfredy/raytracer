//
// Created by fredy on 03/08/2019.
//

#include <cstring>
#include "sceneGenerator.h"
#include "scene.h"
#include "../entities/objects/sphereGenerator.h"


SceneGenerator::SceneGenerator() {
  lightStep = 1.0f;
  lightEnd  = 1.0f;
  frame = 0.0f;
  lastFrame = 1.0f;
  ambientStatic = Color(0.1f);

  //TODO: background static/fn

  lightGenerators  = new std::vector<LightGenerator*>();
  objectGenerators = new std::vector<ObjectGenerator*>();
}


Scene* SceneGenerator::generateScene() {
  return generateScene(frame);
}


Scene* SceneGenerator::generateScene(float frame) {
  Scene *scene = new Scene(ambientStatic);

  scene->lightVariations =  lightEnd / lightStep;
  scene->ambientFn       = ambientFn;
  scene->ambientStatic   = ambientStatic;
  scene->frame           = frame;

  memcpy(&scene->camera, &camera, sizeof(camera));

  auto currentLights = new Light[scene->lightVariations];
  for(auto const& generator: *lightGenerators) {
    LightOmniGenerator *lightOmniGenerator = dynamic_cast<LightOmniGenerator*>((LightGenerator*)(generator));
    if (lightOmniGenerator) {
      Light *lightOmnit = lightOmniGenerator->eval(frame);
      for (int i = 0; i < scene->lightVariations; i++) {
        currentLights[i] = *lightOmnit;
      }
      break;
    }
  }
  scene->lights->push_back(currentLights);
//  scene->lights.push_back(nullptr);

  for(auto const& generator: *objectGenerators) {
    SphereGenerator *sphereGenerator = dynamic_cast<SphereGenerator*>((ObjectGenerator*)(generator));
    if (sphereGenerator) {
      Object *object = sphereGenerator->eval(frame);
      scene->objects->push_back(object);
      break;
    }
  }
//  scene->objects.push_back(nullptr);

  return scene;
}

SceneGenerator::~SceneGenerator() {
  delete lightGenerators;
  delete objectGenerators;
  // scene should delete itself, and not generator deleting instanciated scene
}
