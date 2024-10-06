#!/opt/homebrew/bin/bash

# Script will only run if homebrew exists with bash env
echo "Checking for updates to local version of Homebrew..."
brew update && brew upgrade
if [ $? -ne 0 ]; then 
echo "Error encountered while attempting to update brew... please visit https://brew.sh/ for troubleshooting."
echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
kill -INT 0
fi

echo "Attempting to install dependencies and update to most current stable version..."
brew -y --ignore-missing install $(< ./graph_repo/mac_requirements.txt)

if [ $? -ne 0 ]; then
    echo "Error: Failed to install all package dependencies listed in \"requirements.txt\""
    echo "Please ensure you have not moved \"requirements.txt\" from its original position within the cloned repository"
    echo "If you wish to retry at any time, simply delete the \"build\" directory and re-run setup script"
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
    kill -INT 0
fi

# Attempt to enter directory of git repository
cd ./graph_repo
if [ $? -ne 0 ]; then
    echo "Failed to change to \"graph_repo\" directory from current working directory of ${PWD}."
    echo "Please ensure bash script is called at current working directory one level above directory containing git repository (level at which git clone was called)"
    echo "If you wish to retry at any time, simply delete the \"build\" directory and re-run setup script"
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
    kill -INT 0
fi

# Attempt to create main build directory in cloned git repo
mkdir build
if [ $? -ne 0 ]; then
    echo "Failed to create \"build\" directory in cloned repo directory."
    echo "Aborting setup process..."
    echo "If you wish to retry at any time, simply delete the \"build\" directory and re-run setup script"
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
    kill -INT 0
else
    echo "\"build\" directory successfully created."
fi

# Attempt to create a release subdirectory within build directory
mkdir ./build/release
if [ $? -ne 0 ]; then
    echo "Failed to create \"build/release/\" subdirectory in cloned repo directory."
    echo "Aborting setup process.."
    echo "If you wish to retry at any time, simply delete the \"build\" directory and re-run setup script"
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
    kill -INT 0
else
    echo "\"release\" subdirectory successfully created."
fi

# Attempt to create debug subdirectory within build directory
mkdir ./build/debug
if [ $? -ne 0 ]; then
    echo "Failed to create \"build/debug/\" subdirectory in cloned repo directory."
    echo "Aborting setup process.."
    echo "If you wish to retry at any time, simply delete the \"build\" directory and re-run setup script"
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
    kill -INT 0
else
    echo "\"debug\" subdirectory successfully created."
fi

# build cmake projects configured for release and debug within corresponding subdirectories of build
cd ./build/release
echo "building cmake project in debug and release configurations..."

# Generate CMakefile for Release Configuration of CMake Project
CMAKE_BUILD_PARALLEL_LEVEL=8 cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ ../../
if [ $? -ne 0 ]; then
    echo "Failed to create CMake \"Release\" Configuaration in \"build/release/\" subdirectory in cloned repo directory."
    echo "Please ensure you are calling script from top level directory. Aborting setup process.."
    echo "If you wish to retry at any time, simply delete the \"build\" directory and re-run setup script according to README instructions"
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
    cd ../../../
    kill -INT 0
else
    echo "Attempting to build \"Release\" configuration using generated CMakefile..."
fi

# Attempt to build Release Configuration based on generated CMakefile
make
if [ $? -ne 0 ]; then
    echo "Failed to build CMake \"Release\" Configuaration in \"build/release/\" subdirectory in cloned repo directory."
    echo "Please ensure you are calling script from top level directory. Aborting setup process.."
    echo "If you wish to retry at any time, simply delete the \"build\" directory and re-run setup script according to README instructions"
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
    cd ../../../
    kill -INT 0
else
    echo "\"Release\" Configuration of CMake Project successfully built!"
fi


cd ../debug
# Generate CMakefile for Debug Configuration of CMake Project
CMAKE_BUILD_PARALLEL_LEVEL=8 cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ ../../
if [ $? -ne 0 ]; then
    echo "Failed to create CMake \"Debug\" Configuaration in \"build/debug/\" subdirectory in cloned repo directory."
    echo "Please ensure you are calling script from top level directory. Aborting setup process.."
    echo "If you wish to retry at any time, simply delete the \"build\" directory and re-run setup script according to README instructions"
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
    cd ../../../
    kill -INT 0
else
echo "Attempting to build \"Debug\" configuration using generated CMakefile..."
fi

# Attempt to build Debug Configuration based on generated CMakefile
make
if [ $? -ne 0 ]; then
    echo "Failed to build CMake \"Debug\" Configuaration in \"build/debug/\" subdirectory in cloned repo directory."
    echo "Please ensure you are calling script from top level directory. Aborting setup process.."
    echo "If you wish to retry at any time, simply delete the \"build\" directory and re-run setup script according to README instructions"
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
    cd ../../../
    kill -INT 0
else
    echo "\"Debug\" Configuration of CMake Project successfully built!"
fi

cd ../../

# Provide Usage Instructions

echo ""
echo "Both CMake projects have been successfully built and compiled!"
echo ""
echo "EXECUTING PROGRAM:"
echo "To Run the Program in Release Mode, Enter into the Terminal: \"./build/release/Graph_TIProject\""
echo "To Run the Program in Debug Mode, Enter into the Terminal: \"./build/debug/Graph_TIProject\""
echo ""
echo "EXECUTING TESTING SUITE:"
echo "To Run all tests within GoogleTest testing suite, Enter: \"./build/release/tests\" or \"./build/debug/tests\" for additional reporting"
echo ""
echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"