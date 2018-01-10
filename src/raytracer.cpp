/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include "frontend/display.h"
#include "utils/debounce.h"


int main() {
  Display *mainWindow = new Display();

  while (mainWindow->keepLooping()) {

    // Toggle display for the sample patterns
    if (Debounce::isKeyPressed(sf::Keyboard::S))  {
      mainWindow->showSamplerPatterns ^= true; // invert the state
    }

    mainWindow->renderLoop();
  }

  return 0;
}
