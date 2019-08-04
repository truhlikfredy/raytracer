//
// Created by fredy on 04/08/2019.
//

#include <cmath>
#include <iostream>
#include "../entities/lights/lightOmniGenerator.h"
#include "generated.h"
#include "../entities/objects/sphereGenerator.h"

Generated::Generated(): SceneGenerator() {
  camera = {
    .position    = Vector3(0.2f, 1.0f, 0.3f),
    .lookAt      = Vector3(0.0f, 0.0f, 60.0f),
    .aperture    = 8.0f,
    .shutterBlur = 0.0f
  };

  auto onlyLight = new LightOmniGenerator(Vector3(32, 0.6, 20), Color(0.9f, 0.9f, 1.0f));
  lightGenerators->push_back(onlyLight);

  auto sphere = new SphereGenerator(Vector3(), 10.0f);
  objectGenerators->push_back(sphere);
  std::cout << "Made\r\n";
}

Generated::~Generated() {
  std::cout << "Destroying\r\n";
}
