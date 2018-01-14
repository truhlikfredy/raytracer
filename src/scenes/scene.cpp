/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 13/01/2018
 */

#include "scene.h"

void Scene::evaluate(Scene staticScene, float frameInit) {
  frame = frameInit;

  for (auto &light: lights) {
    if (light.evaluateFn) {
      staticScene.lights.push_back(light.evaluateFn(frame));
    }
    else {
      staticScene.lights.push_back(light);
    }
  }

  for (auto &object: objects) {
    if (object.evaluateFn) {
      staticScene.objects.push_back((Object)object.evaluateFn(frame));
    }
    else {
      staticScene.objects.push_back(object);
    }
  }
}