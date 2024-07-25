#!/bin/bash

cd ./graph_repo
mkdir build
mkdir ./build/release
mkdir ./build/debug
cmake -B ./build -S ../graph_repo
cd ./build
make
cd ./release
cmake -DCMAKE_BUILD_TYPE=Release ../../
make
cd ..
cd ./debug
cmake -DCMAKE_BUILD_TYPE=Debug ../../
make
cd ../../