#!/opt/homebrew/bin/bash

# Script will only run if homebrew exists with bash env
echo "Attempting to update homebrew..."
brew update && brew upgrade
if [ $? -ne 0 ]; then 
echo "Error encountered while attempting to update brew... please visit https://brew.sh/ for troubleshooting."
kill -INT 0
fi

echo "Attempting to install dependencies and update to most current stable version..."
brew -y --ignore-missing install $(< ./graph_repo/requirements.txt)

if [ $? -ne 0 ]; then
    echo "Error: Failed to install all package dependencies listed in \"requirements.txt\""
    echo "Please ensure you have not moved \"requirements.txt\" from its original position within the cloned repository"
    kill -INT 0
fi

# Attempt to enter directory of git repository
cd ./graph_repo
if [ $? -ne 0 ]; then
    echo "Failed to change to \"graph_repo\" directory from current working directory of ${PWD}."
    echo "Please ensure bash script is called at current working directory one level above directory containing git repository (level at which git clone was called)"
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
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ ../../
make
cd ..
cd ./debug
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ ../../
make
cd ../../

# Provide Usage Instructions
echo "Both CMake projects have been successfully built and compiled!"
echo "To Run in Release Mode, Enter into the Terminal: \"./build/release/Graph_TIProject\""
echo "To Run in Debug Mode, Enter into the Terminal: \"./build/debug/Graph_TIProject\""
echo "To Run all tests within GoogleTest testing suite. Enter: \"./build/tests\" or \"./build/tests\""