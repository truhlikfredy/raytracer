//
// Created by fredy on 11/01/18.
//

#include "object.h"

Object::Object(std::function<Color(Vector3 point)> material): material(material) {

}

//Color getColorAt(Vector3 point)