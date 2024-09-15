#pragma once

#include "derived_hashmap.hpp"

/**
 * Using the information on the shortest path stored in the `path_list` and `path_map` containers, reads the file containing all graphical information
 * extracted from the user-selected text file in dot format, `graph_filename` and rewrites each line within the file designated for storage of information on
 * the shortest path, `path_filename`, such that all verticies and/or edge(s) within the shortest path are easily distinguished in the generated graphical image.
 * @param graph_filename Relative path to the file containing all graphical information extracted from the user-selected text file of initial graph edges to be processed
 * @param path_filename Relative path to the file designated to hold all graphical information with the features of the shortest path altered to enhanced visual effect
 * @param path_list Vector-type container holding all verticies found within the shortest path, in order of traversal from source to destination
 * @param path_map Hashmap-like container holding key:value pairs of all directed edges found within the shortest path with their associated cost/weight values
 * @return 0 if successful, -1 upon failure
 */
extern int write_shortest_path_overlay(const std::string& graph_filename, const std::string& path_filename, std::vector<std::string>& path_list, soa_hashmap<double>&& path_map);


/**
 * Using the information on the Minimum Spanning Tree(MST) stored within the `MST_verticies` container, reads the file containing all graphical information
 * extracted from the user-selected text file in dot format, `graph_filename` and rewrites each line within the file designated for storage of information on
 * the MST, `MST_filename`, such that all edge(s) found within the MST are easily distinguished in the generated graphical image.
 * @param graph_filename Relative path to the file containing all graphical information extracted from the user-selected text file of initial graph edges to be processed
 * @param MST_filename Relative path to the file designated to hold all graphical information with the features of the shortest path altered to enhanced visual effect
 * @param MST_verticies Vector-type container holding string pairs of verticies that form each unique edge found within the generated MST
 * @return 0 if successful, -1 upon failure
 */
extern int write_MST_overlay(const std::string& graph_filename, const std::string& MST_filename, std::vector<std::pair<std::string, std::string>>& MST_verticies);


/**
 * Returns a string copy of `target_string`, where the copy has the first detected whitespace(" ") replaced with an underscore character ('_')
 * @param target_string string value to copied and returned with its first whitespace replaced with an underscore, if found
 * @return a string copy of `target_string` with position of first whitespace now replaced with an underscore characeter ('_')
 */
extern std::string underscore_spaces(const std::string& target_string);

/**
 * Writes graphical information specific to the title of the entire graph to be visualized using dot language format into `graph_file`,
 * the file designated to store all graphical information extracted from the user-selected file containing all graph edges to be processed.
 * The dot language format will be written according to accepted format for the type of graph provided by the value of `graph_type` and
 * displaying the title provided by the value of `title`.
 * @param graph_file Relative path to the file containing all graphical information extracted from the user-selected text file of initial graph edges to be processed
 * @param graph_type Type of graph to be depicted in the graphical visualization of the entire graph represented by the edges provided in user-selected text file
 * @param title String value to be displayed as the main title of graphical image displaying the entire graph
 * @note `graph_type` is used to specify how edges are displayed in graph_visualization:
 * 
 * "directed" results in one way travel from `vertex1_name` to `vertex2_name`, while "undirected" results in two-way travel between both verticies
 * @return 0 if successful, -1 upon failure
 */
extern int write_graph_header(std::fstream& graph_file, const std::string& graph_type, std::string& title);


/**
 * Writes graphical information specific to the specified vertex, `vertex_name`, within the main graph to be visualized using dot language format into `graph_file`,
 * the file designated to store all graphical information extracted from the user-selected file containing all graph edges to be processed.
 * The dot language format will be written according to the accepted format for individual node information, naming the node with value provided by `vertex_name`.
 * @param graph_file Relative path to the file containing all graphical information extracted from the user-selected text file of initial graph edges to be processed
 * @param vertex_name Name of node to display the corresponding information associated with vertex with matching name
 * @return 0 if successful, -1 upon failure
 */
extern int write_vertex_node (std::fstream& graph_file, const std::string& vertex_name);


/**
 * Writes graphical information specific to the edge within the main graph formed between the pair of verticies, `vertex1_name` and `vertex2_name` to be visualized
 * using dot language format into `graph_file`, the file designated to store all graphical information extracted from the user-selected file containing all graph edges
 * to be processed. The dot language format will be written according to the accepted format for individual edge information of the graph type, `graph_type`, and
 * associating the specific edge with the corresponding names of the verticies that form it, `vertex1_name` and `vertex2_name`, along with the value of its cost/weight,
 * `weight`.
 * @param graph_file Relative path to the file containing all graphical information extracted from the user-selected text file of initial graph edges to be processed
 * @param vertex1_name Name of first vertex node associated with edge whose information is to be linked to
 * @param vertex2_name Name of second vertex node associated with edge whose information is to linked to
 * @param weight Numerical value specific to the edge formed between the verticies of `vertex1_name` and `vertex2_name`
 * @param graph_type String value identifying type of graph
 * @note `graph_type` is used to specify how edges are displayed in graph_visualization:
 * 
 *  "directed" results in one way travel from `vertex1_name` to `vertex2_name`, while "undirected" results in two-way travel between both verticies
 * @return 0 if successful, -1 upon failure
 */
extern int write_edge(std::fstream& graph_file, const std::string& vertex1_name, const std::string& vertex2_name, double& weight, const std::string& graph_type);