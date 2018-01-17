/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 17/01/2018
 */

#include <cmath>
#include "mandelbrot.h"

Color Mandelbrot::renderMandelbrotPixel(float lookAtX, float lookAtY, float width, float height, float gamma, uv pixel) {
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


Mandelbrot::Mandelbrot(): Scene(1, 1) {

  lights[0] = LightOmniGen([](float frame) {
    const float lightRotate = (M_PI * frame) / 31;
    Vector3 center(320 * cosf(lightRotate), 0.6 * 200 * (sinf(lightRotate) - 0.5), -100);
    Color color(0.0f, 0.8f, 0.3f);

    return LightOmni(center, color);
  });


  objects[0] = SphereGen([this](float frame) {
    std::function<MaterialStatic(Vector3 point, float frame)> materiaFn =
    [this](Vector3 point, float frame) {
      uv textureCoord = Sphere::toUv(~point);
      textureCoord.u += frame / 1800.0f;
      textureCoord.v += frame / 200.0f;

      Color fractal = renderMandelbrotPixel(-0.0068464412f, -0.80686056f, 0.0160606767f, 0.00782957993f, 1.0f, textureCoord);
      Color glow(0.0f);
      if (fractal.x == 0) {
        glow = Color(0.03f);
      }

      return MaterialStatic{
        .ambient = glow,
        .diffuse = fractal,
        .specular = Color(0.2f),
        .emission = Color(0.0),
        .shininess = 5
      };
    };
    return Sphere(Vector3(0.0f, 0.0f, 100.0f), 60.0f, materiaFn);
  });


}

