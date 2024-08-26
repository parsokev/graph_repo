#pragma once

#include "../includes/derived_hashmap.hpp"
// #include "master_hashmap.hpp"
#include "gprintf.hpp"

extern int get_graph_filename(std::string& directory_name, std::string& user_file); 

extern void get_graph_vertex_count(long int& vertex_count);

extern int get_shortest_path(main_hashmap<double>& main, std::string& path_filename);

extern int get_requested_algorithm (std::string& algorithm_type, main_hashmap<double>& main, std::string& path_filename);