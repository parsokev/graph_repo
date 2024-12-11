// Suppress non-critical compiler warnings if using Microsoft Visual Studio compiler
#ifdef VS_PRESENT
#pragma warning(disable : 4265 4625 4626 4688 4710 4711 4866 4820 5045 )
#endif

#include <iostream>
#include <vector>
#include <iosfwd>
#include <tuple>
#include <string>
#include <cmath>
#include <limits>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <utility>
#include <memory>

#include "../includes/pair_minheap.hpp"
#include "../includes/derived_hashmap.hpp"
#include "../includes/graph_input.hpp"
#include "../includes/gprintf.hpp"
#include "../includes/graph_writing.hpp"

/**
 * Local function for printing vector container contents in linked-list style
 * format to standard output to depict shortest path in direction of travel
 * from source to destination
 * @param path_list Vector-type container holding verticies composing the shortest path in order of traversal to destination
 */
static void print_shortest_path(const std::vector<std::string>& path_list) {
    for (auto& key : path_list) {
        if (key == path_list.back() ) {
            std::cout << key;
        } else {
            std::cout << key << " -> ";
        }
    }
    std::cout << '\n';
    return;
}


int build_adjacency_list(const std::string &filename,
                         const std::string &write_name,
                         unsigned int vertex_count,
                         main_hashmap<double> &&adj_list)
{
    std::fstream read_file;
    // Open write.gv file with name of `write_file`, creating it if it doesn't exist or replacing its contents if it does
    std::fstream write_file{write_name, write_file.trunc | write_file.out};

    read_file.open(filename);
    /*
    Try to open user-provided text file of graph edges `filename`, and if successful, try to open
    file to write to in Dot language format `write_name`, or create it if it does not already exist.
    If either fails, notify user and abort program
    */
    if (read_file.is_open()) {
        std::string close_brace = "}";
        std::string graph_type = "undirected";
        std::string title = "Full Graph";

        int header_write = write_graph_header(write_file, graph_type, title);
        if (header_write < 0) {
            std::cerr << "\nERROR encountered while writing header to graph file '"
                      << write_name << "'!" << '\n';
            return -1;
        }

        std::string line;
        int line_count = 0;
        // Process each line according to expected format, notify user of any detected deviation
        while (getline(read_file, line)) {
            line_count++;
            std::istringstream line_read(line);
            size_t line_length = line.size();
            long int spacer = 2;
            auto end = line.find(',');

            // Ensure comma separating vertex 1 and 2 is found
            if (end == line.npos) {
                std::cerr << "\nFILE ERROR: Line:" << line_count
                          << ", Comma separating first vertex from second vertex not found!"
                          << '\n';
                std::cerr << "Please ensure each line follows format:\n\t VERTEX1_NAME, "
                             "VERTEX2_NAME, DISTANCE_BETWEEN_VERTICIES"
                          << '\n';
                read_file.close();
                write_file.close();
                return -1;
            }
            std::string vertex = line.substr(0, end);

            // Ensure comma separting vertex 2 and the edge weight is found
            auto end_2 = line.rfind(',');
            if (end == line.npos) {
                std::cerr << "\nFILE ERROR: Line:" << line_count
                          << ", Comma separating second vertex from edge weight between vertex "
                             "1 and 2 not found!"
                          << '\n';
                std::cerr << "Please ensure each line follows format:\n\t VERTEX1_NAME, "
                             "VERTEX2_NAME, DISTANCE_BETWEEN_VERTICIES"
                          << '\n';
                read_file.close();
                write_file.close();
                return -1;
            }

            // Ensure vertex 1 is found after a comma and a space
            long int vertex_size = static_cast<long int>(vertex.size());
            if (vertex_size <= 0) {
                std::cerr << "\nFILE ERROR: Line:" << line_count
                          << " , No vertex name found after first comma!" << '\n';
                std::cerr << "Please ensure each line follows format:\n\t VERTEX1_NAME, "
                             "VERTEX2_NAME, DISTANCE_BETWEEN_VERTICIES"
                          << '\n';
                read_file.close();
                write_file.close();
                return -1;
            }
            // Prevent overflow by upcasting
            line_read.seekg(static_cast<long long int>(vertex_size + spacer), line_read.cur);
            // Ensure vertex 2 is found before end of the current line
            // line_read.seekg(line_read.tellg() + spacer + vertex_size);
            if (line_read.tellg() == -1) {
                std::cerr << "\nFILE ERROR: Line:" << line_count
                          << ", Expected position of vertex 2  or weight was not found (out of "
                             "bounds)!"
                          << '\n';
                std::cerr << "Please ensure each line follows format:\n\t VERTEX1_NAME, "
                             "VERTEX2_NAME, DISTANCE_BETWEEN_VERTICIES"
                          << '\n';
                read_file.close();
                write_file.close();
                return -1;
            }

            size_t next_word = static_cast<size_t>(line_read.tellg());
            std::string vertex_2 = line.substr(next_word, end_2 - next_word);

            // Ensure vertex 2 is found between space after first comma and space before second comma
            long int vertex2_size = static_cast<long int>(vertex_2.size());
            if (vertex2_size <= 0) {
                std::cerr << "\nFILE ERROR: Line: " << line_count
                          << ", Second vertex name was not found after second comma!" << '\n';
                std::cerr << "Please ensure each line follows format:\n\t VERTEX1_NAME, "
                             "VERTEX2_NAME, DISTANCE_BETWEEN_VERTICIES"
                          << '\n';
                read_file.close();
                write_file.close();
                return -1;
            }
            line_read.seekg(static_cast<long long int>(vertex2_size + spacer), line_read.cur);
            // Ensure edge weight between verticies is found before end of current line
            // line_read.seekg(line_read.tellg() + vertex2_size + spacer);
            if (line_read.tellg() == -1) {
                std::cerr << "\nFILE ERROR: Line: " << line_count
                          << ", Expected position of vertex 2 was not found (out of bounds)!"
                          << '\n';
                std::cerr << "Please ensure each line follows format:\n\t VERTEX1_NAME, "
                             "VERTEX2_NAME, DISTANCE_BETWEEN_VERTICIES"
                          << '\n';
                read_file.close();
                write_file.close();
                return -1;
            }

            size_t final_word = static_cast<size_t>(line_read.tellg());
            std::string weight_str = line.substr(final_word, line_length - final_word);
            double weight = strtod(weight_str.c_str(), nullptr);

            // Ensure edge weight contains a numerical value
            if (weight == std::numeric_limits<double>::infinity() || weight <= 0) {
                std::cerr << "\nFILE ERROR: Line: " << line_count
                          << ", Entered value did not contain any non-zero numerical digits"
                          << '\n';
                std::cerr << "Please ensure each line follows format:\n\t VERTEX1_NAME, "
                             "VERTEX2_NAME, DISTANCE_BETWEEN_VERTICIES"
                          << '\n';
                read_file.close();
                write_file.close();
                return -1;
            }

            // Replace whitespace within multi-word verticies with underscores to adhere to dot language format
            std::string vertex1_name = underscore_spaces(vertex);
            std::string vertex2_name = underscore_spaces(vertex_2);
            /*
            If main hashmap does not contain any hashmaps associated with `vertex` key, add this new hashmap (now containing its first edge)
            with its associated key, `vertex`, to main hashmap
            */
            if (!adj_list.contains_key(vertex)) {
                auto hash_tab1 = std::make_unique<soa_hashmap<double>>(
                    static_cast<unsigned int>(vertex_count));
                hash_tab1->add(vertex_2, weight);
                adj_list.add(vertex, std::move(*hash_tab1));

                // Write new vertex in dot language format to `write_name` file
                int write_vertex = write_vertex_node(write_file, vertex1_name);
                if (write_vertex < 0) {
                    std::cerr << "\nFILE ERROR: Line: " << line_count
                              << ", encountered while writing vertex node '" << vertex1_name
                              << "' to file '" << write_name << "' !" << '\n';
                    return -1;
                }
            } else {
                /*
                If hashmap associated with `vertex` key already exists in main hashmap but does not yet contain edge
                with `vertex_2` key, add edge with `vertex_2` to hashmap associated with `vertex` key
                */
                try {
                    if (!adj_list.get_hash_key(vertex).contains_key(vertex_2)) {
                        adj_list.get_hash_key(vertex).add(vertex_2, weight);
                    }
                } catch (std::exception &e) {
                    std::cerr << e.what() << '\n';
                }
            }
            /*
            If main hashmap does not contain any hashmaps associated with `vertex_2` key, add this new hashmap (now containing its first edge)
            with its associated key, `vertex_2`, to main hashmap
            */
            if (!adj_list.contains_key(vertex_2)) {
                auto hash_tab2 = std::make_unique<soa_hashmap<double>>(
                    static_cast<unsigned int>(vertex_count));
                hash_tab2->add(vertex, weight);
                adj_list.add(vertex_2, std::move(*hash_tab2));
                // Write new vertex in dot language format to `write_name` file
                int write_vertex2 = write_vertex_node(write_file, vertex2_name);
                if (write_vertex2 < 0) {
                    std::cerr << "\nWRITE ERROR: Line: " << line_count
                              << ", encountered while writing vertex node '" << vertex2_name
                              << "' to file '" << write_name << "' !" << '\n';
                    return -1;
                }

            } else {
                /*
                If hashmap associated with `vertex_2` key already exists in main hashmap but does not yet contain edge
                with `vertex` key, add edge with `vertex` to hashmap associated with `vertex_2` key
                */
                try {
                    if (!adj_list.get_hash_key(vertex_2).contains_key(vertex)) {
                        adj_list.get_hash_key(vertex_2).add(vertex, weight);
                    }
                } catch (std::exception &e) {
                    std::cerr << e.what() << '\n';
                }
            }
            // Write new edge in dot language format to `write_name` file
            int write_new_edge = write_edge(write_file,
                                            vertex1_name,
                                            vertex2_name,
                                            weight,
                                            graph_type);
            if (write_new_edge < 0) {
                std::cerr << "\nWRITE ERROR encountered while writing the edge between '"
                          << vertex << "' and '" << vertex_2 << "' on '" << write_name << "'!"
                          << '\n';
                return -1;
            }
        }
        write_file.write(close_brace.c_str(), static_cast<long int>(close_brace.size()));
        read_file.close();
        write_file.close();
        // Report error to user if file for reading graph information fails to open correctly
    } else {
        std::cerr << "\nFILE ERROR: Opening file '" << filename << "' failed!" << '\n';
        return -1;
    }
    return 0;
}


