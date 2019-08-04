![refractions](/images/screenshot13.png)

![reflections inside a refraction](/images/screenshot14.png)

![refractions](/images/screenshot12.png)

![refractions](/images/screenshot11.png)

# Features

## UI

* Optimized for 320x200 resolution (prepared for TFT screen when ported)
  * Scaling, can be rendered in low-res and then upscaled so the window is decent size
  * Does work corectly on higher resolutions but, it's mostly tested on low res
* **S** to display test pattern of the pseudo randomized sampler results
* **C** capture screenshots
* **Left/Right** switch between scenes
* **\[** and **\]** jump in time (jump back is smaller than jump forward)
* **B** will start benchmark of a sellected scne and when finished it will exit
* **,** and **.** will change speed of time

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
    * Moved from jittered sampler to radical inverse functions.
* Phong shading (ambientStatic + difuse + specular lighting)
* Animated light and objects (they are lamba functions depending on time)
* Using well known predefined materials
* Depth of field effect
* Multiple objects per scene
* Allow for objects to pass a function as materialFn generator (allows change properties of the materialFn depending on coordinates and other variables)
* Support multiple lights and objects in the scene
* Shadows
* Reflection
* Mandelbrot fractal as a texture/material with different "shine" properties in different sections
* Dynamicly adjusting sampler, allowing a range of samples per pixel and ability to stop wheneve desire quality (delta) is achieved
* Improved performance on scenes where there is no motion blur (means that the scene is evaluated only once and not for each ray in each pixel). Benchmark parameters: Width=320 Height=200 SamplingMin=2 SamplingMax=4 Bounches=4. On complex scenes such as "large2" it decreased from 75 seconds to calculate 25 frames to 48seconds. For "lights" it improved from 73 seconds to calculate 120 frames to 52 seconds. Scenes with motion blur enable do not have any benefit and scene with low complexity have mesurable improvement but not as much as complex scenes.
* primitive variant of inverse square law

# TODO (More precisely a wish list)

* Rays should detect hits for AABBs (Axis-aligned bounding boxes) first to save on resources
* More agresive private methods
* Improve test pattern of the jitter results
* Support different objects (plane, box, donut)
* Objects and camera transform (rotation, movement)
* Soft shadows
* Save videos as well.
* Different light types: Spot light, Area flood light.
* Do not shade object until it's for sure it's the winning depth (could be falsely rendered just for different object and depth wining the final result)
* Refraction
* Different materials with different roughfness and textures
  *  Checkerboard
  *  Random 3D noise bump mapping
  *  Results of lamba functions
* Inverse square law to fade off the light with hitDistance
* Film grain: smooth, animated, weighted (shadows are more grainy)
* Render only few time instances of the scene for the whole frame so each pixel doesn't have to be unique time instance, this will have small impact on quality on subpixel level, but large impact on quality.

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

![multiple lights = multiple shadows](/images/screenshot08.png)

![chekerboard with DOF effect and multiple lights](/images/screenshot09.png)

![reflections](/images/screenshot10.png)

# References

## Raytracing

https://steveharveynz.wordpress.com/category/programming/c-raytracer/

## UV mapping

https://en.wikipedia.org/wiki/UV_mapping

https://gamedev.stackexchange.com/a/114416

https://stackoverflow.com/questions/41661369/smoothly-mapping-a-2d-uv-point-onto-a-3d-xyz-sphere

## Coloring, phong-shading, Lights

https://stackoverflow.com/questions/24132774/trouble-with-phong-shading

https://stackoverflow.com/questions/9893316/how-do-i-combine-phong-lighting-with-fresnel-dielectric-reflection-transmission

http://manual.reallusion.com/Character_Creator/ENU/1/15_Multiple_Channel_Texture_Mapping/Modifying_Texture_Settings_Advanced.htm

https://globe3d.sourceforge.io/g3d_html/gl-materials__ads.htm#25_8

http://pratapdafedar.blogspot.ie/2013/05/all-about-opengl.html

https://www.livehome3d.com/support/lh3d-help/images/specular1.png


## Anti-Aliasing, motion blur, depth of field lens effects, soft shadows

### Reading materials and introduction theory

Amazing book on this subject is
Physically Based Rendering: From Theory to Implementation
http://www.pbrt.org/

Even sample chapter is very useful for this raytracer


http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.552.864&rep=rep1&type=pdf

http://holger.dammertz.org/stuff/notes_HammersleyOnHemisphere.html

https://en.wikipedia.org/wiki/Halton_sequence

http://mathworld.wolfram.com/HammersleyPointSet.html

https://en.wikipedia.org/wiki/Low-discrepancy_sequence

https://steveharveynz.wordpress.com/2012/12/21/ray-tracer-part-5-depth-of-field/

https://graphics.pixar.com/library/MultiJitteredSampling/paper.pdf

http://www.pbrt.org/chapters/pbrt_chapter7.pdf

