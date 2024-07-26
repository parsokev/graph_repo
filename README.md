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

NOTE: Implementation and Interaction is primarily conducted by providing terminal input
utilizing Bash

To build this project as a cmake project, please ensure you have the following installed:

- cmake version 3.0.0 (or newer)
- C++14 (or newer)

To build this project using the provided Makefile, please ensure you have:

- C++14 (or newer)

# Building the Program Utilizing CMake
After cloning this repository in your preferred text editor, enter the command into the terminal:

`source ./graph_repo/setup.sh`

`setup.sh` will build a "Release" and "Debug" configuration of the project "Graph_TIProject"

# Executing CMake Project Configurations
After `setup.sh` has completed, execute the main program in Debug mode by entering:

`./build/debug/Graph_TIProject`

To execute the main program in Release mode enter the following in the terminal instead:

`./build/release/Graph_TIProject`

# Building the Program Utilizng The Provided Makefile
After cloning this repository in your preferred text editor, enter the commands into the terminal:

```
cd ./graph_repo
make
```

`make` will build a "Release" and "Debug" configuration with the executable file `graph_interface`

# Executing Standalone MakeFile Configurations
After the `make` file has completed, execute the main program in Debug mode by entering:

`./debug/graph_interface`

To execute the main program in Release mode enter the following in the terminal instead:

`./release/graph_interface`


# GoogleTest Unit Testing Suite
A GoogleTest Testing Suite is available for the CMake version of the main program

After `setup.sh` has completed, the file `tests.cc` can be executed to run any tests defined within by entering:

`./build/debug/tests`

OR

`./build/release/tests`
