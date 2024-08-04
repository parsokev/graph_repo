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
#include <list>

#include "../includes/linked_list.hpp"
#include "../includes/pair_minheap.hpp"
#include "../includes/master_hashmap.hpp"
#include "../includes/graph_ops.hpp"
#include "../includes/gprintf.hpp"


int build_adjacency_list (std::string& filename, unsigned int vertex_count, master_hashmap<double>& adj_list) {
    std::fstream read_file;
    read_file.open(filename);
    if (read_file.is_open()) {
        std::string line;
        while (getline(read_file, line)) {
            auto hash_tab1 = master_hashmap<double>::oa_hashmap(vertex_count);
            auto hash_tab2 = master_hashmap<double>::oa_hashmap(vertex_count);
            std::istringstream line_read(line);
            size_t line_length = line.size();
            long int spacer = 2;
            auto end = line.find(',');
            // Ensure comma separating vertex 1 and 2 is found
            if (end == line.npos) {
                std::cerr << "FILE ERROR: Comma separating first vertex from second vertex not found!" << '\n';
                std::cerr << "Please ensure each line follows format:\n\t VERTEX1_NAME, VERTEX2_NAME, DISTANCE_BETWEEN_VERTICIES" << '\n';
            }
            assert(end != line.npos);
            std::string vertex = line.substr(0, end);
            // std::cout << vertex << '\n';
            // Ensure comma separting vertex 2 and the edge weight is found
            auto end_2 = line.rfind(',');
            if (end == line.npos) {
                std::cerr << "FILE ERROR: Comma separating second vertex from edge weight between vertex 1 and 2 not found!" << '\n';
                std::cerr << "Please ensure each line follows format:\n\t VERTEX1_NAME, VERTEX2_NAME, DISTANCE_BETWEEN_VERTICIES" << '\n';
            }
            assert(end != line.npos);

            // Ensure vertex 1 is found after a comma and a space 
            long int vertex_size = static_cast<long int>(vertex.size());
            if (vertex_size <= 0) {
                std::cerr << "FILE ERROR: No vertex name found after first comma!" << '\n';
                std::cerr << "Please ensure each line follows format:\n\t VERTEX1_NAME, VERTEX2_NAME, DISTANCE_BETWEEN_VERTICIES" << '\n';
            }
            assert(vertex_size > 0);

            // Ensure vertex 2 is found before end of the current line
            line_read.seekg(line_read.tellg() + spacer + vertex_size);
            if (line_read.tellg() == -1) {
                std::cerr << "FILE ERROR: Expected position of vertex 2 was not found (out of bounds)!" << '\n';
                std::cerr << "Please ensure each line follows format:\n\t VERTEX1_NAME, VERTEX2_NAME, DISTANCE_BETWEEN_VERTICIES" << '\n';
            }
            assert(line_read.tellg() != -1);

            size_t next_word = static_cast<size_t>(line_read.tellg());
            std::string vertex_2 = line.substr(next_word, end_2 - next_word);
            // std::cout << vertex_2 << '\n';
            
            // Ensure vertex 2 is found between space after first comma and space before second comma
            long int vertex2_size = static_cast<long int>(vertex_2.size());
            if (vertex2_size <= 0) {
                std::cerr << "FILE ERROR: Second vertex name was not found after second comma!" << '\n';
                std::cerr << "Please ensure each line follows format:\n\t VERTEX1_NAME, VERTEX2_NAME, DISTANCE_BETWEEN_VERTICIES" << '\n';
            }
            assert(vertex2_size > 0);

            // Ensure edge weight between verticies is found before end of current line
            line_read.seekg(line_read.tellg() + vertex2_size + spacer);
            if (line_read.tellg() == -1) {
                std::cerr << "FILE ERROR: Expected position of vertex 2 was not found (out of bounds)!" << '\n';
                std::cerr << "Please ensure each line follows format:\n\t VERTEX1_NAME, VERTEX2_NAME, DISTANCE_BETWEEN_VERTICIES" << '\n';
            }
            assert(line_read.tellg() != -1);

            size_t final_word = static_cast<size_t>(line_read.tellg());
            std::string weight_str = line.substr(final_word, line_length - final_word);
            double weight = strtod(weight_str.c_str(), nullptr);

            // Ensure edge weight contains a numerical value
            if (weight == std::numeric_limits<double>::infinity() || weight <= 0) {
                std::cerr << "FILE ERROR: Entered value did not contain any non-zero numerical digits" << '\n';
                std::cerr << "Please ensure each line follows format:\n\t VERTEX1_NAME, VERTEX2_NAME, DISTANCE_BETWEEN_VERTICIES" << '\n';
            }
            assert(weight != std::numeric_limits<double>::infinity() && weight > 0);
            // std::cout << weight << '\n';
            
            hash_tab1.add(vertex_2, weight);
            hash_tab2.add(vertex, weight);
            
            if (!adj_list.contains_key(vertex)) {
                adj_list.add_key(vertex, hash_tab1);
            } else {
                
                if (!adj_list.get_key_list(vertex).contains_key(vertex_2)) {
                    adj_list.get_key_list(vertex).add(vertex_2, weight);
                }
            }

            if (!adj_list.contains_key(vertex_2)) {
                adj_list.add_key(vertex_2, hash_tab2);
            } else {
                if (!adj_list.get_key_list(vertex_2).contains_key(vertex)) {
                    adj_list.get_key_list(vertex_2).add(vertex, weight);
                }
            }

        }
        read_file.close();
    } else {
        std::cerr << "FILE ERROR: Opening file '" << filename << "' failed!" << '\n';
        return -1; 
    }
    return 0;
}

