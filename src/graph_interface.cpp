#include <iostream>
#include <experimental/random>
#include <vector>
#include <iosfwd>
#include <tuple>
#include <string>
#include <cmath>
#include <limits>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include <stdexcept>
#include <type_traits>


#include "../includes/minheap.hpp"
#include "../includes/vector_minheap.hpp"
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

class INVALID_VERTEX_VALUE_EXCEPTION {};

int main(void) {
    // if (argc != 3) {
    //     std::cerr << "USAGE: FOR DEBUGGING: ./debug/executable_name [vertex_count] [filename_of_weighted_edges]" << '\n';
    //     std::cerr << '\t' << "FOR TESTING: ./release/executable_name [vertex_count] [filename_of_weighted_edges]" << std::endl;
    //     return EXIT_FAILURE;
    // }
    std::cout << "Please Enter the Filename containing the Weighted Graph Edges: ";
    std::string read_name;
    unsigned int vertex_count;
    // decltype (vertex_count) vertex_arg;
    std::cin >> read_name;
    std::cin.clear();
    std::cout << '\n';
    std::cout << "Please Enter the Approximate Number of Unique Verticies: ";
    try {
        std::cin >> vertex_count;
        if (std::cin.fail() || vertex_count <= 0) {
            throw INVALID_VERTEX_VALUE_EXCEPTION();
        }
    }
    catch (INVALID_VERTEX_VALUE_EXCEPTION e) {
        std::cerr << "Invalid Argument: Number of Verticies must be a positive integer value greater than zero." << '\n';
        return EXIT_FAILURE;
    }
    std::cout << '\n';
    // std::string read_name(argv[2]);
    // int vertex_count = 5;
    // int vertex_count = static_cast<int>(strtod(argv[1], nullptr));
    // std::vector<std::string> verticies_list {};
    // auto master = master_hashmap<double>(vertex_count);
    auto main = main_hashmap<double>(vertex_count);
    // build_vertex_list(my_file, file_name, verticies_list);
    // std::cout << verticies_list << std::endl;
    std::cout << "Building graph from '" << read_name << "' file contents..." << '\n';
    // int output = build_adjacency_list(read_name, vertex_count, master);
    int output = build_adjacency_list(read_name, vertex_count, main);
    if (output < 0) {
        return EXIT_FAILURE;
    }
    std::cout << "Graph Successfully Built!" << '\n' << '\n';

    std::string source_vertex;
    
    // std::cout << "Your Verticies Include: " << master.get_master_keys() << '\n';
    std::cout << "Your Verticies Include: " << main.get_main_keys() << '\n';
    std::cout << "Please Enter The Source Vertex: ";
    std::getline(std::cin>>std::ws, source_vertex);
    // while (!master.contains_key(source_vertex) && source_vertex.compare("exit now") != 0) {
    while (!main.contains_key(source_vertex) && source_vertex.compare("exit now") != 0) {
        std::cout << '\n' << "Error: Entered Source Vertex of '" << source_vertex << "' not found Within Generated Graph. Please try again or enter 'exit now' to exit." << '\n';
        // std::cout << "Your Verticies Include: " << master.get_master_keys() << '\n';
        std::cout << "Your Verticies Include: " << main.get_main_keys() << '\n';
        std::cout << "Please Enter The Source Vertex: ";
        std::getline(std::cin>>std::ws, source_vertex);
    }
    if (source_vertex.compare("exit now") == 0) {
        return EXIT_SUCCESS;
    }

    std::string dest_vertex;
    // std::cout << '\n' << "Your Verticies Include: " << master.get_master_keys() << '\n';
    std::cout << '\n' << "Your Verticies Include: " << main.get_main_keys() << '\n';
    std::cout << "Please Enter The Destination Vertex: ";
    std::getline(std::cin>>std::ws, dest_vertex);
    // while (!master.contains_key(dest_vertex) && dest_vertex.compare("exit now") != 0) {
    while (!main.contains_key(dest_vertex) && dest_vertex.compare("exit now") != 0) {
        std::cout << '\n' << "Error: Entered Destination Vertex of '" << dest_vertex << "' not found Within Generated Graph. Please try again or enter 'exit now' to exit." << '\n';
        // std::cout << "Your Verticies Include: " << master.get_master_keys() << '\n';
        std::cout << "Your Verticies Include: " << main.get_main_keys() << '\n';
        std::cout << "Please Enter The Destination Vertex: ";
        std::getline(std::cin>>std::ws, dest_vertex);
    }
    if (dest_vertex.compare("exit now") == 0) {
        return EXIT_SUCCESS;
    }

    std::string algorithm_type;
    std::cout << '\n' << "Please Enter Desired Graph Output ('M' for Minimum Spanning Tree OR 'S' for Shortest Distance): ";
    std::getline(std::cin, algorithm_type);
    while (algorithm_type.compare("M") != 0 && algorithm_type.compare("S") != 0 && algorithm_type.compare("exit now")) {
        std::cout << "Error: '" << algorithm_type << "' is not a valid. Please try again or enter 'exit now' to exit." << '\n';
        std::cout << "Please Enter Desired Graph Output ('M' for Minimum Spanning Tree OR 'S' for Shortest Distance): ";
        std::getline(std::cin, algorithm_type);
    }
    if (algorithm_type.compare("exit now") == 0) {
        return EXIT_SUCCESS;
    }
    if (algorithm_type.compare("M") == 0) {
        std::cout << '\n';
        // apply_prims_algorithm(source_vertex, master);
        apply_prims_algorithm(source_vertex, main);
        
    }

    if (algorithm_type.compare("S") == 0) {
        std::cout << '\n';
        // apply_djikstras_algorithm(source_vertex, dest_vertex, vertex_count, master);
        apply_djikstras_algorithm(source_vertex, dest_vertex, vertex_count, main);
        
    }
    return EXIT_SUCCESS;
}