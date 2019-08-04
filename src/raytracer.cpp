/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include "frontend/display.h"
#include "utils/debounce.h"
#include "utils/utils.h"

//#include "scenes/plain.h"
#include "scenes/generated.h"
//#include "scenes/dof.h"
//#include "scenes/mandelbrot.h"
//#include "scenes/lights.h"
//#include "scenes/large.h"
//#include "scenes/large2.h"


int main() {
  Display *mainWindow = new Display();
  bool quitRequested = false;

  SceneGenerator sceneGenerators[1] = {
    Generated()
//    Plain(),
//    Large2(),
//    Large(),
//    Dof(),
//    Mandelbrot()
  };

  int sceneIndex = 0;

  while (mainWindow->keepLooping() && !quitRequested) {

    if (Debounce::isKeyPressed(sf::Keyboard::S))  {
      // Toggle display for the sample patterns
      mainWindow->showSamplerPatterns ^= true; // invert the state
    }

    if (Debounce::isKeyPressed(sf::Keyboard::M))  {
      // Start video capture
      mainWindow->videoCapture = ~mainWindow->videoCapture;
      printf("Video capture status: %d \r\n", mainWindow->videoCapture);
    }

    if (Debounce::isKeyPressed(sf::Keyboard::F) || mainWindow->videoCapture)  {
      // Capture screenshot and save it to the file
      char filename[120];
      Utils::getTimeStampFilename("images/screenshot", filename);
      mainWindow->saveScreenshot(filename);
    }

    if (Debounce::isKeyPressed(sf::Keyboard::Q))  {
      // stop raytracer
      quitRequested = true;
    }

    if (Debounce::isKeyPressed(sf::Keyboard::Right)) {
      // next scene
      sceneIndex++;
      mainWindow->timeSpeed = 1.0f; // start new scene at default speed
      sceneIndex %= array_size(sceneGenerators);
    }

    if (Debounce::isKeyPressed(sf::Keyboard::Left)) {
      // previous scene
      sceneIndex--;
      mainWindow->timeSpeed = 1.0f; // start new scene at default speed
      if (sceneIndex<0)  sceneIndex = array_size(sceneGenerators)-1;
    }

    if (Debounce::isKeyPressed(sf::Keyboard::RBracket)) {
      // jump forward in time
      sceneGenerators[sceneIndex].frame += 30;
    }

    if (Debounce::isKeyPressed(sf::Keyboard::LBracket)) {
      // jump backward in time
      sceneGenerators[sceneIndex].frame -= 15;
    }

    if (Debounce::isKeyPressed(sf::Keyboard::B)) {
      // start benchmark
      sceneGenerators[sceneIndex].frame = 0;
      mainWindow->benchmarkAllowed = true;
    }

    if (Debounce::isKeyPressed(sf::Keyboard::Comma)) {
      // , will halve speed of the time
      mainWindow->timeSpeed /= 2.0f;
    }

    if (Debounce::isKeyPressed(sf::Keyboard::Period)) {
      // . will double speed of the time
      mainWindow->timeSpeed *= 2.0f;
    }

    mainWindow->renderLoop(&sceneGenerators[sceneIndex]);
  }

  if (mainWindow->benchmarkEnded) {
    mainWindow->benchmarkSummary();
  }

  return 0;
}
