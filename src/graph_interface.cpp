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
#endif

#include <memory>

#include "../includes/graph_input.hpp"
#include "../includes/pair_minheap.hpp"
#include "../includes/derived_hashmap.hpp"
#include "../includes/graph_processing.hpp"
#include "../includes/graph_writing.hpp"


int main(void) {
    // Establish preset file paths for reading and writing operations
    std::string graph_filename = "../../dot_graphs/full_graph.gv";
    std::string rel_path = "../../sample_graphs/";
    std::string path_filename = "../../dot_graphs/shortest_path_overlay.gv";
    std::string MST_filename = "../../dot_graphs/MST_overlay.gv";
    std::string graph_path = "../../graph_images/full_graph.png";
    std::string read_name;
    #ifdef _WIN32
    std::string graphviz_path = "../../Graphviz/bin/";
    #endif


    
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
// Initialize Path Variables that will be Employed Based on Detected Platform's OS
    std::string script_path = "";
    std::string request_type = "";
    std::string destination_file = "";
    std::string command_val = "";
    // Set Universal Printed Output and Graph Image Locations based on type of Information Requested By User
    if (algorithm_type.compare("S") == 0) {
        request_type = "SHORTEST PATH";
        destination_file = "../../graph_images/shortest_path_overlay.png";
    } else {
        request_type = "MINIMUM SPANNING TREE";
        destination_file = "../../graph_images/MST_overlay.png";
    }

// Select Linux-Compatible Bash Script and set CLI command to environment path to linux bash if Linux is detected
// BUILD COMMANDS FOR LINUX
#ifdef __linux__
    // Preset Script Path and Graph Image Locations based on User Requested Information for Linux Users
    command_val = "/bin/bash";
    if (algorithm_type.compare("S") == 0) {
        script_path = "../../scripts/Linux/visualize_graph_SP.sh";
    } else {
        script_path = "../../scripts/Linux/visualize_graph_MST.sh";
    }
    // Ensure script written in Windows have carriage return characters replaced for read compatibility with Linux/Unix systems
    int windows_check;
    windows_check = check_for_CLRF(script_path);
    if (windows_check < 0) {
        std::cerr << "ERROR: Read error(s) were encountered while checking file '" << script_path << "'\n";
        return -1;
    }
#endif
    // BUILD COMMANDS FOR MACOS
    // If Preprocessor Conditional Detects MacOS, Directly Execute Multiple Bash Commands to Graphviz's Dot Executable through A Pipeline
    // Program Requires use of HomeBrew Executable to set Bash environment path and Graphviz bin path
#ifdef __APPLE__
    command_val = "";
    std::string dot_path = "dot";
    // IF MANUALLY ADDING GRAPHVIZ TO GRAPHVIZ DIRECTORY INSTEAD OF BASH ENV PATH UNCOMMENT THIS AND DELETE ABOVE LINE
    // std::string dot_path = "./Graphviz/bin/dot.exe";

    // Preset Script Path and Graph Image Locations based on User Requested Information for MacOS Users
    if (algorithm_type.compare("S") == 0) {
        // Set Output Image File Path Designated for Shortest Path and Specify Output Format to Graphviz's Dot using Appropriate .gv files for Input
        script_path = "chmod +x ";
        script_path..append(dot_path).append(" -Tpng:cairo ").append(graph_filename).append(" -o ").append(graph_path);
// Toggle verbosity of both graphviz commands based on based on build configuration
#ifndef RELEASE
        script_path.append(" -v; ");
#else
        script_path.append("; ");
#endif
        script_path.append(dot_path).append(" -Tpng:cairo ").append(path_filename).append(" -o ").append(destination_file);
// Toggle verbosity of both graphviz commands based on based on build configuration
#ifndef RELEASE
        script_path.append(" -v");
#endif
        gprintf("Path for Full Graph Image is '%s'", graph_path.c_str());
        gprintf("Path for Shortest Path Solution Image is '%s'", path_filename.c_str());
    } else {
        // Set Output Image File Path Designated for MST and Specify Output Format to Graphviz's Dot using Appropriate .gv files for Input
        script_path = "chmod +x ";
        script_path.append(dot_path).append(" -Tpng:cairo ").append(graph_filename).append(" -o ").append(graph_path);
#ifndef RELEASE
        script_path.append(" -v; ");
#else
        script_path.append("; ");
#endif
        script_path.append(dot_path).append(" -Tpng:cairo ").append(MST_filename).append(" -o ").append(destination_file);
#ifndef RELEASE
        script_path.append(" -v");
#endif
        gprintf("Path for Full Graph Image is '%s'", graph_path.c_str());
        gprintf("Path for MST Solution Image is '%s'", MST_filename.c_str());
    }
#endif
    // BUILD COMMANDS FOR WINDOWS
#ifdef _WIN32
    // If Preprocessor Conditional Detects Windows OS, Directly Execute Multiple Powershell Commands to Graphviz's Dot Executable through A Pipeline
    command_val = "powershell -Command \"";
    if (algorithm_type.compare("S") == 0) {
        // Set Output Image File Path Designated for Shortest Path and Specify Output Format to Graphviz's Dot using Appropriate .gv files for Input
        script_path = graphviz_path;
        script_path.append("dot -Tpng:cairo ").append(graph_filename).append(" -o ").append(graph_path);
// Toggle verbosity of both graphviz commands based on based on build configuration
#ifndef RELEASE
        script_path.append(" -v; ");
#else
        script_path.append("; ");
#endif
        script_path.append(graphviz_path).append("dot -Tpng:cairo ").append(path_filename).append(" -o ").append(destination_file);
#ifndef RELEASE
        script_path.append(" -v\"");
#else
        script_path.append("\"");
#endif
        gprintf("Path for Full Graph Image is '%s'", graph_path.c_str());
        gprintf("Path for Shortest Path Solution Image is '%s'", path_filename.c_str());
    } else {
        // Set Output Image File Path Designated for MST and Specify Output Format to Graphviz's Dot using Appropriate .gv files for Input
        script_path = graphviz_path;
        script_path.append("dot -Tpng:cairo ").append(graph_filename).append(" -o ").append(graph_path);
// Toggle verbosity of both graphviz commands based on based on build configuration
#ifndef RELEASE
        script_path.append(" -v; ");
#else
        script_path.append("; ");
#endif
        script_path.append(graphviz_path).append("dot -Tpng:cairo ").append(MST_filename).append(" -o ").append(destination_file);
#ifndef RELEASE
        script_path.append(" -v\"");
#else
        script_path.append("\"");
#endif
        gprintf("Path for Full Graph Image is '%s'", graph_path.c_str());
        gprintf("Path for MST Solution Image is '%s'", MST_filename.c_str());
    }
#endif
    // Return Without Executing Script Program if Preprocessor Conditionals indicate Unexpected/Undefined OS Detection
    if (script_path.size() == 0) {
        std::cerr << "Unexpected/Undefined OS detected.\nPlease view the README to ensure the OS is compatible";
        return EXIT_FAILURE;
    }
    gprintf("Attempting to Execute Script or Command of '%s'...", script_path.c_str());

// EXECUTE LINUX SCRIPTS
// Execute Bash Shell Scripts using Linux-Compliant <sys/wait.h> Library Functions for Image Generation if Linux OS is Detected
#ifdef __linux__
    // Run Appropriate Bash Script for Generating Graph Images
    pid_t pid = fork();
    int child_status;
    switch(pid) {
    case -1:
        perror("fork");
        break;
    case 0:
        gprintf("Executing '%s' to overlay the '%s' using the processed graphical information...\n", script_path.c_str(), request_type.c_str());
        std::cout << "\n=============================== IMAGE GENERATION RESULTS ====================================\n";
        execl(command_val.c_str(), command_val.c_str(), script_path.c_str(), nullptr);
        perror("execl");
        break;
    default:
        pid = waitpid(pid, &child_status, 0);
    }
    gprintf("Success!\nThe Image of the '%s' was placed within '%s'\n", request_type.c_str(), destination_file.c_str());
    gprintf("The Image of the Entire Graph was placed within:   '%s'", graph_path.c_str());
#else
     // EXECUTE WINDOWS/MACOS COMMANDS USING PIPELINE
    // Use popen(MacOS) or _popen (Windows), to Execute Commands/Scripts within a Pipeline and Read/Monitor its Output for Errors
    FILE *pipe_stream;
    command_val.append(script_path);
    gprintf("Generating the '%s' using the processed graphical information...\n", request_type.c_str());
    std::cout << "\n=============================== IMAGE GENERATION RESULTS ====================================\n";
#ifdef _WIN32
    // Establish Stream with Intent to both Execute the Powershell Script and Read from Buffer containing the Command Line Output for Error Detection
    // Use _popen for compatibility over broader range of windows systems
    pipe_stream = _popen(command_val.c_str(), "r");
#else
    // If MacOS use standard popen instead
    pipe_stream = popen(command_val.c_str(), "r");
#endif
    // If Stream is Successfully Established with Pipeline, Attempt to Execute Powershell Commands to Generate Requested Solution and Full Graph Images
    if (pipe_stream != NULL) {
#ifdef _WIN32
        // Use _pclose for windows
        int script_error = _pclose(pipe_stream);
#else \
    // Use standard pclose for MacOS
        int script_error = pclose(pipe_stream);
#endif \
    // If One or More Errors are Encountered in Execution of Powershell/Bash Commands, Notify User
        if (script_error == -1) {
            std::cerr << "ERROR: '" << script_path << "' encountered error(s) while executing to generate image of '"<< request_type << "' \n";
            return EXIT_FAILURE;
        } else {
            // Else, Proceed with Indicating Images are Ready for Viewing, report to debugging for status checking
            std::cout << "Success!\nThe Image of the '" << request_type << "' was placed within '" << destination_file << "'\n";
            std::cout << "The Image of the Entire Graph was placed within:   '" << graph_path << '\n';
        }

    } else {
        // Exit if Internal Fork or Pipe Operations Fail
        perror("pipe/fork");
        std::cerr << "ERROR: Failed to establish pipeline stream for executing shell commands using popen with '" << script_path << "'\n";
        return EXIT_FAILURE;
    }
#endif
    return EXIT_SUCCESS;
}

