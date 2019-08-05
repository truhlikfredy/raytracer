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
#define VFD_DITHER 2      // undefined = no dithering, 1 = JJN, 2 = Sierra-3
#define VFD_DITHER_FLIP
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

  unsigned char getGetRow(unsigned int x, unsigned y, unsigned int threashold);
  void          normalizeRaw(unsigned x, unsigned y);
  void          sendToUart();
  void          reset();

public:
  // https://rules.sonarsource.com/cpp/RSPEC-1709
  explicit VFD(const char *portName);

  ~VFD();

  void memToVFD(sf::Uint8* pixels);

};

#endif //RAYTRACER_VFD_H
