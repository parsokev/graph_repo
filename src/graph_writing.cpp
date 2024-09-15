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
#include <stdlib.h>
#include <sys/wait.h>
#include <memory>

#include "../includes/pair_minheap.hpp"
#include "../includes/derived_hashmap.hpp"
#include "../includes/graph_processing.hpp"
#include "../includes/graph_writing.hpp"
#include "../includes/gprintf.hpp"


/**
 * Modifies the line containing the graph title information in dot language format, `line`,
 * to display the matching source and destination vertex names in graph visualization of shortest path
 * extracted from `path_list`
 * @param path_list Vector-type container holding all verticies within shortest path in order of traversal
 * @param line Line matching dot language format for holding the graph title information
 */
static void write_path_title(std::vector<std::string>& path_list, std::string& line) {
    // std::cout << "first edge of path_map is " << path_map.get_val("Total Distance") << '\n';
    auto start_title_pos = line.find("label=") + 7;
    auto end_title_pos = line.find('"', start_title_pos);
    std::string path_title = "Shortest Path FROM ";
    path_title.append(path_list.front()).append(" TO ").append(path_list.back());
    size_t p = 0;
    // Directly Replace as many characters as possible of previous title with those of designated title for shortest path image
    for (; p < end_title_pos - start_title_pos && p < path_title.size(); p++) {
        line[start_title_pos + p] = path_title[p];
    }
    // Remove any Remaining characters if name of previous title is longer than name of new title
    if (path_title.size() < end_title_pos - start_title_pos) {
            line.erase(line.begin() + static_cast<long int>(start_title_pos) + static_cast<long int>(p), line.begin() + static_cast<long int>(end_title_pos));
    } else {
    // Insert any remaining characters of name of new title if it is longer than name of previous title
        for (; p < path_title.size(); p++) {
            line.insert(line.begin() + static_cast<long int>(start_title_pos) + static_cast<long int>(p), path_title[p]);
        }
    }
    return;
}

/**
 * Modifies line(s) defining a vertex node found within the shortest path in dot language format, `line`,
 * to distinguish vertex nodes found in the shortest path in the corresponding graph visualization
 * @param line Line matching dot language format for holding node information for a vertex found in the shortest path
 * @param find_right_bracket Last index position in `line`, which is used for position referencing in insertion/removal operations
 */
static void write_path_node(std::string& line, size_t& find_right_bracket) {
    // Set text color of vertex nodes found within shortest path to different color than default text 
    std::string node_label = " fontcolor=\"";
    std::string node_text_color = "darkorange1";
    std::string node_fill_color = "darkslategrey";
    node_label.append(node_text_color).append("\" ");
    line.insert(find_right_bracket, node_label);

    // Check if there is a preset fill color for vertex nodes found within shortest path
    auto find_fill_label = line.find("fillcolor=");
    if (find_fill_label != line.npos) {
        // If a preset fillcolor is found, change fill color to a new chosen color to highlight vertex nodes within shortest path
        auto fcolor_start_pos = find_fill_label + static_cast<size_t>(11);
        auto fcolor_end_pos = line.find('"', fcolor_start_pos);
        size_t n = 0;
        // Directly replace as many characters as possible of previous color used as fillcolor with those of new color for shortest path image
        for (; n < fcolor_end_pos - fcolor_start_pos && n < node_fill_color.size(); n++) {
            line[fcolor_start_pos + n] = node_fill_color[n];
        }
        // Remove any remaining characters if name of previous fillcolor is longer than name of new color
        if (node_fill_color.size() < fcolor_end_pos - fcolor_start_pos) {
                line.erase(line.begin() + static_cast<long int>(fcolor_start_pos) + static_cast<long int>(n), line.begin() + static_cast<long int>(fcolor_end_pos));
        } else {
        // Insert any remaining characters of name of new color if it is longer than name of previous fillcolor
            for (; n < node_fill_color.size(); n++) {
                line.insert(line.begin() + static_cast<long int>(fcolor_start_pos) + static_cast<long int>(n), node_fill_color[n]);
            }
        }
    } else {
        // If no preset fillcolor is detected, add a new fillcolor setting for vertex nodes in shortest path
        std::string fill_line = " fillcolor=\"";
        fill_line.append(node_fill_color).append("\" ");
        line.insert(find_right_bracket, fill_line);
    }
    return;
}


