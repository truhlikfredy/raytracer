#!/bin/bash

mkdir Debug
cd Debug
cmake ../
make -j2

cd ..
mkdir Release
cd Release
cmake -DCMAKE_BUILD_TYPE=Release ../
make -j2

./raytracer