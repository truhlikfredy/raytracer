/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "object.h"

class Sphere: public Object {

public:
  float   radius;

  // Sphere(std::function<Sphere(float frame)> propertiesFnInit);

  // Sphere(Vector3 centerInit, float radiusInit, std::function<Sphere(float frame)> propertiesFnInit);

  Sphere(Vector3 centerInt, float radiusInit, std::function<MaterialStatic(Vector3 point, float frame)> materialFnInit);

  Sphere();

  bool detectHit(Ray ray, Vector3 &hitPoint);

  Vector3 operator ^ (Vector3 pointOnSurface);


  //Sphere(Vector3 centerInt, float radiusInit, Materials materialInit);

  // Get normalized normal vector from sphere's surface point
  // Vector3 operator ^ (Vector3 pointOnSurface);

  // bool detectHit(Ray ray, Vector3 &hitPoint);

};


#endif //RAYTRACER_SPHERE_H
