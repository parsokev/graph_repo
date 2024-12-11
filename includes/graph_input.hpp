#pragma once

#include "derived_hashmap.hpp"

/**
 * Prompts user for name of text file found within `directory` to be processed for graphical information,
 * and upon receiving a valid filename, stores the filename within `user_file` for reading operations
 * @param directory_name Relative path to directory holding text file(s) that can be processed for graphical information
 * @param user_file Name of text file that user has chosen for processing by the program
 * @return 0 if successful, -1 upon failure 
 */
extern int get_graph_filename(std::string& directory_name, std::string& user_file); 


/**
 * Depending on whether the user wishes to provide an approximate number of unique verticies, either continues to
 * prompt user for approximate value until a valid integer value is received and stores the number
 * of unique verticies in `vertex_count` or estimates `vertex_count` to half the number of lines found within `read_name`
 * @param vertex_count User-provided number of total unique verticies found within graph to be processed by program
 * @param read_name Name of text file that user has chosen for processing by the program
 * @return 0 if successful, -1 upon failure
 */
extern int get_graph_vertex_count(long int& vertex_count, std::string& read_name);


/**
 * Prompts user for the identities of the source and destination verticies from which to generate the shortest path, and upon
 * receiving two valid verticies found within the file selected by the user for processing, passes these verticies, the
 * customized hashmap container, `main`, which holds all edge and vertex information extracted from the user-selected text file,
 * `graph_filename` and the file to be written in the dot language format used for visualization of the shortest path, `path_filename`
 * @param main Customized hashmap-like container storing all of the graphical information extracted from the user-selected text file
 * @param graph_filename Relative path to text file containing all graphical edges comprising of graph to be processed by program
 * @param path_filename Relative path to text file used for writing shortest path in dot language format for subsequent visualization
 * @return 0 if successful, -1 upon failure  
 */
extern int get_shortest_path(main_hashmap<double>&& main, const std::string& graph_filename, const std::string& path_filename);


/**
 * Prompts user for the desired type of information to be extracted and visualized from the selected text file of graphical information,
 * and upon receiving a valid response, stores the response in `algorithm_type` to be passed to the appropriate function(s) for generating
 * requested type of information and visualizing this information.
 * @param algorithm_type User-provided type of requested information to be provided using the selected file of graphical information
 * @param main Container holding all graphical information extracted from text file selected by user for processing
 * @param graph_filename Relative path to user-selected text file containing the graphical information to be processed by the program
 * @param path_file Relative path to text file to which the shortest path will be written to in dot language, if requested by the user
 * @param MST_filename Relative path to text file to which the Minimum Spanning Tree will be written to in dot language format, if requested by the user
 */
extern int get_requested_algorithm (std::string& algorithm_type, main_hashmap<double>&& main, const std::string& graph_filename, const std::string& path_filename, const std::string& MST_filename);