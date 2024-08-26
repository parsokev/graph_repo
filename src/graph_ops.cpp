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
#include <list>

#include "../includes/linked_list.hpp"
#include "../includes/pair_minheap.hpp"
// #include "../includes/master_hashmap.hpp"
#include "../includes/derived_hashmap.hpp"
#include "../includes/graph_ops.hpp"
#include "../includes/gprintf.hpp"


int build_adjacency_list (std::string& filename, std::string& write_name, unsigned int vertex_count, main_hashmap<double>& adj_list) {
    std::fstream read_file;
    std::fstream write_file {write_name, write_file.trunc | write_file.out};
    read_file.open(filename);
    /*
    Try to open user-provided text file of graph edges `filename`, and if successful, try to open
    file to write to in Dot language format `write_name`, or create it if it does not already exist.
    If either fails, notify user and abort program 
    */
    if (read_file.is_open()) {
        if (write_file.is_open()) {
            std::string close_brace = "}";
            std::string graph_type = "undirected";
            std::string title = write_name;
            int header_write = write_graph_header(write_file, graph_type, write_name);
            if (header_write < 0) {
                std::cerr << "ERROR encountered while writing header to graph file '" << write_name << "'!" << '\n';
                return -1;
            }
            
            std::string line;

            // Process each line according to expected format, notify user of any detected deviation
            while (getline(read_file, line)) {
                auto hash_tab1 = soa_hashmap<double>(vertex_count);
                auto hash_tab2 = soa_hashmap<double>(vertex_count);
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
                
                hash_tab1.add(vertex_2, weight);
                hash_tab2.add(vertex, weight);
                /// Replace whitespace within multi-word verticies with underscores to adhere to dot language format
                std::string vertex1_name = underscore_spaces(vertex);
                std::string vertex2_name = underscore_spaces(vertex_2);
                /*
                If main hashmap does not contain any hashmaps associated with `vertex` key, add this new hashmap (now containing its first edge)
                with its associated key, `vertex`, to main hashmap
                */ 
                if (!adj_list.contains_key(vertex)) {
                    adj_list.add_key(vertex, hash_tab1);
                    /// Write new vertex in dot language format to `write_name` file
                    int write_vertex = write_vertex_node(write_file, vertex1_name);
                    if (write_vertex < 0) {
                        std::cerr << "ERROR encountered while writing vertex node '" << vertex1_name <<"' to file '" << write_name << "' !" << '\n';
                        return -1;
                    }
                } else {
                    /*
                    If hashmap associated with `vertex` key already exists in main hashmap but does not yet contain edge
                    with `vertex_2` key, add edge with `vertex_2` to hashmap associated with `vertex` key 
                    */
                    if (!adj_list.get_key_list(vertex).contains_key(vertex_2)) {
                        adj_list.get_key_list(vertex).add(vertex_2, weight);
                    }
                }
                /*
                If main hashmap does not contain any hashmaps associated with `vertex_2` key, add this new hashmap (now containing its first edge)
                with its associated key, `vertex_2`, to main hashmap
                */ 
                if (!adj_list.contains_key(vertex_2)) {
                    adj_list.add_key(vertex_2, hash_tab2);
                    /// Write new vertex in dot language format to `write_name` file
                    int write_vertex2 = write_vertex_node(write_file, vertex2_name);
                    if (write_vertex2 < 0) {
                        std::cerr << " WRITE ERROR encountered while writing vertex node '" << vertex2_name <<"' to file '" << write_name << "' !" << '\n';
                        return -1;
                    }

                } else {
                    /*
                    If hashmap associated with `vertex_2` key already exists in main hashmap but does not yet contain edge
                    with `vertex` key, add edge with `vertex` to hashmap associated with `vertex_2` key 
                    */
                    if (!adj_list.get_key_list(vertex_2).contains_key(vertex)) {
                        adj_list.get_key_list(vertex_2).add(vertex, weight);                           
                    }
                }
                /// Write new edge in dot language format to `write_name` file
                int write_new_edge = write_edge(write_file, vertex1_name, vertex2_name, weight, graph_type);
                if (write_new_edge < 0) {
                    std::cerr << " WRITE ERROR encountered while writing the edge between '" << vertex << "' and '" << vertex_2 << "' on '" << write_name << "'!" << '\n';
                    return -1;
                }
                
            }
            write_file.write(close_brace.c_str(), static_cast<long int>(close_brace.size()));
            read_file.close();
            write_file.close();
        } else {
            std::cerr << "FILE ERROR: Opening file '" << write_name << "' failed!" << '\n';
            return -1;
        }
        
    } else {
        std::cerr << "FILE ERROR: Opening file '" << filename << "' failed!" << '\n';
        return -1; 
    }
    return 0;
}


