#include "display.h"

int main() {
  Display *mainWindow = new Display();

  while (mainWindow->keepLooping()) {
    mainWindow->loop();
  }

  return 0;
}