void apply_djikstras_algorithm(std::string s_vertex, std::string des_vertex, unsigned int vertex_count, master_hashmap<double>& adj_list) {
    #ifdef NDEBUG
    #else
    std::cerr << adj_list << '\n';
    #endif
    auto visited_vertices = master_hashmap<double>::oa_hashmap(vertex_count);
    auto mhp = paired_min_heap<double, 0>{};
    auto vertex_list = adj_list.get_master_keys();
    auto vertex_path = master_hashmap<std::string>::oa_hashmap(vertex_count);

    // auto test_path = dl_list<std::string, 0> {};
    // auto master_path = master_hashmap<double>(vertex_count);
    // auto shorty_vertex = master_hashmap<double>::oa_hashmap(vertex_count);
    // test_path.add_to_back(s_vertex);


    // Prefill visited verticies hashmap key-value pairs of each vertex with a floating infinity distance value
    for (unsigned int i = 0; i < vertex_list.size(); i++) {
        visited_vertices.add(vertex_list[i], std::numeric_limits<double>::infinity());
    }
    // Set source vertex's distance to 0
    visited_vertices.add(s_vertex, 0.0);

    // Add source vertex to minimum heap
    mhp.add_node(s_vertex, 0);
    std::string popped_vertex;
    double popped_vertex_distance;

    // Initiate while loop until all verticies have been visited (minheap will be empty)
    while (mhp.get_heap_size() > 0) {
        // Remove next vertex with smallest distance from minimum heap
        std::tie(popped_vertex, popped_vertex_distance) = mhp.remove_min();
        // Retrieve current distance from source vertex to extracted vertex held in visited verticies
        auto current_min_distance = visited_vertices.get_val(popped_vertex);
        // If distance value of extracted value is greater than stored value, extract next vertex from minheap
        if (popped_vertex_distance > current_min_distance) {
            continue;
        }
        // If extracted vertex is destination vertex, shortest path has been found to destination vertex
        if (popped_vertex.compare(des_vertex) == 0) {
            break;
             

        }

        // Retrieve list of adjacent verticies for extracted vertex
        auto adjacent_vertex_list = adj_list.get_key_list(popped_vertex);
        
        // Iterate through list of all verticies present in graph to identify and access edge weights for each adjacent vertex
        for (unsigned int j = 0; j < vertex_list.size(); j++){
            // If vertex is found in list of verticies adjacent to extracted vertex, retrieve its weight
            if (adjacent_vertex_list.contains_key(vertex_list[j])) {
                gprintf("VISITING VERTEX OF %s with ADJACENT VERTEX %s", popped_vertex.c_str(), vertex_list[j].c_str());
                auto weight = adjacent_vertex_list.get_val(vertex_list[j]);
                // Check if sum of current distance and edge formed with adjacent vertex is less than current distance associated with vertex in shortest distance list
                // distance = distance from source to extracted vertex
                // weight = distance between extracted vertex and adjacent vertex
                // di = total distance from source vertex to adjacent vertex
                double di = weight + popped_vertex_distance;
                // If new edge creates a shorter path to adjacent vertex, update distance associated with adjacent vertex to shortest distance list
                if (di < visited_vertices.get_val(vertex_list[j])) {
                    // If new edge to be updated is the destination vertex, determine whether to update the vertices forming shortest path
                    if (des_vertex.compare(vertex_list[j]) == 0) {
                        gprintf("CURRENT VERTEX: ");
                        // std::cout << test_path << '\n';
                        #ifdef NDEBUG
                        #else
                        std::cerr << visited_vertices << '\n';
                        #endif
                        gprintf("UPDATING MINIMUM DISTANCE/PATH FROM SOURCE VERTEX TO DESTINATION VERTEX");
                        gprintf("Current vertex is %s", popped_vertex.c_str());

                        gprintf("Weight of edge between %s and %s is %.2lf", popped_vertex.c_str(), vertex_list[j].c_str(), weight);
                        gprintf("Current Distance from Source (%s) is %.2lf", s_vertex.c_str(), popped_vertex_distance);
                        gprintf("Previous minimum distance to destination vertex is %.2lf", visited_vertices.get_val(des_vertex));
                        gprintf("Updated minimum distance from to destination vertex is %.2lf\n", di);
                    }
                    visited_vertices.add(vertex_list[j], di);
                    vertex_path.add(vertex_list[j], popped_vertex);              
                    mhp.add_node(vertex_list[j], di);

                    // shorty_vertex.add(popped_vertex, 0);
                    // master_path.add_key(vertex_list[j], shorty_vertex);
                    // shorty_vertex.clear();
                }

            }
        }
    }

    gprintf("LIST OF SHORTEST DISTANCES FROM %s to EACH LABELED VERTEX", s_vertex.c_str());
    #ifdef NDEBUG
    #else
    std::cerr << visited_vertices << '\n';
    #endif
    gprintf("LIST OF LAST VERTEX TO VISIT EACH LABELED VERTEX");
    #ifdef NDEBUG
    #else
    std::cerr << vertex_path << '\n';
    #endif

    std::cout << "The Shortest Path from " << s_vertex << " TO " << des_vertex << " : " << '\n';

    auto prev_vertex = vertex_path.get_val(des_vertex);
    auto shortest_path = dl_list<std::string>{};
    shortest_path.add_to_front(des_vertex);


    // auto shorty = dl_list<std::string, 0>{};
    // auto next_v_list = master_path.get_key_list(des_vertex);
    // auto shorty_next = next_v_list.get_keys()[0];
    // auto shorty_val = vertex_path.get_val(des_vertex);
    // shorty.add_to_front(des_vertex);
    // auto test_val3 = next_v_list.get_val(des_vertex);
    // auto test_val4 = next_v_list.get_val(s_vertex);
    // auto test_val = vertex_path.get_val(des_vertex);
    // auto test_val2 = vertex_path.get_val(s_vertex);
    // auto test_val_key = master_path.get_key_val(s_vertex, des_vertex);
    // auto faux_val = master_path.get_key_val("Rome", s_vertex);

    // #ifdef NDEBUG
    // #else
    // std::cout << test_path << '\n';
    // std::cout << test_val << '\n';
    // std::cout << test_val2 << '\n';
    // std::cout << test_val3 << '\n';
    // std::cout << test_val4 << '\n';
    // std::cout << test_val_key << '\n';
    // std::cout << faux_val << '\n';
    // if (test_val2.empty()){
    //     std::cout << "Found empty" << s_vertex << '\n';
    // }
    // #endif

 
    // while (shorty_next.compare(s_vertex) != 0) {
    //     // auto next_val = test_path.get_val(shorty_next);
    //     shorty.add_to_front(shorty_next);
    //     next_v_list = test_path.get_key_list(shorty_next);
    //     shorty_next = next_v_list.get_keys()[0];
    // }
    // shorty.add_to_front(s_vertex);
    // #if NDEBUG
    // #else
    // std::cout << shorty << '\n';
    // std::cout << vertex_path << '\n';
    // #endif
    while (prev_vertex.compare(s_vertex) != 0) {
        shortest_path.add_to_front(prev_vertex);
        prev_vertex = vertex_path.get_val(shortest_path.get_front());
    }
    shortest_path.add_to_front(s_vertex);
    std::cout << shortest_path << '\n';

    std::cout << "Total Distance: " << visited_vertices.get_val(des_vertex) << '\n';
    std::cout << '\n';

}



