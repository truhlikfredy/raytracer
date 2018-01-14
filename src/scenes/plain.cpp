/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 13/01/2018
 */

#include <cmath>
#include "plain.h"
#include "../entities/lights/omni.h"
#include "../entities/objects/sphere.h"

Plain::Plain(): Scene(1, 1) {


//  lights.push_back(Entity([](float frame) {
//    const float lightRotate = (M_PI * frame) / 11;
//    Vector3 center(320  * cosf(lightRotate), 0.6*200 * (sinf(lightRotate)-0.5), 20);
//    Color   color(0.0f,0.7f,0.0f);
//
//    return LightOmni(center, color);
//  }));

  objects[0] =  SphereGen([](float frame) {

    std::function<MaterialStatic(Vector3 point, float frame)> materiaFn =
      [](Vector3 point, float frame) {
        return Materials::red;
      };


    Sphere sphere(Vector3(0.0f, 0.0f, 100.0f), 25.0f, materiaFn);

    return sphere;

//    return Sphere(Vector3(0.0f, 0.0f, 100.0f), 25.0f, [](Vector3 point, float frame) {
//      return MaterialStatic{
//        .ambient = Color(0.0f, 0.0f, 0.0f),
//        .diffuse = Color((sinf(point.x/2+point.y+point.z + frame/5)+0.2)*0.5),
//        .specular = Color(0.2f),
//        .emission = Color(0.0),
//        .shininess = point.z
//      };
//    });

  });

//    checkerboard attempt
//    if ((int)point.x/5 % 2 ^ (int)point.y/5 % 2 ^ (int)point.z/5 % 2) {
//      return Materials::red;
//    }
//    else {
//      return Materials::mirror;
//    }

//    });
//  }));

//  objects.push_back(Sphere(Vector3(15, 10, 60), 7, [](Vector3 point, float frame) {
//    return Materials::mirror;
//  }));

}



