#!/usr/bin/env bash

# MacOS Homebrew Users:
# replace top line with line contained within <> if script does not run as is: <#!/opt/homebrew/bin/bash>

echo "NOTE: If you wish to add or remove any original files from the \"src\" or \"includes\" directories,"
echo "you may need to delete the \"build\" directory and rerun the appropriate setup script to rebuild."
echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"


# Attempt to navigate to directory containing Release Configuration of CMake Project
cd ./build/release
if [ $? -ne 0 ]; then 
echo "Error encountered while attempting to navigate to the Release Directory."
echo "Please ensure you call \"update.sh\" in current working directory of \"graph_repo\""
echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
kill -INT 0
fi

# Try to Rebuild Release Configuration using Generated Unix Makefile
make
if [ $? -ne 0 ]; then 
echo "Error encountered while attempting to rebuild the Release Configuration."
echo "Please ensure you have run the \"setup.sh\" script at least once before calling the \"update.sh\" script"
echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
cd ../../
kill -INT 0
fi

# Navigate upwards back to Project's Source Directory
cd ../../

# Attempt to navigate to directory containing Debug Configuration of CMake Project
cd ./build/debug
if [ $? -ne 0 ]; then 
echo "Error encountered while attempting to navigate to the Source Directory."
echo "Please ensure you have Debug Configuration is located at \"./graph_repo/build/debug\""
echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
kill -INT 0
fi

# Try to Rebuild Debug Configuration using Generated Unix Makefile
make
if [ $? -ne 0 ]; then 
echo "Error encountered while attempting to rebuild the Debug Configuration."
echo "Please ensure you have run the \"setup.sh\" script at least once before calling the \"update.sh\" script"
echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
cd ../../
kill -INT 0
fi

# Return to Source Directory of CMake Project
cd ../../

echo "Release and Debug Configurations Have Been Successfully Rebuilt!"
echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"