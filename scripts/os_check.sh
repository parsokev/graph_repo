#!/usr/bin/env bash

# Check for Local OS Type
case "$(uname -sr)" in
   Darwin*)
     Platform='MAC_OS'
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

# If Linux, check for supported Linux Distributions
if [[ "$Platform" == 'Linux' ]]; then

    # Check for Linux Distribution Type
    case "$(lsb_release -is)" in
    CentOS*)
        Linux_Distro='CentOS'
        ;;
    RedHat*|RedHatEnterpriseServer*)
        Linux_Distro='Red Hat'
        ;;
    Ubuntu*|Debian*)
        Linux_Distro='Ubuntu'
        ;;  
        *)
        Linux_Distro='Unrecognized'
        ;;
    esac

    # Attempt to install package dependencies if Debian/Ubuntu is detected
    if [[ "$Linux_Distro" == 'Ubuntu' ]]; then
        echo "Ubuntu/Debian distribution or WSL detected."
        echo ""
        echo "Run the \"linux_setup.sh\" script to build the CMake Project by entering the following line in the terminal: "
        echo "    \"source ./graph_repo/scripts/linux_setup.sh\""
        echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
    # Attempt to install package dependencies if CentOS is detected
    elif [[ "$Linux_Distro" == 'CentOS' ]]; then
        echo "CentOS Linux Distribution Detected"
        echo ""
        echo "Run the \"linux_setup.sh\" script to build the CMake Project by entering the following line in the terminal: "
        echo "    \"source ./graph_repo/scripts/linux_setup.sh\""
        echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"    
    # Attempt to install package dependencies if Red Hat is detected
    elif [[ "$Linux_Distro" == 'Red Hat' ]]; then
        echo "Red Hat Linux Distribution detected"
        echo ""
        echo "Run the \"linux_setup.sh\" script to build the CMake Project by entering the following line in the terminal: "
        echo "    \"source ./graph_repo/scripts/linux_setup.sh\""
        echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"

    # Notify user if Linux Distribution is not recognized as supported by GraphViz with potential solutions
    else
        echo "Linux distribution was unrecognized from list of distributions known to be compatible with graph visualization tools"
        echo ""
        echo "Please visit https://www.graphviz.org/download/ to ensure your Linux distribution is compatible."
        echo "If you believe your linux distribution is compatible, you may try one of the following commands to see if it can be run by the script:"
        echo "      \"sudo yum -y --ignore-missing install $(< ./graph_repo/requirements.txt)\""
        echo "      \"sudo dnf -y --ignore-missing install $(< ./graph_repo/requirements.txt)\""
        echo "If both commands fail, you may try to install the package dependencies within \"requirements.txt\" manually and run \"linux_setup.sh\" after deleting lines above 109 in the script"
        echo "You may still use the Unix Makefile to run the program without running the setup script of building the CMake Project"
        echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
    fi

# If MacOSX, attempt to detect Homebrew notify user that homebrew is required for setup script
elif [[ "$Platform" == 'MAC_OS' ]]; then
    echo "Mac OS detected. Please ensure you have Homebrew installed before continuing!"
    echo ""
    echo "Checking for homebrew..."
    brew --version
    if [ $? -ne 0 ]; then 
      echo "Homebrew not detected on local machine... please visit https://brew.sh/ to have Homebrew installed."
      echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
    else
      echo "Homebrew detected!"
      echo ""
      echo "Run the \"macOS_setup.sh\" script to build the CMake Project by entering the following line in the terminal"
      echo "    \"source ./graph_repo/scripts/macOS_setup.sh\""
    fi

# If Windows is detected, notify of script incompatibility
elif [[ "$Platform" == 'Windows' ]]; then
    echo "Windows OS detected with bash environment. Please ensure you have WSL installed to run this script in a Bash shell."
    echo ""
    echo "If you wish to use WSL to Execute Program:"
    echo "      Visit https://learn.microsoft.com/en-us/windows/wsl/install to setup WSL, which is supported by \"linux_setup.sh\""
    echo ""
    echo "If you wish to use Powershell instead of Bash:"
    echo "      Visit https://www.msys2.org/ to see if your system is compatible with MSYS2, which is supported by \"windows_setup.ps1\""
    echo ""
    echo "You may also view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"

# If OS is not recognized, exit with notification
else
    echo "Unrecognized distribution. Try entering \"uname -sr\" into the terminal to see currently listed OS information"
    echo "Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
fi