void apply_prims_algorithm(std::string s_vertex, master_hashmap<double>& adj_list) {
    auto MST_verticies = std::vector<std::tuple<std::string, std::string>>{};
    auto MST_traversal = std::vector<std::string>{};
    double MST_sum = 0;
    auto mhp = paired_min_heap<double, 0>{};
    auto vertex_list = adj_list.get_master_keys();

    auto source_vertex = s_vertex;
    MST_traversal.push_back(source_vertex);
    mhp.add_node(source_vertex, 0);
    std::string vertex;
    double distance;
    while ( vertex_list.size() > MST_traversal.size()) {
        std::tie(vertex, distance) = mhp.remove_min();
        bool in_traversal = false;
        auto current_min_distance = adj_list.get_key_by_val(vertex, distance);
        auto adjacent_vertex_list = adj_list.get_key_list(vertex);
        for (unsigned int k = 0; k < MST_traversal.size(); k++) {
            if (MST_traversal[k].compare(vertex) == 0) {
                in_traversal = true;
                break;
            } 
        }

        if (!in_traversal) {
            MST_traversal.push_back(vertex);
            auto new_path = std::tuple<std::string, std::string>(current_min_distance, vertex);
            MST_verticies.push_back(new_path);
            MST_sum += distance;
        }
        
        
        for (unsigned int j = 0; j < vertex_list.size(); j++){
            // Find all adjacent verticies
            
            if(adjacent_vertex_list.contains_key(vertex_list[j])) {
                bool adj_in_traversal = false;
                // search for each adjacent vertex in MST_traversal
                for (unsigned int m = 0; m < MST_traversal.size(); m++) {
                    if (MST_traversal[m].compare(vertex_list[j]) == 0) {
                        adj_in_traversal = true;
                        break;
                    }

                }
                
                if (!adj_in_traversal) {
                    auto weight = adjacent_vertex_list.get_val(vertex_list[j]);
                    mhp.add_node(vertex_list[j], weight);
                }

            }

       }
    }
    std::cout << "The Minimum Spanning Tree is formed from the Edges of:" << '\n';
    for (unsigned int i = 0; i < MST_verticies.size(); i++) {
        std::string source;
        std::string dest;
        std::tie(source, dest) = MST_verticies[i];
        
        std::cout << source << " <----> " << dest << '\n';
    }
    std::cout << "With a Total Distance of " << MST_sum << '\n';

}