/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 21/01/2018
 */

#include <cmath>
#include "lights.h"

Color renderMandelbrotPixel(float lookAtX, float lookAtY, float width, float height, float gamma, uv pixel) {
  const int   maxIterations = 255.0f * gamma;
  const float x = lookAtX - (width  / 2) + pixel.u * width;
  const float y = lookAtY - (height / 2) + pixel.v * height;

  float u  = 0.0f;
  float v  = 0.0f;
  float u2 = 0.0f;
  float v2 = 0.0f;
  int iterations;

  for (iterations = 0 ; iterations < maxIterations && ( u2+v2 < 4.0f); iterations++) {
    v  = 2 * (u*v) + y;
    u  = (u2) - (v2) +x;
    u2 = u * u;
    v2 = v * v;
  }

  Color ret;

  if (iterations == maxIterations) {
    ret = Color(0.0f, 0.0f, 0.0f);
  } else if (iterations < 16) {
    ret = Color(iterations * 0.04, 0.0f, 0.0f);
  } else if (iterations < 32) {
    ret = Color(((iterations - 32) * 0.01f)  + 0.5f, 0.0f, 0.0f);
  } else if (iterations < 64) {
    ret = Color((((iterations - 64) * 0.2f) / 8) + 0.7f, 0.0f, 0.0f);
  } else if (iterations < 128) {
    ret = Color(0.5, (((iterations - 128) * 62) / 255) + 0.5f, iterations / 255.0f);
  } else {
    ret = Color(1.0f, 1.0f, (255-iterations) / 255.0f );
  }

  return ret;
}



Lights::Lights(): Scene(2, 4) {

  camera = {
    .possition    = Vector3(0.0f, 0.0f,  -20.0f),
    .lookAt       = Vector3(0.0f, 10.0f, 30.0f),
    .apeture      = 0.0f,
    .shutterSpeed = 0.0f
  };

  const MaterialStatic squares[6] = {
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
    std::function<MaterialStatic(Vector3 point, float frame)> materiaFn =
      [squares](Vector3 point, float frame) {
//        uv textureCoord = Sphere::toUv(point);
//        textureCoord.u += frame / 1800.0f;
//        textureCoord.v += frame / 200.0f;
//        Color fractal = renderMandelbrotPixel(-0.0068464412f, -0.80686056f, 0.0160606767f, 0.00782957993f, 1.0f, textureCoord);
//        return MaterialStatic{
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
