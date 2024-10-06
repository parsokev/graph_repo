

Write-Output "  NOTE: If you wish to add or remove any original files from the 'src' or 'includes' directories,"
Write-Output "  you may need to delete the 'build' directory and rerun the appropriate setup script to rebuild."
Write-Output "  Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
Write-Output ""
$error_log = $True
while ($error_log) {
    # Attempt to navigate to directory containing Release Configuration of CMake Project
    Set-Location ./build/release
    if ( $? -ne 1 ){
        Write-Output "  Error encountered while attempting to navigate to the Release Directory."
        Write-Output "  Please ensure you call 'update.sh' in current working directory of 'graph_repo'"
        Write-Output "  Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
        Set-Location ../../
        break
    }

    # Try to Rebuild Release Configuration using Generated Unix Makefile
    ninja
    if ( $? -ne 1 ){
        Write-Output "  Error encountered while attempting to rebuild the Release Configuration."
        Write-Output "  Please ensure you have run the 'setup.sh' script at least once before calling the 'update.sh' script"
        Write-Output "  Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
        Set-Location ../../
        break
    } else {
        Write-Output ""
        Write-Output "  'Release' Configuration of project successully rebuilt!"
    }

    # Attempt to navigate to directory containing Debug Configuration of CMake Project
    Set-Location ../debug
    if ( $? -ne 1 ){
        Write-Output "  Error encountered while attempting to navigate to the Source Directory."
        Write-Output "  Please ensure you have Debug Configuration is located at './graph_repo/build/debug'"
        Write-Output "  Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
        Set-Location ../../
        break
    } 

    # Try to Rebuild Debug Configuration using Generated Unix Makefile
    ninja
    if ( $? -ne 1 ){
        Write-Output "  Error encountered while attempting to rebuild the Debug Configuration."
        Write-Output "  Please ensure you have run the 'setup.sh' script at least once before calling the 'update.sh' script"
        Write-Output "  Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
        Set-Location ../../
        break
    } else {
        Write-Output ""
        Write-Output "  'Debug' Configuration of project successfully rebuilt!"
    }

    # Return to Source Directory of CMake Project
    Set-Location ../../
    Write-Output ""
    Write-Output "  Release and Debug Configurations Have Been Successfully Rebuilt!"
    Write-Output "  Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
    break
}
