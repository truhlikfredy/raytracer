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
#include <cstdlib>


Sampler::Sampler(unsigned int minSamples, unsigned int maxSamples, float shutterInit, float apetureInit, unsigned int lightsInit,
                 unsigned int patternInit) {
  this->indexMinimum = minSamples;      // Dynamic sampling
  this->indexMaximum = maxSamples;
  this->shutter      = shutterInit;     // Speed of the shutter of the camera
  this->apeture      = apetureInit;
  this->lights       = lightsInit;
  this->pattern      = patternInit;     // Initial seed value
}


/**
 * Change the seed a bit and start for new pixel
 */
void Sampler::nextPixel() {
  this->index             = 0;
  this->patternSpace      = rand();
  this->patternTime       = rand();
  this->patternLens       = rand();
  this->patternLight      = rand();
  this->patternLightSpace = rand();
}


/**
 * Did all samples got iterated yet
 */
bool Sampler::isNext() {
  return index < indexMaximum;
}


bool Sampler::isMinimumDone() {
  return index > indexMinimum;
}


void Sampler::finish() {
  index = indexMaximum;
}


/**
 * Calculate new pixel and time coordinates for a new ray to sample
 */
void Sampler::getNextSample(sampleTuple *ret) {
  unsigned int origIndex = index++;
  sample2D sample;

  ret->spaceX = 0.0f;
  ret->spaceY = 0.0f;
  ret->time   = 0.0f;
  ret->lensX  = 0.0f;
  ret->lensY  = 0.0f;
  ret->light  = 0;
  ret->lightx = 0.0f;
  ret->lighty = 0.0f;

  if   (indexMaximum == 1 ) {
    return;
  }

  vanDerCoruptSobol2(origIndex, patternSpace, sample);
  ret->spaceX = sample.x;
  ret->spaceY = sample.y;

  if (shutter > 0) {
    ret->time   = vanDerCorput(origIndex, patternTime) * shutter;
  }

  if (apeture > 0.0f) {
    vanDerCoruptSobol2(origIndex, patternLens, sample);
    ret->lensX = sample.x * apeture;
    ret->lensY = sample.y * apeture;
    // the lens is sampled in a sqaure instead of circle/aperture shape, proper implementation
    // of the lens shape is not worth the overhead it will cause and not noticable quality gain,
    // still it needs magnitude more rays and the sampling strategy will not save from that
  }

  if (lights > 0) {
    ret->light = (int)(origIndex) % lights;
  }

  vanDerCoruptSobol2(origIndex, patternLightSpace, sample);
  ret->lightx = sample.x;
  ret->lighty = sample.y;
}


/**
 * pseudoShuffle is meant to be used to map between two different dimensions, e.g. space dimension has 9 entries and
 * time dimension has 9 entries but the index of space dimension will get shuffled before it is used as time
 * dimension index. This will avoid situations where the very first row of space dimension subpixel would be
 * sampling the very first samples in time dimension and so on...
 */
unsigned int Sampler::pseudoShuffle(unsigned int index, unsigned int maximum) {
  return ((index ^ 0x16) % maximum);
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


float Sampler::vanDerCorput(unsigned int sampleIndex, unsigned int pattern) {
  sampleIndex = (sampleIndex << 16) | (sampleIndex >> 16);
  sampleIndex = ((sampleIndex & 0x00ff00ff) << 8) | ((sampleIndex & 0xff00ff00) >> 8);
  sampleIndex = ((sampleIndex & 0x0f0f0f0f) << 4) | ((sampleIndex & 0xf0f0f0f0) >> 4);
  sampleIndex = ((sampleIndex & 0x33333333) << 2) | ((sampleIndex & 0xcccccccc) >> 2);
  sampleIndex = ((sampleIndex & 0x55555555) << 1) | ((sampleIndex & 0xaaaaaaaa) >> 1);
  sampleIndex ^= pattern;
  return (float)sampleIndex / (float)0x100000000LL;
}


float Sampler::sobol2(unsigned int sampleIndex, unsigned int pattern) {
  for (unsigned int v = 1 << 31; sampleIndex != 0; sampleIndex >>= 1, v ^= v >> 1)
    if (sampleIndex & 0x1) pattern ^= v;
  return (float)pattern / (float)0x100000000LL;
}


void Sampler::vanDerCoruptSobol2(unsigned int sampleIndex, unsigned int pattern, sample2D &sample) {
  sample.x = vanDerCorput(sampleIndex, pattern);
  sample.y = sobol2(sampleIndex, pattern);
}

