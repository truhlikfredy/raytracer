/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 13/01/2018
 */

#include "scene.h"
#include "../entities/objects/sphere.h"
#include "../entities/lights/lightOmniGen.h"

Scene::Scene(int nlightsInit, int nobjectsInit): nLights(nlightsInit), nObjects(nobjectsInit) {
  this->lights = new LightOmniGen[nlightsInit];
  this->objects = new SphereGen[nobjectsInit];

  // mem leak, need destructor
};

void Scene::evaluateLights(LightOmni* result, float frame) {
  for (int i = 0; i<nLights; i ++) {
    LightOmni light = lights[i].evaluateFn(frame);
    result[i] = light;
  }
}


void Scene::evaluateObjects(Sphere* result, float frame) {
  for (int i = 0; i<nObjects; i ++) {
    Sphere sphere = objects[i].evaluateFn(frame);
    result[i] = sphere;
  }
}


//  for (auto &object: objects) {
//    if (object.evaluateFn) {
//      Entity* it = &object;
//      Sphere *object = static_cast<Sphere *>(it);
//
//      Sphere result = object->evaluateFn(frame);
//      staticScene->objects.push_back(result);
//    }
//    else {
//      staticScene->objects.push_back(object);
//    }
//  }
//}