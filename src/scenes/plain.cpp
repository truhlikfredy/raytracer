//
// Created by fredy on 13/01/18.
//


#include <cmath>
#include "plain.h"
#include "../entities/lights/omni.h"
#include "../entities/objects/sphere.h"

Plain::Plain(): Scene() {
  LightOmni light1([](float frame) {
    const float lightRotate = (M_PI * frame) / 11;
    Vector3 center(320  * cosf(lightRotate), 0.6*200 * (sinf(lightRotate)-0.5), 20);
    Color   color(0.0f,0.7f,0.0f);

    return LightOmni(center, color);
  });

  lights.push_back(light1);

  Sphere sphere = Sphere([](float frame) {
    Sphere ret = Sphere(Vector3(0.0f, 0.0f, 100.0f), 25.0f, [](Vector3 point, float frame) {
      return MaterialStatic{
        .ambient = Color(0.0f, 0.0f, 0.0f),
        .diffuse = Color((sinf(point.x/2+point.y+point.z + frame/5)+0.2)*0.5),
        .specular = Color(0.2f),
        .emission = Color(0.0),
        .shininess = point.z
      };
    });

    return ret;
   //return nullptr;
  });

//    , 25, [](Vector3 point, float frame) {
//    if ((int)point.x/5 % 2 ^ (int)point.y/5 % 2 ^ (int)point.z/5 % 2) {
//      return Materials::red;
//    }
//    else {
//      return Materials::mirror;
//    }
//  });

}



