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
    .position    = Vector3(0.1f, 0.2f, 0.3f),
    .lookAt      = Vector3(0.0f, 10.0f, 60.0f),
    .aperture    = 0.0f,
    .shutterBlur = 0.3f
  };

  lightEnd = 2.0f;
  lastFrame = 130.0f;

//  auto animatedLight = new LightOmniGenerator(Vector3(32, 0.6, 20), Color(0.9f, 0.9f, 1.0f));
//  auto animatedLight = new LightOmniGenerator([](float frame) {
//    const float lightRotate = (M_PI * frame) / 31;
//    Vector3 center(320 * cosf(lightRotate), 0.6 * 200 * (sinf(lightRotate) - 0.5), 20);
//    Color color(0.5f, 0.5f, 0.9f);
//
//    return new LightOmni(center, color);
//  });
//  lightGenerators->push_back(animatedLight);

  lightGenerators->push_back(new LightOmniGenerator(Vector3(600, -50, 200),Color(0.0f, 0.8f, 0.0f) ));


  objectGenerators->push_back(new SphereGenerator([](float frame) {
    return new Sphere(Vector3(0.0f, 0.0f, 100.0f), 25.0f, Materials::green);
  }));

  objectGenerators->push_back(new SphereGenerator([](float frame) {
    return new Sphere(Vector3(sinf(frame / 8) * 15,
                              sinf(frame / 4) * 2 + 9,
                              sinf(frame / 20) * 45 + 65),
                     10,
                     [](Vector3 point, float frame) {
                        return Materials::red;
                     });
  }));

  std::cout << "Made sceneGenerator 'generated'\r\n";
}

Generated::~Generated() {
  std::cout << "Destroying sceneGenerator 'generated'\r\n";
}
