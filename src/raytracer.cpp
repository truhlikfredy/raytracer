/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include "display.h"

int main() {
  Display *mainWindow = new Display();

  while (mainWindow->keepLooping()) {
    mainWindow->loop();
  }

  return 0;
}
