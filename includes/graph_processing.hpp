#pragma once

#include "derived_hashmap.hpp"

extern int build_adjacency_list(std::string& filename, std::string& graph_file, unsigned int vertex_count, main_hashmap<double>&& adj_list);

extern int find_shortest_path(std::string& s_vertex, std::string& des_vertex, std::string& graph_filename, std::string& path_filename, main_hashmap<double>&& adj_list);

extern int find_MST(std::string& s_vertex, std::string& graph_filename, std::string& MST_filename, main_hashmap<double>&& adj_list);