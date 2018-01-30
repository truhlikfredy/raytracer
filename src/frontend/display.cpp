/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include <chrono>
#include "display.h"


Display::Display():
  showSamplerPatterns(false), onScreenDisplay(false), stdOutLog(false), timeSpeed(1.0f),
  benchmarkAllowed(false), benchmarkEnded(false), elapsedTotal(0), videoCapture(false)  {

  pixels = new sf::Uint8[WIDTH * HEIGHT * 4];
  render = new Render(WIDTH, HEIGHT);

  window.create(sf::VideoMode(WIDTH*SCALE, HEIGHT*SCALE), "Anton's RayTracer");
  texture.create(WIDTH, HEIGHT);
  sprite.setTexture(Display::texture);
  sprite.setScale(SCALE, SCALE);
}

void Display::saveScreenshot(char* filename) {
  static int count = 0;
  char fullName[120];

  sprintf(fullName, "%s-%04d.png", filename, count);
  texture.copyToImage().saveToFile(fullName);
  count++;
}


void Display::clearDisplayMem() {
  // clean buffer
  for (int i = 0; i < HEIGHT * WIDTH *4; i++) pixels[i]=0;
}


void Display::convertToDisplayMem() {
  for (int i = 0; i < HEIGHT * WIDTH; i++) {
    const Color average = render->dynamicPixels[i];
    pixels[i*4 + 0] = (int)(average.x*255);
    pixels[i*4 + 1] = (int)(average.y*255);
    pixels[i*4 + 2] = (int)(average.z*255);
    pixels[i*4 + 3] = 255;
  }
}


void Display::displaySamplerPattern(float frame) {
  static Sampler sampler(SAMPLING_MAX, SAMPLING_MAX, 0.1f, 0.0f, 1, (int)(frame / 20));
  sampleTuple sample;

  sampler.nextPixel();
  for (int i = 0; i < SAMPLING_MAX; i++) {
    sampler.getNextSample(&sample);
    const int x = sample.spaceX * WIDTH;
    const int y = sample.spaceY * HEIGHT;
    const int offset = (x + y * WIDTH) *4;
    pixels[offset + 0] = 255;
    pixels[offset + 1] = 255;
    pixels[offset + 2] = 255;
    pixels[offset + 3] = 255;
  }
}


void Display::renderLoop(Scene *scene) {
  sf::Event event;

  if (scene->frame == 0.0f) {
    elapsedTotal = 0;

    if (benchmarkAllowed) {
      printf("\r\nBenchmark started, wait for results (will do %f frames):\r\n", scene->lastFrame);
      printf("%d, %d, %f", scene->nLights, scene->nObjects, scene->lastFrame);
    }
  }

  while (window.pollEvent(event))  {
    if (event.type == sf::Event::Closed) window.close();
  }

  clearDisplayMem();

  // measure how much time is passed while rendering of a whole frame happened
  auto start = std::chrono::high_resolution_clock::now();
  render->renderFullWindow(scene);
  auto elapsed = std::chrono::high_resolution_clock::now() - start;
  long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
  elapsedTotal += microseconds;

  convertToDisplayMem();
  if (showSamplerPatterns) {
    displaySamplerPattern(scene->frame);
  }

  window.clear();
  texture.update(pixels);
  window.draw(sprite);
  window.display();

  if (benchmarkAllowed) {
    printf(", %d", microseconds);
  }

  if ( (scene->lastFrame < scene->frame) && benchmarkAllowed){
    benchmarkEnded = true;
    printf("\r\n");
  }

  scene->frame+= timeSpeed;
}


bool Display::keepLooping() {
  return window.isOpen() && !benchmarkEnded;
}

void Display::benchmarkSummary() {
  printf("%d ms elapsed (Width=%d Height=%d SamplingMin=%d SamplingMax=%d Bounches=%d)",
         elapsedTotal / 1000, WIDTH, HEIGHT, SAMPLING_MIN, SAMPLING_MAX, MAX_BOUNCES);
}