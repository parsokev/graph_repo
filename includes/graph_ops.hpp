#pragma once

#include "master_hashmap.hpp"
#include "gprintf.hpp"
extern int build_adjacency_list (std::string& filename, unsigned int vertex_count, master_hashmap<double>& adj_list);

extern void apply_djikstras_algorithm(std::string s_vertex, std::string des_vertex, unsigned int vertex_count, master_hashmap<double>& adj_list);

extern void apply_prims_algorithm(std::string s_vertex, master_hashmap<double>& adj_list);