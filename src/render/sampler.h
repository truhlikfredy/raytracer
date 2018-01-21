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

public:
  Sampler(unsigned int spaceInt, unsigned int timeInt, float shutterInit, unsigned int overlapInit,
          unsigned int patternInit, float apetureInit);

  void nextPixel();

  bool isNext();

  void getNextSample(sampleTuple *ret);

  static float radicalInverse(int sampleIndex, int base);

  static float vanDerCorput(unsigned int sampleIndex, unsigned int pattern);

  static float foldedRadicalInverse(int sampleIndex, int base);

  static float sobol2(unsigned int sampleIndex, unsigned int pattern);

  static void vanDerCoruptSobol2(unsigned int sampleIndex, unsigned int pattern, sample2D *sample);

};

#endif //RAYTRACER_SAMPLER_H
