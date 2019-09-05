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
  updateEtherRay(new Sphere(Vector3(), -1.0f, Materials::air));

};


Scene::Scene(): Scene(Color(0.1f)) {
};


Scene::~Scene() {
}


void Scene::updateEtherRay(Object *etherObjectInit) {
  etherObject = etherObjectInit;
  etherRay = new Ray();
  etherRay->inside = etherObject;
  etherRay->hitMaterial = &etherObject->material;
}
