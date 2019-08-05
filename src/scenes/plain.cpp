//
// Created by fredy on 04/08/2019.
//

#include <cmath>
#include "../entities/lights/lightOmniGenerator.h"
#include "../entities/objects/sphereGenerator.h"
#include "plain.h"

Plain::Plain(): SceneGenerator() {
  camera = {
    .position    = Vector3(0.1f, 0.2f, 0.3f),
    .lookAt      = Vector3(0.0f, 10.0f, 60.0f),
    .aperture    = 0.0f,
    .shutterBlur = 0.5f
  };

  frameFirst = 760.0f;
  frame = frameFirst;
  frameLast = frameFirst + 430.0f;
  lightEnd = 1.0f; // how many light positions to iterate, how detailed the area lights and soft shadows are

  auto animatedLight = new LightOmniGenerator([](float frame) {
    const float lightRotate = (M_PI * frame) / 31;
    Vector3 center(320 * cosf(lightRotate), 0.6 * 200 * (sinf(lightRotate) - 0.5), 20);
    Color color(0.5f, 0.5f, 0.9f);

    return new LightOmni(center, color);
  });
  lightGenerators->push_back(animatedLight);

  lightGenerators->push_back(new LightOmniGenerator(Vector3(100, -50, 200),Color(0.0f, 0.8f, 0.0f) ));


  objectGenerators->push_back(new SphereGenerator([](float frame) {
    std::function<materialStatic(Vector3 point, float frame)> materialFn =
      [](Vector3 point, float frame) {
        return materialStatic{
          .castsShadows = true,
          .ambient = Color(0.1f, 0.025f, 0.1f),
          .diffuse = Color((sinf(point.x / 2 + point.y     + point.z     + frame / 5)  + 0.3f) * 0.5f,
                           (sinf(point.x / 4 + point.y / 2 + point.z     + frame / 10) + 0.4f) * 0.7f,
                           (sinf(point.x / 8 + point.y     + point.z / 4 + frame / 20) + 0.2f) * 0.3f),
          .specular = Color(0.2f),
          .emission = Color(0.0),
          .shininess = point.z,
          .reflectivity = 0.55f,
          .transparency = 0.0f
        };
      };
    return new Sphere(Vector3(0.0f, 0.0f, 100.0f), 25.0f, materialFn);
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
}
