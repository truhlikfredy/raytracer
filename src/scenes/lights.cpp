/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 21/01/2018
 */

#include <cmath>
#include "lights.h"


Lights::Lights(): Scene(2, 2) {

  camera = {
    .possition    = Vector3(0.0f, 0.0f,  0.0f),
    .lookAt       = Vector3(0.0f, 10.0f, 60.0f),
    .apeture      = 0.0f,
    .shutterSpeed = 0.5f
  };


  lights[0] = LightOmniGen([](float frame) {
    const float lightRotate = (M_PI * frame) / 31;
    Vector3 center(320 * cosf(lightRotate), 10 * (sinf(lightRotate) - 20 ), 20);
    Color color(0.1f, 0.0f, 0.7f);

    return LightOmni(center, color);
  });

  lights[1] = LightOmniGen([](float frame) {
    Vector3 center(300, -50, 200);
    Color color(0.0f, 0.8f, 0.0f);

    return LightOmni(center, color);
  });


  objects[0] = SphereGen([](float frame) {
    std::function<MaterialStatic(Vector3 point, float frame)> materiaFn =
      [](Vector3 point, float frame) {
      if (((((int)point.x+400)/15) % 2) ^ (((int)point.z+400)/15) % 2) {
        return Materials::white;
      }
      else {
        return Materials::mirror;
      }

//        return Materials::white;
      };
    return Sphere(Vector3(0.0f, 510.0f, 100.0f), 500.0f, materiaFn);
  });


  objects[1] = SphereGen([](float frame) {
    return Sphere(Vector3(sinf(frame / 8) * 15, sin(frame / 4) * 2 + 9, sin(frame / 20) * 15 + 25), 10,
                  [](Vector3 point, float frame) {
                    return Materials::red;
                  });
  });


}
