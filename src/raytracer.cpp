/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include "frontend/display.h"
#include "utils/debounce.h"
#include "utils/utils.h"

#include "scenes/plain.h"
#include "scenes/dof.h"
#include "scenes/mandelbrot.h"
#include "scenes/lights.h"
#include "scenes/large.h"
#include "scenes/large2.h"


int main() {
  Display *mainWindow = new Display();
  bool quitRequested = false;

  Scene scenes[6] = {
    Plain(),
    Large2(),
    Large(),
    Lights(),
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
      Utils::getTimeStampFilename("images/screenshot",filename);
      mainWindow->texture.copyToImage().saveToFile(filename);
    }

    if (Debounce::isKeyPressed(sf::Keyboard::Q))  {
      // stop raytracer
      quitRequested = true;
    }

    if (Debounce::isKeyPressed(sf::Keyboard::Right)) {
      // next scene
      sceneIndex++;
      sceneIndex %= array_size(scenes);
    }

    if (Debounce::isKeyPressed(sf::Keyboard::Left)) {
      // previous scene
      sceneIndex--;
      if (sceneIndex<0)  sceneIndex = array_size(scenes)-1;
    }

    if (Debounce::isKeyPressed(sf::Keyboard::RBracket)) {
      // jump forward in time
      scenes[sceneIndex].frame += 30;
    }

    if (Debounce::isKeyPressed(sf::Keyboard::LBracket)) {
      // jump backward in time
      scenes[sceneIndex].frame -= 15;
    }

    mainWindow->renderLoop(&scenes[sceneIndex]);
  }

  return 0;
}
