$fullPS_version = $PSVersionTable.OS.Split(' ')
$name = $fullPS_version[0] + ' ' + $fullPS_version[1]
$major_version = ($fullPS_version[2].Split('.'))[0]


# Determine if Powershell and OS Major Version is for Windows 10 or newer and notify user if 
if ( $name -eq "Microsoft Windows" -and $major_version -ge "10" ) {
    Write-Output "  $name $major_version (Powershell version) detected. Local machine is fully supported by project!`n"
    Write-Output "  Execute the 'install_reqs.ps1' script to install all package dependencies and follow the instructions printed to the terminal to proceed with completing the project setup`n"
} else {
    Write-Warning "  $name $major_version detected.`n  This version is not fully supported by the project using Powershell`nNot all build/setup operations may operate as intended on this machine`n" 
}

