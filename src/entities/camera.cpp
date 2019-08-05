/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 28/01/2018
 */

#include "camera.h"


Vector3 Camera::down(0.0f, -1.0f, 0.0f);


Camera::Camera(int widthInit, int heightInit): width(widthInit), height(heightInit) {
}


void Camera::getRay(int x, int y, sampleTuple &sample, Scene *scene, Ray &ray) {
  const float recenterX = ( x + sample.spaceX - width  / 2.0f ) / ( 2.0 * width  );
  const float recenterY = ( y + sample.spaceY - height / 2.0f ) / ( 2.0 * height );

  Vector3 start  = scene->camera.position + Vector3(sample.lensX, sample.lensY, 0);
  Vector3 lookAt = scene->camera.lookAt;
  Vector3 right  = (~Vector3(lookAt & down))  * 320;
  Vector3 up     = (~Vector3(lookAt & right)) * 200;
  Vector3 dest   = ~Vector3((right * recenterX) + (up * recenterY) + lookAt - start);

  ray = Ray(start, dest);
}
