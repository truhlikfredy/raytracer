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


## Anti-Aliasing, motion blur, depth of field lens effects, soft shadows

### Reading materials and introduction theory

http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.552.864&rep=rep1&type=pdf

http://holger.dammertz.org/stuff/notes_HammersleyOnHemisphere.html

https://en.wikipedia.org/wiki/Halton_sequence

http://mathworld.wolfram.com/HammersleyPointSet.html

https://en.wikipedia.org/wiki/Low-discrepancy_sequence

https://steveharveynz.wordpress.com/2012/12/21/ray-tracer-part-5-depth-of-field/

https://graphics.pixar.com/library/MultiJitteredSampling/paper.pdf

http://www.pbrt.org/chapters/pbrt_chapter7.pdf

Bolied down, super sampling where each pixel's rays are divided with perfectly equal and even separation will still cause aliasing, but it will be slightly less noticable. The desire is using randomized sampling instead, to create noise instead of aliasing patterns, which are more pleasing on eyes. Problem is that random distribution can cause some rays to be sampled too close to each other, while neglecting some areas and causing some sparse regions. The goal is to have pseudo randomized sampling which still is close to the perfect grid, desire is to have even volume density.

![different samplers compared](/images/samplers.png)

Some compromises have to be made, if the final sampling size is not known in advance then Halton sampler can be used which is not producing as good results as Hammersley, but for Hammersley the sampling size needs to be known in advance. With Halton sampler the raytracer could be "probing" rays and if desired quality is gained (averageOfAllRaysForThatPixel - lastRay) < delta then sampling can be stopped. So for completely black parts of the scenes the raytracer can only do 2-4 rays to figure out that the pixel is pretty boring and give up. While on complex pixels it can ramup the sampler to much higher samples per pixel.

Other advantages are to combine domains, the brute force aproach is to go through all pixel, for each pixel go through all permutation of space anti aliasing and for each light, for example AA 3x3 by 3 lights. Then for each of these go throug some combinations of time to generate samples over different times to achieve motion blur, for example 6 samples to capture movement. Then for each of these go through 9 variants of different space location inside the camera sensor. Which emuates the depth of field and aperture effects. These extra high dimmension can ramp up complexity very quickly (3x3x3x6x9). Means doing 1458 samples per pixel for a secene with only 3 lights and very low quality AA sampling, bad motion and low quality DOF. So the trick is to overlay samples with other dimensions and shuffle them between each other. While doing antialiasing samples do samples in other higher dimensions as well, while doing 3x3 antiliasing dedicate each sample to different time and different lens aperture location so the complexity will stay just 3x3 while doing everything esle for free.

This freedom alows to get involved even in much higher dimmensions such as soft shadows for area light with very small impact on the performance. To avoid any paterns / corelations and maintain the error seen as noise these samples have to be shuffled between the dimensions on single pixel and between each pixels as well. The quality of the sampler is greatly affecting the performance and quality of the raytracer, not talking about the extra features (motion blur, DOF, soft shadows) which gives almost for free without any significant complexity to code, nor computational complexity.

### Halton sampler

Halton sampler is good when sample size is unknown:

![halton sampler](https://upload.wikimedia.org/wikipedia/commons/a/a5/Halton_sequence_2_3.svg)

In 1D dimension the halton distributes pretty well and splits the unsampled left space into halves (if base is 2, or thirds when base is 3). The good feature is that it will be able to give as much samples as needed, while even small sample size will get even coverage.
Both x and y are produced with radicalInverse functions, but with different bases (in the picture x is base 2 and y is base 3), it' important to chose good base numbers which are prime and still have to pay extra attention which one are chosen, because some bases produce almost identical outcomes.


### Hammersley

The x is divided evenly between the samples (they total num of samples has to be known in advance) and the Y is calculated
by radical inverse function. This make it hard to fit any good new samples into already existing sample set and the sample size can't grow as in Hlaton sampler:

![few samples](/images/hammersley1.png)

![more samples](/images/hammersley2.png)


## Shading and Coloring

https://globe3d.sourceforge.io/g3d_html/gl-materials__ads.htm

https://stackoverflow.com/questions/24132774/trouble-with-phong-shading

https://stackoverflow.com/questions/9893316/how-do-i-combine-phong-lighting-with-fresnel-dielectric-reflection-transmission