https://cims.nyu.edu/~regev/teaching/lattices_fall_2004/ln/introduction.pdf

http://citeseerx.ist.psu.edu/viewdoc/download;jsessionid=A2A2605C68EBF68DE1FCD941AFCA8EA8?doi=10.1.1.871.3498&rep=rep1&type=pdf

http://slideplayer.com/slide/8978898/

Bolied down, super sampling where each pixel's rays are divided with perfectly equal and even separation will still cause aliasing, but it will be slightly less noticable. The desire is using randomized sampling instead, to create noise instead of aliasing patterns, which are more pleasing on eyes. Problem is that random distribution can cause some rays to be sampled too close to each other, while neglecting some areas and causing some sparse regions. The goal is to have pseudo randomized sampling which still is close to the perfect grid, desire is to have even volume density.

![different samplers compared](/images/samplers.png)

Regular sampler can also cause undesired moire effects.

Some compromises have to be made, if the final sampling size is not known in advance then Halton sampler can be used which is not producing as good results as Hammersley, but for Hammersley the sampling size needs to be known in advance. With Halton sampler the raytracer could be "probing" rays and if desired quality is gained (averageOfAllRaysForThatPixel - lastRay) < delta then sampling can be stopped. So for completely black parts of the scenes the raytracer can only do 2-4 rays to figure out that the pixel is pretty boring and give up. While on complex pixels it can ramup the sampler to much higher samples per pixel.

Other advantages are to combine domains, the brute force aproach is to go through all pixel, for each pixel go through all permutation of space anti aliasing and for each light, for example AA 3x3 by 3 lights. Then for each of these go throug some combinations of time to generate samples over different times to achieve motion blur, for example 6 samples to capture movement. Then for each of these go through 9 variants of different space location inside the camera sensor. Which emuates the depth of field and aperture effects. These extra high dimmension can ramp up complexity very quickly (3x3x3x6x9). Means doing 1458 samples per pixel for a secene with only 3 lights and very low quality AA sampling, bad motion and low quality DOF. So the trick is to overlay samples with other dimensions and shuffle them between each other. While doing antialiasing samples do samples in other higher dimensions as well, while doing 3x3 antiliasing dedicate each sample to different time and different lens aperture location so the complexity will stay just 3x3 while doing everything esle for free.

This freedom alows to get involved even in much higher dimmensions such as soft shadows for area light with very small impact on the performance. To avoid any paterns / corelations and maintain the error seen as noise these samples have to be shuffled between the dimensions on single pixel and between each pixels as well. The quality of the sampler is greatly affecting the performance and quality of the raytracer, not talking about the extra features (motion blur, DOF, soft shadows) which gives almost for free without any significant complexity to code, nor computational complexity. Some of the samplers will work well even without getting power of 2 samples.

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

Notice the larger sample size contains the previous smaller sample size.

### Radical inverse function

In essence it converts the index input number into a binary represation (for example base 2) and then mirrors the result:

 | Index input   | Base 2 value  | Radical inverse value |
 | ------------- | ------------- | --------------------- |
 | 1             |             1 | .1   (1/2)            |
 | 2             |            10 | .01  (1/4)            |
 | 3             |            11 | .11  (3/4)            |
 | 4             |           100 | .001 (1/8)            |
 | 5             |           101 | .101 (5/8)            |

 Both Halton and Hammersley samplers are using this function.

### Folded radical inverse function

Is slightly modified variant of radical inverse function which gains better distribution and less frequent "grouping" of the samples. By adding i offset to i-th sample.
Both halton and hammersley can use it, but it has strongest effect on halton.

### van der Corput sequence

Is in essence radical inverse function with base fixed to 2. Base has interesting property which can be used for advantage. Using regular XOR can be equivalent of shuffling and van der Corput can be improved to accept "pattern" which will be "suffled" with to randomize the outputs. XOR is very fast and function can produce decent samples with mininal system requirements.

### radical inverse function due to Sobol'

Is modified inverse function which can be used together with van der Corupt, is base 2 and pattern can be used to XOR / shuffle the pattern. When ech van der Corup and Sobol'2 are used for samples they create sampling set which satifies condition where there is only 1 point in the grid cell. This is true no matter how "sliced the pixel is", for 1 pixel which contains 16 samples, the grid can be 4x4, 2x8, 8x2, 16x1 and 1x16 and there will be only 1 sample per cell. Meaning that the samples are not grouping up and are evenly distributed. Also this can be suffled pretty well.


## Shading and Coloring

https://globe3d.sourceforge.io/g3d_html/gl-materials__ads.htm

https://stackoverflow.com/questions/24132774/trouble-with-phong-shading

https://stackoverflow.com/questions/9893316/how-do-i-combine-phong-lighting-with-fresnel-dielectric-reflection-transmission

http://en.wikipedia.org/wiki/Color_difference
