/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 28/01/2018
 */

#include <cmath>
#include "large2.h"
#include "../render/sampler.h"
#include "../utils/utils.h"
#include "../entities/objects/sphereGenerator.h"

#define BALLS 20
#define BALL_MATERIALS 13

Large2::Large2():SceneGenerator(25.0f) {

  camera = {
    .position    = Vector3(0.0f, 0.0f, -80.0f),
    .lookAt      = Vector3(0.0f, 10.0f, 30.0f),
    .aperture    = 0.0f,
    .shutterBlur = 0.0f
  };

  const materialStatic materials[BALL_MATERIALS] = {
    Materials::green,
    Materials::mirror,
    Materials::blue,
    Materials::lightGray,
    Materials::indigo,
    Materials::yellow,
    Materials::red,
    Materials::glass,
    Materials::violet,
    Materials::black,
    Materials::pollishedCopper,
    Materials::mirror,
    Materials::white
  };

  lightGenerators->push_back(new LightOmniGenerator([](float frame) {
    const float lightRotate = (M_PI_F * frame) / 11;
    Vector3 center(25.0f * cosf(lightRotate)+7, 15.0f * (sinf(lightRotate*2) - 2.0f ), 50.0f);
    Color color(0.8f, 0.8f, 0.95f);

    return new LightOmni(center, color);
  }));

  objectGenerators->push_back(new SphereGenerator([materials](float frame) {
    Sphere *sphere = new Sphere(Vector3(0.0f, 0.0f, 6000.0f), 5900.0f, Materials::green);

    auto materialFn = new std::function<materialStatic(Vector3 point, float frame)>(
    [sphere](Vector3 point, float frame) mutable {
        uv points = sphere->toUv(point);

        if (((int)(points.u*1000) % 2) ^ ((int)(points.v*1000) % 2)) {
          return Materials::red;
        } else {
          return Materials::yellow;
        }
    });
    sphere->materialFn = *materialFn;
    return sphere;
  }));


  for (int i=0; i < BALLS; i++) {
    sample2D sample;

    Sampler::vanDerCoruptSobol2(i, 0, sample);
    float index = Sampler::foldedRadicalInverse(i, 2);

    objectGenerators->push_back(new SphereGenerator(
      [sample, materials, index, i](float frame) {
        return new Sphere(Vector3( -80 + ((float)i / BALLS) * 160, -40 + 120* sample.y, 93), 7+3*(i%3),
                          [index, i, materials](Vector3 point, float frame) {

          materialStatic ret = materials[i % BALL_MATERIALS];
          ret.refractiveIndex = 1 + index;
          return ret;
        });
      }
    ));
  }

  for (int x = 0; x < 3; x ++) {
    for (int y = 0; y < 2; y++) {
      const int index = (x + y * 3);
      objectGenerators->push_back(new SphereGenerator([x, y, index](float frame) {
        return new Sphere(Vector3(x * 40 - 40, -5.0f + 40 * y, 15.0f + (index % 2) * 15), 19.0f,
                          [index](Vector3 point, float frame) mutable {
          if (index % 2) {
            return Materials::mirror;
          } else {
            return Materials::glass;
          }
        });
      }));
    }
  }

}