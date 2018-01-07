# Features

* Multi-threaded, will try to use all threads detected on the system.
* Anti-aliasing at moment is done through super-sampling
* Phong shading (ambient + difuse + specular lighting)
* Animated light

# TODO

* Jitter randomized AA, with scatered sample points in space, time and lens settings, which should allow motion blur, lens effects and aliasing resistant AA (supersampling can still observe aliasing)
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


# Screenshots

![Screenshot of a sphere](/images/screenshot01.png)