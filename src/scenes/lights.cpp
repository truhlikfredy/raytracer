///*
// * author: Anton Krug anton.krug@gmail.com
// * date: 21/01/2018
// */
//
//#include <cmath>
//#include "lights.h"
//
////#define LIGHTS_SMALL_BALL
//
//Lights::Lights(): Scene(2, 1, 120.0f) {
//
//  camera = {
//    .position    = Vector3(0.0f, 0.0f, -15.0f),
//    .lookAt       = Vector3(0.0f, 10.0f, 30.0f),
//    .aperture      = 0.0f,
//    .shutterBlur  = 0.0f
//  };
//
//  const materialStatic squares[6] = {
//    Materials::green,
//    Materials::blue,
//    Materials::lightGray,
//    Materials::indigo,
//    Materials::yellow,
//    Materials::red
//  };
//
//  lights[0] = LightOmniGen([](float frame) {
//    const float lightRotate = (M_PI * frame) / 31;
//    Vector3 center(320 * cosf(lightRotate), 10 * (sinf(lightRotate) - 20 ), -20);
//    Color color(0.9f, 0.1f, 0.9f);
//
//    return LightOmni(center, color);
//  });
//
//  lights[1] = LightOmniGen([](float frame) {
//    Vector3 center(80, -50, 100);
//    Color color(0.2f, 0.9f, 0.0f);
//
//    return LightOmni(center, color);
//  });
//
//  Sphere first([squares](float frame) {
//    std::function<materialStatic(Vector3 point, float frame)> materiaFn =
//      [squares](Vector3 point, float frame) {
//        const int x = (((int)point.x+400)/15);
//        const int z = (((int)point.z+400)/15);
//
//        if ((x % 2) ^ (z % 2)) {
//          return squares[(x+z * 6) % 6];
//        }
//        else {
//          return Materials::mirror;
//        }
//      };
//    return Sphere(Vector3(0.0f, 2520.0f, 100.0f), 2500.0f, materiaFn);
//  });
//
//  objects[0] = std::make_shared<Sphere>([squares](float frame) {
//    std::function<materialStatic(Vector3 point, float frame)> materiaFn =
//      [squares](Vector3 point, float frame) {
//        const int x = (((int)point.x+400)/15);
//        const int z = (((int)point.z+400)/15);
//
//        if ((x % 2) ^ (z % 2)) {
//          return squares[(x+z * 6) % 6];
//        }
//        else {
//          return Materials::mirror;
//        }
//      };
//    return Sphere(Vector3(0.0f, 2520.0f, 100.0f), 2500.0f, materiaFn);
//  });
//
////  objects[1] = Sphere([](float frame) {
////#ifdef LIGHTS_SMALL_BALL
////    return Sphere(Vector3(sinf(frame / 8)  * 15,
////                          sinf(frame / 4)  * 2  + 3,
////                          sinf(frame / 20) * 15 + 16),
////                  2,
////                  [](Vector3 point, float frame) {
////                    return Materials::brass;
////                  });
////#else
////    return Sphere(Vector3(sinf(frame / 8)  * 15,
////                          sinf(frame / 4)  * 2  + 3,
////                          sinf(frame / 20) * 15 + 25),
////                  15,
////                  [](Vector3 point, float frame) {
////                    return Materials::brass;
////                  });
////#endif
////  });
////
////  objects[2] = Sphere([](float frame) {
////    return Sphere(Vector3( 15, 25, 10), 15,
////                  [](Vector3 point, float frame) {
////                    return Materials::green;
////                  });
////  });
////
////  objects[3] = Sphere([](float frame) {
////#ifdef LIGHTS_SMALL_BALL
////    return Sphere(Vector3( -4, 2, -2), 10,
////                  [](Vector3 point, float frame) {
////                    return Materials::glass;
////                  });
////#else
////    return Sphere(Vector3( -4, 2, 0), 8,
////                  [](Vector3 point, float frame) {
////                    return Materials::glass;
////                  });
////#endif
////  });
//
//}
