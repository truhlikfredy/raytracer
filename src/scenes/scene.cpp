/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 13/01/2018
 */

#include "scene.h"

Scene::Scene(int nlightsInit, int nobjectsInit): nLights(nlightsInit), nObjects(nobjectsInit) {
  frame = 0.0f;
  this->lights = new LightOmniGen[nlightsInit];
  this->objects = new SphereGen[nobjectsInit];
};

Scene::~Scene() {
//  delete[] lights;
//  delete[] objects;
}

void Scene::evaluateLights(LightOmni* result, float frame) {
  for (int i = 0; i < nLights; i ++) {
    LightOmni light = lights[i].evaluateFn(frame);
    result[i] = light;
  }
}


void Scene::evaluateObjects(Sphere* result, float frame) {
  for (int i = 0; i < nObjects; i ++) {
    Sphere sphere = objects[i].evaluateFn(frame);
    result[i] = sphere;
  }
}
