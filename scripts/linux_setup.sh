#!/usr/bin/env bash

# Check for Local OS Type
case "$(uname -sr)" in
   Darwin*)
     Platform='MAC_OS_X'
     ;;
   Linux*)
     Platform='Linux'
     ;;
    *)
     Platform='Unrecognized'
     ;;
esac

# If Linux, attempt to update distribution and install dependencies
if [[ "$Platform" == 'Linux' ]]; then
    echo "Checking for updates to Ubuntu Distribution..."
    sudo apt-get -y update && sudo apt-get -y upgrade

    if [ $? -ne 0 ]; then 
        echo "Error in checking for unknown linux distribution has been detected."
        kill -INT 0
    fi
    sudo apt-get -y --ignore-missing install $(< ./graph_repo/requirements.txt)

    if [ $? -ne 0 ]; then
        echo "Failed to install package dependencies"
        echo "All dependencies are required in order to properly utlize the project."
        echo "Please ensure you have not moved \"requirements.txt\" from its original position within the cloned repository"
        echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
        kill -INT 0
    fi

# If MacOSX, notify User to use macOS_setup script
elif [[ "$Platform" == 'MAC_OS_X' ]]; then
    echo "Mac OS detected. Please run the \"macOS_setup.sh\" script intended for MacOSX users."
    echo "Please ensure you have homebrew installed before running \"macOS_setup.sh\"!"
    echo "You can install the latest version of homebrew at https://brew.sh/"
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
    kill -INT 0

# If OS is not recognized, exit with notification
else
    echo "Unrecognized distribution. Please run \"os_check.sh\" to determine whether your system is compatible with either bash script"
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
    kill -INT 0
fi


# Attempt to enter directory of git repository
cd ./graph_repo
if [ $? -ne 0 ]; then
    echo "Failed to change to \"graph_repo\" directory from current working directory of ${PWD}."
    echo "Please ensure bash script is called at current working directory one level above directory containing git repository (level at which git clone was called)"
    echo "If you wish to retry at any time, simply delete the \"build\" directory and re-run setup script according to README instructions"
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
    kill -INT 0
fi

# Attempt to create main build directory in cloned git repo
mkdir build
if [ $? -ne 0 ]; then
    echo "Failed to create \"build\" directory in cloned repo directory."
    echo "Aborting setup process..."
    echo "If you wish to retry at any time, simply delete the \"build\" directory and re-run setup script according to README instructions"
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
    echo "If you wish to retry at any time, simply delete the \"build\" directory and re-run setup script according to README instructions"
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
    echo "If you wish to retry at any time, simply delete the \"build\" directory and re-run setup script according to README instructions"
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
    kill -INT 0
else
    echo "\"debug\" subdirectory successfully created."
fi

# build cmake projects configured for release and debug within corresponding subdirectories of build
cd ./build/release
echo "building cmake project in debug and release configurations..."

# Generate CMakefile for Release Configuration of CMake Project
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ ../../
if [ $? -ne 0 ]; then
    echo "Failed to create CMake \"Release\" Configuaration in \"build/release/\" subdirectory in cloned repo directory."
    echo "Please ensure you are calling script from top level directory. Aborting setup process.."
    echo "If you wish to retry at any time, simply delete the \"build\" directory and re-run setup script according to README instructions"
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
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
    kill -INT 0
else
    echo "\"Release\" Configuration of CMake Project successfully built!"
fi


cd ..
cd ./debug
# Generate CMakefile for Debug Configuration of CMake Project
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ ../../
if [ $? -ne 0 ]; then
    echo "Failed to create CMake \"Debug\" Configuaration in \"build/debug/\" subdirectory in cloned repo directory."
    echo "Please ensure you are calling script from top level directory. Aborting setup process.."
    echo "If you wish to retry at any time, simply delete the \"build\" directory and re-run setup script according to README instructions"
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
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