int apply_djikstras_algorithm(std::string s_vertex, std::string des_vertex, std::string& path_filename, main_hashmap<double>& adj_list) {
    #ifdef NDEBUG
    #else
    std::cerr << "ENTIRE LIST OF ALL GRAPH VERTICIES AND THEIR CORRESPONDING ADJACENT VERTICIES:" << '\n';
    std::cerr << adj_list << '\n';
    #endif

    if (s_vertex.compare(des_vertex) == 0) {
        std::string empty_path = s_vertex;
        empty_path.append(" -> ").append(des_vertex).append("\n");
        std::cout << "The Shortest Path from " << s_vertex << " TO " << des_vertex << " : " << '\n';
        std::cout << empty_path;
        std::cout << "Total Distance: " << 0 << '\n';
        return 0;
    }

    auto vertex_list = adj_list.get_main_keys();
    auto vertex_count = static_cast<unsigned int>(vertex_list.size());

    auto visited_vertices = soa_hashmap<double>(vertex_count);
    auto mhp = paired_min_heap<double>{};

    // auto vertex_path = master_hashmap<std::string>::oa_hashmap(vertex_count);
    auto vertex_path = soa_hashmap<std::string>(vertex_count);

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
    while (!mhp.is_empty()) {
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
                }
            }
        }
    }
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

    std::cout << "The Shortest Path from " << s_vertex << " TO " << des_vertex << " : " << '\n';
    auto path_map = soa_hashmap<double>(vertex_count);
    auto new_vertex = des_vertex;
    auto prev_vertex = vertex_path.get_val(des_vertex);
    std::string edge_name = "";
    edge_name.append(underscore_spaces(prev_vertex));
    edge_name.append(" -> ");
    edge_name.append(underscore_spaces(new_vertex));
    path_map.add(edge_name, adj_list.get_key_val(new_vertex, prev_vertex));
    auto shortest_path = dl_list<std::string>{};
    shortest_path.add_to_front(des_vertex);

    while (prev_vertex.compare(s_vertex) != 0) {
        new_vertex = prev_vertex;
        shortest_path.add_to_front(prev_vertex);
        prev_vertex = vertex_path.get_val(shortest_path.get_front());

        std::string next_edge = "";
        next_edge.append(underscore_spaces(prev_vertex));
        next_edge.append(" -> ");
        next_edge.append(underscore_spaces(new_vertex));
        path_map.add(next_edge, adj_list.get_key_val(new_vertex, prev_vertex));
    }

    shortest_path.add_to_front(s_vertex);
    shortest_path.print_nodes();

    int path_build = build_shortest_graph(path_filename, path_map, shortest_path);
    if (path_build < 0) {
        std::cerr << "There was an error in building shortest path graph!" << '\n';
    }
    std::cout << "Total Distance: " << visited_vertices.get_val(des_vertex) << '\n';
    std::cout << '\n';
    return 0;
}




