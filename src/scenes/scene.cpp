/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 13/01/2018
 */

#include "scene.h"

Scene::Scene(int nlightsInit, int nobjectsInit, float lastFrameInit):
  nLights(nlightsInit), nObjects(nobjectsInit), lastFrame(lastFrameInit) {

  frame = 0.0f;
  ambient = Color(0.1f);
  this->lights = new LightOmniGen[nlightsInit];
  this->objects = new Sphere[nobjectsInit];
};


Scene::Scene(int nlightsInit, int nobjectsInit): Scene(nlightsInit, nobjectsInit, 0.0f) {
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


void Scene::evaluateObjects(Object* result, float frame) {
  for (int i = 0; i < nObjects; i ++) {
    Entity entity = objects[i].evaluateFn(frame);
    Entity *pEntity = &entity;
    Object *pObject = (Object*) pEntity;
    result[i] = *pObject;
  }
}
