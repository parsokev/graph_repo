# Project Description

## Overview

This project was built to demonstrate the combined utilization of basic graphical applications and
the well-known Djikstra's algorithm and Prim's algorithm to process and visualize optimal path solutions.

Instead of accepting graphical information in the traditional forms of adjacency matricies or adjacency
lists, this program processes graphical information in a more human-friendly format for ease of access
to individuals who wish to both provide and view graphical data in a more readily understood format. 


## Processing of User-Provided Graphical Information

This program processes a text file where each line contains the information for each unique edge
in the graph to be processed. This line-by-line format is structured in the following way:

```
vertex1_name, vertex2_name, distance_between_vertex1_and_vertex2
```

The program will process the text file to generate a graphical representation to be
utilized by customized Hashmap and Binary Minimum Heap data structures to:

1.  Find the shortest path between a user-provided source vertex and destination vertex
2.  Find the Minimum Spanning Tree given a user-provided source vertex

For referencing purposes, several sample text files (of varying amounts of graphical densities)
that adhere to the proper format for processing are included in the [sample_graphs](./sample_graphs/) directory.

Text files, whose contents match the outlined format and are placed within the `sample_graphs` directory,
will be detected by the program and presented to the user in the terminal for selection upon starting the program.

After recieving the required information from the user through the terminal, the program will then utilize 
[Graphviz](https://www.graphviz.org/) to generate:

1. PNG-format image of the entire graph extracted from the user-selected text file in the `sample_graphs` directory.
2. PNG-format depiction of the requested MST or Shortest Path generated (according to the type of request placed by
   the user into the terminal).

Both of these images will be placed within the `graph_images` directory for viewing after completion.


# Getting Started

This project can be built by either using:

1. [CMake](https://www.kitware.com/cmake-3-30-1-available-for-download)
2. [Provided Unix Makefile](./makefile)

> [!WARNING]
> Project-involved implementation and interaction is primarily conducted within a Bash shell.
> The provided shell script and commands listed below require use of a Bash-integrated command-line
> terminal on the local machine cloning the repository in order to operate as intended.


# Building The Project Using CMake

## Testing for Local Machine Compatibility

The repository provides several different shell scripts to build the project using CMake 
on local machines with **MacOS** and **Linux** within the [Scripts Directory](./scripts/).
These will be addressed in further detail below.

For users that are unsure of their local machine's compatibility with the shell scripts used to build 
the project using CMake, the `os_check.sh` script can be run after cloning the repository to their
local machine. The `os_check.sh` script will print out the OS description of their local machine and
the corresponding instructions by entering:

```
source ./graph_repo/scripts/os_check.sh
```

> [!TIP]
> The appropriate shell script will attempt to install and/or update the items listed below
> when it attempts to build the project locally ***with the exception of Homebrew***.
> 
> If the expected path to Bash does not exist or is incorrect, the script will not run.
> If this occurs and Bash does exist within the local machine, the top line of the script
> can be changed to the correct path to Bash locally to allow for the script(s) to be run.

### Required Dependencies

The following are required to build the project using CMake:
1. [cmake version 3.0.0 (or newer)](https://www.kitware.com/cmake-3-30-1-available-for-download/)
2. GCC Compiler using standard of C++20 (or newer)
3. [Homebrew](https://brew.sh/) (*MacOS users only*)
4. [Graphviz](https://www.graphviz.org/)

> [!WARNING]
> For local machines with **MacOS**, please ensure you have **Homebrew** installed on your local machine if intending
> to build the program using cmake. Please install [Homebrew](https://brew.sh/) if not currently installed.
>
> For local machines with **Linux Distributions**, if the distribution is not **Debian** or **Ubuntu**,
> the shell scripts will most likely be unable to properly build the CMake Project. However, the project
> can still be built using the provided [Makefile](./makefile).
>
> For local machines with **Windows**, if you are utilizing **Cygwin** or **MingW**, the shell scripts
> will most likely be unable to properly build the CMake Project. Please install the [Windows Subsystem for Linux(WSL)](https://learn.microsoft.com/en-us/windows/wsl/install)
> in order to build the CMake Project on a local machine using Windows.


## Running Provided Shell Script for CMake Build

After cloning this repository in your preferred text editor, you may run one of several shell
scripts provided within the [Scripts Directory](./scripts/) to build/rebuild the project.


### Shell Script for Building CMake Project on MacOS

For users wishing to build the project on a local machine using **MacOS**, run the
`macOS_setup.sh` shell script to build the project by entering the following:

```
source ./graph_repo/scripts/macOS_setup.sh
```

`macOS_setup.sh` will build a **Release** and **Debug** configuration of the project **Graph_TIProject**


### Shell Script for Building CMake Project on Linux/Windows

For users wishing to build the project on a local machine using either a **Debian**/**Ubuntu** Linux
Distribution or the **Windows Subsystem for Linux**, run the `linux_setup.sh` shell script to build
the project by entering the following:

```
source ./graph_repo/scripts/linux_setup.sh
```

`linux_setup.sh` will build a **Release** and **Debug** configuration of the project **Graph_TIProject**


### Shell Script for Building/Rebuilding Project Configurations

***After running either setup scripts***, the `update.sh` shell script can be run at any time to
rebuild the **Debug** and **Release** configurations of the CMake Project files by entering the following:

```
source ./scripts/update.sh
```

This script should be compatible with both **MacOS** and **Linux** machines but **MacOS** users may simply
replace the `update.sh` script's top line of `#!/usr/bin/env bash` with `#!/opt/homebrew/bin/bash`
if any issues are encountered.


## Executing the CMake Project Configurations using the Command Line Interface 

After the appropriate shell script has finished running, the main program can be executed in the
**Debug** Configuration (Provides additional information reporting not visible in **Release**) 
or **Release** Configuration.

Execute the main program in **Debug** mode by entering the following in the terminal:

```
./build/debug/Graph_TIProject
```

Execute the main program in **Release** mode by enter the following in the terminal:

```
./build/release/Graph_TIProject
```

To Rebuild/Update both Configurations, run the `update.sh` shell script:

```
source ./scripts/update.sh
```

> [!NOTE]
> All provided commands ***with the exception of those for running `linux_setup.sh`, `macOS_setup.sh`, and `check_os.sh`*** 
> are intended to be run with `graph_repo` as the current working directory. If entering any of the other provided commands
> ***verbatim***, please ensure the current working directory is `graph_repo` when entering these into the terminal.


## Executing the CMake Project Configurations using the CMakeTools Extension

After the appropriate initial setup script has finished running, any user using the **Microsoft Visual Studio/VSCode**
text editor may utilize the [CMakeTools](https://code.visualstudio.com/docs/cpp/CMake-linux) extension to generate a UI for managing the CMake Project:

1. Reopen the `graph_repo` directory as the **root** directory in your text editor
   -  The highest level of your active directory must be `graph_repo` in order for CMakeTools
      to recognize `graph_repo` as the active folder for configuration.

2. Ensure You have the CMakeTools extension installed and enabled. 
   - As this extension is specific to the **Microsoft VS/VSCode** editor, the CMakeTools option is only 
     accessible to Microsoft VS/VSCode users. If you have Microsoft VS/VSCode installed but do not have the CMakeTools
     extension, please install and setup the CMakeTools extension before proceeding further.

3. Click on The CMakeTools Extension Icon on Extension Bar on the far left-hand side of editor.

4. Configure the Build Target for the CMake Project using the provided `CMakePresets.json` file:

    1. Locate the section titled `Project Status`
    2. Click the `Select Configure Preset` Icon under the Section titled `Configure`
    3. Select the Preferred Configuration for Building/Executing from the drop-down Command Palette menu:
      - Select `Debug_DIR` to Utilize the **Debug** Configuration
      - Select `Release_DIR` to Utilize the **Release** Configuration

5. Build or Rebuild all files within the target `Graph_TIProject` CMake Project by doing **ONE** of the following:

  -  Click the `Build` icon in upper right-hand corner of the title for the `Build` section under `Project Status`
     to rebuild the selected project configuration

  - After ensuring the current working directory is `graph_repo`, enter the following into the terminal,
    which will rebuild both the **Debug** and **Release** Configurations simultaneously:

            ```
            source ./scripts/update.sh
            ```

6. Select the Appropriate File to Execute/Run

  - Click the ***Icon that appears immediately below the Play Icon*** in the right-hand corner of the `Launch` Section.
  - Select the `Graph_TIProject` executable from Dropdown Command Palette to set it as the Launch Target.

7. Run/Execute the Appropriate File

  - Click the Play Icon in the right-hand corner of the "Launch" Section to execute the selected configuration of the program.


# Building the Program Utilizing The Provided Makefile

The following are required to build the project utilizing the provided standalone Makefile:
1. GCC Compiler using standard of C++20 (or newer)


After cloning this repository in your preferred text editor, enter the commands into the terminal:

```
cd ./graph_repo
make
```

`make` will build a **Release** and **Debug** configuration with the executable file `graph_interface`


## Executing And Rebuilding the Standalone MakeFile Configurations

After the `make` file has completed, execute the main program in **Debug** mode by entering:

```
./debug/graph_interface
```

To execute the main program in **Release** mode enter the following in the terminal instead:

```
./release/graph_interface
```

To Rebuild the Debug and Release Configurations enter the following:

```
make
```

> [!NOTE]
> All above commands for the non-CMake build are intended to be run within the current working directory
> of `graph_repo`. If entering any of the other provided commands ***verbatim***, Please ensure you are
> in this directory when entering any of the above commands into the terminal.

# GoogleTest Unit Testing Suite (CMake Projects Only)

A GoogleTest Testing Suite is available for the **CMake** build of the project to implement testing scenarios
for different functional aspects of the program.

>[!CAUTION]
> Do not attempt to execute the GoogleTest Testing Suite using the **Release** Configuration.
> The Testing Suite includes tests that require the use of assertions that will fail to properly
> execute within the **Release** Configuration. Please use the **Debug** Configuration when
> utilizing the GoogleTest Testing Suite.

## Executing The GoogleTest Testing Suite using the Command Line Interface

After the appropriate initial setup shell script has completed, the file `tests.cc` can be executed to run any tests defined within by entering:

```
./build/debug/tests
```

## Executing The GoogleTest Testing Suite using the CMakeTools Extension

After the appropriate initial setup shell script has completed, the file `tests.cc` can be executed to run any tests defined within using
CMakeTools:
  1. Click the Icon to the right of the `Configure` Section Bar under the `Project Status` Section. 
  2. Select the **Debug** Configuration Preset for the CMake Project, `Debug_DIR` from the Dropdown Command Palette.
  3. Click the Icon to the right of the `Build` Section Bar under the `Project Status` Section to Rebuild the Project.
  4. Click ***Icon that appears immediately below the Play Icon*** in the right-hand corner of the `Launch` Section under the `Project Status` Section.
  5. Select the `tests` executable from Dropdown Command Palette to set it as the Launch Target.
  6. Click the Play Icon in the right-hand corner of the `Launch` Section to execute the GoogleTest Testing Suite.