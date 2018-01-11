/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

//#define pseudoShuffle(index, maximum)  ( ((index) ^ 0x16) % (maximum) )

#ifndef RAYTRACER_SAMPLER_H
#define RAYTRACER_SAMPLER_H

#include <utility>

struct sampleTuple {
  float spaceX;
  float spaceY;
  float time;
};

struct sample2D {
  float spaceX;
  float spaceY;
};

class Sampler {

private:
  unsigned int index;
  unsigned int maximum;
  unsigned int pattern;
  unsigned int overlap;
  unsigned int space;
  unsigned int time;
  float shutter;

  unsigned int pseudoShuffle(unsigned int index, unsigned int maximum);

  unsigned int permute(unsigned int input, unsigned int maximum, unsigned int pattern);

  float randomFloat(unsigned int maximum, unsigned int pattern);

  sample2D multiJitter(unsigned int sample, unsigned int width, unsigned int height,
                       unsigned int pattern);

public:
  Sampler(unsigned int spaceInt, unsigned int timeInt, float shutterInit, unsigned int overlapInit,
          unsigned int patternInit);

  void nextPixel();

  bool isNext();

  sampleTuple getNextSample();

};

#endif //RAYTRACER_SAMPLER_H
