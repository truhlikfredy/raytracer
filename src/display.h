/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_DISPLAY_H
#define RAYTRACER_DISPLAY_H

#define WIDTH  320
#define HEIGHT 200
#define SCALE 3.0  // display the window bigger than it really is (render low-res while having large window)

#include <SFML/Graphics.hpp>
#include "render.h"

class Display {
private:
  Render           *render;
  sf::Uint8*       pixels;
  sf::Texture      texture;
  sf::Sprite       sprite;
  sf::RenderWindow window;

public:
  Display();

  void loop();
  bool keepLooping();
  void clearDisplayMem();
  void convertToDisplayMem();
};

#endif //RAYTRACER_DISPLAY_H
