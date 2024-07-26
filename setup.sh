#!/bin/bash

# Ensure cmake is installed
cmake --version
if [ $? -ne 0 ]; then 
    echo "cmake is required in order to properly utlize the project."
    echo "Please visit to https://www.kitware.com/cmake-3-30-1-available-for-download/ to download most updated version"
    kill -INT 0
fi

# Check if directory holding cloned git repository was successfully created after git clone call
if [ ! -d "graph_repo" ]; then
    echo $'Cloning of git repository failed to create expected directory, \'graph_repo\'\nAborting setup process...'
    kill -INT 0
else
    echo $'Directory of git repository \'graph_repo\' found! Attempting to creating build folders...'
fi

# Attempt to enter directory of git repository
cd ./graph_repo
if [ $? -ne 0 ]; then
    echo "Failed to change to \"graph_repo\" directory from current working directory of ${PWD}."
    echo "Please ensure bash script is called at current working directory one level above directory containing git repository"
    kill -INT 0
fi

# Attempt to create main build directory in cloned git repo
mkdir build
if [ $? -ne 0 ]; then
    echo "Failed to create \"build\" directory in cloned repo directory."
    echo "Aborting setup process..."
    kill -INT 0
else
    echo "\"build\" directory successfully created."
fi

# Attempt to create a release subdirectory within build directory
mkdir ./build/release
if [ $? -ne 0 ]; then
    echo "Failed to create \"build/release/\" subdirectory in cloned repo directory."
    echo "Aborting setup process.."
    kill -INT 0
else
    echo "\"release\" subdirectory successfully created."
fi

# Attempt to create debug subdirectory within build directory
mkdir ./build/debug
if [ $? -ne 0 ]; then
    echo "Failed to create \"build/debug/\" subdirectory in cloned repo directory."
    echo "Aborting setup process.."
    kill -INT 0
else
    echo "\"debug\" subdirectory successfully created."
fi

# build cmake projects configured for release and debug within corresponding subdirectories of build
cd ./build/release
echo "building cmake project in debug and release configurations..."
cmake -DCMAKE_BUILD_TYPE=Release ../../
make
cd ..
cd ./debug
cmake -DCMAKE_BUILD_TYPE=Debug ../../
make
cd ../../

# Provide Usage Instructions
echo "Both CMake projects have been successfully built and compiled!"
echo "To Run in Release Mode, Enter into the Terminal: \"./build/release/Graph_TIProject\""
echo "To Run in Debug Mode, Enter into the Terminal: \"./build/debug/Graph_TIProject\""
echo "To Run all tests within GoogleTest testing suite. Enter: \"./build/tests\" or \"./debug/tests\""