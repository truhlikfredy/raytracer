# Features

## UI

* 320x200 fixed resolution (prepared for TFT screen when ported)
  * Scaling, can be rendered in low-res and then upscaled so the window is decent size
* **S** to display test pattern of the pseudo randomized sampler results
* **C** capture screenshots
* **Left/Right** switch between scenes

## Programing

* Using C++11 features. Try new features, but not too new (14/17) so this can be ported to embedded if desired (avoid loading files/textures)
* Allowed portability by keeping it software only renderer, did not went OpenCL, Cuda route even when it's tempting.
* Whole raytracer is designed from ground up to smallers scenes, it will not handle huge scenes well.
* Multi-threaded, will try to use all threads detected on the system (but the load balancer is crude at the moment)
  *  Keet MT support very simple, no extra syncing required.
* Travis build on each commit

## Rendering

* Instead of calculating the scene for given time, it calculates the scene per each ray, this will allow for each ray to be in different time (motion blur) and even subpixels in a single pixel be sampled from slightly different time. Allowing easy multi dimensional sampling.
* Randomized multi dimensional sampling in space and time (instead of aliasing it creates noise which is much more pleasing for the eyes, the lens, time jitter is not implemented)
* Phong shading (ambient + difuse + specular lighting)
* Animated light and objects (they are lamba functions depending on time)
* Using well known predefined materials
* Multiple objects per scene
* Allow for objects to pass a function as materialFn generator (allows change properties of the materialFn depending on coordinates and other variables)
* Shadows
* Mandelbrot fractal as a texture/material with different "shine" properties in different sections

# TODO (More precisely a wish list)

* More agresive private methods
* Dynamicly adjusting sampler, allowing a range of samples per pixel and ability to stop wheneve desire quality (delta) is achieved
* Improve test pattern of the jitter results
* Support different objects (plane, box, donut)
* Support multiple lights and objects in the scene
  *  Soft shadows
* Save videos as well.
* Different light types: Spot light, Area flood light.
* Do not shade object until it's for sure it's the winning depth (could be falsely rendered just for different object and depth wining the final result)
* Depth of field effect
* Reflection
* Refraction
* Different materials with different roughfness and textures
  *  Checkerboard
  *  Random 3D noise bump mapping
  *  Results of lamba functions
* Inverse square law to fade off the light with hitDistance
* Film grain: smooth, animated, weighted (shadows are more grainy)

# Dependancies

* Tested on linux, windows could be supported but a the moment didn't spend any effort.
* Using SFML library for window creation and drawing the pixels (sudo apt-get install libsfml-dev)
* cmake for building

# Screenshots

![Two balls with dynamic materials](/images/screenshot02.png)

![First working motion blur](/images/screenshot03.png)

![Shadows](/images/screenshot04.png)

![Depth of field example](/images/screenshot05.png)

![fractal with different shiny properties](/images/screenshot06.png)

![fractal with different shiny properties](/images/screenshot07.png)

![Screenshot of a sphere under extreme lens settings](/images/screenshot01.png)

# References

## Raytracing

https://steveharveynz.wordpress.com/category/programming/c-raytracer/

## UV mapping

https://en.wikipedia.org/wiki/UV_mapping

https://gamedev.stackexchange.com/a/114416

https://stackoverflow.com/questions/41661369/smoothly-mapping-a-2d-uv-point-onto-a-3d-xyz-sphere


## Anti-Aliasing, motion blur, lens effects

https://steveharveynz.wordpress.com/2012/12/21/ray-tracer-part-5-depth-of-field/

https://graphics.pixar.com/library/MultiJitteredSampling/paper.pdf

http://www.pbrt.org/chapters/pbrt_chapter7.pdf

## Shading and Coloring

https://globe3d.sourceforge.io/g3d_html/gl-materials__ads.htm

https://stackoverflow.com/questions/24132774/trouble-with-phong-shading

https://stackoverflow.com/questions/9893316/how-do-i-combine-phong-lighting-with-fresnel-dielectric-reflection-transmission