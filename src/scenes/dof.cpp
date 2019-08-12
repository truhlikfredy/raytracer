/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 16/01/2018
 */

#include <cmath>
#include "dof.h"
#include "../entities/objects/sphereGenerator.h"

Dof::Dof(): SceneGenerator(60.0f) {

  camera = {
    .position    = Vector3(0.0f, 0.0f, 0.0f),
    .lookAt      = Vector3(0.0f, 0.0f, 60.0f),
    .aperture    = 8.0f,
    .shutterBlur = 0.0f
  };

  const materialStatic balls[5] = {
    Materials::green,
    Materials::pollishedCopper,
    Materials::brass,
    Materials::white,
    Materials::red
  };

  lightGenerators->push_back(new LightOmniGenerator([](float frame) {
    const float lightRotate = (M_PI * frame) / 31;
    Vector3 center(320 * cosf(lightRotate), 0.6 * 200 * (sinf(lightRotate) - 0.5), 20);
    Color color(0.9f, 0.9f, 1.0f);

    return new LightOmni(center, color);
  }));

  for (int i = 0; i < 5; i++) {
    objectGenerators->push_back(new SphereGenerator([balls, i](float frame) {
      int j = i;
      if (i == 3) j = 2*i;
      if (i == 4) j = 6*i;
      return new Sphere(Vector3(-20 + j*25, 10 - j*10, 30+ j*20), 15,
                    [balls, i](Vector3 point, float frame) {
        return balls[i];
      });
    }));
  }

}
