//
// Created by fredy on 10/01/18.
//

#ifndef RAYTRACER_DEBOUNCE_H
#define RAYTRACER_DEBOUNCE_H

#include <SFML/Window/Keyboard.hpp>

class Debounce {

private:

public:
  static bool pressed[];
  static bool isKeyPressed(sf::Keyboard::Key key);

};

#endif //RAYTRACER_DEBOUNCE_H
