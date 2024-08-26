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
#include <stdlib.h>
#include <sys/wait.h>

#include "../includes/graph_input.hpp"
#include "../includes/linked_list.hpp"
#include "../includes/pair_minheap.hpp"
#include "../includes/derived_hashmap.hpp"
// #include "../includes/master_hashmap.hpp"
#include "../includes/graph_ops.hpp"
#include "../includes/gprintf.hpp"

std::ostream& operator<<(std::ostream& out, const std::vector<std::tuple<std::string, std::string>>& vertex_list) {
    out << "[ ";
    for (unsigned int i = 0; i < vertex_list.size(); i++) {
        std::string vertex1;
        std::string vertex2;
        std::tie(vertex1, vertex2) = vertex_list[i];
        out << "( " << vertex1 << ", " << vertex2 << " )";
        if (i != vertex_list.size() - 1) {
            out << ", ";
        }
    }
    return out;
}


int main(void) {

    /// Establish preset file paths for reading and writing operations
    std::string graph_filename = "./dot_graphs/full_graph.gv";
    // std::string graph_filename = "./dot_graphs/full_graph.gv";
    std::string rel_path = "sample_graphs/";
    std::string path_filename = "./dot_graphs/shortest_path.gv";
    std::string read_name;
    /// Determine and present acceptable files from designated directory for user-provided graph text files
    int file_output = get_graph_filename(rel_path, read_name);
    if (file_output < 0) {
        return EXIT_SUCCESS;
    }

    /// Handle User Input For Total Number of Verticies in Submitted Graph
    long int vertex_count;
    get_graph_vertex_count(vertex_count);

    /// Build main_hashmap data struct to store a relevant graphical information extracted from user-provided graph file
    /// Write relevant extracted information in dot language format to designated .gv file for building graph visualization 
    auto main = main_hashmap<double>(static_cast<unsigned int>(vertex_count));
    std::cout << "Building graph from '" << read_name << "' file contents..." << '\n';
    std::cout << "Writing graph information to file '" << graph_filename << "' for image processing..." << '\n';
    unsigned int file_vertex_count = static_cast<unsigned int>(vertex_count);
    int output = build_adjacency_list(rel_path, graph_filename, file_vertex_count, main);
    if (output < 0) {
        return EXIT_FAILURE;
    }

    /// Handle User Input for Preferred Calculation to Apply using Extracted Information
    std::cout << "Graph Successfully Built!" << '\n' << '\n';
    std::string algorithm_type;
    int request_output = get_requested_algorithm (algorithm_type, main, path_filename);
    if (request_output < 0) {
        return EXIT_FAILURE;
    }

    /// Run Bash Script for Generating Graph Images
    char visualize_script_path[] = "./scripts/visualize_graph.sh";
    char bash_path[] = "/bin/bash";
    // char bash_path[] = "/opt/homebrew/bin/bash"
    pid_t pid = fork();
    int childStatus;
    switch(pid) {
        case -1:
            perror("fork");
            break;
        case 0:
            std::cout << "Running \"visualize_graph.sh\" to build graphs from graph information..." << '\n';
            execl(bash_path, bash_path, visualize_script_path, nullptr);
            perror("execl");
            break;
        default:
            pid = waitpid(pid, &childStatus, 0);

            std::cout << "Graph generation complete!\nThe generated image of the complete graph within the \"graph_images\" directory as \"full_graph.png\".\n";
            if (algorithm_type.compare("S") == 0) {
                std::cout << "The generated image of the shortest path from your provided verticies will be within \"shortest_path.png\"" << std::endl;
            }
    }
    return EXIT_SUCCESS;
}
