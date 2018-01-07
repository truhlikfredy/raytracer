//
// Created by fredy on 05/01/18.
//

#ifndef RAYCASTER_TRIPLE_H
#define RAYCASTER_TRIPLE_H

class Triple {

//protected:

public:
  float x, y, z;

  Triple();

  Triple(float xInit, float yInit, float zInit);

  Triple(float init);

  //Triple(Triple &triple);

  Triple operator+(Triple secondTriple);

  Triple operator-(Triple secondTriple);

  Triple operator*(float scalar);

  Triple operator/(float scalar);

  //Triple operator=(Triple& secondTriple);
};


#endif //RAYCASTER_TRIPLE_H
