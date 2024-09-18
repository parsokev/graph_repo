#include <iostream>
#include <vector>
#include <iosfwd>
#include <tuple>
#include <string>
#include <cstdio>
#include <fstream>
#include <filesystem>
#include <list>
#include <algorithm>

#include "../includes/derived_hashmap.hpp"
#include "../includes/graph_input.hpp"
#include "../includes/graph_processing.hpp"

/**
 * Overloading function for printing string Vector-type container arrays to standard output stream
 */
std::ostream& operator<<(std::ostream& out, const std::vector<std::string>& string_list) {
    out << "[ ";
    out << '\n';
    int key_counter = 0;
    for (std::string key : string_list) {
        if (key_counter == 10) {
            out << '\n';
            key_counter = 0;
        }
        if ( key == string_list.back()) {
            out << key;
        } else {
            out << key << ", ";
        }
        key_counter ++;
    }
    out << '\n';
    out << " ]";
    return out;
}

/**
 * Local function for printing string List-type container array to standard output
 * @param list_s List container holding string values to be printed in readable format
 */
static void print_list(std::list<std::string>& list_s) {
    std::cout << "[ ";
    for (std::string i : list_s) {
        if ( i == list_s.back()) {
            std::cout << i;
        } else {
            std::cout << i << ", ";
        }
    }
    std::cout << " ]" << '\n';
    return;
}


