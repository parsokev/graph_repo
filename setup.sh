#!/bin/bash

REPO_DIR = "graph_repo"
# Check if directory holding cloned git repository was successfully created after git clone call
if [ ! -d "$REPO_DIR" ]; then
    echo $'Cloning of git repository failed to create expected directory, \'graph_repo\'\nAborting setup process...'
    exit 1
else
    echo $'Directory of git repository \'graph_repo\' found! Attempting to creating build folders...'
fi

# Attempt to enter directory of git repository
cd ./$REPO_DIR
if [ $? -ne 0 ]; then
    echo "Failed to change to \"graph_repo\" directory from current working directory of ${PWD}."
    echo "Please ensure bash script is called at current working directory one level above directory containing git repository"
    exit 1
fi

# Attempt to create main build directory in cloned git repo
mkdir build
if [ $? -ne 0 ]; then
    echo "Failed to create \"build\" directory in cloned repo directory."
    echo "Aborting setup process..."
    exit 1
else
    echo "\"build\" directory successfully created."
fi

# Attempt to create a release subdirectory within build directory
mkdir ./build/release
if [ $? -ne 0 ]; then
    echo "Failed to create \"build/release/\" subdirectory in cloned repo directory."
    echo "Aborting setup process.."
    exit 1
else
    echo "\"release\" subdirectory successfully created."
fi

# Attempt to create debug subdirectory within build directory
mkdir ./build/debug
if [ $? -ne 0 ]; then
    echo "Failed to create \"build/debug/\" subdirectory in cloned repo directory."
    echo "Aborting setup process.."
    exit 1
else
    echo "\"debug\" subdirectory successfully created."
fi

# build cmake projects configured for release and debug within corresponding subdirectories of build
cd ./build/release
cmake -DCMAKE_BUILD_TYPE=Release ../../
make
cd ..
cd ./debug
cmake -DCMAKE_BUILD_TYPE=Debug ../../
make
cd ../../