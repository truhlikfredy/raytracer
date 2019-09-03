/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 24/01/2018
 */

#include <cmath>
#include "large.h"
#include "../entities/objects/sphereGenerator.h"
#include "../render/sampler.h"

#define BALLS 6

Large::Large():SceneGenerator(20.0f) {

  camera = {
    .position    = Vector3(0.0f, 0.0f, -80.0f),
    .lookAt      = Vector3(0.0f, 10.0f, 30.0f),
    .aperture    = 0.0f,
    .shutterBlur = 0.0f
  };

  const materialStatic squares[6] = {
    Materials::green,
    Materials::blue,
    Materials::lightGray,
    Materials::indigo,
    Materials::yellow,
    Materials::red
  };

  lightGenerators->push_back(new LightOmniGenerator([](float frame) {
    const float lightRotate = (M_PI * frame) / 11;
    Vector3 center(3 * cosf(lightRotate)+7, 2 * (sinf(lightRotate) - 10 ), -40);
    Color color(0.0f, 0.1f, 1.1f);

    return new LightOmni(center, color, 400.0f, 0.8f);
  }));

  lightGenerators->push_back(new LightOmniGenerator([](float frame) {
    const float lightRotate = (M_PI * frame) / 11;
    Vector3 center(3 * cosf(lightRotate*1.7)+6, 2 * (sinf(lightRotate*1.7) - 12 ), -40);
    Color color(1.1f, 0.0f, 0.1f);

    return new LightOmni(center, color, 400.0f, 0.8f);
  }));

  lightGenerators->push_back(new LightOmniGenerator([](float frame) {
    const float lightRotate = (M_PI * frame) / 11;
    Vector3 center(3 * cosf(lightRotate*2.5)-7, 2 * (sinf(lightRotate*2.5) - 10 ), -40);
    Color color(0.1f, 1.1f, 0.0f);

    return new LightOmni(center, color, 400.0f, 0.8f);
  }));

  objectGenerators->push_back(new SphereGenerator([squares](float frame) {
    Sphere *sphere = new Sphere(Vector3(0.0f, 200.0f, 600.0f), 500.0f);

    auto materialFn = new std::function<materialStatic(Vector3 point, float frame)>(
      [sphere](Vector3 point, float frame) mutable {
        //return Materials::white;
        const int x = (((int)point.x+400)/30);
        const int y = (((int)point.y+400)/30);

        mandelbrotSet set = {-0.0068464412f, -0.80686056f, 0.0160606767f*2, 0.00782957993f*2, 1.0f };
        uv textureCoord = sphere->toUv(point);
        textureCoord.u += frame / 1800.0f;
        textureCoord.v += frame / 200.0f;

        Color fractal =  Materials::mandelbrot(set, textureCoord);
        float reflect = 0.0f;
        if (fractal.x == 0) {
          reflect = 0.95f;
        }

        return materialStatic{
          .castsShadows = true,
          .ambient      = fractal / 7,
          .diffuse      = fractal,
          .specular     = Color(0.2f),
          .emission     = Color(0.0),
          .shininess    = 85,
          .reflectivity = 0.0f,
          .transparency = 0.0f
        };
      });
    sphere->materialFn = *materialFn;
    return sphere;
  }));


  objectGenerators->push_back(new SphereGenerator([](float frame) {
    Sphere *sphere = new Sphere(Vector3(35.0f, 35.0f, 15.0f), 20.0f, Materials::red);

    auto materiaFn = new std::function<materialStatic(Vector3 point, float frame)>(
      [sphere](Vector3 point, float frame) mutable {
        uv a = sphere->toUv(point);
        a.u += 1100;
        a.v += 1100;
        a.v += 0.06;

        if (((int)(a.u*8) % 2) ^ ((int)(a.v*8) % 2)) {
          return Materials::glass;
        } else {
          return Materials::mirror;
        }
      });
    sphere->materialFn = *materiaFn;
    return sphere;
  }));

  for (int i=0; i < BALLS; i++) {
    sample2D sample;

    Sampler::vanDerCoruptSobol2(i, 0, sample);
    float index = Sampler::vanDerCorput(i, 0);

    objectGenerators->push_back(new SphereGenerator([sample, index, i](float frame) {
      return new Sphere(Vector3( -40 + sample.x * 80, -30 + 60* sample.y, (i% 3)* 7 -0), 8,
                    [index](Vector3 point, float frame) {
                      materialStatic ret = Materials::glass;
                      ret.refractiveIndex = 1 + index;
                      return ret;
                    });
    }));
  }

}