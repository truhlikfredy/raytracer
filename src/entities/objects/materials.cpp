/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 11/01/2018
 *
 * Predefined materials inspired with values from:
 *
 * https://globe3d.sourceforge.io/g3d_html/gl-materials__ads.htm
 */

#include "materials.h"

materialStatic Materials::red = {
  .castsShadows    = true,
  .ambient         = Color(0.1f, 0.0f, 0.0f),
  .diffuse         = Color(1.0f, 0.0f, 0.0f),
  .specular        = Color(0.0225f),
  .emission        = Color(),
  .shininess       = 12.8f,
  .reflectivity    = 0.0f,
  .transparency    = 0.0f,
  .refractiveIndex = 1.0f
};

materialStatic Materials::yellow = {
  .castsShadows    = true,
  .ambient         = Color(),
  .diffuse         = Color(1.0f,    0.964706f, 0.0f),
  .specular        = Color(0.0225f, 0.0225f,   0.0225f),
  .emission        = Color(),
  .shininess       = 12.8f,
  .reflectivity    = 0.0f,
  .transparency    = 0.0f,
  .refractiveIndex = 1.0f
};

materialStatic Materials::white= {
  .castsShadows    = true,
  .ambient         = Color(),
  .diffuse         = Color(0.992157f, 0.992157f, 0.992157f),
  .specular        = Color(0.0225f,   0.0225f,   0.0225f),
  .emission        = Color(),
  .shininess       = 12.8f,
  .reflectivity    = 0.1f,
  .transparency    = 0.0f,
  .refractiveIndex = 1.0f
};

materialStatic Materials::green= {
  .castsShadows    = true,
  .ambient         = Color(),
  .diffuse         = Color(0.0f,    1.0f,    0.0f),
  .specular        = Color(0.0225f, 0.0225f, 0.0225f),
  .emission        = Color(),
  .shininess       = 12.8f,
  .reflectivity    = 0.5f,
  .transparency    = 0.0f,
  .refractiveIndex = 1.0f
};

materialStatic Materials::indigo= {
  .castsShadows    = true,
  .ambient         = Color(),
  .diffuse         = Color(0.0980392f, 0.0f,    0.458824f),
  .specular        = Color(0.0225f),
  .emission        = Color(),
  .shininess       = 12.8f,
  .reflectivity    = 0.0f,
  .transparency    = 0.0f,
  .refractiveIndex = 1.0f
};

materialStatic Materials::blue= {
  .castsShadows    = true,
  .ambient         = Color(),
  .diffuse         = Color(0.0f,    0.0f,    1.0f),
  .specular        = Color(0.0225f),
  .emission        = Color(),
  .shininess       = 12.8f,
  .reflectivity    = 0.2f,
  .transparency    = 0.0f,
  .refractiveIndex = 1.0f
};

materialStatic Materials::violet= {
  .castsShadows    = true,
  .ambient         = Color(),
  .diffuse         = Color(0.635294f, 0.0f,    1.0f),
  .specular        = Color(0.0225f),
  .emission        = Color(),
  .shininess       = 12.8f,
  .reflectivity    = 0.0f,
  .transparency    = 0.0f,
  .refractiveIndex = 1.0f
};

materialStatic Materials::black= {
  .castsShadows    = true,
  .ambient         = Color(),
  .diffuse         = Color(),
  .specular        = Color(0.0225f),
  .emission        = Color(),
  .shininess       = 12.8f,
  .reflectivity    = 0.0f,
  .transparency    = 0.0f,
  .refractiveIndex = 1.0f
};

materialStatic Materials::mediumGray= {
  .castsShadows    = true,
  .ambient         = Color(),
  .diffuse         = Color(0.454902f),
  .specular        = Color(0.0225f),
  .emission        = Color(),
  .shininess       = 12.8f,
  .reflectivity    = 0.0f,
  .transparency    = 0.0f,
  .refractiveIndex = 1.0f
};

materialStatic Materials::lightGray= {
  .castsShadows    = true,
  .ambient         = Color(),
  .diffuse         = Color(0.682353f),
  .specular        = Color(0.0225f),
  .emission        = Color(),
  .shininess       = 12.8f,
  .reflectivity    = 0.1f,
  .transparency    = 0.0f,
  .refractiveIndex = 1.0f
};

materialStatic Materials::mirror = {
  .castsShadows    = true,
  .ambient         = Color(0.1f),
  .diffuse         = Color(0.1f),
  .specular        = Color(0.8f),
  .emission        = Color(),
  .shininess       = 77.0f,
  .reflectivity    = 0.95f,
  .transparency    = 0.0f,
  .refractiveIndex = 1.0f
};

materialStatic Materials::brass= {
  .castsShadows    = true,
  .ambient         = Color(0.329412f, 0.223529f, 0.027451f),
  .diffuse         = Color(0.780392f, 0.568627f, 0.113725f),
  .specular        = Color(0.992157f, 0.941176f, 0.807843f),
  .emission        = Color(),
  .shininess       = 27.8974f,
  .reflectivity    = 0.8f,
  .transparency    = 0.0f,
  .refractiveIndex = 1.0f
};

materialStatic Materials::pollishedCopper= {
  .castsShadows    = true,
  .ambient         = Color(0.2295f,   0.08825f,  0.0275f),
  .diffuse         = Color(0.5508f,   0.2118f,   0.066f),
  .specular        = Color(0.580594f, 0.223257f, 0.0695701f),
  .emission        = Color(),
  .shininess       = 51.2f,
  .reflectivity    = 0.0f,
  .transparency    = 0.0f,
  .refractiveIndex = 1.0f
};

materialStatic Materials::glass= {
  .castsShadows    = true,
  .ambient         = Color(),
  .diffuse         = Color(0.588235f, 0.670588f, 0.729412f),
  .specular        = Color(0.9f),
  .emission        = Color(),
  .shininess       = 96.0f,
  .reflectivity    = 0.2f,
  .transparency    = 0.95f,
  .refractiveIndex = 1.8f
};

Color Materials::mandelbrot(mandelbrotSet &set, uv &pixel) {
  const int   maxIterations = 255.0f * set.gamma;
  const float x = set.lookAtX - (set.width  / 2) + pixel.u * set.width;
  const float y = set.lookAtY - (set.height / 2) + pixel.v * set.height;

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
