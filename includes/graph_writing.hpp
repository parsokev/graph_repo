#pragma once

#include "derived_hashmap.hpp"

extern int write_shortest_path_overlay(std::string& dot_file, std::string& path_file, std::vector<std::string>& path_list, soa_hashmap<double>&& path_map);

extern int write_MST_overlay(std::string& graph_filename, std::string& MST_filename, std::vector<std::pair<std::string, std::string>>& MST_verticies);

extern std::string underscore_spaces(const std::string& target_string);

extern int write_graph_header(std::fstream& graph_file, std::string& graph_type, std::string& title);

extern int write_vertex_node (std::fstream& graph_file, std::string& vertex_name);

extern int write_edge(std::fstream& graph_file, std::string& vertex1_name, std::string& vertex2_name, double& weight, std::string& graph_type);