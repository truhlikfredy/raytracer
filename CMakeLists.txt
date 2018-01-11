cmake_minimum_required(VERSION 3.4)
project(raytracer)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/types/color.cpp
        src/types/color.h
        src/entities/lights/omni.cpp
        src/entities/lights/omni.h
        src/raytracer.cpp
        src/types/vector3.cpp
        src/types/vector3.h src/types/triple.cpp src/types/triple.h src/entities/objects/sphere.h src/entities/objects/sphere.cpp src/render/ray.h src/render/ray.cpp src/frontend/display.cpp src/frontend/display.h src/render/render.cpp src/render/render.h src/render/sampler.cpp src/render/sampler.h src/utils/debounce.cpp src/utils/debounce.h src/entities/objects/object.h src/scene/plain.h src/entities/objects/object.cpp)

add_executable(raytracer ${SOURCE_FILES} src/types/triple.cpp src/types/triple.h)

target_link_libraries(raytracer sfml-graphics sfml-window sfml-system Threads::Threads)