int get_graph_filename(std::string& directory_name, std::string& user_file) {
    /// Retrieve contents of designated directory for storing user-provided graph information 
    auto file_list = std::list<std::string>{};
    for (const auto& sample_file : std::filesystem::directory_iterator(directory_name)){
        std::string file_name = sample_file.path().string();
        file_name.erase(file_name.begin(), file_name.begin() + 14);
        file_list.emplace_back(std::move(file_name));
    }
    /// Display file contents to user
    std::cout << "Current text files available are: " << '\n';
    print_list(file_list);
    std::cout << '\n';
    /// Handle user input of graph filename
    std::cout << "Please Enter the Filename containing the Weighted Graph Edges: ";
    getline(std::cin>>std::ws, user_file);
    // while(!file_list.contains_node(user_file) && user_file.compare("exit now") != 0) {
    while(std::find(file_list.begin(), file_list.end(), user_file) == file_list.end() && user_file.compare("exit now") != 0) {
        std::cerr << "\nERROR: Filename of '" << user_file << "' not found in \"sample_graphs\" directory" << '\n';
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


int get_graph_vertex_count(long int& vertex_count) {
    /// Handle user provided value for total number of unique verticies in provided graph file
    std::cout << "Please Enter the Approximate Number of Unique Verticies (or Enter \"0\" to abort): ";
    while(!(std::cin >> vertex_count) || vertex_count > UINT32_MAX || vertex_count < 0) {

        /// Handle when user provides a negative integer or a non-integer value
        if (std::cin.fail() || vertex_count < 0) {
            std::cerr << "Invalid Vertex Count: Number of Verticies must be a positive integer value greater than zero" << '\n';
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
        std::cout << "Please Enter the Approximate Number of Unique Verticies (or Enter \"0\" to abort): ";
    }

    /// Convert zero values to default size of 5
    if (vertex_count == 0) {
        std::cerr << "Recognized exit value of \"0\" detected. Closing Program... Goodbye!" << '\n';
        return -1;
    }

    /// Prompt user for confirmation when number of unique verticies within graph exceed 1000 before proceeding further
    if (vertex_count > 1000) {
        std::string conf_line;
        std::cout << "Please confirm '" << vertex_count << "' is the expected number of UNIQUE verticies: [y/n]: ";
        std::getline(std::cin >> std::ws, conf_line);
        while(conf_line.compare("y") != 0 && conf_line.compare("n") != 0) {
            std::cerr << "ERROR: The entered value of '" << conf_line << "' is not a recognized entry\n";
            std::cout << "Please enter either 'y' or 'n' to confirm whether '" << vertex_count << "' is the expected number of UNIQUE verticies within the graph to be processed: ";
            std::getline(std::cin >> std::ws, conf_line);
        }
        if (conf_line.compare("n") == 0) {
            std::cout << "\nUnintended vertex count entry confirmed.\n";
            std::cout << "You may restart the program at any time to re-enter the intended number of unique verticies within the graph to be processed. Goodbye!\n";
            return -1;
        } else {
            std::cout << "Confirmation of '" << vertex_count << "' unique verticies within the graph to be processed received!\n";
        }
    }
    std::cout << '\n';
    return 0;
}


int get_shortest_path(main_hashmap<double>&& main, const std::string& graph_filename, const std::string& path_filename) {
    /// Provide User with All Possible Verticies Extracted From User-Provided Graph File
    std::cout << '\n';
    std::cout << "Shortest Path Calculation Selected" << '\n';
    std::cout << "If you wish to exit the program, enter \"exit now\" at any time" << '\n';
    std::cout << '\n';
    std::string source_vertex;
    std::cout << "Your Verticies Include: " << main.get_keys() << '\n';
    
    /// Get User's Requested Source Vertex
    std::cout << "Please Enter The Source Vertex: ";
    std::getline(std::cin >> std::ws, source_vertex);
    while (!main.contains_key(source_vertex) && source_vertex.compare("exit now") != 0) {
        std::cout << '\n' << "Error: Entered Source Vertex of '" << source_vertex << "' not found Within Generated Graph." << '\n';
        std::cout << "Please try again or enter 'exit now' to exit." << '\n';
        std::cout << "Your Verticies Include: " << main.get_keys() << '\n';
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
    std::cout << '\n' << "Your Verticies Include: " << main.get_keys() << '\n';
    std::cout << "Please Enter The Destination Vertex: ";
    std::getline(std::cin >> std::ws, dest_vertex);
    while (!main.contains_key(dest_vertex) && dest_vertex.compare("exit now") != 0) {
        std::cout << '\n' << "Error: Entered Destination Vertex of '" << dest_vertex << "' not found Within Generated Graph. Please try again or enter 'exit now' to exit." << '\n';
        std::cout << "Your Verticies Include: " << main.get_keys() << '\n';
        std::cout << "Please Enter The Destination Vertex: ";
        std::getline(std::cin >> std::ws, dest_vertex);
    }
    std::cout << '\n';
    /// Get User Request for Exiting Program
    if (dest_vertex.compare("exit now") == 0) {
        std::cout << "Exiting Program... Goodbye!" << std::endl;
        return 0;
    }
    /// Generate Shortest Path from user-provided graph file
    int valid_path = 0;
    try {
        valid_path = find_shortest_path(source_vertex, dest_vertex, graph_filename, path_filename, std::move(main));
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return -1;
    }

    if (valid_path < 0) {
        return -1;
    }
    return 0;
}


int get_requested_algorithm (std::string& algorithm_type, main_hashmap<double>&& main, const std::string& graph_filename, const std::string& path_filename, const std::string& MST_filename) {
    /// Generate Requested Output based on User Request
    std::cout << "For Calculating the Minimum Spanning Tree, Enter \"M\"" << '\n';
    std::cout << "For Calculating the Shortest Path Between Two Verticies, Enter \"S\"" << '\n';
    std::cout << "To Exit the Program, Enter \"exit now\"" << '\n';
    std::cout << '\n' << "Please Enter Desired Graph Output: ";

    /// Handle user input for type of requested calculation
    getline(std::cin >> std::ws, algorithm_type);
    while (algorithm_type.compare("M") != 0 && algorithm_type.compare("S") != 0 && algorithm_type.compare("exit now") != 0) {
        std::cout << "Error: '" << algorithm_type << "' is not an accepted value. Please try again or enter 'exit now' to exit." << '\n';
        std::cout << "Please Enter Desired Graph Output ('M' for Minimum Spanning Tree OR 'S' for Shortest Distance OR 'exit now' to exit): ";
        std::getline(std::cin >> std::ws, algorithm_type);
    }
    /// User wishes to exit program
    if (algorithm_type.compare("exit now") == 0) {
        std::cout << "Exiting Program... Goodbye!" << std::endl;
        return -1;
    }

    /// User wishes to have MST calculated of provided graph
    if (algorithm_type.compare("M") == 0) {
        std::cout << '\n';
        std::cout << "Minimum Spanning Tree Calculations Selected" << '\n';
        std::string start_vertex = main.get_keys()[0];
        int valid_tree = 0;
        try {
            valid_tree = find_MST(start_vertex, graph_filename, MST_filename, std::move(main));
        } catch (std::exception& e) {
            std::cerr << e.what() << '\n';
        }

        if (valid_tree < 0) {
            return -1;
        }
    }

    /// User wishes to have shortest path calculated using provided graph
    if (algorithm_type.compare("S") == 0) {
        int path_output = 0;
        try {
            path_output = get_shortest_path(std::move(main), graph_filename, path_filename);
        } catch (std::exception& e) {
            std::cerr << e.what() << '\n';
        }

        if (path_output < 0) {
            return -1;
        }
    }
    return 0;
}