$fullPS_version = $PSVersionTable.OS.Split(' ')
$major_version = ($fullPS_version[2].Split('.'))[0]
$pshl_mv = $PSVersionTable.PSVersion.Major

# Direct Linux Users to Appropriate Script for checking System Compatibility and Setup Instructions for Linux Users in README
if ( $IsLinux ) {
    Write-Warning "Linux Distribution Detected`nPowershell scripts for building this project were not designed to be executed within Linux Distributions.`n"
    Write-Output "  Please follow the README instructions for Linux systems and use the 'os_check.sh' script to test for prerequisites specific to Linux systems." 
# Direct MacOS Users to Appropriate Script for checking System Compatibility and Setup Instructions for MacOs Users in README
} elseif ( $IsMacOS ) {
    Write-Warning "MacOS Detected`nPowershell scripts for building this project were not designed to be executed within MacOS Systems`n"
    Write-Output "  Please follow the README instructions for MacOS systems and use the 'os_check.sh' script to test for prerequisites specific to MacOS systems."
# Determine if Powershell and OS Major Version is for Windows 10 or newer and Notify User of Project Compatibility
} elseif ( $IsWindows ) {
    if ( $pshl_mv -ge "7" -and $major_version -ge "10" ) {
        Write-Output "  Powershell version 7 and Windows OS Version 10 or newer detected. Local machine is fully supported by project!"
        Write-Output "  Execute the 'install_reqs.ps1' script to install all package dependencies and follow the instructions printed to the terminal to proceed with completing the project setup`n"
    } else {
        Write-Warning "Windows $major_version with Powershell version of $pshl_mv detected.`n Windows OS versions older than 10 and Powershell version older than 7 are not fully supported by this program."
        Write-Output "If your Powershell version is less than 7, 'install_reqs.ps1' will attempt to update the newest supported version of Powershell."
        Write-Output "If your local machine OS version is less than 10, several features and package dependencies do not support use of Windows versions older than 10 at this time. It is not reccommended to proceed further in setup."
    }
} else {
    Write-Warning "Unknown OS type detected. Please view the README for possibly compatibility or troubleshooting problems that may have resulted in this outcome"
}



