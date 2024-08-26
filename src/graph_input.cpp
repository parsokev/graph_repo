#include <iostream>
#include <vector>
#include <iosfwd>
#include <tuple>
#include <string>
#include <cstdio>
#include <fstream>
#include <filesystem>

#include "../includes/derived_hashmap.hpp"
#include "../includes/linked_list.hpp"
#include "../includes/graph_input.hpp"
#include "../includes/graph_ops.hpp"

std::ostream& operator<<(std::ostream&out, const std::vector<std::string>& string_list) {
    out << "[ ";
    for (unsigned int i = 0; i < string_list.size(); i++) {
        if ( i == string_list.size() - 1) {
            out << string_list[i];
        } else {
            out << string_list[i] << ", ";
        }
    }
    out << " ]";
    return out;
}

int get_graph_filename(std::string& directory_name, std::string& user_file) {
    /// Retrieve contents of designated directory for storing user-provided graph information 
    auto file_list = dl_list<std::string>{};
    for (const auto& sample_file : std::filesystem::directory_iterator(directory_name)){
        std::string file_name = sample_file.path().string();
        file_name.erase(file_name.begin(), file_name.begin() + 14);
        file_list.add_to_back(file_name);
    }
    /// Display file contents to user
    std::cout << "Current text files available are: " << '\n';
    std::cout << file_list << '\n';
    std::cout << '\n';
    /// Handle user input of graph filename
    std::cout << "Please Enter the Filename containing the Weighted Graph Edges: ";
    getline(std::cin>>std::ws, user_file);
    while(!file_list.contains_node(user_file) && user_file.compare("exit now") != 0) {
        std::cerr << "Error: Filename of '" << user_file << "' not found in \"sample_graphs\" directory" << '\n';
        std::cout << "If you wish to Exit, Enter \"exit now\" instead." << '\n';
        std::cout << "Please Enter the Filename of file within \"sample_graphs\" directory containing the Weight Graph Edges: ";
        std::getline(std::cin >> std::ws, user_file);
    }
    /// Exit Program if user requests it
    if (user_file.compare("exit now") == 0) {
        std::cout << "Exiting Program... Goodbye" << std::endl;
        return -1;
    }
    /// Clear error flags for next user testing phase
    std::cin.clear();
    // Update relative path to user-provided graph_file for reading operation
    directory_name.append(user_file);
    std::cout << '\n';
    return 0;
}

void get_graph_vertex_count(long int& vertex_count) {
    /// Handle user provided value for total number of unique verticies in provided graph file
    std::cout << "Please Enter the Approximate Number of Unique Verticies: ";
    while(!(std::cin >> vertex_count) || vertex_count > UINT32_MAX) {
        /// Handle when user provides non-integer value
        if (std::cin.fail()) {
            std::cerr << "Invalid Vertex Count: Number of Verticies must be a positive integer value greater than zero (and preferably much less than 4294967294)." << '\n';
        }
        /// Handle when user provides an integer value larger than maximum size used for storage in hashmap objects
        if (vertex_count > UINT32_MAX) {
            std::cerr << "Invalid Vertex Count: Number exceeding maximum acceptable size of 4294967294 detected" << '\n';
        }
        // Clear failbit error flag
        std::cin.clear();
        // Discard rest of string line from standard input stream
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // Ask for user input
        std::cout << "Please Enter the Approximate Number of Unique Verticies (or Enter \"Ctrl+C\" to abort): ";
    }
    /// Convert negative integer to positive integer if provided by user
    if (vertex_count < 0) {
        vertex_count *= -1;
        std::cerr << "Negative integer value entered, changing value to " << vertex_count << '\n';
    }
    /// Convert zero values to default size of 5
    if (vertex_count == 0) {
        vertex_count += 5;
        std::cerr << "Invalid integer value of zero entered, incrementing value to " << vertex_count << '\n';
    }

    std::cout << '\n';
}

