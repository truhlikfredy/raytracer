/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 13/01/2018
 */

#include <cmath>
#include "plain.h"


Plain::Plain(): Scene(2, 2, 130.0f) {

  camera = {
    .possition    = Vector3(0.0f, 0.0f,  -170.0f),
    .lookAt       = Vector3(0.0f, 0.0f, 60.0f),
    .apeture      = 0.0f,
    .shutterBlur  = 0.9f
  };

  lights[0] = LightOmniGen([](float frame) {
    const float lightRotate = (M_PI * frame) / 31;
    Vector3 center(60 * cosf(lightRotate), 0.6 * 50 * (sinf(lightRotate) - 0.5), 30);
    Color color(0.9f, 0.9f, 0.9f);

    return LightOmni(center, color);
  });

  lights[1] = LightOmniGen([](float frame) {
    Vector3 center(300, -50, 200);
    Color color(0.4f, 0.8f, 0.9f);

    return LightOmni(center, color);
  });


  objects[0] = SphereGen([](float frame) {
    std::function<materialStatic(Vector3 point, float frame)> materiaFn =
      [](Vector3 point, float frame) {
        return materialStatic{
          .castsShadows = true,
          .ambient = Color(0.4f),
          .diffuse = Color(0.7f),
          .specular = Color(1.0f),
          .emission = Color(0.0),
          .shininess = point.z,
          .reflectivity = 0.5f,
          .transparency = 0.0f
        };
      };
    return Sphere(Vector3(0.0f, 0.0f, 100.0f), 55.0f, materiaFn);
  });


  objects[1] = SphereGen([](float frame) {
    return Sphere(Vector3(sinf(frame / 3) * 45,
                          sinf(frame / 4) * 2 + 9,
                          sinf(frame / 20) * 0.1f + 35),
                  10,
                  [](Vector3 point, float frame) {
                    return Materials::pollishedCopper;
                  });
  });


}