cmake_minimum_required(VERSION 3.4)
project(raytracer)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/color.cpp
    src/color.h
    src/light.cpp
    src/light.h
        src/raytracer.cpp
        src/vector3.cpp
        src/vector3.h src/triple.cpp src/triple.h src/sphere.h src/sphere.cpp src/ray.h src/ray.cpp src/display.cpp src/display.h src/render.cpp src/render.h)

add_executable(raytracer ${SOURCE_FILES} src/triple.cpp src/triple.h)

target_link_libraries(raytracer sfml-graphics sfml-window sfml-system Threads::Threads)
