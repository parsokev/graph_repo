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
// sys/wait.h is only compatible Linux OS
#ifdef __linux__
#include <sys/wait.h>
#else
#endif

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

    // Execute Bash shell scripts for image generation if Linux OS is detected
    #ifdef __linux__
    // Preset Script Path and Graph Image Locations based on User Requested Information for Linux Users
    std::string script_path;
    std::string_view request_type;
    if (algorithm_type.compare("S") == 0) {
        script_path = "./scripts/Linux/visualize_graph_SP.sh";
        request_type = "SHORTEST PATH";
    } else {
        script_path = "./scripts/Linux/visualize_graph_MST.sh";
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
    #else
        // Preset Script Path and Graph Image Locations based on User Requested Information and OS type
        std::string script_path;
        std::string_view request_type;
        std::string_view destination_file;
        #ifdef _WIN32
        if (algorithm_type.compare("S") == 0) {
            script_path = "dot -Tpng:cairo ./dot_graphs/full_graph.gv -o ./graph_images/full_graph.png; dot -Tpng:cairo ./dot_graphs/shortest_path_overlay.gv -o ./graph_images/shortest_path_overlay.png\"";
            request_type = "SHORTEST PATH";
            destination_file = "./graph_images/shortest_path_overlay.png";
        } else {
            script_path = "dot -Tpng:cairo ./dot_graphs/full_graph.gv -o ./graph_images/full_graph.png; dot -Tpng:cairo ./dot_graphs/MST_overlay.gv -o ./graph_images/MST_overlay.png\"";
            request_type = "MINIMUM SPANNING TREE";
            destination_file = "./graph_images/MST_overlay.png";
        }
        #elif __APPLE__
        if (algorithm_type.compare("S") == 0) {
            script_path = "./scripts/MacOS/MACvisualize_graph_SP_MAC.sh";
            request_type = "SHORTEST PATH";
            destination_file = "./graph_images/shortest_path_overlay.png";
        } else {
            script_path = "./scripts/MacOS/MACvisualize_graph_MST_MAC.sh";
            request_type = "MINIMUM SPANNING TREE";
            destination_file = "./graph_images/MST_overlay.png";
        }
        #else
            // Don't attempt to execute image scripts using command line if preprocessor conditionals indicate possible OS incompatibility
            return EXIT_SUCCESS;
        #endif
        FILE *pipe_stream;
        // std::string command_val = "powershell ";
        std::string command_val = "powershell -Command \"";
        command_val.append(script_path);
        std::cout << "Generating the " << request_type << " using the processed graphical information..." << '\n';
        std::cout << "\n=============================== IMAGE GENERATION RESULTS ====================================\n";
        // Establish stream with intent to read from buffer containing the command line output written to standard output 
        pipe_stream = popen(command_val.c_str(), "r");
        // If stream is successfully established with pipeline and is able to read it, extract the line count printed by 
        if (pipe_stream != NULL) {
            int script_error = pclose(pipe_stream);
            if (script_error == -1) {
                std::cerr << "ERROR: '" << script_path << "' encountered error(s) while executing to generate image of '"<< request_type << "' \n"; 
            } else {
                std::cout << "Success!\n";
                std::cout << "The Image of the " << request_type << " was placed within:    " << destination_file << '\n';
                std::cout << "The Image of the Entire Graph was placed within:   ./graph_images/full_graph.png\n";
            }
            pclose(pipe_stream);
        } else {
            // Exit if fork or pipe operations fail
            perror("pipe/fork");
            std::cerr << "ERROR: Failed to establish pipeline stream for executing powershell script '" << script_path << "'\n";
            return -1;
        }

    #endif
    return EXIT_SUCCESS;
}