/**
 * Modifies line containing edge information in dot language format, `line`,
 * to distinguish edges that form the shortest path in graphical visualization of the shortest path 
 * extracted from `path_edges`, using the ending index position of the first vertex, `first_sapce` for referencing
 * @param first_space Index position within `line` at which the end of the first vertex name within edge depicted by `line` is located
 * @param path_edges Vector-type container holding all edges in proper directionality that form shortest path, in dot language format
 * @param line Line matching dot language format for holding a single edge's information and features
 */
static void write_path_edge(size_t& first_space, std::vector<std::string>& path_edges, std::string& line) {
    std::string arrow_label = "arrowsize=0 ";   // Edges not part of shortest path do not have arrows
    std::string color_label = "darkcyan";       // Edges that are part of shortest path
    // Get Previous Color Size and Position within Line
    auto start_color_pos = line.find(" color=") + 8;
    auto end_color_pos = line.find('"', start_color_pos);
    auto prev_color_size = end_color_pos - start_color_pos;

    // Update Actual Line used for Extracting Node Information To Directed Edge Format
    line[line.find("--") + 1] = '>';
    bool in_shortest_path = false;   // Bool value for determining if extracted node is in shortest path
    auto second_space = line.find(" ", first_space); // Position of whitespace between second vertex name and arrow character ('>')
    auto third_space = line.find('[', second_space);
    std::string vertex1 = line.substr(0, first_space); // Substring containing first vertex name
    std::string vertex2 = line.substr(first_space + static_cast<size_t>(4), third_space - static_cast<size_t>(5) - second_space); // Substring containing second vertex name

    std::string straight_edge = vertex1;
    straight_edge.append(" -> ").append(vertex2);
    std::string reverse_edge = vertex2;
    reverse_edge.append(" -> ").append(vertex1);
    // Loop through List of Edges found in Shortest Path and Compare them to Substring containing Directed Edge
    for (const auto& edge : path_edges) {
        bool straight_match = edge.compare(straight_edge) == 0;
        bool reverse_match = edge.compare(reverse_edge) == 0;
        // Check each directed edge in shortest path for matches in alternate ordering of directionality
        if (straight_match || reverse_match) {
            // If matching edge has verticies in reverse order, rewrite line to depict correct directionality
            if (reverse_match) {
                for (size_t m = 0; m < reverse_edge.size(); m++) {
                    line[m] = reverse_edge[m];
                }
            }
            in_shortest_path = true;
            size_t j = 0;
            // Directly Replace as many characters as possible of preset color to designated color for shortest path edges
            for (; j < color_label.size() && j < prev_color_size; j++) {
                line[start_color_pos + j] = color_label[j];
            }
            // Remove any Remaining characters if name of previous color is longer than name of new color
            if (color_label.size() < prev_color_size) {
                line.erase(line.begin() + static_cast<long int>(start_color_pos) + static_cast<long int>(j), line.begin() + static_cast<long int>(end_color_pos));
            // Insert any remaining characters if name of new color is longer than name of previous color
            } else {
                for (; j < color_label.size(); j++) {
                    line.insert(line.begin() + static_cast<long int>(start_color_pos) + static_cast<long int>(j), color_label[j]);
                }
            }
        }
    }
    // If line defines an edge that is not part of the shortest path, remove arrow head feature and retain preset color
    if (!in_shortest_path) {
        line.insert(line.find('[') + 1, arrow_label);
    // If line defines an edge that is part of shortest path, change the text color of the weight label
    } else {
        auto find_right_bracket = line.rfind(']');
        std::string text_label = " fontcolor=\"";
        std::string text_color = "darkmagenta";
        text_label.append(text_color).append("\" ");
        line.insert(find_right_bracket, text_label);
    }
    return;
}


