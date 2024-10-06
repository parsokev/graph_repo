$no_errors = $True
# Install Package Dependencies
$package_list = Get-Content -Path ./graph_repo/windows_requirements.txt
$is_installed = $null
foreach( $package in $package_list ) {
    winget install -e --id $package
    # Ensure winget properly installed package on local machine
    $is_installed = winget list -e --id $package
    if ( $null -eq $is_installed ) {
        Write-Output "  $package was unable to be properly installed with winget"
        Write-Output "  Please ensure you have 'winget' installed are calling script at directory level above graph_repo directory"
        $no_errors = $False
    }
    # Fix for non-winget users:
    # Install-Package -Force -Scope CurrentUser -Name $package
}

# Print instructions to User for Setting Environment Paths for Packages executed within Powershell scripts
if ($no_errors) {
    Write-Output ""
    Write-Output "  Installation of all Package Dependencies Successful!"
    Write-Output "  Please Add Graphviz and Cmake to your system PATH to allow scripts to build/rebuild program"
    Write-Output ""
    Write-Output "  The default local path of Graphviz will be:   C:\Program Files\Graphviz\bin"
    Write-Output "  The default local path of Cmake will be:      C:\Program Files\Cmake\bin"
    Write-Output ""
    Write-Output "  Add each of these to the system PATH:"
    Write-Output "  Click Windows Start Icon > Settings > Enter and Select 'Edit environment variables for your account' from the search bar"
    Write-Output "  > Double Click 'Path' under the 'User Variables for ..' section within the 'Environment Variables' window"
    Write-Output "  > Click 'New' > Copy and Paste provided path of Graphviz > Repeat 'New' process for Cmake"
    Write-Output "  > Click 'Ok' in 'Edit Environment Variable' window AND in 'Environment Variables' window to confirm addition of both paths"
    Write-Output ""
    Write-Output "  After completing the above steps, enter the following line into the Powershell terminal to complete the project setup:"
    Write-Output "          ./graph_repo/scripts/Windows/windows_setup.ps1"
    Write-Output ""
} else {
    Write-Output ""
    Write-Output "  Errors were encountered while attempting to install package dependencies using 'winget'"
    Write-Output "  Please ensure your Windows OS is compatible with and has 'winget' installed"
}


 