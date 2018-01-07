//
// Created by fredy on 07/01/18.
//

#ifndef RAYCASTER_DISPLAY_H
#define RAYCASTER_DISPLAY_H

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

#endif //RAYCASTER_DISPLAY_H
