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
                 unsigned int patternInit, float apetureInit) {
  this->space   = spaceInt;      // How many samples in space dimension (this value gets squared)
  this->time    = timeInt;       // How many samples in time dimension
  this->shutter = shutterInit;   // Speed of the shutter of the camer
  this->overlap = overlapInit;   // How much the dimensions overlap
  this->pattern = patternInit;   // Initial seed value
  this->index   = 0;
  this->apeture = apetureInit;

  // when overlap is 1 or more multiply all, when it's 0 count only to space squared
  this->maximum       = (overlap) ? (space * space * time * overlap) : (space * space);
}


/**
 * Change the seed a bit and start for new pixel
 */
void Sampler::nextPixel() {
  this->index = 0;
  this->pattern+=space+3;
}


/**
 * Did all samples got iterated yet
 */
bool Sampler::isNext() {
  return index < maximum;
}


/**
 * Calculate new pixel and time coordinates for a new ray to sample
 */
sampleTuple Sampler::getNextSample() {
  sampleTuple ret;
  ret.spaceX = 0.0f;
  ret.spaceY = 0.0f;
  ret.time   = 0.0f;
  ret.lensX  = 0.0f;
  ret.lensY  = 0.0f;


  if (space == 1 ) {
    index++;
    return ret;
  }

  const sample2D spaceSample = multiJitter(index, space, space, pattern);
  ret.spaceX = spaceSample.x;
  ret.spaceY = spaceSample.y;

  if (time == 1) {
    index++;
    return ret;
  }

  const sample2D timeSample  = multiJitter(pseudoShuffle(index, time), time, 1, pattern);
  ret.time   = timeSample.x * shutter;

  if (apeture == 0.0f) {
    index++;
    return ret;
  }

  const sample2D lensSample = multiJitter(index, space, space, pattern);
  ret.lensX = lensSample.x * apeture;
  ret.lensY = lensSample.y * apeture;
  // the lens is sampled in a asqaure instead of circle/aperture shape, proper implementation
  // of the lens shape is not worth the overhead it will cause and not noticable quality gain,
  // still it needs magnitude more rays and the sampling strategy will not save from that

  index++;
  return ret;
}

/**
 * Decide on the resulting sample, where sample < width*height
 */
sample2D Sampler::multiJitter(unsigned int sample, unsigned int width, unsigned int height,
                                             unsigned int pattern) {

  const int staticX = permute(sample % width, width,  pattern * 0xa511e9b3);
  const int staticY = permute(sample / width, height, pattern * 0x63d83595);
  const float jitterX = randomFloat(sample, pattern * 0xa399d265);
  const float jitterY = randomFloat(sample, pattern * 0x711ad6a5);

  return {(sample % width + (staticY + jitterX) / height) / width,
          (sample / width + (staticX + jitterY) / width) / height};
}

/**
 * pseudoShuffle is meant to be used to map between two different dimensions, e.g. space dimension has 9 entries and
 * time dimension has 9 entries but the index of space dimension will get shuffled before it is used as time
 * dimension index. This will avoid situations where the very first row of space dimension subpixel would be
 * sampling the very first samples in time dimension and so on...
 */
unsigned int Sampler::pseudoShuffle(unsigned int index, unsigned int maximum) {
  return ((index ^ 0x16) % maximum);
//  return (index % maximum);
}


/**
 * Permutate between the pattern combinations.
 */
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


/**
 * Get pseudorandom number between 0 and maximum with a specific pattern (seed)
 */
float Sampler::randomFloat(unsigned int maximum, unsigned int pattern) {
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


float Sampler::radicalInverse(int sampleIndex, int base) {
  float inverseBased = 1.0f / base;
  float inverseBaseSquared = inverseBased;
  float ret = 0;

  while (sampleIndex > 0) {
    int digit = (sampleIndex % base);
    ret += digit * inverseBaseSquared;
    sampleIndex /= base;
    inverseBaseSquared *= inverseBased;
  }
  return ret;
}


float Sampler::vanDerCorupt(int n) {
  return this->radicalInverse(n, 2);
}


float Sampler::foldedRadicalInverse(int sampleIndex, int base) {
  float inverseBase = 1.0f / base;
  float inverseBaseSquared = inverseBase;
  float ret = 0;

  int offset = 0;
  while (ret + base * inverseBaseSquared != ret) {
    int digit = ((sampleIndex + offset) % base);
    ret += digit * inverseBaseSquared;
    sampleIndex /= base;
    inverseBaseSquared *= inverseBase;
    ++offset;
  }
  return ret;
}
