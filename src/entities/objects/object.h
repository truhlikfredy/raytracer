/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 11/01/2018
 */

#ifndef RAYTRACER_OBJECT_H
#define RAYTRACER_OBJECT_H

#include <functional>
#include "../../render/ray.h"
#include "../../types/color.h"

class Object {
protected:

public:
  std::function<Color(Vector3 point)> material;

  Object(std::function<Color(Vector3 point)> material);

  virtual bool detectHit(Ray ray, Vector3 &hitPoint) = 0;


  //void setMaterial(Color (*Arg)(Vector3 point));

  virtual Vector3 operator ^ (Vector3 pointOnSurface) = 0;

  Color getColorAt(Vector3 point);

};

#endif //RAYTRACER_OBJECT_H
