#include <iostream>
#include <vector>
#include <iosfwd>
#include <tuple>
#include <string>
#include <cmath>
#include <limits>
#include <cstdio>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <sys/wait.h>
#include <memory>

#include "../includes/graph_input.hpp"
#include "../includes/pair_minheap.hpp"
#include "../includes/derived_hashmap.hpp"
#include "../includes/graph_processing.hpp"


int main(void) {
    // Establish preset file paths for reading and writing operations
    std::string graph_filename = "./dot_graphs/full_graph.gv";
    std::string rel_path = "sample_graphs/";
    std::string path_filename = "./dot_graphs/shortest_path_overlay.gv";
    std::string MST_filename = "./dot_graphs/MST_overlay.gv";
    std::string read_name;
    
    // Determine and present acceptable files from designated directory for user-provided graph text files
    int file_output = 0;
    try {
        file_output = get_graph_filename(rel_path, read_name);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    if (file_output < 0) {
        return EXIT_SUCCESS;
    }

    // Handle User Input For Total Number of Verticies in Submitted Graph
    long int vertex_count;
    int vertex_output = 0;
    try {
        vertex_output = get_graph_vertex_count(vertex_count, rel_path);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    if (vertex_output < 0) {
        return EXIT_SUCCESS;
    }
    
    // Build main_hashmap data struct to store a relevant graphical information extracted from user-provided graph file
    // Write relevant extracted information in dot language format to designated .gv file for building graph visualization
    auto main = std::make_unique<main_hashmap<double>>(static_cast<unsigned int>(vertex_count)); 
    std::cout << "Building graph from '" << read_name << "' file contents..." << '\n';
    std::cout << "Writing graph information to file '" << graph_filename << "' for image processing..." << '\n';
    
    int output = 0;
    unsigned int file_vertex_count = static_cast<unsigned int>(vertex_count);
    try {
        output = build_adjacency_list(rel_path, graph_filename, file_vertex_count, std::move(*main));
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    if (output < 0) {
        return EXIT_FAILURE;
    }

    // Handle User Input for Preferred Calculation to Apply using Extracted Information
    std::cout << "Graph Successfully Built!" << '\n' << '\n';
    std::string algorithm_type;
    int request_output = 0;
    try {
        request_output = get_requested_algorithm (algorithm_type, std::move(*main), graph_filename, path_filename, MST_filename);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    if (request_output < 0) {
        return EXIT_FAILURE;
    }

    // Preset Script Path and Graph Image Locations based on User Requested Information
    std::string script_path;
    std::string_view request_type;
    if (algorithm_type.compare("S") == 0) {
        script_path = "./scripts/visualize_graph_SP.sh";
        request_type = "SHORTEST PATH";
    } else {
        script_path = "./scripts/visualize_graph_MST.sh";
        request_type = "MINIMUM SPANNING TREE";
    }

    // Run Appropriate Bash Script for Generating Graph Images
    char bash_path[] = "/bin/bash";
    // char bash_path[] = "/opt/homebrew/bin/bash"
    pid_t pid = fork();
    int child_status;
    switch(pid) {
        case -1:
            perror("fork");
            break;
        case 0:
            std::cout << "Executing \"" << script_path << "\" to overlay the " << request_type << " using the processed graphical information..." << '\n';
            std::cout << "\n=============================== IMAGE GENERATION RESULTS ====================================\n";
            execl(bash_path, bash_path, script_path.c_str(), nullptr);
            perror("execl");
            break;
        default:
            pid = waitpid(pid, &child_status, 0);
    }
    return EXIT_SUCCESS;
}
