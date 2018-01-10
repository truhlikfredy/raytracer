/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 10/01/2018
 *
 * This static class is doing crude de-bouncing of the keyboard input events and disables auto-repeat
 */

#include "debounce.h"

bool Debounce::pressed[sf::Keyboard::KeyCount];

bool Debounce::isKeyPressed(sf::Keyboard::Key key) {
  bool ret = false;

  if (sf::Keyboard::isKeyPressed(key))  {
    if (!pressed[key]) {
      // if it was not pressed already then return true
      ret = true;
    }
    pressed[key] = true;
  }
  else {
    pressed[key] = false;
  }

  return(ret);
}

