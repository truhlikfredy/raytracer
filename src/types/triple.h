/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_TRIPLE_H
#define RAYTRACER_TRIPLE_H

class Triple {

public:
  float x, y, z;

  Triple();

  Triple(float xInit, float yInit, float zInit);

  Triple(float init);

  //Triple(Triple &triple);

  Triple operator+(Triple secondTriple);

  Triple operator-(Triple secondTriple);

  Triple operator*(float scalar);

  Triple operator*(Triple secondTriple);

  Triple operator/(float scalar);

  float distance(Triple secondTriple);

  float sum();

  //Triple operator=(Triple& secondTriple);
};


#endif //RAYTRACER_TRIPLE_H
