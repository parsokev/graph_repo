#!/usr/bin/env bash

# Check for Local OS Type
case "$(uname -sr)" in
   Darwin*)
     Platform='MAC_OS_X'
     ;;

   Linux*)
     Platform='Linux'
     ;;
   CYGWIN*|MINGW*|MINGW32*|MSYS*)
     Platform='Windows'
     ;;  
    *)
     Platform='Unrecognized'
     ;;
esac

# If Linux, attempt to update distribution and install dependencies
if [[ "$Platform" == 'Linux' ]]; then
    sudo apt-get -y update && sudo apt-get -y upgrade

    if [ $? -ne 0 ]; then 
        echo "Error in checking for unknown linux distribution has been detected."
        kill -INT 0
    fi
    sudo apt-get -y --ignore-missing install $(< requirements.txt)

    if [ $? -ne 0 ]; then
        echo "Failed to install package dependencies"
        echo "cmake is required in order to properly utlize the project."
        echo "Please visit to https://www.kitware.com/cmake-3-30-1-available-for-download/ to download most updated version"
        kill -INT 0
    fi

# If MacOSX, attempt to update Homebrew and install dependencies using Homebrew
elif [[ "$Platform" == 'MAC_OS_X']]; then
    echo "Mac OS detected. Please ensure you have Homebrew installed before continuing!"
    echo "Attempting to update homebrew..."
    
    brew --version
    if [ $? -ne 0 ]; then 
    echo "Homebrew not detected on local machine... please visit https://brew.sh/ to have Homebrew installed."
    kill -INT 0
    fi

    brew update && brew upgrade
    if [ $? -ne 0 ]; then 
    echo "Error encountered while attempting to update brew... please visit https://brew.sh/ for troubleshooting."
    kill -INT 0
    fi

    brew -y --ignore-missing install $(< requirements.txt)

    if [ $? -ne 0 ]; then
        echo "Failed to install package dependencies"
        echo "Please visit https://brew.sh/ to ensure you have Homebrew properly installed on your local machine."
        kill -INT 0
    fi

# If Windows is detected, notify of script incompatibility
elif [["$Platform" == 'Windows']]; then
    echo "Windows detected. Please visit https://learn.microsoft.com/en-us/windows/wsl/install to in order to run this script in a Linux environment."
    echo "Script is unable to run within Windows Powershell"
    kill -INT 0

# If OS is not recognized, exit with notification
else
    echo "Unrecognized distribution. If running in Linux environment other than Debian or Ubuntu, this script is currently unable to run in these environments."
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
echo "To Run all tests within GoogleTest testing suite. Enter: \"./build/release/tests\" or \"./build/debug/tests\""