/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_DISPLAY_H
#define RAYTRACER_DISPLAY_H

#define RENDER_COMPLEXITY 2

#if RENDER_COMPLEXITY == 0
  #define WIDTH  80
  #define HEIGHT 50
  #define SCALE 10.0  // display the window bigger than it really is (render low-res while having large window)

#elif RENDER_COMPLEXITY == 1
  #define WIDTH  160
  #define HEIGHT 100
  #define SCALE 8.0  // display the window bigger than it really is (render low-res while having large window)

#elif RENDER_COMPLEXITY == 2
  #define WIDTH  320
  #define HEIGHT 200
  #define SCALE 4.0  // display the window bigger than it really is (render low-res while having large window)

#elif RENDER_COMPLEXITY == 3
  #define WIDTH  640
  #define HEIGHT 400
  #define SCALE 2.0  // display the window bigger than it really is (render low-res while having large window)

#elif RENDER_COMPLEXITY == 4
  #define WIDTH  960
  #define HEIGHT 600
  #define SCALE 1.0

#elif RENDER_COMPLEXITY == 5
  #define WIDTH  1280
  #define HEIGHT 800
  #define SCALE 1.0

#endif

#include <SFML/Graphics.hpp>
#include "../render/render.h"
#include "../scenes/scene.h"

class Display {
private:
  Render           *render;
  sf::Uint8*       pixels;
  sf::Sprite       sprite;
  sf::RenderWindow window;

  void displaySamplerPattern(float frame);

public:
  bool             showSamplerPatterns;
  bool             onScreenDisplay;
  bool             stdOutLog;
  bool             benchmarkAllowed;
  bool             benchmarkEnded;
  bool             videoCapture;
  sf::Texture      texture;
  long long        elapsedTotal;
  Display();

  void renderLoop(Scene *scene);
  bool keepLooping();
  void clearDisplayMem();
  void convertToDisplayMem();
  void log(char *text);
  void benchmarkSummary();
  void saveScreenshot(char* filename);
};

#endif //RAYTRACER_DISPLAY_H
