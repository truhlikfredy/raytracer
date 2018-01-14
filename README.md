# Features

* Using C++11 features. Try new features, but not too new (14/17) so this can be ported to embedded if desired.
* Multi-threaded, will try to use all threads detected on the system (but the load balancer is crude at the moment)
* Randomized multi dimensional sampling in space and time (instead of aliasing it creates noise which is much more pleasing for the eyes, the lens, time jitter is not implemented)
* Phong shading (ambient + difuse + specular lighting)
* Animated light
* Scaling, can be rendered in low-res and then upscaled so the window is decent size
* Using well known predefined materials
* Allow for objects to pass a function as materialFn generator (allows change properties of the materialFn depending on coordinates and other variables)

# TODO (More precisely a wish list)

* Instead of calculating the scene for given time, do calculate the scene per each ray, this will allow for each ray to be in different time (motion blur) and even subpixels in a single pixel be sampled from slightly different time. Allowing easy multi dimensional sampling.
* Private methods
* Sampler using scatered sample points in lens as well. Lens effects and aliasing resistant AA (supersampling can still observe aliasing)
* Display test pattern of the jitter results
* Support different objects (plane, box, donut)
* Support multiple lights and objects in the scene
* Shadows
  *  Soft shadows
* Spot light
* Depth of field effect
* Reflection
* Refraction
* Different materials with different roughfness and textures
  *  Checkerboard
  *  Random 3D noise bump mapping
* Inverse square law to fade off the light with distance
* Film grain: smooth, animated, weighted (shadows are more grainy)

# Dependancies

* Tested on linux
* Using SFML library for window creation and drawing the pixels (sudo apt-get install libsfml-dev)
* cmake for building

# Screenshots

![Two balls with dynamic materials](/images/screenshot02.png)

![Screenshot of a sphere under extreme lens settings](/images/screenshot01.png)

# References

## Anti-Aliasing

https://graphics.pixar.com/library/MultiJitteredSampling/paper.pdf

http://www.pbrt.org/chapters/pbrt_chapter7.pdf

## Shading and Coloring

https://globe3d.sourceforge.io/g3d_html/gl-materials__ads.htm

https://stackoverflow.com/questions/24132774/trouble-with-phong-shading

https://stackoverflow.com/questions/9893316/how-do-i-combine-phong-lighting-with-fresnel-dielectric-reflection-transmission