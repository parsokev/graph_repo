$error_log = $True
while ($error_log) {
    # Confirm Graphviz and CMake have been placed within system PATH for Powershell access
    $graphviz_path_detected = $False
    $cmake_path_detected = $False
    $path_list = $env:path -split ';'
    Write-Output ""
    foreach( $path in $path_list ) {
        if ( $path -like '*Graphviz*' ) {
            Write-Output "  Graphviz detected in PATH at:  $path"
            $graphviz_path_detected = $True
        }
        if ( $path -like '*CMake*' ) {
            Write-Output "  CMake detected in PATH at: $path"
            $cmake_path_detected = $True
        }
        if ($cmake_path_detected -and $graphviz_path_detected) {
            break
        }
    }
    
    # Notify user if either Package is not found in PATH and cease script execution
    if ( !$graphviz_path_detected) {
        Write-Warning "Graphviz was not detected in PATH!"
        Write-Output  "  Please follow instructions provided after executing 'install_reqs.ps1' to set Graphviz within PATH`n"
        break
    }
    
    if ( !$cmake_path_detected) {
        Write-Warning "CMake was not detected in PATH!"
        Write-Output  "  Please follow instructions provided after executing 'install_reqs.ps1' to set CMake within PATH`n"
        break
    }
    
    # Attempt to enter directory of git repository
    Set-Location ./graph_repo
    if ( $? -ne 1 ){
        Write-Warning "Failed to change to 'graph_repo' directory from current working directory of ${PWD}."
        Write-Output "  Please ensure bash script is called at current working directory one level above directory containing git repository (level at which git clone was called)"
        Write-Output "  If you wish to retry at any time, simply delete the 'build' directory and re-run setup script according to README instructions"
        Write-Output "  Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo`n"
        Set-Location ..
        break
    }

    # Attempt to create main build directory in cloned git repo
    New-Item -Type Directory build
    if ( $? -ne 1 ) {
        Write-Warning "Failed to create 'build' directory in cloned repo directory."
        Write-Output "  Aborting setup process..."
        Write-Output "  If you wish to retry at any time, simply delete the 'build' directory and re-run setup script according to README instructions"
        Write-Output "  Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
        Set-Location ..
        break
    } else {
        Write-Output "  'build' directory successfully created."
    }

    # Attempt to create a release subdirectory within build directory
    New-Item -Type Directory build/release
    if ( $? -ne 1 ) {
        Write-Warning "Failed to create 'build/release' subdirectory in cloned repo directory."
        Write-Output "  Aborting setup process.."
        Write-Output "  If you wish to retry at any time, simply delete the 'build' directory and re-run setup script according to README instructions"
        Write-Output "  Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
        Set-Location ..
        break
    } else {
        Write-Output "  'release' subdirectory successfully created."
    }

    # Attempt to create debug subdirectory within build directory
    New-Item -Type Directory build/debug
    if ( $? -ne 1 ) {
        Write-Warning "Failed to create 'build/debug' subdirectory in cloned repo directory."
        Write-Output "  Aborting setup process.."
        Write-Output "  If you wish to retry at any time, simply delete the 'build' directory and re-run setup script according to README instructions"
        Write-Output "  Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
        Set-Location ..
        break
    } else {
        Write-Output "  'debug' subdirectory successfully created."
    }
    
    # build cmake projects configured for release and debug within corresponding subdirectories of build
    Set-Location ./build/release
    Write-Output "  Building cmake project in debug and release configurations..."
    
    # Generate CMakefile for Release Configuration of CMake Project
    cmake -G Ninja ../../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=C:\msys64\ucrt64\bin\gcc.exe -DCMAKE_CXX_COMPILER=C:\msys64\ucrt64\bin\g++.exe
    cmake --build . 
    if ( $? -ne 1 ) {
        Write-Warning "Failed to create CMake 'Release' Configuaration in 'build/release/' subdirectory in cloned repo directory."
        Write-Output "  Please ensure you are calling script from top level directory. Aborting setup process.."
        Write-Output "  If you wish to retry at any time, simply delete the 'build' directory and re-run setup script according to README instructions"
        Write-Output "  Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
        Set-Location ../../../
        break
    }
    else {
        Write-Output "  Attempting to build 'Release' configuration using generated CMakefile..."
    }
    
    # Attempt to build Release Configuration based on generated CMakefile
    ninja
    if ( $? -ne 1 ) {
        Write-Warning "Failed to build CMake 'Release' Configuaration in 'build/release/' subdirectory in cloned repo directory."
        Write-Output "  Please ensure you are calling script from top level directory. Aborting setup process.."
        Write-Output "  If you wish to retry at any time, simply delete the 'build' directory and re-run setup script according to README instructions"
        Write-Output "  Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
        Set-Location ../../../
        break
    } else {
        Write-Output "`n  'Release' Configuration of CMake Project successfully built!"
    }
    
    Set-Location ../debug
    # Generate CMakefile for Debug Configuration of CMake Project
    cmake -G Ninja ../../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=C:\msys64\ucrt64\bin\gcc.exe -DCMAKE_CXX_COMPILER=C:\msys64\ucrt64\bin\g++.exe
    cmake --build .
    if ( $? -ne 1 ) {
        Write-Warning "Failed to create CMake 'Debug' Configuaration in 'build/debug/' subdirectory in cloned repo directory."
        Write-Output "  Please ensure you are calling script from top level directory. Aborting setup process.."
        Write-Output "  If you wish to retry at any time, simply delete the 'build' directory and re-run setup script according to README instructions"
        Write-Output "  Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
        Set-Location ../../../
        break
    } else {
        Write-Output "  Attempting to build 'Debug' configuration using generated CMakefile..."
    }
    
    # Attempt to build Debug Configuration based on generated CMakefile
    ninja
    if ( $? -ne 1 ) {
        Write-Warning "Failed to build CMake 'Debug' Configuaration in 'build/debug/' subdirectory in cloned repo directory."
        Write-Output "  Please ensure you are calling script from top level directory. Aborting setup process.."
        Write-Output "  If you wish to retry at any time, simply delete the 'build' directory and re-run setup script according to README instructions"
        Write-Output "  Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo"
        Set-Location ../../
        break
    } else {
        Write-Output "`n'Debug' Configuration of CMake Project successfully built!"
        
    }

    Set-Location ../../
    
    # Provide Usage Instructions
    Write-Output "`n  Both CMake projects have been successfully built and compiled!"
    Write-Output "`n  EXECUTING PROGRAM:"
    Write-Output "      To Run the Program in Release Mode, Enter into the Terminal:    './build/release/Graph_TIProject'"
    Write-Output "      To Run the Program in Debug Mode, Enter into the Terminal:      './build/debug/Graph_TIProject'"
    Write-Output "`n  EXECUTING TESTING SUITE:"
    Write-Output "      To Run all tests within GoogleTest testing suite in Release Mode, Enter:    './build/release/tests'"
    Write-Output "      To Run all tests within GoogleTest testing suite in Debug Mode, Enter:      './build/debug/tests' (for additional reporting)"
    Write-Output "`n  Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo`n"
    break
}