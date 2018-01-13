//
// Created by fredy on 13/01/18.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <vector>
#include "../entities/entity.h"
#include "../entities/objects/object.h"

class Scene {
public:
  float frame;

  std::vector<Entity> lights;
  std::vector<Object> objects;

  void evaluate(Scene staticScene, float frameInit);

};

#endif //RAYTRACER_SCENE_H
