# Project Description
This project was built to demonstrate the basic graphical applications of Djikstra's algorithm
and Prim's Algorithm in finding optimal solutions when provided sets of graphical information


This program processes a user-provided text file containing lines in the format:

```
vertex1, vertex2, distance_between_vertex1_and_vertex2
```

The program will process the text file to generate a graphical representation to be
utilized by customized hashmap and binary minimum heap data structures to:

1.  Find the shortest path between a user-provided source vertex and destination vertex
2.  Find the Minimum Spanning Tree given a user-provided source vertex

Sample text files (of varying amounts of graphical densities) that can be used are [included](./sample_graphs/)


# Getting Started
This project can be built by either using:
1. CMake
2. [Provided Unix Makefile](./makefile)

> [!WARNING]
> Project-involved implementation and interaction is primarily conducted through use of a Bash
> terminal utilizing a **Linux(Ubuntu) distribution**. The provided shell script and commands listed below require
> these be present on local machine cloning the repository in order to operate as intended.


## Building this project as a CMake Project

>[!TIP]
> `setup.sh` will attempt to install and/or update the items listed below when it
> attempts to build the project locally ***with the exception of Homebrew***

The following are required to build the project as a CMake Project:
1. cmake version 3.0.0 (or newer)
2. GCC Compiler using standard of C++20 (or newer)
3. Homebrew (*MacOSX users only*)

> [!WARNING]
> For local machines with **MacOSX**, please ensure you have **Homebrew** installed on your local machine if intending
> to build the program using cmake and the `setup.sh` script as it run commands using Homebrew syntax
> Please install [Homebrew](https://brew.sh/) if not currently installed.


## Building this project using the provided Makefile
The following are required to build the project utilizing the provided standalone Makefile:
1. GCC Compiler using standard of C++20 (or newer)


# Building the Program Utilizing CMake
After cloning this repository in your preferred text editor, enter the command into the terminal:

```
source ./graph_repo/setup.sh
```

`setup.sh` will build a **Release** and **Debug** configuration of the project **Graph_TIProject**


## Executing CMake Project Configurations using CLI Commands
After `setup.sh` has completed, execute the main program in **Debug** mode by entering:

```
./build/debug/Graph_TIProject
```

To execute the main program in **Release** mode enter the following in the terminal instead:

```
./build/release/Graph_TIProject
```
> [!NOTE]
> All CLI Commands ***with the exception of `setup.sh`*** are intended to be run within the current working
> directory of `graph_repo`. Please ensure you are in this directory when entering any of the provided CLI
> commands into the terminal.

## Setting up CMake Project Configurations using CMakeTools Extension
After `setup.sh` has completed, the user may utilize the CMakeTools extension for Build Process:

1. Ensure You have the CMakeTools extension installed and enabled. 
As this extension is specific, to the Microsoft VS/VSCode editor, the CMakeTools option is only 
accessible to VS/VSCode users. If you have VS/VSCode installed but do not have the CMakeTools
extension, please install and setup the [CMakeTools](https://code.visualstudio.com/docs/cpp/CMake-linux)
extension before proceeding further.

2. Click on The CMakeTools Extension Icon

3. Configure the Build Target for the CMake Project using the provided `CMakePresets.json` file by:

    1. Locating the section titled `Project Status`
    2. Clicking the `Select Configure Preset` Icon under the Section titled `Configure`
    3. Selecting `BUILD_DIR` from the drop-down Command Palette menu

4. Build or Rebuild all files within the target `Graph_TIProject` CMake Project using the provided
`CMakeLists.txt` file and the `update.sh` shell script:

   1. To Rebuild the Main Build of the CMake Project:
       - Clicking the `Build` icon in upper right-hand corner of the title for the `Build` section
         under `Project Status`

       - Clicking the `Build` icon to the right of `Graph_TIProject(Executable)` section bar under
         `Project Outline`

   2. To Rebuild the **Debug** and **Release** Configurations of the CMake Project:
       - Ensure the current working directory is `graph_repo`
       - Enter the following in the terminal to rebuild both configurations:
            ```
            source update.sh
            ```

5. Build or Rebuild the GoogleTesting Suite by:
    - Clicking on the `Build` icon to the right of the `tests(Executable)` section bar under the `Project Outline`


# Building the Program Utilizing The Provided Makefile
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
> All above CLI Commands for the non-CMake build are intended to be run within the current working directory
> of `graph_repo`. Please ensure you are in this directory when entering any of the above CLI commands into the terminal.

# GoogleTest Unit Testing Suite

A GoogleTest Testing Suite is available for the **CMake** build of the project

After `setup.sh` has completed, the file `tests.cc` can be executed to run any tests defined within by entering:

```
./build/tests
```