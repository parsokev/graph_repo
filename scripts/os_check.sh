#!/usr/bin/env bash

# Check for Local OS Type
case "$(uname -sr)" in
   Darwin*)
     Platform='MAC_OS_X'
     ;;
   Linux*)
     Platform='Linux'
     ;;
   CYGWIN*|MINGW*|MSYS*)
     Platform='Windows'
     ;;  
    *)
     Platform='Unrecognized'
     ;;
esac

# If Linux, attempt to update distribution and install dependencies
if [[ "$Platform" == 'Linux' ]]; then
    echo "Linux or WSL detected"
    echo "Run the \"linux_setup.sh\" script to build the CMake Project"
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"

# If MacOSX, attempt to update Homebrew and install dependencies using Homebrew
elif [[ "$Platform" == 'MAC_OS_X' ]]; then
    echo "Mac OS detected. Please ensure you have Homebrew installed before continuing!"
    echo "Run the \"macOS_setup.sh\" script to build the CMake Project"
    echo "Checking for homebrew..."
    brew --version
    if [ $? -ne 0 ]; then 
    echo "Homebrew not detected on local machine... please visit https://brew.sh/ to have Homebrew installed."
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
    fi

# If Windows is detected, notify of script incompatibility
elif [[ "$Platform" == 'Windows' ]]; then
    echo "Windows OS detected with bash environment. Please ensure you have WSL installed to run this script in a Bash shell."
    echo "The \"linux_setup.sh\" script is not intended to run in Cygwin/MingW due to varying environment file paths"
    echo "Please visit https://learn.microsoft.com/en-us/windows/wsl/install to setup WSL, which is supported by \"linux_setup.sh\""
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"

# If OS is not recognized, exit with notification
else
    echo "Unrecognized distribution. If running in Linux environment other than Debian or Ubuntu, this script is currently unable to run in these environments."
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
fi