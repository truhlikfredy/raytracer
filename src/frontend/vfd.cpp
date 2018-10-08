//
// Created by fredy on 07/10/18.
//

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "vfd.h"
#include "display.h"

// Implementing driver for Futaba TGP1118BA4 VFD display

VFD::VFD(const char *portName) {
  this->portName   = portName;
  this->uartHandle = -1;
}


int VFD::set_interface_attribs(int speed, int parity) {
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
  tty.c_cc[VMIN] = 0;            // read doesn't block
  tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

  tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

  tty.c_cflag |= (CLOCAL | CREAD); // ignore modem controls,
  // enable reading
  tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
  tty.c_cflag |= parity;
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
    set_interface_attribs(B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)

    write(uartHandle, "\x00", 1);
    usleep(30000);
  }
}


unsigned char VFD::getGetRow(unsigned int x, unsigned int row) {
  unsigned int y = row * 8;
  unsigned char value = 0;

  for (int i = 0; i < 8; i++) {
    unsigned int rounded = quantized[y+i][x];
    if (rounded>0) value |= 1 << i;
  }
  return value;
}


void VFD::sendToUart() {
  write(uartHandle, "\x06", 1);
  for (int row = 0; row < HEIGHT/8; row++) {
    for (int x = 0; x < WIDTH; x++) {
      unsigned char final = getGetRow(x, row);
      write(uartHandle, &final, 1);
    }
  }
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
    openHandle();
  }

  for (int y=0; y < VFD_HEIGHT; y++) {
    for (int x=0; x < VFD_WIDTH; x++) {
      int index = (y*VFD_WIDTH) + x;
      raw[y][x] = (pixels[index*4] + pixels[index*4+1] + pixels[index*4+2])/3;
    }
  }

  for (int y=0; y < VFD_HEIGHT; y++) {
    for (int x=0; x < VFD_WIDTH; x++) {
      normalizeRaw(x, y);
      unsigned char shade = (raw[y][x] + VFD_SHADE_ROUND) / VFD_SHADE_DIVIDER;
      quantized[y][x] = shade;
      int error = raw[y][x] - (shade * VFD_SHADE_DIVIDER);

      // http://www.tannerhelland.com/4660/dithering-eleven-algorithms-source-code/
      // Jarvis, Judice, and Ninke Dithering
      if (x < (VFD_WIDTH-1)) {
        raw[y][x+1] += (error * 7)/48;
      }
      if (x < (VFD_WIDTH-2)) {
        raw[y][x+2] += (error * 5)/48;
      }

      if (y < (VFD_HEIGHT-1)) {
        if (x > 2) {
          raw[y+1][x-2] += (error * 3)/48;
        }
        if (x > 1) {
          raw[y+1][x-1] += (error * 5)/48;
        }
        raw[y+1][x] += (error * 7)/48;

        if (x < (VFD_WIDTH-1)) {
          raw[y+1][x+1] += (error * 5)/48;
        }
        if (x < (VFD_WIDTH-2)) {
          raw[y+1][x+2] += (error * 3)/48;
        }
      }

      if (y < (VFD_HEIGHT-2)) {
        if (x > 2) {
          raw[y+2][x-2] += (error * 1)/48;
        }
        if (x > 1) {
          raw[y+2][x-1] += (error * 3)/48;
        }
        raw[y+2][x] += (error * 5)/48;

        if (x < (VFD_WIDTH-1)) {
          raw[y+2][x+1] += (error * 3)/48;
        }
        if (x < (VFD_WIDTH-2)) {
          raw[y+2][x+2] += (error * 1)/48;
        }
      }

    }
  }

  sendToUart();
}
