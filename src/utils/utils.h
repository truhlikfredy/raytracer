/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 28/01/2018
 */

#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include <stdlib.h>
#include <time.h>

#define M_PI_F	3.141592653589f  // single point variant of pi

template<size_t SIZE, class T> inline size_t array_size(T (&arr)[SIZE]) {
  return SIZE;
}

class Utils {
public:
  static void getTimeStampFilename(char *prefix, char *filename);
};

#endif //RAYTRACER_UTILS_H
