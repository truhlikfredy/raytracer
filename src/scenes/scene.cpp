/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 13/01/2018
 */

#include "scene.h"


Scene::Scene(Color ambientStaticInit) {
  lights = new std::vector<Light*>;  // 2D array of lights
  objects = new std::vector<Object*>;  // 1D array to pointers

  frame = 0.0f;
  ambientStatic = ambientStaticInit;
//  this->lights = new LightOmniGen[nlightsInit];
//  this->objects = new Object[nobjectsInit];
//  this->objects = std::vector<std::shared_ptr<Object>>(nobjectsInit);
//  this->objects = std::vector<std::shared_ptr<Object>>(nobjectsInit);
};

Scene::Scene(): Scene(Color(0.1f)) {
};



Scene::~Scene() {
//  delete[] lights;
//  delete[] objects;
}


//void Scene::evaluateLights(LightOmni* result, float frame) {
//  for (int i = 0; i < nLights; i ++) {
//    LightOmni light = lights[i].evaluateFn(frame);
//    result[i] = light;
//  }
//}


//void Scene::evaluateObjects(std::vector<std::shared_ptr<Object>> result, float frame) {
//  for (int i = 0; i < nObjects; i ++) {
////    Object entity = objects[i].evaluateObjFn(frame);
////    Object *pEntity = &entity;
////    Object *pObject = (Object*) pEntity;
////    result[i] = *pObject;
//
////    result[i] = std::make_shared(objects[i]->evaluateObjFn(frame));
//  }
//}
