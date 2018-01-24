/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 24/01/2018
 */

#include <cmath>
#include "large.h"
#include "../render/sampler.h"

#define BALLS 20

Large::Large():Scene(1, BALLS +1) {

  camera = {
    .possition    = Vector3(0.0f, 0.0f,  -50.0f),
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
    const float lightRotate = (M_PI * frame) / 11;
    Vector3 center(3 * cosf(lightRotate), 2 * (sinf(lightRotate) - 20 ), 0);
    Color color(0.1f, 0.0f, 0.4f);

    return LightOmni(center, color);
  });

  objects[0] = SphereGen([squares](float frame) {
    std::function<materialStatic(Vector3 point, float frame)> materiaFn =
      [squares](Vector3 point, float frame) {
        const int x = (((int)point.x+400)/30);
        const int y = (((int)point.y+400)/30);

        mandelbrotSet set = {-0.0068464412f, -0.80686056f, 0.0160606767f, 0.00782957993f, 1.0f };
        uv textureCoord = Sphere::toUv(point);
        textureCoord.u += frame / 1800.0f;
        textureCoord.v += frame / 200.0f;

        Color fractal =  Materials::mandelbrot(set, textureCoord);
        float reflect = 0.0f;
        if (fractal.x == 0) {
          reflect = 0.95f;
        }

        return materialStatic{
          .castsShadows = true,
          .ambient = fractal / 10,
          .diffuse = fractal,
          .specular = Color(0.2f),
          .emission = Color(0.0),
          .shininess = 5,
          .reflectivity = 1.0f-fractal.x,
          .transparency = 0.0f
        };

//        uv a Sphere::toUv(point);
//
//        if ((x % 2) ^ (y % 2)) {
//          return squares[(x+y * 6) % 6];
//          //return Materials::white;
//        }
//        else {
//          return Materials::mirror;
//        }
      };
    return Sphere(Vector3(0.0f, 200.0f, 600.0f), 500.0f, materiaFn);
  });

  for (int i=1; i <= BALLS; i++) {
    sample2D sample;

    Sampler::vanDerCoruptSobol2(i, 0, sample);
    float index = Sampler::vanDerCorput(i, 0);
    objects[i] = SphereGen([sample, index, i](float frame) {
      return Sphere(Vector3( -60 + sample.x * 120, -40 + 80* sample.y, (i% 5)* 7 +9), 8,
                    [index](Vector3 point, float frame) {
                      materialStatic ret = Materials::glass;
                      ret.refractiveIndex = 1 + index;
                      return ret;
                    });
    });
  }



}