/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 17/01/2018
 */

#include <cmath>
#include "mandelbrot.h"
#include "../entities/objects/sphereGenerator.h"


Mandelbrot::Mandelbrot(): SceneGenerator(40.0f) {

  camera = {
    .position    = Vector3(0.0f, 0.0f, 35.0f),
    .lookAt      = Vector3(0.0f,0.0f,60.0f),
    .aperture    = 0.0f,
    .shutterBlur = 0.0f
  };

  lightGenerators->push_back(new LightOmniGenerator([](float frame) {
    const float lightRotate = (M_PI * frame) / 31;
    Vector3 center(320 * cosf(lightRotate), 0.6 * 200 * (sinf(lightRotate) - 0.5), -100);
    Color color(0.7f, 0.95f, 0.8f);

    return new LightOmni(center, color);
  }));

  objectGenerators->push_back( new SphereGenerator([this](float frame) {
    Sphere *sphere = new Sphere(Vector3(0.0f, 0.0f, 100.0f), 57.0f);

    auto materialFn = new std::function<materialStatic(Vector3 point, float frame)>(
    [sphere](Vector3 point, float frame) mutable {
      mandelbrotSet set = {-0.0068464412f, -0.80686056f, 0.0160606767f * 2, 0.00782957993f *2, 1.0f };
      uv textureCoord = sphere->toUv(point);
      textureCoord.u += frame / 1800.0f;
      textureCoord.v += frame / 200.0f;

      Color fractal =  Materials::mandelbrot(set, textureCoord);
      Color glow(0.0f);
      if (fractal.x == 0) {
        glow = Color(0.05f);
      }

      return materialStatic{
        .castsShadows = true,
        .ambient      = glow,
        .diffuse      = fractal,
        .specular     = Color(0.2f),
        .emission     = Color(0.0),
        .shininess    = 5,
        .reflectivity = 0.0f,
        .transparency = 0.0f
      };
    });

    sphere->materialFn = *materialFn;
    return sphere;
  }));

}

