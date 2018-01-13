/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include "frontend/display.h"
#include "utils/debounce.h"
#include "scenes/plain.h"

int main() {
  Display *mainWindow = new Display();

  Scene scene = Plain();

  while (mainWindow->keepLooping()) {

    // Toggle display for the sample patterns
    if (Debounce::isKeyPressed(sf::Keyboard::S))  {
      mainWindow->showSamplerPatterns ^= true; // invert the state
    }

    mainWindow->renderLoop(scene);
  }

  return 0;
}
