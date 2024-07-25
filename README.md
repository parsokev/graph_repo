NOTE: To toggle default printing, set C_MAKE_BUILD_TYPE = "Release" to disable debug printing or "Debug" to enable print debugging
# Building CMAKE File using CLI
In terminal window of directory to be filled with cmake project:
1. `cd ./graph_repo`
2. `bash ./setup.sh`
setup.sh builds both a "Release" and "Debug" configurations of the cmake project "Graph_TIProject"
# Executing Project Configurations
- After setup.sh has completed, execute the main program in debug mode by entering the following in the terminal:
    - `./build/debug/Graph_TIProject`
- To execute the main program in release mode enter the following in the terminal instead:
    - `./build/release/Graph_TIProject`

# GoogleTest Unit Testing Suite
- After setup.sh has completed, the file 'tests.cc' can be executed to run any tests defined within by entering:
    - `./build/debug/Graph_TIProject/tests` OR `./build/release/Graph_TI_Project/tests`