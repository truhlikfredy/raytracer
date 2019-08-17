/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 08/01/2018
 */

#include <cmath>
#include "sphere.h"
#include "../../utils/utils.h"

// Sphere::Sphere(std::function<Sphere(float frame)> propertiesFnInit): Object(propertiesFnInit) {
// }

Sphere::Sphere(Vector3 centerInt, float radiusInit):  Object(centerInt) {
  radius = radiusInit;
}

Sphere::Sphere(Vector3 centerInt, float radiusInit, std::function<materialStatic(Vector3 point, float frame)> materialFnInit):
  Object(centerInt, materialFnInit) {
  radius = radiusInit;
}

Sphere::Sphere(Vector3 centerInt, float radiusInit, materialStatic material):
  Object(centerInt, material) {
  radius = radiusInit;
}

Sphere::Sphere():Object() {

}

// Get normalized normal vector from sphere's surface point
Vector3 Sphere::operator ^ (Vector3 pointOnSurface) {
  return ~Vector3(pointOnSurface - this->center);
}

float Sphere::detectHit(Ray ray) {
  // http://mathforum.org/mathimages/index.php/Ray_Tracing
  // All points at sphere's surface meet this equation:
  // (point - center).(point - center) - radius^2 = 0
  // While any point on the ray's path can be calculated:
  // point = source + direction * hitDistance
  // Source and direction are known, reversing the equations to find if there
  // is a hitDistance on the path which meets sphere's equation.
  Vector3 inRef   = ray.source - this->center;
  float   dotDir  = ray.direction % ray.direction;
  float   temp1   = (ray.direction % inRef);
  float   temp2   = (inRef % inRef) - this->radius * this->radius;
  float   tempAll = temp1 * temp1 - dotDir * temp2;

  if (tempAll < 0) return -1.0f; // The ray didn't hit the sphere at all

  // 2 points are intersecting the sphere, chose the closest point to the camera
  float hitDistance = fminf( (-temp1 + sqrt(tempAll)) / dotDir,
                             (-temp1 - sqrt(tempAll)) / dotDir );

  if (hitDistance <= 0 ) return -1.0f;
  return hitDistance;
}

float Sphere::detectHit(Ray ray, Vector3 &hitPoint) {
  // http://mathforum.org/mathimages/index.php/Ray_Tracing
  // All points at sphere's surface meet this equation:
  // (point - center).(point - center) - radius^2 = 0
  // While any point on the ray's path can be calculated:
  // point = source + direction * hitDistance
  // Source and direction are known, reversing the equations to find if there
  // is a hitDistance on the path which meets sphere's equation.
  Vector3 inRef   = ray.source - this->center;
  float   dotDir  = ray.direction % ray.direction;

  //if (dotDir < 0 ) return -1.0f;

  float   temp1   = (ray.direction % inRef);
  float   temp2   = (inRef % inRef) - this->radius * this->radius;
  float   tempAll = temp1 * temp1 - dotDir * temp2;

  if (tempAll < 0) return -1.0f; // The ray didn't hit the sphere at all

  // 2 points are intersecting the sphere, chose the closest point to the camera
  float distanceA = (-temp1 + sqrt(tempAll)) / dotDir;
  float distanceB = (-temp1 - sqrt(tempAll)) / dotDir;
  float hitDistance;

  // Skip if both points are behind the ray
  if (distanceA <0.0f && distanceB <0.0f )
    return -1.0f;

  if (distanceA >0.0f && distanceB >0.0f )
    // Choose the closest when both points are in front of ray
    hitDistance= fminf( distanceA, distanceB);
  else {
    // If one point is behind the ray, we must be inside the object, pick the point in front of the ray
    hitDistance= fmaxf( distanceA, distanceB);

    // Just in case the point on front you is just tiny miscalculation (rounding error) and actually it's the
    // very same point you just bounced from, then do not consider it as a hit, as it could be then counted
    // as new reflection or as point which is throwing shadow on itself
    if (hitDistance < 0.05f) return -1;
  }
  //
//  if (distanceA <0 && distanceB >0 )
//    hitDistance=distanceB;
//  else if (distanceB <0 && distanceA >0)
//    hitDistance=distanceA;
//  else
//  if (hitDistance < 0.0f) {
//    hitDistance = fmaxf(distanceA, distanceB);
//  }
//  if (hitDistance <= 0.0f ) return -1.0f;

  hitPoint = ray.source + ray.direction * hitDistance;

  return hitDistance;
}


float Sphere::detectHitMax(Ray ray, Vector3 &hitPoint) {
  // http://mathforum.org/mathimages/index.php/Ray_Tracing
  // All points at sphere's surface meet this equation:
  // (point - center).(point - center) - radius^2 = 0
  // While any point on the ray's path can be calculated:
  // point = source + direction * hitDistance
  // Source and direction are known, reversing the equations to find if there
  // is a hitDistance on the path which meets sphere's equation.
  Vector3 inRef   = ray.source - this->center;
  float   dotDir  = ray.direction % ray.direction;

  if (dotDir < 0 ) return -1.0f;

  float   temp1   = (ray.direction % inRef);
  float   temp2   = (inRef % inRef) - this->radius * this->radius;
  float   tempAll = temp1 * temp1 - dotDir * temp2;

  if (tempAll < 0) return -1.0f; // The ray didn't hit the sphere at all

  // 2 points are intersecting the sphere, chose the closest point to the camera
  float hitDistance = fmaxf( (-temp1 + sqrtf(tempAll)) / dotDir,
                             (-temp1 - sqrtf(tempAll)) / dotDir );

  if (hitDistance <= 0 ) return -1.0f;

  hitPoint = ray.source + ray.direction * hitDistance;

  return hitDistance;
}


uv Sphere::toUv(Vector3 point) {
  // https://gamedev.stackexchange.com/a/114416
  // https://en.wikipedia.org/wiki/UV_mapping

  Vector3 newPoint = ~Vector3(this->center - point);
  return {
    .u = atan2f(newPoint.x, newPoint.z) / (2.0f * M_PI_F) + 0.5f,
    .v = 0.5f - asinf(newPoint.y) / M_PI_F
  };
}