/*
 * Driver for Futaba TGP1118BA4 VFD display
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#ifndef RAYTRACER_VFD_H
#define RAYTRACER_VFD_H

#include <SFML/Graphics.hpp>

#define VFD_WIDTH 128
#define VFD_HEIGHT 64

#define VFD_SHADES 5
#define VFD_DITHER 1
#define VFD_SHADE_DIVIDER (256/VFD_SHADES)
#define VFD_SHADE_ROUND (VFD_SHADE_DIVIDER/2)

class VFD {
private:
  int              uartHandle;
  const char       *portName;
  bool             isBufferA;
  int              raw[VFD_HEIGHT][VFD_WIDTH];
  unsigned char    quantized[VFD_HEIGHT][VFD_WIDTH];

  int openHandle();
  int set_interface_attribs(int speed);

  void normalizeRaw(unsigned x, unsigned y);
  unsigned char getGetRow(unsigned int x, unsigned y, unsigned int threashold);
  void sendToUart();

public:
  VFD(const char *portName);
  void memToVFD(sf::Uint8* pixels);
};

#endif //RAYTRACER_VFD_H
