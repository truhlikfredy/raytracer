/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include "display.h"


Display::Display()  {
  showSamplerPatterns = false;
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


void Display::displaySamplerPattern(int width, int height, float frame) {
  static Sampler sampler(ANTI_ALIASING, 1, 0.1f, 0, frame / 100);

  sampler.nextPixel();
  for (int i = 0; i < width * height; i++) {
    sampleTuple sample = sampler.getNextSample();
    const int x = sample.spaceX * WIDTH;
    const int y = sample.spaceY * HEIGHT;
    const int offset = (x + y * WIDTH) *4;
    pixels[offset + 0] = 255;
    pixels[offset + 1] = 255;
    pixels[offset + 2] = 255;
    pixels[offset + 3] = 255;
    //printf(" %f, %f \r\n", sample.first, sample.second);
  }
}


void Display::renderLoop(Scene *scene) {
  static float frame = 90;
  sf::Event event;

  while (window.pollEvent(event))  {
    if (event.type == sf::Event::Closed) window.close();
  }

  clearDisplayMem();
  render->renderFullWindow(scene, frame);
  convertToDisplayMem();
  if (showSamplerPatterns) {
    displaySamplerPattern(ANTI_ALIASING, ANTI_ALIASING, frame);
  }

  window.clear();
  texture.update(pixels);
  window.draw(sprite);
  window.display();
  frame++;
}


bool Display::keepLooping() {
  return window.isOpen();
}