int apply_prims_algorithm(std::string s_vertex, main_hashmap<double>& adj_list) {
    auto MST_verticies = std::vector<std::tuple<std::string, std::string>>{};
    auto MST_traversal = dl_list<std::string>{};
    // auto MST_traversal = std::vector<std::string>{};
    double MST_sum = 0;
    auto mhp = paired_min_heap<double>{};
    // auto vertex_list = adj_list.get_master_keys();
    auto vertex_list = adj_list.get_main_keys();

    auto source_vertex = s_vertex;
    MST_traversal.add_to_back(source_vertex);
    mhp.add_node(source_vertex, 0);
    std::string vertex;
    double distance = 0;
    std::string current_min_distance;
    while ( vertex_list.size() > MST_traversal.get_size()) {
        if (mhp.is_empty()) {
            std::cerr << "ERROR: Provided Graph is not a connected graph, so no valid Minimum Spanning tree exists!" << '\n';
            std::cerr << "Please ensure the graph is connected (a path exists between all verticies) to generate a valid MST" << '\n';
            return -1;
        }
        std::tie(vertex, distance) = mhp.remove_min();
        auto adjacent_vertex_list = adj_list.get_key_list(vertex);
        #ifdef NDEBUG
        #else
        gprintf("\nExtracted VERTEX is: %s with a DISTANCE of %.2lf", vertex.c_str(), distance);
        gprintf("\nThe Minimum HEAP currently contains: ");
        std::cerr << mhp << '\n';
        gprintf("\nThe list of ADJACENT vertices for %s is: ", vertex.c_str());

        std::cerr << adjacent_vertex_list << '\n';
        #endif

        if (vertex.compare(source_vertex) == 0) {
            current_min_distance = source_vertex;
        } else {
            current_min_distance = adj_list.get_key_by_value(vertex, distance);
        }
        /// If extracted vertex has not been visited before, mark as visited and add edge to MST 
        if (!MST_traversal.contains_node(vertex)) {
            MST_traversal.add_to_back(vertex);
            auto new_path = std::tuple<std::string, std::string>(current_min_distance, vertex);
            MST_verticies.push_back(new_path);
            MST_sum += distance;
        }

        /// If any verticies adjacent to extracted vertex
        auto adjacent_verticies = adjacent_vertex_list.get_keys();
        #ifdef NDEBUG
        #else
        gprintf("\nChecking list of verticies for those not visited yet");
        #endif
        for (unsigned int j = 0; j < adjacent_verticies.size(); j++) {
            if (!MST_traversal.contains_node(adjacent_verticies[j])) {
                auto weight = adjacent_vertex_list.get_val(adjacent_verticies[j]);
                mhp.add_node(adjacent_verticies[j], weight);
                #ifdef NDEBUG
                #else
                gprintf("\nAdding vertex %s to Minimum HEAP", adjacent_verticies[j].c_str());
                std::cerr << "HEAP is now: " << mhp << '\n';
                #endif
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
    std::cout << '\n';
    std::cout << "With a Total Distance of " << MST_sum << '\n';
    std::cout << '\n';
    return 0;
}

bool is_connected (main_hashmap<double>& adj_list, std::string& source_vertex) {

    auto vertex_list = adj_list.get_main_keys();
    auto stack_vert = dl_list<std::string>{};
    auto visited_verticies = dl_list<std::string>{};
    bool is_connected = false;
    stack_vert.add_to_back(source_vertex);
    while (stack_vert.get_size() > 0) {
        std::string next_vertex = stack_vert.pop();
        auto adj_verticies = adj_list.get_key_list(next_vertex).get_keys();
        if (!visited_verticies.contains_node(next_vertex)) {
            visited_verticies.add_to_back(next_vertex);
            for (size_t i = 0; i < adj_verticies.size(); i++) {
                stack_vert.add_to_back(adj_verticies[i]);
            }
        }
    }
    if (visited_verticies.get_size() == static_cast<unsigned int>(vertex_list.size())) {
        is_connected = true;
    }
    return is_connected;
}

int build_shortest_graph(std::string& dot_file, soa_hashmap<double>& path_map, dl_list<std::string>& path) {
    std::fstream read_file {dot_file, read_file.trunc | read_file.out };
    std::string graph_type = "directed";
    std::string s_vertex = path.get_front();
    std::string d_vertex = path.get_back(); 
    std::string title = "Shortest Path from ";
    title.append(s_vertex).append(" TO ").append(d_vertex);
    if (read_file.is_open()) {
        auto path_verticies = std::vector<std::string>{};
        std::string close_brace = "}";
        int write_d_header = write_graph_header(read_file, graph_type, title);
        if (write_d_header < 0) {
            std::cerr << "WRITE ERROR encountered while writing header to '" << dot_file << "' file for shortest path" << '\n';
            return -1;
        }

        for (size_t m = 0; m < path.get_size(); m++) {
            auto path_vertex = underscore_spaces(path[m]);
            int vertex_write = write_vertex_node(read_file, path_vertex);
            if (vertex_write < 0) {
                std::cerr << "WRITE ERROR encountered while writing information for vertex '" << path[m] << "' to '" << dot_file << "'!" << '\n';
                return -1;
            }
        }
        auto path_edges = path_map.get_keys();
        for (size_t n = 0; n < path_edges.size(); n++) {
            auto edge_weight = path_map.get_val(path_edges[n]);
            if constexpr (std::is_same_v<decltype(edge_weight), std::string>) {
                std::cerr << "Weight value must be a numerical value!" << '\n';
                return -1;
            }
            std::string weight_string = std::to_string(edge_weight);
            weight_string.erase(weight_string.find_last_not_of("0") + 2, std::string::npos);

            std::string edge_label_size = "50";
            std::string edge_width = "3";
            std::string edge_color = "darkorange1";
            std::string edge_name = path_edges[n];
            std::string edge_line = edge_name;
            edge_line.append(" [label=\"").append(weight_string).append("\" weight=").append(edge_label_size);
            edge_line.append(" penwidth=").append(edge_width).append(" color=\"").append(edge_color).append("\" tooltip=\"");
            edge_line.append(edge_name).append("\" labeltooltip=\"").append(edge_name).append("\"]\n");
            read_file.write(edge_line.c_str(), static_cast<long int>(edge_line.size()));
        }
    
        read_file.write(close_brace.c_str(), static_cast<long int>(close_brace.size()));
        read_file.close();
    } else {
        std::cerr << "FILE ERROR: Opening file '" << dot_file << "' failed!" << '\n';
        return -1; 
    }
    return 0;
}

std::string underscore_spaces(const std::string& target_string) {
    auto underscore_string = target_string;
    auto find_space = underscore_string.find(" ");

    if (find_space != underscore_string.npos) {
        std::string under_score = "_";
        underscore_string.replace(find_space, under_score.size(), under_score.c_str());
    }
    return underscore_string;
}

int write_graph_header(std::fstream& graph_file, std::string& graph_type, std::string& title) {
    std::string g_type = "";
    if (graph_type.compare("undirected") == 0) {
        g_type = "strict graph";
    } else if (graph_type.compare("directed") == 0) {
        g_type = "strict digraph";
    } else {
        std::cerr << "graph type of '" << graph_type << "' is not an acceptable type" << '\n';
        std::cerr << "Please use either 'directed' or 'undirected' for argument 'graph_type";
        return -1;
    }
    std::string header = g_type;
    std::string main_graph_name = " main_graph ";
    std::string main_graph_font_name = "DejaVu Sans,Arial,sans-serif";
    // std::string main_graph_size = "5";
    std::string graph_ratio_setting = "auto";
    std::string node_font_name = "Impact,Arial,sans-serif";
    std::string edge_font_name = "Comic Sans,Arial,sans-serif";
    std::string node_style = "filled";
    std::string landscape_enabled = "false";

    // std::string edge_style = "filled";
    // std::string edge_color_scheme = "darkolivegreen";
    // std::string node_color_scheme = "darkgoldenrod";
    std::string node_fill_color = "darkolivegreen2";
    // std::string edge_fill_color = "darkgoldenrod1";
    std::string cluster_name = "Full Graph";
    std::string cluster_shape = "box";
    std::string cluster_fontsize = "14";
    std::string cluster_label = title;
    std::string cluster_tooltip = "All Nodes";
    // header.append(" main_graph {\nfontname=\"Helvetica,Arial,sans-serif\"\nnode [fontname=\"Helvetica,Arial,sans-serif\"]\nedge [fontname=\"Helvetica,Arial,sans-serif\"]\nnode [style=filled fillcolor=\"#f8f8f8\"]\n");
    header.append(main_graph_name).append("{\nfontname=\"").append(main_graph_font_name).append("\"\nnode [fontname=\"").append(node_font_name).append("\"]\nedge [fontname=\"");
    header.append(edge_font_name).append("\"]\nnode [style=").append(node_style).append(" fillcolor=\"").append(node_fill_color).append("\"]\n");
    header.append("ratio=").append(graph_ratio_setting).append("\nlandscape=").append(landscape_enabled).append("\n");
    // header.append("ratio=").append(graph_ratio_setting).append("\nlandscape=").append(landscape_enabled).append("\nsize=").append(main_graph_size).append("\n");
    std::string sub_header = "subgraph cluster {\"";
    sub_header.append(cluster_name).append("\" [shape=").append(cluster_shape).append(" fontsize=").append(cluster_fontsize).append(" label=\"");
    sub_header.append(cluster_label).append("\" tooltip=\"").append(cluster_tooltip).append("\"] }\n");
    // std::string sub_header = "subgraph cluster {\"Full Graph\" [shape=box fontsize=16 label=\"Main Graph\" tooltip=\"All Nodes\"] }\n";
    graph_file.write(header.c_str(), static_cast<long int>(header.size()));
    graph_file.write(sub_header.c_str(), static_cast<long int>(sub_header.size()));
    if (graph_file.bad()) {
        return -1;
    }
    return 0;
}

int write_vertex_node (std::fstream& graph_file, std::string& vertex_name) {
    std::string node_line = vertex_name;
    std::string node_shape = "box3d";
    std::string node_border_color = "darkgreen";
    std::string node_inside_color = "darkolivegreen2";
    std::string node_color3 = "darkskyblue";
    std::string node_font_size = "12";
    node_line.append(" [").append("label=\"").append(vertex_name).append("\" id=\"");
    node_line.append(vertex_name).append("\" fontsize=").append(node_font_size).append(" shape=");
    node_line.append(node_shape).append(" tooltip=\"").append(vertex_name).append("\" color=\"");
    node_line.append(node_border_color).append("\"fillcolor=\"").append(node_inside_color).append("\"]\n");
    // node_line.append("\" fillcolor=\"");
    // node_line.append(node_fill_color);
    // node_line.append("\"]\n");
    // std::string node_color = "#b20400";
    // std::string node_fill_color = "#edd6d5";

    // node_line.append(" [");
    // node_line.append("label=\"");
    // node_line.append(vertex_name);
    // node_line.append("\" id=\"");
    // node_line.append(vertex_name);
    // node_line.append("\" fontsize=");
    // node_line.append(node_font_size);
    // node_line.append(" shape=");
    // node_line.append(node_shape);
    // node_line.append(" tooltip=\"");
    // node_line.append(vertex_name);
    // node_line.append("\" color=\"");
    // // node_line.append("\" color=\"");
    // node_line.append(node_color1);
    // node_line.append("\"fillcolor=\"");
    // node_line.append(node_color2);
    // node_line.append("\"]\n");
    // node_line.append("\" fillcolor=\"");
    // node_line.append(node_fill_color);
    // node_line.append("\"]\n");
    graph_file.write(node_line.c_str(), static_cast<long int>(node_line.size()));
    if (graph_file.bad()) {
        return -1;
    }
    return 0;
}

int write_edge(std::fstream& graph_file, std::string& vertex1_name, std::string& vertex2_name, double& weight, std::string& graph_type) {
        std::string weight_string = std::to_string(weight);

        weight_string.erase(weight_string.find_last_not_of("0") + 2, std::string::npos);

        std::string edge_char = "";
        if (graph_type.compare("undirected") == 0) {
            edge_char = " -- ";
        } else if (graph_type.compare("directed") == 0) {
            edge_char = " -> ";
        } else {
            std::cerr << "graph type of '" << graph_type << "' is not an acceptable type" << '\n';
            std::cerr << "Please use either 'directed' or 'undirected' for argument 'graph_type";
            return -1;
        }
        std::string edge_label_size = "60";
        std::string edge_width = "3";
        std::string edge_color = "darkgoldenrod2";
        // std::string edge_color = "#b20300";
        std::string edge_name = vertex1_name;
        edge_name.append(edge_char).append(vertex2_name);
        std::string edge_line = edge_name;
        edge_line.append(" [label=\"").append(weight_string).append("\" weight=").append(edge_label_size);
        edge_line.append(" penwidth=").append(edge_width).append(" color=\"").append(edge_color);
        edge_line.append("\" tooltip=\"").append(edge_name).append("\" labeltooltip=\"").append(edge_name).append("\"]\n");
        graph_file.write(edge_line.c_str(), static_cast<long int>(edge_line.size()));
        if (graph_file.bad()) {
            return -1;
        }
        return 0;
}

// int build_dot_graph(std::string& dot_file, unsigned int vertex_count, main_hashmap<double>& graph_rep) {
//     std::fstream read_file {dot_file, read_file.trunc | read_file.out };
//     if (read_file.is_open()) {
//         auto vertex_list = graph_rep.get_main_keys();
//         std::string edge_char = " -- ";
//         std::string new_line = "\n";
//         std::string close_brace = "}";
//         std::string header = "strict graph main_graph {\nfontname=\"Helvetica,Arial,sans-serif\"\nnode [fontname=\"Helvetica,Arial,sans-serif\"]\nedge [fontname=\"Helvetica,Arial,sans-serif\"]\nnode [style=filled fillcolor=\"#f8f8f8\"]\n";
//         std::string sub_header = "subgraph cluster {\"Full Graph\" [shape=box fontsize=16 label=\"Main Graph\" tooltip=\"All Nodes\"] }\n";
//         read_file.write(header.c_str(), static_cast<long int>(header.size()));
//         read_file.write(sub_header.c_str(), static_cast<long int>(sub_header.size()));

//         for (size_t k = 0; k < vertex_list.size(); k++) {
//             auto vertex_name = underscore_spaces(vertex_list[k]);
//             // auto find_space = vertex_name.find(" ");

//             // std::string under_score = "_";
//             // if (find_space != vertex_name.npos) {
//             //     vertex_name.replace(find_space, under_score.size(), under_score.c_str());
//             // }
//             std::string node_line = vertex_name;
//             std::string node_shape = "box";
//             std::string node_color = "#b20400";
//             std::string node_fill_color = "#edd6d5";
//             node_line.append(" [");
//             node_line.append("label=\"");
//             node_line.append(vertex_name);
//             node_line.append("\" id=\"");
//             node_line.append(vertex_name);
//             node_line.append("\" fontsize=10 shape=");
//             node_line.append(node_shape);
//             node_line.append(" tooltip=\"");
//             node_line.append(vertex_name);
//             node_line.append("\" color=\"");
//             node_line.append(node_color);
//             node_line.append("\" fillcolor=\"");
//             node_line.append(node_fill_color);
//             node_line.append("\"]\n");
//             read_file.write(node_line.c_str(), static_cast<long int>(node_line.size()));
//         }
//         auto edge_pairs = soa_hashmap<std::string>(vertex_count);
//         for (size_t i = 0; i < vertex_list.size(); i++) {
//             auto hash = graph_rep.get_key_list(vertex_list[i]);
//             auto hash_keys = hash.get_keys();
//             auto vertex_name = underscore_spaces(vertex_list[i]);
//             // auto find_space = vertex_name.find(" ");
//             // std::string under_score = "_";
//             // if (find_space != vertex_name.npos) {
//             //     vertex_name.replace(find_space, under_score.size(), under_score.c_str());
//             // }

//             for (size_t j = 0; j < hash_keys.size(); j++) {

//                 auto adj_vertex = underscore_spaces(hash_keys[j]);
//                 // auto get_space = adj_vertex.find(" ");
//                 // if (get_space != adj_vertex.npos) {
//                 //     adj_vertex.replace(get_space, under_score.size(), under_score.c_str());
//                 // }

//                 auto edge_weight = hash.get_val(hash_keys[j]);
//                 if constexpr (std::is_same_v<decltype(edge_weight), std::string>) {
//                     std::cerr << "Weight value must be a numerical value!" << '\n';
//                     return -1;
//                 }
//                 std::string weight_string = std::to_string(edge_weight);
//                 // std::snprintf(edge.data(), edge.size() - 4, "%.2f", edge_weight);
//                 weight_string.erase(weight_string.find_last_not_of("0") + 1, std::string::npos);
//                 // std::to_chars(edge.data(), edge.size(), hash.get_val(hash_keys[j]), std::chars_format::fixed, 2);
//                 // std::snprintf(edge.data(), edge.size(), "%.2lf", edge_weight);

//                 std::string edge_label_size = "50";
//                 std::string edge_width = "3";
//                 std::string edge_color = "#b20300";
//                 std::string edge_name = vertex_name;
//                 edge_name.append(edge_char);
//                 edge_name.append(adj_vertex);
//                 std::string edge_line = edge_name;
//                 edge_line.append(" [label=\"");
//                 // edge_line.append(std::sprintf( , "%.2lf",edge_weight));
//                 edge_line.append(weight_string);
//                 // edge_line.append(std::to_string(edge_weight));
//                 edge_line.append("\" weight=");
//                 edge_line.append(edge_label_size);
//                 edge_line.append(" penwidth=");
//                 edge_line.append(edge_width);
//                 edge_line.append(" color=\"");
//                 edge_line.append(edge_color);
//                 edge_line.append("\" tooltip=\"");
//                 edge_line.append(edge_name);
//                 edge_line.append("\" labeltooltip=\"");
//                 edge_line.append(edge_name);
//                 edge_line.append("\"]");
//                 edge_line.append(new_line);
//                 read_file.write(edge_line.c_str(), static_cast<long int>(edge_line.size()));
//             }
//         }    
//         read_file.write(close_brace.c_str(), static_cast<long int>(close_brace.size()));
//         read_file.close();
//     } else {
//         std::cerr << "FILE ERROR: Opening file '" << dot_file << "' failed!" << '\n';
//         return -1; 
//     }
//     return 0;
// }