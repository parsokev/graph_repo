#pragma once

#include "derived_hashmap.hpp"


/**
 * Parses the information for each edge of the graph to be processed in its entirety within the text file selected by the user, `filename`. After
 * processing each line, the edge inforamtion is stored with the hashmap-like container, `adj_list` and writing the edge and vertex information
 * included within each line in the dot language format within the file designated to store all extracted graphical information used in the visualization
 * of the main graph, `graph_file`.
 * @param filename Relative path to the text file selected by the user that contains line-by-line information on each edge forming graph to be processed by the program
 * @param graph_file Relative path to the file designated for storing the dot language-converted graphical information extracted from `filename`
 * @param vertex_count Integer value provided by the user representing the approximate number of unqiue verticies within the graph
 * @note `vertex_count` is used to initialize the container used to store the accumulated edge information, `adj_list` with its underlying storage array
 * having preallocated memory to store the provided number of unique verticies.
 * @param `adj_list` Hashmap-like container used to store information for each new vertex and unique edge read from `filename` in similar fashion to an adjacency list
 * @return 0 if successful, -1 upon failure
 */
extern int build_adjacency_list(const std::string& filename, const std::string& graph_file, unsigned int vertex_count, main_hashmap<double>&& adj_list);


/**
 * Applies Djikstra's algorithm to generate the shortest path from the user-provided source vertex, `s_vertex`, to the user-provided destination vertex, `des_vertex`,
 * using the graphical information stored within the container, `adj_list`.
 * Upon determining the shortest path, the relative paths of the file containing the graphical information extracted the user-provided text file, `graph_filename`,
 * and the file to be edited with the reformatted shortest path information,`path_filename` are passed to the function responsible for visualization of the shortest path.
 * @param s_vertex User-provided name of the source vertex from which to generate the starting position of the shortest path within the processed graph
 * @param des_vertex User-provided name of the destination vertex from which to generate the ending position of the shortest path within the processed graph
 * @param graph_filename Relative path to the file designated for storing the dot language-converted graphical information extracted from the text file of edge information
 * @param path_filename Relative path to the file to recieve the dot language converted graphical information of the generated shortest path
 * @param adj_list Hashmap-like container used to store the graphical information extracted from the user-selected text file containing the graph to be processed
 * @return 0 if successful, -1 upon failure
 */
extern int find_shortest_path(const std::string& s_vertex, const std::string& des_vertex, const std::string& graph_filename, const std::string& path_filename, main_hashmap<double>&& adj_list);


/**
 * Applies Prim's algorithm to generate the Minimum Spanning Tree (MST) starting from the source vertex, `s_vertex`, using the graphical information stored within the
 * container, `adj_list`.
 * Upon determining the MST, the relative paths of the file containing the graphical information extracted the user-provided text file, `graph_filename`,
 * and the file to be edited with the reformatted MST information,`MST_filename` are passed to the function responsible for visualization of the MST.
 * @param s_vertex User-provided name of the source vertex from which to generate the MST within the processed graph
 * @param graph_filename Relative path to the file designated for storing the dot language-converted graphical information extracted from the text file of edge information
 * @param MST_filename Relative path to the file to recieve the dot language converted graphical information of the MST
 * @param adj_list Hashmap-like container used to store the graphical information extracted from the user-selected text file containing the graph to be processed
 * @return 0 if successful, -1 upon failure
 */
extern int find_MST(std::string& s_vertex, const std::string& graph_filename, const std::string& MST_filename, main_hashmap<double>&& adj_list);