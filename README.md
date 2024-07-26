# Getting Started
This properly utilize this project please ensure you have the following installed:
- cmake version 3.0.0 (or newer)
- C++14 (or newer)

# Building CMAKE File using CLI
After cloning this repository in your preferred text editor, you can generate the cmake project utilizing by entering the following command into the terminal:

`source ./graph_repo/setup.sh`

The bash shell script `setup.sh` will build both a "Release" and "Debug" configuration of the cmake project "Graph_TIProject"

# Executing Project Configurations
- After `setup.sh` has completed, execute the main program in Debug mode by entering the following in the terminal:
    `./build/debug/Graph_TIProject`
- To execute the main program in Release mode enter the following in the terminal instead:
    `./build/release/Graph_TIProject`

# GoogleTest Unit Testing Suite
- After `setup.sh` has completed, the file `tests.cc` can be executed to run any tests defined within by entering:
    `./build/debug/tests` OR `./build/release/tests`