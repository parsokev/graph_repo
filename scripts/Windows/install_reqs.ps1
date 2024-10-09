$no_errors = $True

# Verify Script was Called within Expected Working Directory
$package_list = Get-Content -Path ./graph_repo/windows_requirements.txt
if ( $null -eq $package_list ) {
    Write-Warning "'install_reqs.ps1' was executed from an unexpected location`nPlease ensure you are calling this script from:`n' ./graph_repo/windows_requirements.txt'`n"
    $no_errors = $False
}

# Check Powershell Version and Update Powershell to Newer Versions if Found
$ps_mjv = $PSVersionTable.PSVersion.Major
if ($ps_mjv -lt "7" ) {
    $response = Read-Host "Detected Powershell that is older than version 7.0.0. Would you like to update Powershell?`n         Yes[Y] No[N]"
    if ($response -eq "Y" ) {
        Write-Output "Updating Windows Powershell to newest available version..."
        winget install -e --Id Microsoft.PowerShell
    }
} 

# Install Package Dependencies
$is_installed = $null
if ($no_errors) {
    Write-Output "Attempting to Install and/or Update all Project Dependencies..."
    foreach( $package in $package_list ) {
        winget install -e --id $package
        # Ensure winget properly installed package on local machine
        $is_installed = winget list -e --id $package
        if ( $null -eq $is_installed ) {
            Write-Warning "$package was unable to be properly installed with winget`nPlease ensure you have 'winget' installed are calling script at directory level above graph_repo directory"
            $no_errors = $False
        }
        # Fix for non-winget users:
        # Install-Package -Force -Scope CurrentUser -Name $package
    }
}


# Print instructions to User for Setting Environment Paths for Packages executed within Powershell scripts
if ($no_errors) {
    Write-Output "`n  Installation of all Package Dependencies Successful!"
    Write-Output "  Please Add Graphviz and Cmake to your system PATH to allow scripts to build/rebuild program`n"
    Write-Output "  The default local path of Graphviz will be:   C:\Program Files\Graphviz\bin"
    Write-Output "  The default local path of Cmake will be:      C:\Program Files\CMake\bin`n"
    Write-Output "  Add each of these to the system PATH:"
    Write-Output "  Click Windows Start Icon > Settings > Enter and Select 'Edit environment variables for your account' from the search bar"
    Write-Output "  > Double Click 'Path' under the 'User Variables for ..' section within the 'Environment Variables' window"
    Write-Output "  > Click 'New' > Copy and Paste provided path of Graphviz > Repeat 'New' process for Cmake"
    Write-Output "  > Click 'Ok' in 'Edit Environment Variable' window AND in 'Environment Variables' window to confirm addition of both paths`n"
    Write-Output "  After completing the above steps, enter the following line into the Powershell terminal to complete the project setup:"
    Write-Output "          ./graph_repo/scripts/Windows/windows_setup.ps1`n"
} else {
    Write-Warning "Errors were encountered while attempting to install package dependencies using 'winget'`nPlease view the errors listed above to determine possible causes"
}


 