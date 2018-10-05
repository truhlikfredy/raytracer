/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include <chrono>
#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "display.h"

int fd;

int set_interface_attribs(int fd, int speed, int parity) {
  struct termios tty;
  memset(&tty, 0, sizeof tty);
  if (tcgetattr(fd, &tty) != 0) {
    printf("error %d from tcgetattr\n", errno);
    return(-1);
  }

  cfsetospeed(&tty, speed);
  cfsetispeed(&tty, speed);

  tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
  // disable IGNBRK for mismatched speed tests; otherwise receive break
  // as \000 chars
  tty.c_iflag &= ~IGNBRK;         // disable break processing
  tty.c_lflag = 0;                // no signaling chars, no echo,
  // no canonical processing
  tty.c_oflag = 0;                // no remapping, no delays
  tty.c_cc[VMIN] = 0;            // read doesn't block
  tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

  tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

  tty.c_cflag |= (CLOCAL | CREAD); // ignore modem controls,
  // enable reading
  tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
  tty.c_cflag |= parity;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CRTSCTS;

  if (tcsetattr(fd, TCSANOW, &tty) != 0) {
    printf("error %d from tcsetattr\n", errno);
    return(-1);
  }
  return(0);
}


Display::Display():
  showSamplerPatterns(false), onScreenDisplay(false), stdOutLog(false), timeSpeed(1.0f),
  benchmarkAllowed(false), benchmarkEnded(false), elapsedTotal(0), videoCapture(false)  {

  pixels = new sf::Uint8[WIDTH * HEIGHT * 4];
  render = new Render(WIDTH, HEIGHT);

  window.create(sf::VideoMode(WIDTH*SCALE, HEIGHT*SCALE), "Anton's RayTracer");
  texture.create(WIDTH, HEIGHT);
  sprite.setTexture(Display::texture);
  sprite.setScale(SCALE, SCALE);

  char *portname = "/dev/ttyUSB0";
  fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
  if (fd < 0) {
    printf("error %d opening %s: %s\n", errno, portname, strerror(errno));
  }
  else {
    set_interface_attribs(fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)

    write(fd, "\x00", 1);
    usleep(30000);
  }


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

unsigned char Display::getAveragePixel(unsigned int pixel){
  return ((pixels[pixel*4] + pixels[pixel*4+1] + pixels[pixel*4+2])/3);
}

unsigned char Display::getGetRow(unsigned int x, unsigned y) {
  int index = (y *8)*WIDTH +x;
  unsigned char value = 0;
  static int error = 0;

  for (int i = 0; i < 8; i++) {
    unsigned int current = getAveragePixel(index +i *WIDTH);
    unsigned int rounded = (current + error) / 128;
    error += current - rounded * 128;
    if (rounded>0) value |= 1 << i;
  }
  return value;
}

void Display::convertToDisplayMem() {
  for (int i = 0; i < HEIGHT * WIDTH; i++) {
    const Color average = render->dynamicPixels[i];
    pixels[i*4 + 0] = (int)(average.x*255);
    pixels[i*4 + 1] = (int)(average.y*255);
    pixels[i*4 + 2] = (int)(average.z*255);
    pixels[i*4 + 3] = 255;
  }
  write(fd, "\x06", 1);
  for (int y = 0; y < HEIGHT/8; y++) {
    for (int x = 0; x < WIDTH; x++) {
      unsigned char final = getGetRow(x,y);
      write(fd, &final, 1);
    }
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
  if (timeSpeed != 1.0f) {
    // Display what frame it is, when running atypical speeds
    printf("Frame: %f \r\n", scene->frame);
  }
}


bool Display::keepLooping() {
  return window.isOpen() && !benchmarkEnded;
}

void Display::benchmarkSummary() {
  printf("%d ms elapsed (Width=%d Height=%d SamplingMin=%d SamplingMax=%d Bounches=%d)",
         elapsedTotal / 1000, WIDTH, HEIGHT, SAMPLING_MIN, SAMPLING_MAX, MAX_BOUNCES);
}