int get_shortest_path(main_hashmap<double>& main, std::string& path_filename) {
    /// Provide User with All Possible Verticies Extracted From User-Provided Graph File
    std::cout << '\n';
    std::cout << "Shortest Path Calculation Selected" << '\n';
    std::cout << "If you wish to exit the program, enter \"exit now\" at any time" << '\n';
    std::cout << '\n';
    std::string source_vertex;
    std::cout << "Your Verticies Include: " << main.get_main_keys() << '\n';
    
    /// Get User's Requested Source Vertex
    std::cout << "Please Enter The Source Vertex: ";
    std::getline(std::cin >> std::ws, source_vertex);
    while (!main.contains_key(source_vertex) && source_vertex.compare("exit now") != 0) {
        std::cout << '\n' << "Error: Entered Source Vertex of '" << source_vertex << "' not found Within Generated Graph." << '\n';
        std::cout << "Please try again or enter 'exit now' to exit." << '\n';
        std::cout << "Your Verticies Include: " << main.get_main_keys() << '\n';
        std::cout << "Please Enter The Source Vertex: ";
        std::getline(std::cin >> std::ws, source_vertex);
    }
    /// Get User Request for Exiting Program    
    if (source_vertex.compare("exit now") == 0) {
        std::cout << "Exiting Program... Goodbye!" << std::endl;
        return 0;
    }

    /// Get User's Requested Destination Vertex
    std::string dest_vertex;
    std::cout << '\n' << "Your Verticies Include: " << main.get_main_keys() << '\n';
    std::cout << "Please Enter The Destination Vertex: ";
    std::getline(std::cin >> std::ws, dest_vertex);
    while (!main.contains_key(dest_vertex) && dest_vertex.compare("exit now") != 0) {
        std::cout << '\n' << "Error: Entered Destination Vertex of '" << dest_vertex << "' not found Within Generated Graph. Please try again or enter 'exit now' to exit." << '\n';
        std::cout << "Your Verticies Include: " << main.get_main_keys() << '\n';
        std::cout << "Please Enter The Destination Vertex: ";
        std::getline(std::cin >> std::ws, dest_vertex);
    }
    std::cout << '\n';
    /// Get User Request for Exiting Program
    if (dest_vertex.compare("exit now") == 0) {
        std::cout << "Exiting Program... Goodbye!" << std::endl;
        return 0;
    }
    /// Generate MST from user-provided graph file
    int valid_path = apply_djikstras_algorithm(source_vertex, dest_vertex, path_filename, main);
    if (valid_path < 0) {
        return -1;
    }
    return 0;
}

int get_requested_algorithm (std::string& algorithm_type, main_hashmap<double>& main, std::string& path_filename) {
    /// Generate Requested Output based on User Request
    std::cout << "For Calculating the Minimum Spanning Tree, Enter \"M\"" << '\n';
    std::cout << "For Calculating the Shortest Path Between Two Verticies, Enter \"S\"" << '\n';
    std::cout << "To Exit the Program, Enter \"exit now\"" << '\n';
    std::cout << '\n' << "Please Enter Desired Graph Output: ";

    /// Handle user input for type of requested calculation
    getline(std::cin >> std::ws, algorithm_type);
    while (algorithm_type.compare("M") != 0 && algorithm_type.compare("S") != 0 && algorithm_type.compare("exit now") != 0) {
        std::cout << "Error: '" << algorithm_type << "' is not an accepted value. Please try again or enter 'exit now' to exit." << '\n';
        std::cout << "Please Enter Desired Graph Output ('M' for Minimum Spanning Tree OR 'S' for Shortest Distance): ";
        std::getline(std::cin >> std::ws, algorithm_type);
    }
    /// User wishes to exit program
    if (algorithm_type.compare("exit now") == 0) {
        std::cout << "Exiting Program... Goodbye!" << std::endl;
        return 0;
    }

    /// User wishes to have MST calculated of provided graph
    if (algorithm_type.compare("M") == 0) {
        std::cout << '\n';
        std::cout << "Minimum Spanning Tree Calculations Selected" << '\n';
        std::string start_vertex = main.get_main_keys()[0];
        int valid_tree = apply_prims_algorithm(start_vertex, main);
        if (valid_tree < 0) {
            return -1;
        }
    }

    /// User wishes to have shortest path calculated using provided graph
    if (algorithm_type.compare("S") == 0) {
        int path_output = get_shortest_path(main, path_filename);
        if (path_output < 0) {
            return -1;
        }
    }
    return 0;
}