int find_shortest_path(const std::string& s_vertex, const std::string& des_vertex, const std::string& graph_filename, const std::string& path_filename, main_hashmap<double>&& adj_list) {
#ifdef NDEBUG
#else
    std::cerr << "ENTIRE LIST OF ALL GRAPH VERTICIES AND THEIR CORRESPONDING ADJACENT VERTICIES:" << '\n';
    std::cerr << adj_list << '\n';
#endif
    // If source vertex is also the destination vertex, simply return the vertex with a distance of 0
    if (s_vertex.compare(des_vertex) == 0) {
        std::string empty_path = s_vertex;
        std::cerr << "============================= SHORTEST PATH RESULTS ====================================\n";
        empty_path.append(" -> ").append(des_vertex).append("\n");
        std::cerr << "The Shortest Path from " << s_vertex << " TO " << des_vertex << " : " << '\n';
        std::cerr << empty_path;
        std::cerr << "\nTOTAL COST/DISTANCE: " << 0 << '\n';
        return 0;
    }
    // Initialize data structures for more efficient processing of graph information using Djkstra's Algorithm
    auto vertex_list = adj_list.get_keys();    // List of all verticies within graph
    auto vertex_count = static_cast<unsigned int>(vertex_list.size());      // User Provided number of unique verticies within graph
    auto visited_vertices = soa_hashmap<double>(vertex_count);      // Hashmap holding key:value pairs corresponding current minimum distance from source vertex to specified vertex key
    auto  mhp = std::make_unique<paired_min_heap<double>>(vertex_count);    // Customized Binary Minimum Heap for holding Minimum Distances
    auto vertex_path = soa_hashmap<std::string>(vertex_count / 2);      // Hashmap of key:value pairs corresponding to last vertex visited in shortest path to each vertex key


    // Prefill visited verticies hashmap key-value pairs of each vertex with a floating infinity distance value
    for (const auto& vertex : vertex_list) {
        visited_vertices.add(vertex, std::numeric_limits<double>::infinity());
    }

    // Set source vertex's distance to 0
    visited_vertices.add(s_vertex, 0.0);
    // Add source vertex to minimum heap
    mhp -> add_node(s_vertex, 0.0);
    std::string popped_vertex;
    double popped_vertex_distance = 0;
    double min_distance_edge = 0;

    // Initiate while loop until all verticies have been visited (minheap will be empty)
    while (!mhp -> is_empty()) {
        // Remove next vertex with smallest distance from minimum heap
        try {
            std::tie(popped_vertex, popped_vertex_distance) = mhp -> remove_min();
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            return -1;
        }
        // Retrieve current distance from source vertex to extracted vertex held in visited verticies
        try {
            min_distance_edge = visited_vertices.get_val(popped_vertex);
        } catch (std::exception& e) {
            std::cerr << e.what() << '\n';
            return -1;
        }
        // If distance value of extracted value is greater than stored value, extract next vertex from minheap
        if (popped_vertex_distance > min_distance_edge) {
            continue;
        }
        // If extracted vertex is destination vertex, shortest path has been found to destination vertex
        if (popped_vertex.compare(des_vertex) == 0) {
            break;
        }

        double weight = 0;
        double di = 0;
        // Iterate through list of all verticies present in graph to identify and access edge weights for each adjacent vertex
        for (auto& vertex : vertex_list) {
            // If vertex is found in list of verticies adjacent to extracted vertex, retrieve its weight
            if (adj_list.get_hash_key(popped_vertex).contains_key(vertex)) {
                gprintf("VISITING VERTEX OF %s with ADJACENT VERTEX %s", popped_vertex.c_str(), vertex.c_str());
                try {
                    weight = adj_list.get_hash_key(popped_vertex).get_val(vertex);
                } catch (std::exception& e) {
                    std::cerr << e.what() << '\n';
                    return -1;
                }
                /**
                 * Check if sum of current distance and edge formed with adjacent vertex is less than current distance associated with vertex in shortest distance list
                 *      distance = distance from source to extracted vertex
                 *      weight = distance between extracted vertex and adjacent vertex
                 *      di = total distance from source vertex to adjacent vertex
                 */
                di = weight + popped_vertex_distance;
                try {
                    // If new edge creates a shorter path to adjacent vertex, update distance associated with adjacent vertex to shortest distance list
                    if (di < visited_vertices.get_val(vertex)) {
                        // If new edge to be updated is the destination vertex, determine whether to update the vertices forming shortest path
                        if (des_vertex.compare(vertex) == 0) {
                            gprintf("CURRENT VERTEX: ");
#ifdef NDEBUG
#else
                            std::cerr << visited_vertices << '\n';
#endif
                            gprintf("UPDATING MINIMUM DISTANCE/PATH FROM SOURCE VERTEX TO DESTINATION VERTEX");
                            gprintf("Current vertex is %s", popped_vertex.c_str());
                            gprintf("Weight of edge between %s and %s is %.2lf", popped_vertex.c_str(), vertex.c_str(), weight);
                            gprintf("Current Distance from Source (%s) is %.2lf", s_vertex.c_str(), popped_vertex_distance);
                            gprintf("Previous minimum distance to destination vertex is %.2lf", visited_vertices.get_val(des_vertex));
                            gprintf("Updated minimum distance from to destination vertex is %.2lf\n", di);
                        }
                        visited_vertices.add(vertex, di);
                        vertex_path.add(vertex, popped_vertex);
                        mhp -> add_node(vertex, di);
                    }
                } catch (std::exception& e) {
                    std::cerr << e.what() << '\n';
                    return -1;
                }
            }
        }
    }

    // If loop is exited and destination vertex has not been visited, no path exists between user-provided source and destination vertex
    try {
        if (visited_vertices.get_val(des_vertex) == std::numeric_limits<double>::infinity()) {
            std::cerr << "ERROR: No path exists between '" << s_vertex << "' and '" << des_vertex << "'!" << '\n';
            std::cerr << "Please ensure your submitted graph file is a connected graph(a path exists between all nodes)!" << '\n';
            return -1;
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

    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return -1;
    }
    // Else, at least one path exists between source and destination vertex, with shortest path value being found
    std::cerr << "============================= SHORTEST PATH RESULTS ====================================\n";
    std::cerr << "The Shortest Path from " << s_vertex << " TO " << des_vertex << " : " << '\n';
    std::unique_ptr<soa_hashmap<double>> path_map = std::make_unique<soa_hashmap<double>>(static_cast<unsigned int>(vertex_count / 2));     // Hashmap holding directed edges as keys and their corresponding weight values
    // Trace backward from destination vertex, visiting each subsequent last vertex visited until source vertex is reached
    std::string new_vertex = des_vertex;
    std::string prev_vertex;
    try {
        prev_vertex = vertex_path.get_val(des_vertex);
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return -1;
    }
    // Fill separate hashmap with edge directionality between verticies in shortest path for shortest path visualization
    std::string edge_name = "";
    edge_name.append(underscore_spaces(prev_vertex));
    edge_name.append(" -> ");
    edge_name.append(underscore_spaces(new_vertex));
    path_map -> add(edge_name, std::move(adj_list.get_val(new_vertex, prev_vertex)));

    auto shortest_path = std::vector<std::string>{};
    shortest_path.emplace( shortest_path.begin(), des_vertex);
    // When trace backward to source vertex is complete, all verticies traveled from source to destination in order will be held in shortest_path
    while (prev_vertex.compare(s_vertex) != 0) {
        new_vertex = prev_vertex;
        shortest_path.emplace(shortest_path.begin(), prev_vertex);
        try {
            prev_vertex = vertex_path.get_val(shortest_path.front());
        } catch (std::exception& e) {
            std::cerr << e.what() << '\n';
            return -1;
        }
        // Add new directed edge in shortest path to hashmap for holding all directed edges for subsequent writing of shortest path image
        std::string next_edge = "";
        next_edge.append(underscore_spaces(prev_vertex));
        next_edge.append(" -> ");
        next_edge.append(underscore_spaces(new_vertex));
        path_map -> add(next_edge, std::move(adj_list.get_val(new_vertex, prev_vertex)));
    }
    shortest_path.emplace(shortest_path.begin(), s_vertex);

    // Print simplified shortest path and its total cost/length to terminal output for user
    print_shortest_path(shortest_path);
    std::cerr << '\n' << "TOTAL COST / DISTANCE: " << visited_vertices.get_val(des_vertex) << "\n\n";
    // Pass hashmap containing directed edges of shortest path to function for writing graph file for visualizing shortest path overlaying entire graph
    int path_output  = 0;
    try {
        path_output = write_shortest_path_overlay(graph_filename, path_filename, shortest_path, std::move(*path_map));
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return -1;
    }

    if (path_output < 0) {
        std::cerr << "ERROR: An error was encountered while overlaying the full graph with the shortest path" << '\n';
        return -1;
    }
    return 0;
}



int find_MST(std::string& source_vertex, const std::string& graph_filename, const std::string& MST_filename, main_hashmap<double>&& adj_list) {
    // Initialize data structures for more efficient processing of graph information using Prim's Algorithm
    auto MST_edges = std::vector<std::pair<std::string, std::string>>{};    // Hashmap holding all edges comprising of MST and their corresponding weight values
    auto MST_traversal = std::vector<std::string>{};    // Array to be filled with all verticies that have already been visited before in traversal of graph
    double MST_sum = 0;     // Total accumulated cost/length of all edges that comprise MST

    auto vertex_list = adj_list.get_keys();        // List of all unique verticies found within entire graph
    auto vertex_count = static_cast<unsigned int>(vertex_list.size());      // User-provided number of unique verticies in entire graph
    std::unique_ptr<paired_min_heap<double>>  mhp = std::make_unique<paired_min_heap<double>>(vertex_count);    // Customized Binary Minimum Heap for holding Minimum Distances

    // Prefill traversal tracking structures with source vertex
    MST_traversal.emplace_back(source_vertex);
    mhp -> add_node(source_vertex, 0);

    std::string vertex;
    double distance = 0;
    std::string min_distance_edge;
    // Traversal continues until all verticies have been visited, at which point the MST will have been established
    while (vertex_list.size() > MST_traversal.size()) {
        // If user-provided graphical information represents an unconnected graph, no MST is possible and minimum heap will be emptied instead
        if (mhp -> is_empty()) {
            std::cerr << "ERROR: Provided Graph is not a connected graph, so no valid Minimum Spanning tree exists!" << '\n';
            std::cerr << "Please ensure the graph is connected (a path exists between all verticies) to generate a valid MST" << '\n';
            return -1;
        }
        // Extract next vertex with miminum edge cost/distance
        try {
            std::tie(vertex, distance) = mhp -> remove_min();
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            return -1;
        }

#ifdef NDEBUG
#else
        gprintf("\nExtracted VERTEX is: %s with a DISTANCE of %.2lf", vertex.c_str(), distance);
        gprintf("\nThe Minimum HEAP currently contains: ");
        std::cerr << *mhp << '\n';
#endif \
        // Find vertex that forms edge with the currently smallest cost/distance with extracted vertex
        if (vertex.compare(source_vertex) == 0) {
            min_distance_edge = source_vertex;
        } else {
            try {
                min_distance_edge = adj_list.get_key_by_value(vertex, distance);
            } catch (std::exception& e) {
                std::cerr << e.what() << '\n';
                return -1;
            }
        }

        bool is_visited = false;
        // Determine whether extracted vertex has already been visited before
        for ( size_t i = 0; i < MST_traversal.size(); i++) {
            if (MST_traversal[i].compare(vertex) == 0) {
                is_visited = true;
                break;
            }

        }
        // If extracted vertex has not been visited before, register as visited, add the edge to MST
        if (!is_visited) {
            MST_traversal.emplace_back(vertex);
            auto new_path = std::pair<std::string, std::string>(min_distance_edge, vertex);
            MST_edges.emplace_back(new_path);
            MST_sum += distance;
        }

        // Gather list of all verticies adjacent to extracted vertex
        std::list<std::string> adjacent_verticies = adj_list.get_hash_key(vertex).get_keys();
        gprintf("\nChecking list of verticies for those not visited yet");

        // Check for any adjacent verticies of extracted vertex that have not been visited yet
        for (auto& next_vertex : adjacent_verticies) {
            bool contains_adjacent = false;
            for (size_t k = 0; k < MST_traversal.size(); k++) {
                if (MST_traversal[k].compare(next_vertex) == 0) {
                    contains_adjacent = true;
                    break;
                }
            }
            double weight;
            /*
            * If any adjacent verticies of extracted vertex have not been visited yet, add them to minimum heap for subsequent traversal
            * and associate their edge weight with the extracted vertex in passing to minimum heap
            */
            if(!contains_adjacent) {
                try {
                    weight = adj_list.get_hash_key(vertex).get_val(next_vertex);
                } catch (std::exception& e) {
                    std::cerr << e.what() << '\n';
                    return -1;
                }
                mhp -> add_node(next_vertex, weight);
                gprintf("\nAdding vertex %s to Minimum HEAP", next_vertex.c_str());
#ifdef NDEBUG
#else
                std::cerr << "HEAP is now: " << *mhp << '\n';
#endif
            }
        }
    }
    // After all verticies have been traversed, MST has been established and all directed edges comprising of MST are now stored within MST_edges

    // Print simplified list of all edges comprising of MST and its total cost/length to terminal output for user
    std::cerr << "============================= MST RESULTS ====================================\n";
    std::cerr << "The Minimum Spanning Tree is formed from the Edges of:" << '\n';
    for (unsigned int i = 0; i < MST_edges.size(); i++) {
        std::string source;
        std::string dest;
        std::tie(source, dest) = MST_edges[i];
        std::cerr << source << " <----> " << dest << '\n';
    }
    std::cerr << '\n';
    std::cerr << "TOTAL COST/DISTANCE: " << MST_sum << '\n';
    std::cerr << '\n';

    // MST_edges can then be passed to function for writing graph file used for generating image overlaying MST onto full graph
    int MST_output = 0;
    try {
        MST_output = write_MST_overlay(graph_filename, MST_filename, MST_edges);
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return -1;
    }

    if (MST_output < 0) {
        std::cerr << "ERROR: An error was encountered while overlaying the full graph with the MST" << '\n';
        return -1;
    }

    return 0;
}