//
// Created by fredy on 03/08/2019.
//

#include <cstring>
#include "sceneGenerator.h"
#include "scene.h"
#include "../entities/objects/sphereGenerator.h"


SceneGenerator::SceneGenerator(): SceneGenerator(1.0f) { }

SceneGenerator::SceneGenerator(float frameEndInit) {
  lightStep     = 1.0f;
  lightEnd      = 1.0f;
  frame         = 0.0f;
  frameFirst    = 0.0f;
  frameLast     = frameEndInit;
  ambientStatic = Color(0.1f);
  etherObject   = nullptr;

  //TODO: background static/fn or no backgrounds and let the object act as background

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
  if (etherObject) {
    scene->updateEtherRay(etherObject);
  }


  memcpy(&scene->camera, &camera, sizeof(camera));

  for(auto const& generator: *lightGenerators) {
    auto currentLights = new std::vector<Light*>;
    LightOmniGenerator *lightOmniGenerator = dynamic_cast<LightOmniGenerator*>((LightGenerator*)(generator));
    if (lightOmniGenerator) {
      Light *lightOmnit = lightOmniGenerator->eval(frame);
      for (int i = 0; i < scene->lightVariations; i++) {
        currentLights->push_back(lightOmnit);
      }
      scene->lights->push_back(*currentLights);
      continue;
    }
  }

  for(auto const& generator: *objectGenerators) {
    SphereGenerator *sphereGenerator = dynamic_cast<SphereGenerator*>((ObjectGenerator*)(generator));
    if (sphereGenerator) {
      Object *object = sphereGenerator->eval(frame);
      scene->objects->push_back(object);
      continue;
    }
  }

  return scene;
}

SceneGenerator::~SceneGenerator() {
  delete lightGenerators;
  delete objectGenerators;
  // scene should delete itself, and not generator deleting instanciated scene
}
