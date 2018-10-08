//
// Created by fredy on 07/10/18.
//

#ifndef RAYTRACER_VFD_H
#define RAYTRACER_VFD_H

#include <SFML/Graphics.hpp>

#define VFD_WIDTH 128
#define VFD_HEIGHT 64

#define VFD_SHADES 2
#define VFD_SHADE_DIVIDER (256/VFD_SHADES)
#define VFD_SHADE_ROUND (VFD_SHADE_DIVIDER/2)

class VFD {
private:
  int              uartHandle;
  const char       *portName;
  int              raw[VFD_HEIGHT][VFD_WIDTH];
  unsigned char    quantized[VFD_HEIGHT][VFD_WIDTH];

  int openHandle();
  int set_interface_attribs(int speed, int parity);

  void normalizeRaw(unsigned x, unsigned y);
  unsigned char getGetRow(unsigned int x, unsigned y);
  void sendToUart();

public:
  VFD(const char *portName);
  void memToVFD(sf::Uint8* pixels);
};

#endif //RAYTRACER_VFD_H
