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
  float lensX;
  float lensY;
};

struct sample2D {
  float x;
  float y;
};

class Sampler {

private:
  unsigned int patternSpace;
  unsigned int patternTime;
  unsigned int patternLens;
  unsigned int index;
  unsigned int maximum;
  unsigned int overlap;
  unsigned int space;
  unsigned int time;
  float apeture;
  float shutter;

  unsigned int pseudoShuffle(unsigned int index, unsigned int maximum);

  unsigned int permute(unsigned int input, unsigned int maximum, unsigned int pattern);

  float randomFloat(unsigned int maximum, unsigned int pattern);

  sample2D multiJitter(unsigned int sample, unsigned int width, unsigned int height,
                       unsigned int pattern);

public:
  Sampler(unsigned int spaceInt, unsigned int timeInt, float shutterInit, unsigned int overlapInit,
          unsigned int patternInit, float apetureInit);

  void nextPixel();

  bool isNext();

  sampleTuple getNextSample();

  float radicalInverse(int sampleIndex, int base);

  float vanDerCorput(unsigned int sampleIndex, unsigned int pattern);

  float foldedRadicalInverse(int sampleIndex, int base);

  float sobol2(unsigned int sampleIndex, unsigned int pattern);

  sample2D vanDerCoruptSobol2(unsigned int sampleIndex, unsigned int pattern);

};

#endif //RAYTRACER_SAMPLER_H