/**
 * Modifies the line containing the graph title information in dot language format, `line`,
 * to identify the graph visualization as depicting the Minimum Spanning Tree
 * @param line Line matching dot language format for holding the graph title information
 */
static void write_MST_title( std::string& line) {
    auto start_title_pos = line.find("label=") + 7;
    auto end_title_pos = line.find('"', start_title_pos);
    std::string path_title = "Minimum Spanning Tree";
    size_t p = 0;
    // Directly Replace as many characters as possible of previous title with those of designated title for shortest path image
    for (; p < end_title_pos - start_title_pos && p < path_title.size(); p++) {
        line[start_title_pos + p] = path_title[p];
    }
    // Remove any Remaining characters if name of previous title is longer than name of new title
    if (path_title.size() < end_title_pos - start_title_pos) {
            line.erase(line.begin() + static_cast<long int>(start_title_pos) + static_cast<long int>(p), line.begin() + static_cast<long int>(end_title_pos));
    } else {
    // Insert any remaining characters of name of new title if it is longer than name of previous title
        for (; p < path_title.size(); p++) {
            line.insert(line.begin() + static_cast<long int>(start_title_pos) + static_cast<long int>(p), path_title[p]);
        }
    }
    return;
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


int write_graph_header(std::fstream& graph_file, const std::string& graph_type, std::string& title) {
    // Write Graph File format according to provided graph type
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

    /// Provide Predefined Variables for Quick Manipulation of Graph Features
    std::string header = g_type;
    std::string main_graph_name = " main_graph ";
    std::string main_graph_font_name = "DejaVu Sans,Arial,sans-serif";
    std::string graph_ratio_setting = "auto";
    std::string node_font_name = "Impact,Arial,sans-serif";
    std::string edge_font_name = "Comic Sans,Arial,sans-serif";
    std::string node_style = "filled";
    std::string landscape_enabled = "false";
    std::string node_fill_color = "darkolivegreen2";
    std::string cluster_name = "Full Graph";
    std::string cluster_shape = "box";
    std::string cluster_fontsize = "14";
    std::string cluster_label = title;
    std::string cluster_tooltip = "All Nodes";
    /// Main Graph Features
    header.append(main_graph_name).append("{\nfontname=\"").append(main_graph_font_name).append("\"\nnode [fontname=\"").append(node_font_name).append("\"]\nedge [fontname=\"");
    header.append(edge_font_name).append("\"]\nnode [style=").append(node_style).append(" fillcolor=\"").append(node_fill_color).append("\"]\n");
    header.append("ratio=").append(graph_ratio_setting).append("\nlandscape=").append(landscape_enabled).append("\n");
    /// SubGraph Features
    std::string sub_header = "subgraph cluster {\"";
    sub_header.append(cluster_name).append("\" [shape=").append(cluster_shape).append(" fontsize=").append(cluster_fontsize).append(" label=\"");
    sub_header.append(cluster_label).append("\" tooltip=\"").append(cluster_tooltip).append("\"] }\n");

    graph_file.write(header.c_str(), static_cast<long int>(header.size()));
    graph_file.write(sub_header.c_str(), static_cast<long int>(sub_header.size()));
    /// Check Failbit for logged errors during writing operation
    if (graph_file.bad()) {
        std::cerr << "Failbit set in writing operation" << '\n';
        return -1;
    }
    return 0;
}


int write_vertex_node (std::fstream& graph_file, const std::string& vertex_name) {
    /// Provide Predefined Variables for Quick Manipulation of Individual Node Features
    std::string node_line = vertex_name;
    std::string node_shape = "box3d";
    std::string node_border_color = "darkgreen";
    std::string node_inside_color = "darkolivegreen2";
    std::string node_font_size = "12";
    /// Specific Node Features
    node_line.append(" [").append("label=\"").append(vertex_name).append("\" id=\"");
    node_line.append(vertex_name).append("\" fontsize=").append(node_font_size).append(" shape=");
    node_line.append(node_shape).append(" tooltip=\"").append(vertex_name).append("\" color=\"");
    node_line.append(node_border_color).append("\" fillcolor=\"").append(node_inside_color).append("\"]\n");

    graph_file.write(node_line.c_str(), static_cast<long int>(node_line.size()));
    /// Check Failbit for logged errors during writing operation
    if (graph_file.bad()) {
        std::cerr << "Failbit set in writing operation" << '\n';
        return -1;
    }
    return 0;
}


int write_edge(std::fstream& graph_file, const std::string& vertex1_name, const std::string& vertex2_name, double& weight, const std::string& graph_type) {
        // Convert provided edge weight to string for writing to graph file
        std::string weight_string = std::to_string(weight); 
        // Remove excessive trailing zeros for edge label values
        weight_string.erase(weight_string.find_last_not_of("0") + 2, std::string::npos);
        // Write edges in format matching provided graph type
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
        /// Provide Predefined Variables for Quick Manipulation of Individual Edge Features
        std::string edge_label_size = "60";
        std::string edge_width = "3";
        std::string edge_color = "darkgoldenrod2";
        std::string edge_name = vertex1_name;
        /// Specific Edge Features
        edge_name.append(edge_char).append(vertex2_name);
        std::string edge_line = edge_name;
        edge_line.append(" [label=\"").append(weight_string).append("\" weight=").append(edge_label_size);
        edge_line.append(" penwidth=").append(edge_width).append(" color=\"").append(edge_color);
        edge_line.append("\" tooltip=\"").append(edge_name).append("\" labeltooltip=\"").append(edge_name).append("\"]\n");
        graph_file.write(edge_line.c_str(), static_cast<long int>(edge_line.size()));
        /// Check Failbit for logged errors during writing operation
        if (graph_file.bad()) {
            return -1;
        }
        return 0;
}


int write_shortest_path_overlay(const std::string& graph_filename, const std::string& path_filename, std::vector<std::string>& path_list, soa_hashmap<double>&& path_map) {
    auto path_edges = path_map.get_keys();
    std::fstream write_file {path_filename, write_file.trunc | write_file.out};
    std::fstream read_file {graph_filename, read_file.in};
    if (read_file.is_open()) {
        if (write_file.is_open()) {
            std::string line;
            // Locate the leading 'g' of expected "graph" word in first line to edit for denoting a directed graph
            getline(read_file, line);
            auto get_first_g = line.find('g');  
            if (get_first_g == line.npos) {
                std::cerr << "\nERROR: expected at least once occurence in 'g' in first line of '" << graph_filename << "' file\n";
                read_file.close();
                write_file.close();
                return -1;
            }
            // Write file format to declare directed graph
            line.insert(get_first_g, "di").append("\n");
            write_file.write(line.c_str(), static_cast<long int>(line.size()));

            while (getline(read_file, line)) {
                // Initialize parameters to track and locate key characters that define information type of each line
                auto begin = write_file.tellg();    // Capture starting file pointer position
                auto find_left_bracket = line.find('['); // Position of left bracket character ('[')
                auto find_double_dash = line.find("--"); // Position of existing "--" substring if present
                auto find_first_space = line.find(" ");  // Position immediately following name of first vertex for lines representing vertex nodes and edges
                auto find_right_bracket = line.find("]");   // Position of last expected character in current line ("]");
                // Call function to edit title of shortest path image to match user-requested information
                auto find_cluster_bracket = line.find('{');
                if (find_cluster_bracket != line.npos) {
                    write_path_title(path_list, line);
                }
                bool has_double_dash = find_double_dash != line.npos;     // True if current line contains "--" substring
                // If line depicts an undirected edge, call function to parse the line and alter its appearance, if it is found within the shortest path
                if (find_left_bracket != line.npos && has_double_dash) {
                    write_path_edge(find_first_space, path_edges, line);
                // If the line does not contain a double dash, it depicts an individual node/vertex instead
                } else {
                    // std::string node_label = " fontcolor=\"";
                    // std::string node_color = "firebrick";
                    // node_label.append(node_color).append("\" ");
                    // std::string node_slice = line.substr(0, find_first_space);
                    std::string node_slice = line.substr(0, find_first_space);
                    // Replace single underscore with a space if found within the vertex extracted from the substring
                    auto find_underscore = node_slice.find("_");
                    if (find_underscore != node_slice.npos) {
                        node_slice.replace(node_slice.begin() + static_cast<long int>(find_underscore), node_slice.begin() + static_cast<long int>(find_underscore + 1), " ");
                    }
                    // Change the text color of extracted vertex if it is within the shortest path
                    for (const auto& vertex : path_list) {
                        if (node_slice.compare(vertex) == 0) {
                            write_path_node(line, find_right_bracket);
                            // auto find_fill_label = line.find("fillcolor=");
                            // std::string node_fill_color = "darkslategrey";
                            // std::string node_label = " fontcolor=\"";
                            // std::string node_text_color = "firebrick";
                            // node_label.append(node_text_color).append("\" ");
                            
                            // line.insert(find_left_bracket + 1, node_label);
                            // line.insert(find_fill_label + 12, node_fill_color);
                        }
                    }
                }
                // Write each processed line that was intially read from read_file and write it into write_file
                line.append("\n");
                write_file.write(line.c_str(), static_cast<long int>(line.size()));
            }
        // Report failure to open provided file writing graphical information for shortest path  
        } else {
            std::cerr << "\nERROR: Failed to open file '" << path_filename << "' for writing!" << '\n';
            read_file.close();
            return -1;
        }
        // Check failbit for errors encountered during reading
        if (read_file.fail()) {
            // Since file pointers will be out of sync due to insertions into write file, ignore if failbit is for eof
            if (read_file.eof()) {
                read_file.close();
                write_file.close();
                return 0;
            }
            std::cerr << "\nERROR: Failbit indicates an error occurred while reading\n";
            read_file.close();
            write_file.close();
            return -1;
        }
        // Check failbit for errors encountered during writing
        if (write_file.fail()) {
            std::cerr << "\nERROR: Failbit indicates an error occurrred while writing!\n";
            read_file.close();
            write_file.close();
            return -1;
        }
        // Close files and return with no error indication if failbits are not set
        read_file.close();
        write_file.close();
    // Report failure to open file used for parsing and copying graphical information of processed graph
    } else {
        std::cerr << "\nFailed to open file '" << graph_filename << "' for reading!" << '\n';
        return EXIT_FAILURE;
    }
    return 0;
}


int write_MST_overlay(const std::string& graph_filename, const std::string& MST_filename, std::vector<std::pair<std::string, std::string>>& MST_edges) {
    std::fstream write_file {MST_filename, write_file.trunc | write_file.out};
    std::fstream read_file {graph_filename, read_file.in};
    if (read_file.is_open()) {
        if (write_file.is_open()) {
            std::string line;
            while (getline(read_file, line)) {
                auto find_left_bracket = line.find('[');   // Position of left bracket character ('[')
                auto find_double_dash = line.find("--");  // Position of first dash of double dash ("--")
                auto has_left_bracket = find_left_bracket != line.npos; // True if left bracket character is found in current line  ('[')
                auto has_double_dash = line.find("--") != line.npos && line.find("--") < line.find('['); // True if double dashes are found before left bracket character
                auto find_cluster_bracket = line.find('{');
                // Determine whether line matches graph title and change it to reflect that it contains the MST
                if (find_cluster_bracket != line.npos && find_cluster_bracket < line.size() - 1) {
                    write_MST_title(line);
                }
                // Determine whether line matches expected format of an undirected edge
                if (has_left_bracket && has_double_dash) {
                    auto find_space = line.find(" ", find_double_dash);
                    std::string vertex1_name = line.substr(0, find_double_dash - static_cast<size_t>(1));   // Substring of first vertex name
                    std::string vertex2_name = line.substr(find_double_dash + static_cast<size_t>(3), find_left_bracket - find_space - static_cast<size_t>(2)); // Substring of second vertex name
                    // Determine whether edge is part of those that comprise the MST
                    for (const auto& pair : MST_edges) {
                        std::string pair_vertex1 = underscore_spaces(std::get<0>(pair));
                        std::string pair_vertex2 = underscore_spaces(std::get<1>(pair));
                        bool straight_match = pair_vertex1.compare(vertex1_name) == 0 && pair_vertex2.compare(vertex2_name) == 0;
                        bool reverse_match = pair_vertex1.compare(vertex2_name) == 0 && pair_vertex2.compare(vertex1_name) == 0;
                        // If edge is part of MST, alter its edge and weight label coloration to distinguish it from non-MST edges
                        if (straight_match || reverse_match) {
                            auto start_color_pos = line.find(" color=") + 8;    // Position of first character of previous edge color name
                            auto end_color_pos = line.find('"', start_color_pos);   // Position of last character of previous edge color name
                            auto prev_color_size = end_color_pos - start_color_pos;
                            std::string edge_color = "darkcyan";
                            size_t n = 0;
                            // Directly Replace as many characters as possible of preset color to designated color for edges composing MST
                            for (; n < edge_color.size() && n < prev_color_size; n++) {
                                line[start_color_pos + n] = edge_color[n];
                            }
                            // Remove any Remaining characters if name of previous color is longer than name of new color
                            if (edge_color.size() < prev_color_size) {
                                line.erase(line.begin() + static_cast<long int>(start_color_pos) + static_cast<long int>(n), line.begin() + static_cast<long int>(end_color_pos));
                            } else {
                            // Insert any remaining characters if name of new color is longer than name of previous color
                                for (; n < edge_color.size(); n++) {
                                    line.insert(line.begin() + static_cast<long int>(start_color_pos) + static_cast<long int>(n), edge_color[n]);
                                }
                            }
                            // Insert different color for text label for edge weight value
                            auto find_right_bracket = line.rfind(']');
                            std::string text_label = " fontcolor=\"";
                            std::string text_color = "firebrick";
                            text_label.append(text_color).append("\" ");
                            line.insert(find_right_bracket, text_label);
                        }
                    }
                }
                line.append("\n");
                write_file.write(line.c_str(), static_cast<long int>(line.size()));
            }
        } else {
            std::cerr << "\nERROR: Failed to open file '" << MST_filename << "' for writing!" << '\n';
            read_file.close();
            return -1;
        }
        // Check failbit for errors encountered during reading
        if (read_file.fail()) {
            // Since file pointers will be out of sync due to insertions into write file, ignore if failbit is for eof
            if (read_file.eof()) {
                read_file.close();
                write_file.close();
                return 0;
            }
            std::cerr << "\nERROR: Failbit indicates an error occurred while reading\n";
            read_file.close();
            write_file.close();
            return -1;
        }
        // Check failbit for errors encountered during writing
        if (write_file.fail()) {
            std::cerr << "\nERROR: Failbit indicates an error occurrred while writing!\n";
            read_file.close();
            write_file.close();
            return -1;
        }
        // Close files and return with no error indication if failbits are not set
        read_file.close();
        write_file.close();
    // Report failure to open file used for parsing and copying graphical information of processed graph
    } else {
        std::cerr << "\nFailed to open file '" << graph_filename << "' for reading!" << '\n';
        return EXIT_FAILURE;
    }
    return 0;
}