/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 11/01/2018
 *
 * Predefined materials inspired with values from:
 *
 * https://globe3d.sourceforge.io/g3d_html/gl-materials__ads.htm
 */

#include "materials.h"

MaterialStatic Materials::red = {
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

MaterialStatic Materials::yellow = {
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

MaterialStatic Materials::white= {
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

MaterialStatic Materials::green= {
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

MaterialStatic Materials::indigo= {
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

MaterialStatic Materials::blue= {
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

MaterialStatic Materials::violet= {
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

MaterialStatic Materials::black= {
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

MaterialStatic Materials::mediumGray= {
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

MaterialStatic Materials::lightGray= {
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

MaterialStatic Materials::mirror = {
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

MaterialStatic Materials::brass= {
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

MaterialStatic Materials::pollishedCopper= {
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

MaterialStatic Materials::glass= {
  .castsShadows    = true,
  .ambient         = Color(),
  .diffuse         = Color(0.588235f, 0.670588f, 0.729412f),
  .specular        = Color(0.9f),
  .emission        = Color(),
  .shininess       = 96.0f,
  .reflectivity    = 0.2f,
  .transparency    = 0.95f,
  .refractiveIndex = 1.5f
};

