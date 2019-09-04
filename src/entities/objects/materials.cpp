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
  .ambient         = Color(0.1f),
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
  .ambient         = Color(0.02f),
  .diffuse         = Color(0.03f),
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
  .reflectivity    = 0.3f,
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
  .diffuse         = Color(0.0588235f, 0.0670588f, 0.0729412f),
  .specular        = Color(0.9f),
  .emission        = Color(),
  .shininess       = 96.0f,
  .reflectivity    = 0.12f,
  .transparency    = 0.9f,
  .refractiveIndex = 1.52f // http://hyperphysics.phy-astr.gsu.edu/hbase/Tables/indrf.html
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


//blue_marble(float   Ks    = .4, float Kd    = .6, float Ka    = .1, float roughness = .1, float txtscale = 1)  {
//  Color specularcolor(1.0f);
//  Vector3 PP;            /* scaled point in shader space */
//  float csp;           /* color spline parameter */
//  Vector3 Nf;            /* forward-facing normal */
//  Vector3 V;             /* for specular() */
//  float pixelsize, twice, scale, weight, turbulence;
//
///* Obtain a forward-facing normal for lighting calculations. */
//Nf = faceforward( normalize(N), I);
//V = normalize(-I);
//
///*
// * Compute "turbulence" a la [PERLIN85]. Turbulence is a sum of
// * "noise" components with a "fractal" 1/f power spectrum. It gives the
// * visual impression of turbulent fluid flow (for example, as in the
// * formation of blue_marble from molten color splines!). Use the
// * surface element area in texture space to control the number of
// * noise components so that the frequency content is appropriate
// * to the scale. This prevents aliasing of the texture.
// */
//PP = transform("shader", P) * txtscale;
//pixelsize = sqrt(area(PP));
//twice = 2 * pixelsize;
//turbulence = 0;
//for (scale = 1; scale > twice; scale /= 2)
//turbulence += scale * noise(PP/scale);
//
///* Gradual fade out of highest-frequency component near limit */
//if (scale > pixelsize) {
//weight = (scale / pixelsize) - 1;
//weight = clamp(weight, 0, 1);
//turbulence += weight * scale * noise(PP/scale);
//}
//
///*
// * Magnify the upper part of the turbulence range 0.75:1
// * to fill the range 0:1 and use it as the parameter of
// * a color spline through various shades of blue.
// */
//csp = clamp(4 * turbulence - 3, 0, 1);
//Ci = color spline(csp,
//  color (0.25, 0.25, 0.35),      /* pale blue        */
//  color (0.25, 0.25, 0.35),  /* pale blue        */
//  color (0.20, 0.20, 0.30),  /* medium blue      */
//  color (0.20, 0.20, 0.30),  /* medium blue      */
//  color (0.20, 0.20, 0.30),  /* medium blue      */
//  color (0.25, 0.25, 0.35),  /* pale blue        */
//  color (0.25, 0.25, 0.35),  /* pale blue        */
//  color (0.15, 0.15, 0.26),  /* medium dark blue */
//  color (0.15, 0.15, 0.26),  /* medium dark blue */
//  color (0.10, 0.10, 0.20),  /* dark blue        */
//  color (0.10, 0.10, 0.20),  /* dark blue        */
//  color (0.25, 0.25, 0.35),  /* pale blue        */
//  color (0.10, 0.10, 0.20)   /* dark blue        */
//);
//
///* Multiply this color by the diffusely reflected light. */
//Ci *= Ka*ambientStatic() + Kd*diffuse(Nf);
//
///* Adjust for opacity. */
//Oi = Os;
//Ci = Ci * Oi;
//
///* Add in specular highlights. */
//Ci += specularcolor * Ks * specular(Nf,V,roughness);
//}