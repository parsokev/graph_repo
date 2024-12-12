#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "../includes/derived_hashmap.hpp"
#include "../includes/graph_writing.hpp"

/**
 * Modifies the line containing the graph title information in dot language format, `line`,
 * to display the matching source and destination vertex names in graph visualization of shortest path
 * extracted from `path_list`
 * @param path_list Vector-type container holding all verticies within shortest path in order of traversal
 * @param line Line matching dot language format for holding the graph title information
 */
static void write_path_title(std::vector<std::string> &path_list, std::string &line)
{
    size_t start_title_pos = line.find("label=") + static_cast<size_t>(7);
    size_t end_title_pos = line.find('"', start_title_pos);

    std::string path_title = "Shortest Path FROM "; // Graph title for overlayed image of shortest path

    path_title.append(path_list.front()).append(" TO ").append(path_list.back());
    size_t p = 0;
    // Directly Replace as many characters as possible of previous title with those of designated title for shortest path image
    for (; p < end_title_pos - start_title_pos && p < path_title.size(); p++) {
        line[start_title_pos + p] = path_title[p];
    }
    // Remove any Remaining characters if name of previous title is longer than name of new title
    if (path_title.size() < end_title_pos - start_title_pos) {
        line.erase(line.begin() + static_cast<long int>(start_title_pos) + static_cast<long int>(p),
                   line.begin() + static_cast<long int>(end_title_pos));
    } else {
        // Insert any remaining characters of name of new title if it is longer than name of previous title
        for (; p < path_title.size(); p++) {
            line.insert(line.begin() + static_cast<long int>(start_title_pos)
                        + static_cast<long int>(p),
                        path_title[p]);
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
static void write_path_node(std::string &line, size_t &find_right_bracket)
{
    // Set text color of vertex nodes found within shortest path to different color than default text
    std::string node_label = " fontcolor=\"";
    std::string node_text_color = "darkorange1";   // Text color of node(s) in shortest path
    std::string node_fill_color = "darkslategrey"; // Background color of node(s) in shortest path

    node_label.append(node_text_color).append("\" ");
    line.insert(find_right_bracket, node_label);

    // Check if there is a preset fill color for vertex nodes found within shortest path
    size_t find_fill_label = line.find("fillcolor=");
    if (find_fill_label != line.npos) {
        // If a preset fillcolor is found, change fill color to a new chosen color to highlight vertex nodes within shortest path
        size_t fcolor_start_pos = find_fill_label + static_cast<size_t>(11);
        size_t fcolor_end_pos = line.find('"', fcolor_start_pos);
        size_t n = 0;
        // Directly replace as many characters as possible of previous color used as fillcolor with those of new color for shortest path image
        for (; n < fcolor_end_pos - fcolor_start_pos && n < node_fill_color.size(); n++) {
            line[fcolor_start_pos + n] = node_fill_color[n];
        }
        // Remove any remaining characters if name of previous fillcolor is longer than name of new color
        if (node_fill_color.size() < fcolor_end_pos - fcolor_start_pos) {
            line.erase(line.begin() + static_cast<long int>(fcolor_start_pos)
                       + static_cast<long int>(n),
                       line.begin() + static_cast<long int>(fcolor_end_pos));
        } else {
            // Insert any remaining characters of name of new color if it is longer than name of previous fillcolor
            for (; n < node_fill_color.size(); n++) {
                line.insert(line.begin() + static_cast<long int>(fcolor_start_pos)
                            + static_cast<long int>(n),
                            node_fill_color[n]);
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
static void write_path_edge(size_t &first_space,
                            std::list<std::string> &path_edges,
                            std::string &line)
{
    std::string arrow_label
        = "arrowsize=0 "; // Size of arrowheads for edge(s) not in shortest path (eliminates)
    std::string color_label = "darkcyan"; // Color of connecting edge(s) in shortest path

    // Get Previous Color Size and Position within Line
    size_t start_color_pos = line.find(" color=") + static_cast<size_t>(8);
    size_t end_color_pos = line.find('"', start_color_pos);
    size_t prev_color_size = end_color_pos - start_color_pos;

    // Update Actual Line used for Extracting Node Information To Directed Edge Format
    line[line.find("--") + 1] = '>';
    bool in_shortest_path = false; // Bool value for determining if extracted node is in shortest path
    size_t second_space = line.find(
        " ",
        first_space); // Position of whitespace between second vertex name and arrow character ('>')
    size_t third_space = line.find('[', second_space);
    std::string vertex1 = line.substr(0, first_space); // Substring containing first vertex name
    std::string vertex2 = line.substr(first_space + static_cast<size_t>(4),
                                      third_space - static_cast<size_t>(5)
                                          - second_space); // Substring containing second vertex name

    std::string straight_edge = vertex1;
    straight_edge.append(" -> ").append(vertex2);
    std::string reverse_edge = vertex2;
    reverse_edge.append(" -> ").append(vertex1);
    // Loop through List of Edges found in Shortest Path and Compare them to Substring containing Directed Edge
    for (const std::string &edge : path_edges) {
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
                line.erase(line.begin() + static_cast<long int>(start_color_pos)
                           + static_cast<long int>(j),
                           line.begin() + static_cast<long int>(end_color_pos));
                // Insert any remaining characters if name of new color is longer than name of previous color
            } else {
                for (; j < color_label.size(); j++) {
                    line.insert(line.begin() + static_cast<long int>(start_color_pos)
                                + static_cast<long int>(j),
                                color_label[j]);
                }
            }
        }
    }
    // If line defines an edge that is not part of the shortest path, remove arrow head feature and retain preset color
    if (!in_shortest_path) {
        line.insert(line.find('[') + 1, arrow_label);
        // If line defines an edge that is part of shortest path, change the text color of the weight label
    } else {
        size_t find_right_bracket = line.rfind(']');
        std::string text_label = " fontcolor=\"";

        std::string text_color
            = "darkmagenta"; // Color of text for the weight/cost of edge(s) in shortest path

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
static void write_MST_title(std::string &line)
{
    size_t start_title_pos = line.find("label=") + static_cast<size_t>(7);
    size_t end_title_pos = line.find('"', start_title_pos);

    std::string path_title = "Minimum Spanning Tree"; // Graph title for overlayed image of MST

    size_t p = 0;
    // Directly Replace as many characters as possible of previous title with those of designated title for shortest path image
    for (; p < end_title_pos - start_title_pos && p < path_title.size(); p++) {
        line[start_title_pos + p] = path_title[p];
    }
    // Remove any Remaining characters if name of previous title is longer than name of new title
    if (path_title.size() < end_title_pos - start_title_pos) {
        line.erase(line.begin() + static_cast<long int>(start_title_pos) + static_cast<long int>(p),
                   line.begin() + static_cast<long int>(end_title_pos));
    } else {
        // Insert any remaining characters of name of new title if it is longer than name of previous title
        for (; p < path_title.size(); p++) {
            line.insert(line.begin() + static_cast<long int>(start_title_pos)
                        + static_cast<long int>(p),
                        path_title[p]);
        }
    }
    return;
}

static void remove_underscores(std::string &target_string)
{
    size_t find_underscore = target_string.find("_");
    if (find_underscore != target_string.npos) {
        std::string space = " ";
        while (find_underscore != target_string.npos) {
            target_string.replace(find_underscore, space.size(), space.c_str());
            find_underscore = target_string.find("_");
        }
    }
    return;
}


int check_for_CLRF(std::string& filename) {
    // add 'temp_' to filename without modifying path or file extension
    std::string write_name = filename;
    size_t find_filename = write_name.rfind('/');
    if (find_filename != write_name.npos) {
        std::string tempname = "temp_";
        size_t k = 0;
        for (; k < tempname.size(); k++) {
            write_name.insert(write_name.begin() + 1 + static_cast<long int>(find_filename) + static_cast<long int>(k), tempname[k]);
        }
    } else {
        // If file path is not valid return error
        std::cerr << "Invalid filename/path syntax for '" << filename << "'!\n";
        return -1;
    }
    std::fstream read_file;
    // Create temporary file to store copied file lines without CRLF found in Windows files
    std::fstream write_file {write_name, write_file.out | write_file.trunc};
    read_file.open(filename);
    // Copy each line in file to be parsed for CLRF and write modified contents to temp file
    if (read_file.is_open()) {
        std::string line;
        bool is_windows = false;
        while(getline(read_file, line)) {
            std::string next_line = line;
            size_t carr_return_pos = line.find('\r');
            // Check for CRLF characters found in Windows text files
            if (carr_return_pos != line.npos) {
                // If CRLF found, remove '\r\n' characters for Linux compatibility
                next_line.erase(carr_return_pos, carr_return_pos + 1);
                is_windows = true;
            }
            next_line.append(1, '\n');
            try {
                write_file.write(next_line.c_str(), static_cast<long int>(next_line.size()));
            }
            catch (const std::exception& e) {
                std::cerr << e.what();
                return -1;
            }
        }
        if (read_file.bad()) {
            std::cerr << "Error encountered during reading operation of '" << filename << "'\n";
            return -1;
        }
        read_file.close();
        // Pipe commands to either replace original file with temp file or delete temp file
        FILE *pipe_stream;
        std::string command_val = "";
        // If carriage return/CRLF found, temp file should replace windows text file
        if (is_windows) {
            // Pass command to rename temporary file to original file
            command_val = "mv ";
            command_val.append(write_name).append(" ").append(filename);

        } else {
            // If not a single line has carriage return/CRLF that may cause linux-incompatibility, pass command to delete temp file
            command_val = "rm -rf ";
            command_val.append(write_name);
        }
        // If windows system is detected use _popen and _pclose for compatibility across most windows systems
#ifdef _WIN32
        pipe_stream = _popen(command_val.c_str(), "r");
        // Check to ensure pipeline is successfully established, close it if so
        if (pipe_stream != NULL) {
            _pclose(pipe_stream);
        }
        else {
            // Exit if fork or pipe operations fail
            perror("pipe/fork");
            std::cerr << "ERROR: Failed to establish pipeline stream for replacing original file '" << filename << "' with '" << write_name << "'\n";
            return -1;
        }
        // If MacOS or Linux/Unix system use standard popen and pclose instead
#else
        pipe_stream = popen(command_val.c_str(), "r");
        // Check to ensure pipeline is successfully established, close it if so
        if (pipe_stream != NULL) {
            pclose(pipe_stream);
        }
        else {
            // Exit if fork or pipe operations fail
            perror("pipe/fork");
            std::cerr << "ERROR: Failed to establish pipeline stream for replacing original file '" << filename << "' with '" << write_name << "'\n";
            return -1;
        }
#endif
    } else {
        // Exit with error if file to be parsed does not exist
        std::cerr << "Failed to open file " << filename << '\n';
        return -1;
    }
    return 0;
}

std::string underscore_spaces(const std::string &target_string)
{
    std::string underscore_string = target_string;
    size_t find_space = underscore_string.find(" ");

    if (find_space != underscore_string.npos) {
        std::string under_score = "_";
        while (find_space != underscore_string.npos) {
            underscore_string.replace(find_space, under_score.size(), under_score.c_str());
            find_space = underscore_string.find(" ");
        }
    }
    return underscore_string;
}

int write_graph_header(std::fstream &graph_file, const std::string &graph_type, std::string &title)
{
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

    // Provide Predefined Variables for Quick Manipulation of Graph Features
    std::string header = g_type;
    std::string main_graph_name = " main_graph ";                      // Identification of Graph
    std::string main_graph_font_name = "DejaVu Sans,Arial,sans-serif"; // Text Font for Graph Title
    std::string graph_ratio_setting
        = "auto"; // Setting for Vertical/Horizontal Spacing of Nodes and Edges across Image
    std::string node_font_name = "Impact,Arial,sans-serif"; // Text Font for Node Names
    std::string edge_font_name
        = "Comic Sans,Arial,sans-serif"; // Text Font for Edge Weight/Cost Values
    std::string node_style = "filled";   // Toggle Setting for Enabling Background Color of Nodes
    std::string landscape_enabled
        = "false"; // Toggle Setting for Portrait or Landscape Orientation of Image
    std::string background_color = "gainsboro"; // Background Color of Entire Image
    std::string node_fill_color = "cyan";       // Background Color of Individual Nodes
    std::string cluster_name = "Full Graph";    // Main Title Displayed for Image
    std::string cluster_shape = "box";          // Shape of Border Surrounding the Main Title
    std::string cluster_fontsize = "14";        // Font Size of Main Title
    std::string cluster_label = title;
    std::string cluster_tooltip
        = "All Nodes"; // Alternate Pop-up Information Displayed On Cursor Hover in Other Formats that Support Feature

    // Main Graph Features
    header.append(main_graph_name)
        .append("{\nfontname=\"")
        .append(main_graph_font_name)
        .append("\"\nnode [fontname=\"")
        .append(node_font_name)
        .append("\"]\nedge [fontname=\"");
    header.append(edge_font_name)
        .append("\"]\nnode [style=")
        .append(node_style)
        .append(" fillcolor=\"")
        .append(node_fill_color)
        .append("\"]\n");
    header.append("ratio=")
        .append(graph_ratio_setting)
        .append(" landscape=")
        .append(landscape_enabled)
        .append(" bgcolor=\"")
        .append(background_color)
        .append("\"\n");
    // SubGraph Features
    std::string sub_header = "subgraph cluster {\"";
    sub_header.append(cluster_name)
        .append("\" [shape=")
        .append(cluster_shape)
        .append(" fontsize=")
        .append(cluster_fontsize)
        .append(" label=\"");
    sub_header.append(cluster_label)
        .append("\" tooltip=\"")
        .append(cluster_tooltip)
        .append("\"] }\n");

    graph_file.write(header.c_str(), static_cast<long int>(header.size()));
    graph_file.write(sub_header.c_str(), static_cast<long int>(sub_header.size()));
    // Check Failbit for logged errors during writing operation
    if (graph_file.bad()) {
        std::cerr << "Failbit set in writing operation" << '\n';
        return -1;
    }
    return 0;
}

int write_vertex_node(std::fstream &graph_file, const std::string &vertex_name)
{
    // Provide Predefined Variables for Quick Manipulation of Individual Node Features
    std::string node_line = vertex_name; // Displayed Name of Specified Vertex/Node
    std::string node_shape = "box3d"; // Shape of Border Surrounding Name of Specified Vertex/Node
    std::string node_border_color
        = "darkgreen"; // Edge Color of Border Surrounding Name of Specified Vertex/Node
    std::string node_inside_color
        = "darkolivegreen2";           // Background/Fill Color Inside Shape Surround Node/Vertex
    std::string node_font_size = "12"; // Font Size of Text Displaying Node/Vertex Name

    // Specific Node Features
    node_line.append(" [").append("label=\"").append(vertex_name).append("\" id=\"");
    node_line.append(vertex_name).append("\" fontsize=").append(node_font_size).append(" shape=");
    node_line.append(node_shape).append(" tooltip=\"").append(vertex_name).append("\" color=\"");
    node_line.append(node_border_color)
        .append("\" fillcolor=\"")
        .append(node_inside_color)
        .append("\"]\n");

    graph_file.write(node_line.c_str(), static_cast<long int>(node_line.size()));
    // Check Failbit for logged errors during writing operation
    if (graph_file.bad()) {
        std::cerr << "Failbit set in writing operation" << '\n';
        return -1;
    }
    return 0;
}

int write_edge(std::fstream &graph_file,
               const std::string &vertex1_name,
               const std::string &vertex2_name,
               double &weight,
               const std::string &graph_type)
{
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

    // Provide Predefined Variables for Quick Manipulation of Individual Edge Features
    std::string edge_label_size = "60"; // Text Size of Displayed Edge/Cost Value of Specific Edge
    std::string edge_width = "3";       // Thickness of Edge Line
    std::string edge_color = "darkgoldenrod2"; // Color of Edge Line
    std::string edge_name = vertex1_name;      // Name of Vertex From Which The Edge Begins (Source)

    // Specific Edge Features
    edge_name.append(edge_char).append(vertex2_name);
    std::string edge_line = edge_name;
    edge_line.append(" [label=\"").append(weight_string).append("\" weight=").append(edge_label_size);
    edge_line.append(" penwidth=").append(edge_width).append(" color=\"").append(edge_color);
    edge_line.append("\" tooltip=\"")
        .append(edge_name)
        .append("\" labeltooltip=\"")
        .append(edge_name)
        .append("\"]\n");
    graph_file.write(edge_line.c_str(), static_cast<long int>(edge_line.size()));
    // Check Failbit for logged errors during writing operation
    if (graph_file.bad()) {
        return -1;
    }
    return 0;
}

int write_shortest_path_overlay(const std::string &graph_filename,
                                const std::string &path_filename,
                                std::vector<std::string> &path_list,
                                soa_hashmap<double> &&path_map)
{
    std::list<std::string> path_edges = path_map.get_keys();
    // Create shortest_path_overlay .gv file if does not exist or remove contents if it does
    std::fstream write_file{path_filename, write_file.trunc | write_file.out};
    std::fstream read_file{graph_filename, read_file.in};
    if (read_file.is_open()) {
        std::string line;
        // Locate the leading 'g' of expected "graph" word in first line to edit for denoting a directed graph
        getline(read_file, line);
        size_t get_first_g = line.find('g');
        if (get_first_g == line.npos) {
            std::cerr << "\nERROR: expected at least once occurence in 'g' in first line of '"
                      << graph_filename << "' file\n";
            read_file.close();
            write_file.close();
            return -1;
        }
        // Write file format to declare directed graph
        line.insert(get_first_g, "di").append("\n");
        write_file.write(line.c_str(), static_cast<long int>(line.size()));

        while (getline(read_file, line)) {
            // Initialize parameters to track and locate key characters that define information type of each line
            size_t find_left_bracket = line.find('['); // Position of left bracket character ('[')
            size_t find_double_dash = line.find(
                "--"); // Position of existing "--" substring if present
            size_t find_first_space = line.find(
                " "); // Position immediately following name of first vertex for lines representing vertex nodes and edges
            size_t find_right_bracket = line.find(
                "]"); // Position of last expected character in current line ("]");
            // Call function to edit title of shortest path image to match user-requested information
            size_t find_cluster_bracket = line.find('{');
            if (find_cluster_bracket != line.npos) {
                write_path_title(path_list, line);
            }
            bool has_double_dash = find_double_dash
                                   != line.npos; // True if current line contains "--" substring
            // If line depicts an undirected edge, call function to parse the line and alter its appearance, if it is found within the shortest path
            if (find_left_bracket != line.npos && has_double_dash) {
                write_path_edge(find_first_space, path_edges, line);
                // If the line does not contain a double dash, it depicts an individual node/vertex instead
            } else {
                std::string node_slice = line.substr(0, find_first_space);
                // Replace single underscore with a space if found within the vertex extracted from the substring
                remove_underscores(node_slice);

                // Change the text color of extracted vertex if it is within the shortest path
                for (const std::string& vertex : path_list) {
                    if (node_slice.compare(vertex) == 0) {
                        write_path_node(line, find_right_bracket);
                    }
                }
            }
            // Write each processed line that was intially read from read_file and write it into write_file
            line.append("\n");
            write_file.write(line.c_str(), static_cast<long int>(line.size()));
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

int write_MST_overlay(const std::string &graph_filename,
                      const std::string &MST_filename,
                      std::vector<std::pair<std::string, std::string>> &MST_edges)
{
    // Create MST_overlay .gv file if does not exist or overwrite its contents if it does
    std::fstream write_file{MST_filename, write_file.trunc | write_file.out};
    std::fstream read_file{graph_filename, read_file.in};
    if (read_file.is_open()) {
        std::string line;
        while (getline(read_file, line)) {
            size_t find_left_bracket = line.find('['); // Position of left bracket character ('[')
            size_t find_double_dash = line.find(
                "--"); // Position of first dash of double dash ("--")
            size_t has_left_bracket = find_left_bracket != line.npos; // True if left bracket character is found in current line  ('[')
            size_t has_double_dash = line.find("--") != line.npos && line.find("--") < line.find('['); // True if double dashes are found before left bracket character
            size_t find_cluster_bracket = line.find('{');
            // Determine whether line matches graph title and change it to reflect that it contains the MST
            if (find_cluster_bracket != line.npos && find_cluster_bracket < line.size() - 1) {
                write_MST_title(line);
            }
            // Determine whether line matches expected format of an undirected edge
            if (has_left_bracket && has_double_dash) {
                size_t find_space = line.find(" ", find_double_dash);
                std::string vertex1_name
                    = line.substr(0,
                                  find_double_dash
                                      - static_cast<size_t>(
                                          1)); // Substring of first vertex name
                std::string vertex2_name
                    = line.substr(find_double_dash + static_cast<size_t>(3),
                                  find_left_bracket - find_space
                                      - static_cast<size_t>(
                                          2)); // Substring of second vertex name
                // Determine whether edge is part of those that comprise the MST
                for (const auto& pair : MST_edges) {
                    std::string pair_vertex1 = underscore_spaces(std::get<0>(pair));
                    std::string pair_vertex2 = underscore_spaces(std::get<1>(pair));
                    bool straight_match = pair_vertex1.compare(vertex1_name) == 0
                                          && pair_vertex2.compare(vertex2_name) == 0;
                    bool reverse_match = pair_vertex1.compare(vertex2_name) == 0
                                         && pair_vertex2.compare(vertex1_name) == 0;
                    // If edge is part of MST, alter its edge and weight label coloration to distinguish it from non-MST edges
                    if (straight_match || reverse_match) {
                        size_t start_color_pos
                            = line.find(" color=")
                              + 8; // Position of first character of previous edge color name
                        size_t end_color_pos = line.find(
                            '"',
                            start_color_pos); // Position of last character of previous edge color name
                        size_t prev_color_size = end_color_pos - start_color_pos;

                        std::string edge_color = "darkcyan"; // Edge Color for Edges Found In MST

                        size_t n = 0;
                        // Directly Replace as many characters as possible of preset color to designated color for edges composing MST
                        for (; n < edge_color.size() && n < prev_color_size; n++) {
                            line[start_color_pos + n] = edge_color[n];
                        }
                        // Remove any Remaining characters if name of previous color is longer than name of new color
                        if (edge_color.size() < prev_color_size) {
                            line.erase(line.begin() + static_cast<long int>(start_color_pos)
                                       + static_cast<long int>(n),
                                       line.begin() + static_cast<long int>(end_color_pos));
                        } else {
                            // Insert any remaining characters if name of new color is longer than name of previous color
                            for (; n < edge_color.size(); n++) {
                                line.insert(line.begin() + static_cast<long int>(start_color_pos)
                                            + static_cast<long int>(n),
                                            edge_color[n]);
                            }
                        }
                        // Insert different color for text label for edge weight value
                        size_t find_right_bracket = line.rfind(']');
                        std::string text_label = " fontcolor=\"";

                        std::string text_color
                            = "firebrick"; // Text Color for Weight/Cost of Edge(s) in MST

                        text_label.append(text_color).append("\" ");
                        line.insert(find_right_bracket, text_label);
                    }
                }
            }
            line.append("\n");
            write_file.write(line.c_str(), static_cast<long int>(line.size()));
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