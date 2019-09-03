//
// Created by fredy on 03/09/2019.
//

#ifndef RAYTRACER_SETTINGS_H
#define RAYTRACER_SETTINGS_H

#define RENDER_COMPLEXITY 2  // Predefined resolutions, see display.h

#define SEGMENTS 1  // how many partitions the screen should be split
#define SAMPLING_MIN 2  // Samples per light, the final sampling will change depending on the lights present in the scene
#define SAMPLING_MAX 5
#define SAMPLING_DELTA 0.03f
#define MAX_BOUNCES 4
//#define CHROMATIC_ABERRATION_REFRACTION // Comment out to disable
#define CHROMATIC_ABERRATION_STRENGTH 0.02f

//#define AABB // Comment out to disable axis aligned bounding box detection
// Only improvements seen is in the empty and simple scene like the plain.cpp
// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
// http://www.jcgt.org/published/0007/03/04/paper-lowres.pdf
// https://medium.com/@bromanz/another-view-on-the-classic-ray-aabb-intersection-algorithm-for-bvh-traversal-41125138b525


#endif //RAYTRACER_SETTINGS_H
