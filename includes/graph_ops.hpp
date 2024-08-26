#pragma once

#include "../includes/derived_hashmap.hpp"
// #include "master_hashmap.hpp"
#include "gprintf.hpp"
// extern int build_adjacency_list (std::string& filename, unsigned int vertex_count, master_hashmap<double>& adj_list);
extern int build_adjacency_list (std::string& filename, std::string& graph_file, unsigned int vertex_count, main_hashmap<double>& adj_list);

// extern void apply_djikstras_algorithm(std::string s_vertex, std::string des_vertex, unsigned int vertex_count, master_hashmap<double>& adj_list);
extern int apply_djikstras_algorithm(std::string s_vertex, std::string des_vertex, std::string& path_filename, main_hashmap<double>& adj_list);

// extern void apply_prims_algorithm(std::string s_vertex, master_hashmap<double>& adj_list);
extern int apply_prims_algorithm(std::string s_vertex, main_hashmap<double>& adj_list);

// extern int build_dot_graph(std::string& dot_file, unsigned int vertex, main_hashmap<double>& graph_rep);

extern int build_shortest_graph(std::string& dot_file, soa_hashmap<double>& path_map, dl_list<std::string>& path);

extern std::string underscore_spaces(const std::string& target_string);

extern int write_graph_header(std::fstream& graph_file, std::string& graph_type, std::string& title);

extern int write_vertex_node (std::fstream& graph_file, std::string& vertex_name);

extern int write_edge(std::fstream& graph_file, std::string& vertex1_name, std::string& vertex2_name, double& weight, std::string& graph_type);

extern bool is_connected (main_hashmap<double>& adj_list, std::string& source_vertex);