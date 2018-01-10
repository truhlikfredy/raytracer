/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 *
 * Task of this class is to sample subpixels in a multi sampling scenario without getting aliasing (trade it for noise),
 * important is ability to sample in multiple dimensions, 2D space + time + lens and merge these dimensions so the
 * complexity will raise as the higher dimensions increase. This means that each sub-pixel sample in 2D space might
 * be measuring the scene in different time instance. This should allow motion blur as well.
 *
 * References:
 * http://www.pbrt.org/chapters/pbrt_chapter7.pdf
 * https://graphics.pixar.com/library/MultiJitteredSampling/paper.pdf
 */

#include "sampler.h"


Sampler::Sampler(unsigned int spaceInt, unsigned int timeInt, float shutterInit, unsigned int overlapInit,
                 unsigned int patternInit) {
  this->space   = spaceInt;
  this->time    = timeInt;
  this->shutter = shutterInit;
  this->overlap = overlapInit;
  this->pattern = patternInit;
  this->index   = 0;

  // when overlap is 1 or more multiply all, when it's 0 count only to space squared
  this->maximum       = (overlap) ? (space * space * time * overlap) : (space * space);
}


void Sampler::nextPixel() {
  this->index = 0;
  this->pattern++;
}


bool Sampler::isNext() {
  return index < maximum;
}


sampleTuple Sampler::getNextSample() {
  sampleTuple ret;

  if (time == 1) {
    const std::pair<float, float> spaceSample = multiJitter(index, space, space, pattern);
    ret.spaceX = spaceSample.first;
    ret.spaceY = spaceSample.second;
    ret.time   = 1.0f;
  }
  else {
    const std::pair<float, float> spaceSample = multiJitter(index, space, space, pattern);
    const std::pair<float, float> timeSample  = multiJitter(pseudoShuffle(index, time), time, 1, pattern);
    ret.spaceX = spaceSample.first;
    ret.spaceY = spaceSample.second;
    ret.time   = timeSample.first * shutter;
  }

  index++;
  return ret;
}


std::pair<float, float> Sampler::multiJitter(unsigned int sample, unsigned int width, unsigned int height,
                                             unsigned int pattern) {

  const int staticX = permute(sample % width, width,  pattern * 0xa511e9b3);
  const int staticY = permute(sample / width, height, pattern * 0x63d83595);
  const float jitterX = randomFloat(sample, pattern * 0xa399d265);
  const float jitterY = randomFloat(sample, pattern * 0x711ad6a5);

  return {(sample % width + (staticY + jitterX) / height) / width,
          (sample / width + (staticX + jitterY) / width) / height};
}


unsigned int Sampler::pseudoShuffle(unsigned int index, unsigned int maximum) {
  return ((index ^ 0x16) % maximum);
}


unsigned int Sampler::permute(unsigned int input, unsigned int maximum, unsigned int pattern) {
  unsigned w = maximum - 1;
  w |= w >> 1;
  w |= w >> 2;
  w |= w >> 4;
  w |= w >> 8;
  w |= w >> 16;
  do {
    input ^= pattern;
    input *= 0xe170893d;
    input ^= pattern >> 16;
    input ^= (input & w) >> 4;
    input ^= pattern >> 8;
    input *= 0x0929eb3f;
    input ^= pattern >> 23;
    input ^= (input & w) >> 1;
    input *= 1 | pattern >> 27;
    input *= 0x6935fa69;
    input ^= (input & w) >> 11;
    input *= 0x74dcb303;
    input ^= (input & w) >> 2;
    input *= 0x9e501cc3;
    input ^= (input & w) >> 2;
    input *= 0xc860a3df;
    input &= w;
    input ^= input >> 5;
  } while (input >= maximum);
  return ((input + pattern) % maximum);
}


float Sampler::randomFloat(unsigned int maximum, unsigned int pattern) {
  // get pseudorandom number between 0 and maximum with a specific pattern
  maximum ^= pattern;
  maximum ^= maximum >> 17;
  maximum ^= maximum >> 10;
  maximum *= 0xb36534e5;
  maximum ^= maximum >> 12;
  maximum ^= maximum >> 21;
  maximum *= 0x93fc4795;
  maximum ^= 0xdf6e307f;
  maximum ^= maximum >> 17;
  maximum *= 1 | pattern >> 18;

  return (maximum * (1.0f / 4294967808.0f));
}

