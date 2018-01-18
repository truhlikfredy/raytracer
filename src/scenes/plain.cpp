/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 13/01/2018
 */

#include <cmath>
#include "plain.h"
#include "../entities/lights/lightOmni.h"
#include "../entities/objects/sphere.h"

Plain::Plain(): Scene(1, 2) {

  camera = {
    .position     = Vector3(0.0f, 0.0f,  0.0f),
    .lookAt       = Vector3(0.0f, 10.0f, 60.0f),
    .apeture      = 0.0f,
    .shutterSpeed = 2.0f
  };


  lights[0] = LightOmniGen([](float frame) {
    const float lightRotate = (M_PI * frame) / 31;
    Vector3 center(320 * cosf(lightRotate), 0.6 * 200 * (sinf(lightRotate) - 0.5), 20);
    Color color(0.0f, 0.2f, 0.8f);

    return LightOmni(center, color);
  });


  objects[0] = SphereGen([](float frame) {
    std::function<MaterialStatic(Vector3 point, float frame)> materiaFn =
      [](Vector3 point, float frame) {
        return MaterialStatic{
          .ambient = Color(0.0f, 0.025f, 0.0f),
          .diffuse = Color((sinf(point.x / 2 + point.y + point.z + frame / 5) + 0.3) * 0.5,
                           (sinf(point.x / 4 + point.y / 2 + point.z + frame / 10) + 0.4) * 0.7,
                           (sinf(point.x / 8 + point.y + point.z / 4 + frame / 20) + 0.2) * 0.3),
          .specular = Color(0.2f),
          .emission = Color(0.0),
          .shininess = point.z
        };
      };
    return Sphere(Vector3(0.0f, 0.0f, 100.0f), 25.0f, materiaFn);
  });


  objects[1] = SphereGen([](float frame) {
    return Sphere(Vector3(sinf(frame / 8) * 15, sin(frame / 4) * 2 + 9, sin(frame / 20) * 45 + 65), 10,
                  [](Vector3 point, float frame) {
                    return Materials::red;
                  });
  });


}

//    checkerboard attempt
//    if ((int)point.x/5 % 2 ^ (int)point.y/5 % 2 ^ (int)point.z/5 % 2) {
//      return Materials::red;
//    }
//    else {
//      return Materials::mirror;
//    }

