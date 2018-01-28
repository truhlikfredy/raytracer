/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 16/01/2018
 */

#include <cmath>
#include "dof.h"

Dof::Dof(): Scene(1, 5) {

  camera = {
    .possition     = Vector3(0.0f, 0.0f,  0.0f),
    .lookAt       = Vector3(0.0f, 0.0f, 60.0f),
    .apeture      = 8.0f,
    .shutterSpeed = 0.0f
  };

  const materialStatic balls[5] = {
    Materials::green,
    Materials::pollishedCopper,
    Materials::brass,
    Materials::white,
    Materials::red
  };

  lights[0] = LightOmniGen([](float frame) {
    const float lightRotate = (M_PI * frame) / 31;
    Vector3 center(320 * cosf(lightRotate), 0.6 * 200 * (sinf(lightRotate) - 0.5), 20);
    Color color(0.9f, 0.9f, 1.0f);

    return LightOmni(center, color);
  });

  for (int i = 0; i < 5; i++) {
    objects[i] = SphereGen([balls, i](float frame) {
      int j = i;
      if (i == 3) j = 2*i;
      if (i == 4) j = 6*i;
      return Sphere(Vector3(-20 + j*25, 10 - j*10, 30+ j*20), 15,
                    [balls, i](Vector3 point, float frame) {
                      return balls[i];
                    });
    });
  }

}
