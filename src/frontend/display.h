/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_DISPLAY_H
#define RAYTRACER_DISPLAY_H

#define WIDTH  320
#define HEIGHT 200
#define SCALE 4.0  // display the window bigger than it really is (render low-res while having large window)

#include <SFML/Graphics.hpp>
#include "../render/render.h"
#include "../scenes/scene.h"

class Display {
private:
  Render           *render;
  sf::Uint8*       pixels;
  sf::Sprite       sprite;
  sf::RenderWindow window;

  void displaySamplerPattern(int width, int height, float frame);

public:
  bool showSamplerPatterns;
  sf::Texture      texture;
  Display();

  void renderLoop(Scene *scene);
  bool keepLooping();
  void clearDisplayMem();
  void convertToDisplayMem();
};

#endif //RAYTRACER_DISPLAY_H
