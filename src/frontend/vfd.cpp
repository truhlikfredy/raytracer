/*
 * Driver for Futaba TGP1118BA4 VFD display
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "vfd.h"
#include "display.h"


VFD::VFD(const char *portName):
  isBufferA(true), uartHandle(-1), portName(portName)  {
}


int VFD::set_interface_attribs(int speed) {
  struct termios tty;
  memset(&tty, 0, sizeof tty);
  if (tcgetattr(uartHandle, &tty) != 0) {
    printf("error %d from tcgetattr\n", errno);
    return(-1);
  }

  cfsetospeed(&tty, speed);

  tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
  // disable IGNBRK for mismatched speed tests; otherwise receive break
  // as \000 chars
  tty.c_iflag &= ~IGNBRK;         // disable break processing
  tty.c_lflag = 0;                // no signaling chars, no echo,
  // no canonical processing
  tty.c_oflag = 0;                // no remapping, no delays
  tty.c_cc[VMIN]  = 0;            // read doesn't block
  tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

  tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

  tty.c_cflag |= (CLOCAL | CREAD);        // ignore modem controls,

  // enable reading
  tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CRTSCTS;

  if (tcsetattr(uartHandle, TCSANOW, &tty) != 0) {
    printf("error %d from tcsetattr\n", errno);
    return(-1);
  }
  return(0);
}


int VFD::openHandle() {
  uartHandle = open(portName, O_RDWR | O_NOCTTY | O_SYNC);
  if (uartHandle < 0) {
    printf("error %d opening %s: %s\n", errno, portName, strerror(errno));
  }
  else {
    set_interface_attribs(B115200);  // set speed to 115,200 bps, 8n1 (no parity)

    write(uartHandle, "\x00", 1);
    usleep(30000);
  }
}


unsigned char VFD::getGetRow(unsigned int x, unsigned int row, unsigned int threashold) {
  unsigned int y = row * 8;
  unsigned char value = 0;

  for (int i = 0; i < 8; i++) {
    unsigned int rounded = quantized[y+i][x];
    if (rounded > threashold) value |= 1 << i;
  }
  return value;
}


void VFD::sendToUart() {
  const unsigned char bankSelectCodes[4] = { 0x11, 0x15, 0x19, 0x1D };
  unsigned char packetBuffer[(128*64)/8+3];

  // The 4 shade (5 shade if black is included) mode has to write to 4 different 128x64 bit buffer banks
  // there are two sets of these sets to allow double buffering and with 0x04 command you can select which
  // bank is display and to which the write
  // 0x10, 0x14, 0x18, 0x1C sameBuffer than display
  // 0x11, 0x15, 0x19, 0x1D bufferA shades
  // 0x12, 0x16, 0x1A, 0x1E bufferB shades
  // and then you can write whole bank with 0x06 command


  for (int bankIndex = 0; bankIndex < VFD_SHADES-1; bankIndex++) {
    unsigned int index = 0;
    if (VFD_SHADES > 2) {
      // do not use double buffering with 1bit mode as it is fast enough
      packetBuffer[index++] = 0x04;
      packetBuffer[index++] = bankSelectCodes[bankIndex] + isBufferA;
    }
    packetBuffer[index++] = 0x06;

    for (int row = 0; row < VFD_HEIGHT/8; row++) {
      for (int x = 0; x < VFD_WIDTH; x++) {
#ifdef VFD_DITHER_FLIP
        // flips back the flip done before dithering
        packetBuffer[index++] = getGetRow(((isBufferA) ? (VFD_WIDTH-x-1) : x), row, bankIndex);
#else
        packetBuffer[index++] = getGetRow(x, row, bankIndex);
#endif
//        packetBuffer[index++] = getGetRow(x, row, bankIndex);
      }
    }
    write(uartHandle, packetBuffer, index);
  }
  isBufferA = !isBufferA;
}


void VFD::normalizeRaw(unsigned x, unsigned y) {
  if (raw[y][x] > 255) {
    raw[y][x] = 255;
  }
  else if (raw[y][x] < 0) {
    raw[y][x] = 0;
  }
}


void VFD::memToVFD(sf::Uint8* pixels) {
  if (uartHandle == -1) {
    // UART is not opened, try to open it (for example using this call for the first time)
    openHandle();
  }

  if (uartHandle == -1) {
    // If the UART is still not opened, then give up on sending data to the display
    return;
  }

  // Copying RGB data to Grayscale buffer
  for (int y=0; y < VFD_HEIGHT; y++) {
    for (int x=0; x < VFD_WIDTH; x++) {
#ifdef VFD_DITHER_FLIP
      // for every second image do the flip.
      // image is now and then after dithering, the resulting image is
      // in correct orientation, but the dithering was effectively
      // applied right to left and on next frame left to right
      // which dithers a bit over time, not just over x,y dimensions
      int index = (y*VFD_WIDTH) + ((isBufferA) ? (VFD_WIDTH-x-1) : x);
#else
      int index = (y*VFD_WIDTH) + x;
#endif
      raw[y][x] = (pixels[index*4] + pixels[index*4+1] + pixels[index*4+2])/3;
    }
  }

  // Quantize and apply dithering
  for (int y=0; y < VFD_HEIGHT; y++) {
    for (int x=0; x < VFD_WIDTH; x++) {
      normalizeRaw(x, y);  // make sure the original raw value do not overflow nor underflow
      const unsigned char shade = (raw[y][x] + VFD_SHADE_ROUND) / VFD_SHADE_DIVIDER;
      quantized[y][x] = shade;

#ifdef VFD_DITHER
      const int error = raw[y][x] - (shade * VFD_SHADE_DIVIDER);
      // http://www.tannerhelland.com/4660/dithering-eleven-algorithms-source-code/

#if VFD_DITHER == 1
      // Jarvis, Judice, and Ninke Dithering

      const int error1 = (error * 1)/48;
      const int error3 = (error * 3)/48;
      const int error5 = (error * 5)/48;
      const int error7 = (error * 7)/48;

      const int errors[3][5] = {
        {0,      0,      0,      error7, error5 },
        {error3, error5, error7, error5, error3 },
        {error1, error3, error5, error3, error1 }
      };

      // Make sure to NOT apply the error outside boundaries
      const int startX = ( x > 2 ? 0 : 2 - x );
      const int endX   = ( x < (VFD_WIDTH  - 2) ? 4 : (VFD_WIDTH  - x) + 1 );
      const int endY   = ( y < (VFD_HEIGHT - 2) ? 2 : (VFD_HEIGHT - y) - 1 );

      for (int row = 0; row <= endY; row++) {
        for (int col = startX; col <= endX; col++) {
          raw[y+row][x+col-2] += errors[row][col];
        }
      }
#endif

#if VFD_DITHER == 2
      // Sierra-3
      const int error2 = (error * 2)/32;
      const int error3 = (error * 3)/32;
      const int error4 = (error * 4)/32;
      const int error5 = (error * 5)/32;

      const int errors[3][5] = {
        {0,      0,      0,      error5, error3 },
        {error2, error4, error5, error4, error2 },
        {0,      error2, error3, error2, 0      }
      };


      // Make sure to NOT apply the error outside boundaries
      const int startX = ( x > 2 ? 0 : 2 - x );
      const int endX   = ( x < (VFD_WIDTH  - 2) ? 4 : (VFD_WIDTH  - x) + 1 );
      const int endY   = ( y < (VFD_HEIGHT - 2) ? 2 : (VFD_HEIGHT - y) - 1 );

      for (int row = 0; row <= endY; row++) {
        for (int col = startX; col <= endX; col++) {
          raw[y+row][x+col-2] += errors[row][col];
        }
      }
#endif

#endif

    }
  }

  sendToUart();
}
