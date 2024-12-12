$error_log = $True
while ($error_log) {
    # Check for bin directories in Graphviz and Cmake directories to verify user has added files to initially empty directories
    $graphviz_bin_files = Test-Path -Path '.\graph_repo\Graphviz\*' -Include 'bin'
    $cmake_bin_files = Test-Path -Path '.\graph_repo\Cmake\*' -Include 'bin'
    if (!$graphviz_bin_files) {
        Write-Warning "Graphviz does not include all the necessary files!"
        Write-Output  "  Please follow instructions provided for setting up the Graphviz files in the README!`n"
        break
    }

    if (!$cmake_bin_files) {
        Write-Warning "CMake was not include all the necessary files!"
        Write-Output  "  Please follow instructions provided for setting up the CMake files in the README!`n"
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
    
    # Set expected path to local CMake directory's cmake executable
    $cmake_path = "..\..\Cmake\bin\cmake.exe"
    # Generate CMakefile for Release Configuration of CMake Project
    powershell.exe -Command $cmake_path -G Ninja ../../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=C:\msys64\ucrt64\bin\gcc.exe -DCMAKE_CXX_COMPILER=C:\msys64\ucrt64\bin\g++.exe
    powershell.exe -Command $cmake_path --build .
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
    powershell.exe -Command $cmake_path -G Ninja ../../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=C:\msys64\ucrt64\bin\gcc.exe -DCMAKE_CXX_COMPILER=C:\msys64\ucrt64\bin\g++.exe
    powershell.exe -Command $cmake_path --build .
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

    Set-Location ..
    
    # Provide Usage Instructions
    Write-Output "`n  Both CMake projects have been successfully built and compiled!"
    Write-Output "`n  EXECUTING PROGRAM:"
    Write-Output "When executing strictly through the command line, you must execute from WITHIN the directory containing the Graph_TIProject.exe file"
    Write-Output "To Immediately Run the Program in Release Mode: "
    Write-Output "      Enter into the Terminal: 'cd ./release; ./Graph_TIProject' "
    Write-Output "To Immediately Run the Program in Debug Mode: "
    Write-Output "      Enter into the Terminal: 'cd ./debug; ./Graph_TIProject' "
    Write-Output "`n  EXECUTING TESTING SUITE:"
    Write-Output "      To Run all tests within GoogleTest testing suite in Release Mode, Enter:    './release/tests'"
    Write-Output "      To Run all tests within GoogleTest testing suite in Debug Mode, Enter:      './debug/tests' (for additional reporting)"
    Write-Output "`n  Please view the README for further information on feature access and troubleshooting: https://github.com/parsokev/graph_repo`n"
    break
}