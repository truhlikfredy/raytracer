/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 28/01/2018
 */

#include "utils.h"
#include <stdio.h>

void Utils::getTimeStampFilename(const char *prefix, char *filename) {
  char buf[120];
  time_t t = time(0);
  struct tm *timestamp;
  timestamp = gmtime(&t);
  strftime(buf, sizeof(buf), "%Y%m%d-%H%M%S.png", timestamp);
  sprintf(filename, "%s-%s", prefix, buf);
}
