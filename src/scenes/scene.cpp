//
// Created by fredy on 13/01/18.
//

#include "scene.h"

void Scene::evaluate(Scene staticScene, float frameInit) {
  frame = frameInit;

  for (auto &light: lights) {
    staticScene.lights.push_back(light.evaluateFn(frame));
  }

  for (auto &object: objects) {
    object.evaluateFn(frame);
    //staticScene.objects.push_back();
  }
}