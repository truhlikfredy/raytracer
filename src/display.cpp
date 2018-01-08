/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include "display.h"

Display::Display()  {
  pixels = new sf::Uint8[WIDTH * HEIGHT * 4];

  render = new Render(WIDTH, HEIGHT);

  window.create(sf::VideoMode(WIDTH*SCALE, HEIGHT*SCALE), "Anton's RayTracer");
  texture.create(WIDTH, HEIGHT);
  sprite.setTexture(Display::texture);
  sprite.setScale(SCALE, SCALE);
}

void Display::clearDisplayMem() {
  // clean buffer
  for (int i = 0; i < HEIGHT * WIDTH *4; i++) pixels[i]=0;
}

void Display::convertToDisplayMem() {
  for (int i = 0; i < HEIGHT * WIDTH; i++) {
    Color average = render->dynamicPixels[i].color / render->dynamicPixels[i].count;
    pixels[i*4 + 0] = (int)(average.x*255);
    pixels[i*4 + 1] = (int)(average.y*255);
    pixels[i*4 + 2] = (int)(average.z*255);
    pixels[i*4 + 3] = 255;
  }
}

void Display::loop() {
  sf::Event event;

  while (window.pollEvent(event))  {
    if (event.type == sf::Event::Closed) window.close();
  }

  clearDisplayMem();
  render->renderFull();
  convertToDisplayMem();

  window.clear();
  texture.update(pixels);
  window.draw(sprite);
  window.display();
}

bool Display::keepLooping() {
  return window.isOpen();
}

