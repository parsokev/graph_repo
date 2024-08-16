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

Sample text files that can be used are included (of varying amounts of graphical densities):
```
my_graph.txt
my_graph2.txt
my_graph3.txt
my_graph4.txt
```

# Getting Started
This project can be built by either using:
- CMake
- Unix Makefile (included in git repository)

Building this project as a cmake project requires the following:

- cmake version 3.0.0 (or newer)
- GCC Compiler using standard of C++20 (or newer)
- MacOSX Users: Homebrew

Building this project using the provided Makefile requires:

- GCC Compiler using standard of C++20 (or newer)

NOTE: Project-involved implementation and interaction is primarily conducted through use of a Bash
terminal utilizing a Linux(Ubuntu) distribution. The provided shell script and commands listed below require
these be present on local machine cloning the repository in order to operate as intended.

For local machines with MacOSX, please ensure you have Homebrew installed on your local machine if intending
to build the program using cmake and the `setup.sh` script as it run commands using Homebrew syntax

Please visit https://brew.sh/ to install Homebrew if not currently installed.

# Building the Program Utilizing CMake
After cloning this repository in your preferred text editor, enter the command into the terminal:

```
source ./graph_repo/setup.sh
```

`setup.sh` will build a "Release" and "Debug" configuration of the project "Graph_TIProject"

# Executing CMake Project Configurations using CLI Commands
After `setup.sh` has completed, execute the main program in Debug mode by entering:

```
./build/debug/Graph_TIProject
```

To execute the main program in Release mode enter the following in the terminal instead:

```
./build/release/Graph_TIProject
```

# Seeting up CMake Project Configurations using CMakeTools Extension
After `setup.sh` has completed, the user may utilize the CMakeTools extension for Build Process:

1. Ensure You have the CMakeTools extension installed and enabled. 
As this extension is specific, to the Microsoft VS/VSCode editor, the CMakeTools option is only 
accessible to VS/VSCode users. If you have VS/VSCode installed but do not have the CMakeTools
extension, please visit https://code.visualstudio.com/docs/cpp/CMake-linux to properly install
this extension before proceeding further.

2. Click on The CMakeTools Extension Icon

3. Configure the Build Target for the CMake Project using the provided `CMakePresets.json` file by:

- Locating the Section titled `Project Status`
- Clicking the `Select Configure Preset` Icon under the Section titled `Configure`
- Selecting `BUILD_DIR` from the Drop-down Command Palette menu

4. Build or Rebuild all files within the target `Graph_TIProject` CMake Project using the provided
`CMakeLists.txt` file by Either:

-  Clicking the `Build` Icon in upper right-hand corner of the title for the `Build` section
under the Section titled `Project Status`

    OR

-  Clicking the `Build` Icon to the right of `Graph_TIProject(Executable)` section bar Under `Project Outline` 
Section

5. Build or Rebuild the GoogleTesting Suite by:
- Clicking on the `Build` Icon to the right of the `tests(Executable)` section bar Under the `Project Outline`

# Building the Program Utilizng The Provided Makefile
After cloning this repository in your preferred text editor, enter the commands into the terminal:

```
cd ./graph_repo
make
```

`make` will build a "Release" and "Debug" configuration with the executable file `graph_interface`

# Executing Standalone MakeFile Configurations
After the `make` file has completed, execute the main program in Debug mode by entering:

```
./debug/graph_interface
```

To execute the main program in Release mode enter the following in the terminal instead:

```
./release/graph_interface
```


# GoogleTest Unit Testing Suite
A GoogleTest Testing Suite is available for the CMake version of the main program

After `setup.sh` has completed, the file `tests.cc` can be executed to run any tests defined within by entering:

```
./build/tests
```
