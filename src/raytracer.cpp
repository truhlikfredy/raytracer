/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include <time.h>
#include "frontend/display.h"
#include "utils/debounce.h"
#include "scenes/plain.h"
#include "scenes/dof.h"
#include "scenes/mandelbrot.h"

int main() {
  Display *mainWindow = new Display();
  bool quitRequested = false;

  Scene scene = Mandelbrot();

  while (mainWindow->keepLooping() && !quitRequested) {

    if (Debounce::isKeyPressed(sf::Keyboard::S))  {
      // Toggle display for the sample patterns
      mainWindow->showSamplerPatterns ^= true; // invert the state
    }

    if (Debounce::isKeyPressed(sf::Keyboard::C))  {
      // Capture screenshot and save it to the file
      char filename[120];
      time_t t = time(0);
      struct tm *timestamp;

      timestamp = gmtime(&t);
      strftime(filename, sizeof(filename), "images/screenshot-%Y%m%d-%H%M%S.png", timestamp);
      mainWindow->texture.copyToImage().saveToFile(filename);
    }

    if (Debounce::isKeyPressed(sf::Keyboard::Q))  {
      // stop raytracer
      quitRequested = true;
    }


    mainWindow->renderLoop(&scene);
  }

  return 0;
}
