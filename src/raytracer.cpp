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

template<size_t SIZE, class T> inline size_t array_size(T (&arr)[SIZE]) {
  return SIZE;
}

int main() {
  Display *mainWindow = new Display();
  bool quitRequested = false;

  Scene scenes[3] = {
    Plain(),
    Dof(),
    Mandelbrot()
  };

  int sceneIndex = 0;

  while (mainWindow->keepLooping() && !quitRequested) {

    if (Debounce::isKeyPressed(sf::Keyboard::S))  {
      // Toggle display for the sample patterns
      mainWindow->showSamplerPatterns ^= true; // invert the state
    }

    if (Debounce::isKeyPressed(sf::Keyboard::F))  {
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

    if (Debounce::isKeyPressed(sf::Keyboard::Right)) {
      sceneIndex++;
      sceneIndex %= array_size(scenes);
    }

    if (Debounce::isKeyPressed(sf::Keyboard::Left)) {
      sceneIndex--;
      if (sceneIndex<0)  sceneIndex = array_size(scenes)-1;
    }

    mainWindow->renderLoop(&scenes[sceneIndex]);
  }

//  Sampler sampler = Sampler(2,2,1.0f,0.0f,1,0.0f);
//
//  for (int i = 0; i < 32; i++) {
//    printf("%d = %f  %f\r\n", i, sampler.radicalInverse(i,2), sampler.foldedRadicalInverse(i, 2) , sampler.vanDerCorput(i, 0x2313434334), sampler.sobol2(i, 0x23134343343));
//  }
  return 0;
}
