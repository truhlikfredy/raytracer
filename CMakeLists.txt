cmake_minimum_required(VERSION 3.4)
project(raytracer)

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/types/color.cpp
        src/types/color.h
        src/entities/lights/lightOmni.cpp
        src/entities/lights/lightOmni.h
        src/raytracer.cpp
        src/types/vector3.cpp
        src/types/vector3.h src/types/triple.cpp src/types/triple.h src/entities/objects/sphere.h src/entities/objects/sphere.cpp src/render/ray.h src/render/ray.cpp src/frontend/display.cpp src/frontend/display.h src/render/render.cpp src/render/render.h src/render/sampler.cpp src/render/sampler.h src/utils/debounce.cpp src/utils/debounce.h src/entities/objects/object.h src/scenes/plain.h src/entities/objects/object.cpp src/entities/objects/materials.h src/entities/objects/materials.cpp src/entities/entity.h src/entities/entity.cpp src/scenes/scene.h src/scenes/scene.cpp src/scenes/plain.cpp src/entities/objects/sphereGen.h src/entities/objects/sphereGen.cpp src/entities/lights/lightOmniGen.h src/entities/lights/lightOmniGen.cpp src/scenes/dof.h src/scenes/dof.cpp src/scenes/mandelbrot.h src/scenes/mandelbrot.cpp src/scenes/lights.h src/scenes/lights.cpp src/scenes/large.h src/scenes/large.cpp src/scenes/large2.h src/scenes/large2.cpp src/utils/utils.h src/utils/utils.cpp src/entities/camera.h src/entities/camera.cpp)

add_executable(raytracer ${SOURCE_FILES} src/types/triple.cpp src/types/triple.h)

target_link_libraries(raytracer sfml-graphics sfml-window sfml-system Threads::Threads)
