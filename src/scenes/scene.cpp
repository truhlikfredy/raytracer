/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 13/01/2018
 */

#include "scene.h"


Scene::Scene(Color ambientStaticInit) {
  lights  = new std::vector<std::vector<Light*>>;  // 2D array of lights
  objects = new std::vector<Object*>;  // 1D array to pointers

  frame = 0.0f;
  ambientStatic = ambientStaticInit;
};

Scene::Scene(): Scene(Color(0.1f)) {
};



Scene::~Scene() {
}
