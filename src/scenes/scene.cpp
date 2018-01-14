/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 13/01/2018
 */

#include "scene.h"
#include "../entities/objects/sphere.h"

void Scene::evaluate(Scene *staticScene, float frameInit) {
  frame = frameInit;

  for (auto &light: lights) {
    if (light.evaluateFn) {
      staticScene->lights.push_back(light.evaluateFn(frame));
    }
    else {
      staticScene->lights.push_back(light);
    }
  }

  for (auto &object: objects) {
    if (object.evaluateFn) {
      Entity* it = &object;
      Sphere *object = static_cast<Sphere *>(it);

      Sphere result = object->evaluateFn(frame);
      staticScene->objects.push_back(result);
    }
    else {
      staticScene->objects.push_back(object);
    }
  }
}