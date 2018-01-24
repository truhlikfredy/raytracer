/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 21/01/2018
 */

#include <cmath>
#include "lights.h"


Lights::Lights(): Scene(2, 4) {

  camera = {
    .possition    = Vector3(0.0f, 0.0f,  -20.0f),
    .lookAt       = Vector3(0.0f, 10.0f, 30.0f),
    .apeture      = 0.0f,
    .shutterSpeed = 0.0f
  };

  const materialStatic squares[6] = {
    Materials::green,
    Materials::blue,
    Materials::lightGray,
    Materials::indigo,
    Materials::yellow,
    Materials::red
  };

  lights[0] = LightOmniGen([](float frame) {
    const float lightRotate = (M_PI * frame) / 31;
    Vector3 center(320 * cosf(lightRotate), 10 * (sinf(lightRotate) - 20 ), -20);
    Color color(0.1f, 0.0f, 0.4f);

    return LightOmni(center, color);
  });

  lights[1] = LightOmniGen([](float frame) {
    Vector3 center(80, -50, 100);
    Color color(0.2f, 0.9f, 0.0f);

    return LightOmni(center, color);
  });


  objects[0] = SphereGen([squares](float frame) {
    std::function<materialStatic(Vector3 point, float frame)> materiaFn =
      [squares](Vector3 point, float frame) {
//        uv textureCoord = Sphere::toUv(point);
//        textureCoord.u += frame / 1800.0f;
//        textureCoord.v += frame / 200.0f;
//        Color fractal = renderMandelbrotPixel(-0.0068464412f, -0.80686056f, 0.0160606767f, 0.00782957993f, 1.0f, textureCoord);
//        return materialStatic{
//          .castsShadows = true,
//          .ambient = Color(),
//          .diffuse = fractal,
//          .specular = Color(0.2f),
//          .emission = Color(0.0),
//          .shininess = 5,
//          .reflectivity = 0.0f,
//          .transparency = 0.0f
//        };
        const int x = (((int)point.x+400)/15);
        const int z = (((int)point.z+400)/15);

//        uv a Sphere::toUv(point);

        if ((x % 2) ^ (z % 2)) {
          return squares[(x+z * 6) % 6];
          //return Materials::white;
        }
        else {
          return Materials::mirror;
        }
      };
    return Sphere(Vector3(0.0f, 510.0f, 100.0f), 500.0f, materiaFn);
  });


  objects[1] = SphereGen([](float frame) {
    return Sphere(Vector3(sinf(frame / 8) * 15, sin(frame / 4) * 2 +3, sin(frame / 20) * 15 + 25), 15,
                  [](Vector3 point, float frame) {
                    return Materials::brass;
                  });
  });

  objects[2] = SphereGen([](float frame) {
    return Sphere(Vector3( 15, 25, 10), 15,
                  [](Vector3 point, float frame) {
                    return Materials::green;
                  });
  });

  objects[3] = SphereGen([](float frame) {
    return Sphere(Vector3( -4, 2, 0), 8,
                  [](Vector3 point, float frame) {
                    return Materials::glass;
                  });
  });
}
