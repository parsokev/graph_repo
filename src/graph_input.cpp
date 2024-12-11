#include <iostream>
#include <vector>
#include <iosfwd>
#include <string>
#include <cstdio>
#include <fstream>
#include <filesystem>
#include <list>
#include <algorithm>


#include "../includes/graph_input.hpp"
#include "../includes/derived_hashmap.hpp"
#include "../includes/graph_processing.hpp"
#include "../includes/gprintf.hpp"

/**
 * Overloading function for printing string Vector-type container arrays to standard output stream
 */
std::ostream& operator<<(std::ostream& out, const std::list<std::string>& string_list) {
    out << "[ ";
    out << '\n';
    int key_counter = 0;
    for (std::string key : string_list) {
        if (key_counter == 10) {
            out << '\n';
            key_counter = 0;
        }
        if ( key == string_list.back()) {
            out << key;
        } else {
            out << key << ", ";
        }
        key_counter ++;
    }
    out << '\n';
    out << " ]";
    return out;
}

/**
 * Local function for printing string List-type container array to standard output
 * @param list_s List container holding string values to be printed in readable format
 */
static void print_list(std::list<std::string>& list_s) {
    std::cout << "[ ";
    for (std::string i : list_s) {
        if ( i == list_s.back()) {
            std::cout << i;
        } else {
            std::cout << i << ", ";
        }
    }
    std::cout << " ]" << '\n';
    return;
}


/**
 * Assigns the value of the number of unique verticies found within the graph, `vertex_count`, 
 * represented by the graphical information stored within the text file `read_name` to be exactly
 * half the number of lines found within the `read_name`
 * @param vertex_count Number of unique verticies found within graph represented by information stored in `read_name`
 * @param read_name Name of text file that user has chosen for processing by the program
 * @return 0 if successful, -1 upon failure
 */
static int approximate_graph_vertex_count(long int& vertex_count, std::string& read_name) {
    // Generate stream to read from a pipeline that writes commands based on preprocesser conditionals to retain OS-compliance
    FILE *pipe_stream;
    
    // Gather line count of text file containing graphical information using Linux-compliant bash command 'grep'
    #ifdef __linux__
        std::string command_val = "grep -c ^ ";
        command_val.append(read_name);
    // Gather line count of text file containing graphical information using MacOS-compliant bash command 'ggrep' for HomeBrew
    #elif __APPLE__
        std::string command_val = "ggrep -c ^ ";
        command_val.append(read_name);
    // Gather line count of text file containing graphical information using Windows-compliant powershell piped command captured as a single command
    #elif _WIN32
        std::string command_val = "powershell -Command \"(Get-Content -Path ./";
        command_val.append(read_name).append(" | Measure-Object -Line).Lines\"");
    // Exit if unexpected OS-type is detected due to potentially incompatibility or undefined behavior in pipe operation
    #else
        std::cerr << "Compatibility of OS with 'popen' command cannot be verified. Please restart program and manually enter an approximate value for total number of unique verticies\n";
        return -1;
    #endif
    // Establish stream with intent to read from buffer containing the command line output written to standard output
    // Establish stream with intent to read from buffer containing the command line output written to standard output
#ifdef _WIN32
    pipe_stream = _popen(command_val.c_str(), "r");
#else
    pipe_stream = popen(command_val.c_str(), "r");
#endif
    std::string line;
    char buf[11];   // Digit count should not exceed maxmimum number for capacity allocation of data structures holding vertex information
    
    char *result;
    // If stream is successfully established with pipeline and is able to read it, extract the line count printed by grep command
    if (pipe_stream != NULL) {
        result = fgets(buf, sizeof(buf), pipe_stream);
        if (result) {
            line.append(result);
        }
        pclose(pipe_stream);
    } else {
        // Exit if fork or pipe operations fail
        perror("pipe/fork");
        std::cerr << "ERROR: Failed to establish pipeline stream for reading the line count from '" << read_name << "'\n";
        return -1;
    }

    if (line.size() == 0) {
        // If fails to extract information from buffer, exit with proper notification
        std::cerr << "ERROR: Reading of output for pipeline stream failed to extract line count from text file '" << read_name << "'\n";
        return -1;
    }
    // Convert extracted grep command ouput to a long integer and assign half its value to estimate the number of unique verticies for graph
    unsigned long vertex_conversion = strtoul(line.c_str(), nullptr, 10);
    
    // Set appropriate system defined value for unsigned integer maximum value to prevent potential overflow
    #ifndef __linux__
    auto max_int = UINT_MAX;
    #else
    auto max_int = UINT32_MAX;
    #endif
    if (errno == ERANGE || errno == EINVAL || vertex_conversion <= 0 || vertex_conversion > max_int) {
        std::cerr << "ERROR: Conversion of extracted line count for '" << read_name << "' failed. Please ensure text file is not empty and file is not exceedingly large\n";
        return -1;
    }

    double edge_density = 0.5;
    unsigned int edge_count = static_cast<unsigned int>(vertex_conversion);
    /*
     *  Assuming no overlapping edges are listed, can use formula for edge density of directed graphs
     *  to estimate the number of unique verticies from the number of lines in the text file(each line = 1 edge):
     *      Edge Density = # of Edges / (# of Verticies * (# of Verticies - 1))
     */
    vertex_count = static_cast<unsigned int>((((edge_density) + std::sqrt((pow(edge_density, 2)) + (4 * (edge_count) * (edge_density)))) / (2 * edge_density)));


    // Handle Exceedingly Small Line Counts in Parsing User-Selected Text File
    if (vertex_count < 5) {
        vertex_count = 5;
    }
    gprintf("Estimating Vertex Count to %i", vertex_count);
    return 0;
}


int get_graph_filename(std::string& directory_name, std::string& user_file) {
    // Retrieve contents of designated directory for storing user-provided graph information 
    auto file_list = std::list<std::string>{};
    if (std::filesystem::exists(directory_name)) {
        for (const auto& sample_file : std::filesystem::directory_iterator(directory_name)){
            std::string file_name = sample_file.path().string();
            file_name.erase(file_name.begin(), file_name.begin() + static_cast<long int>(directory_name.size()));
            file_list.emplace_back(std::move(file_name));
        }
    } else {
        // Exit program and Notify user if program is launched from an invalid path in terminal
        std::cerr << "\nERROR: Relative path to '" << directory_name << "' is invalid from current working directory\n";
        std::cerr << "Please ensure you are executing the program from within the 'build' directory if choosing to execute the program using the command line\n";
        return -1;
    }

    // Display file contents to user
    std::cout << "Current text files available are: " << '\n';
    print_list(file_list);
    std::cout << '\n';
    // Handle user input of graph filename
    std::cout << "Please Enter the Filename containing the Weighted Graph Edges: ";
    getline(std::cin>>std::ws, user_file);
    // while(!file_list.contains_node(user_file) && user_file.compare("exit now") != 0) {
    while(std::find(file_list.begin(), file_list.end(), user_file) == file_list.end() && user_file.compare("exit now") != 0) {
        std::cerr << "\nERROR: Filename of '" << user_file << "' not found in \"sample_graphs\" directory" << '\n';
        std::cout << "If you wish to Exit, Enter \"exit now\" instead." << '\n';
        std::cout << "Please Enter the Filename of file within \"sample_graphs\" directory containing the Weight Graph Edges: ";
        std::getline(std::cin >> std::ws, user_file);
    }
    // Exit Program if user requests it
    if (user_file.compare("exit now") == 0) {
        std::cout << "Exiting Program... Goodbye" << std::endl;
        return -1;
    }
    
    // Clear error flags for next user testing phase
    std::cin.clear();

    // Update relative path to user-provided graph_file for reading operation
    directory_name.append(user_file);
    std::cout << '\n';
    return 0;
}



int get_graph_vertex_count(long int& vertex_count, std::string& read_name) {
    // Handle user input for querying whether user wishes to provide number of unqiue verticies or have program estimate the number
    std::string response;
    std::cout << "\nIf the approximate number of unique verticies is already known, they may be manually provided to maximize processing time\n";
    std::cout << "Is the approximate number of unique verticies already known? [y/n]: ";
    getline(std::cin >> std::ws, response);
    while (response.compare("y") != 0 && response.compare("n") != 0 && response.compare("exit now") != 0) {
        std::cerr << "\nERROR: '" << response << "' is not a valid response\n";
        std::cout << "If you wish to Exit, Enter \"exit now\" instead." << '\n';
        std::cout << "Please confirm whether you wish to manually enter the number of unique verticies [y/n]: ";
        getline(std::cin >> std::ws, response);
    }

    if (response.compare("exit now") == 0) {
        // Allow user to exit at any time
        std::cerr << "Exiting Program.. Goodbye!\n";
        return -1; 
    }

    if (response.compare("y") == 0) {
        // Handle user provided value for total number of unique verticies in provided graph file
        std::cout << "Please Enter the Approximate Number of Unique Verticies (or Enter \"0\" to abort): ";
        while(!(std::cin >> vertex_count) || vertex_count > INT32_MAX || vertex_count < 0) {

            // Handle when user provides a negative integer or a non-integer value
            if (std::cin.fail() || vertex_count < 0) {
                std::cerr << "Invalid Vertex Count: Number of Verticies must be a positive integer value greater than zero" << '\n';
            }
            // Handle when user provides an integer value larger than maximum size used for storage in hashmap objects
            if (vertex_count > INT32_MAX) {
                std::cerr << "Invalid Vertex Count: Number exceeding maximum acceptable integer size detected" << '\n';
            }
            // Clear failbit error flag
            std::cin.clear();
            // Discard rest of string line from standard input stream
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // Ask for user input
            std::cout << "Please Enter the Approximate Number of Unique Verticies (or Enter \"0\" to abort): ";
        }

        // Discard values after decimal point from standard input stream if floating point value was entered
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        // Convert zero values to default size of 5
        if (vertex_count == 0) {
            std::cerr << "Recognized exit value of \"0\" detected. Closing Program... Goodbye!" << '\n';
            return -1;
        }

        // Prompt user for confirmation when number of unique verticies within graph exceed 1000 before proceeding further
        if (vertex_count > 1000) {
            std::string conf_line;
            std::cout << "\nWARNING: Memory will be pre-allocated according to the provided number of total verticies to improve processing time\n";
            std::cout << "Please confirm '" << vertex_count << "' is the expected number of UNIQUE verticies: [y/n]: ";
            std::getline(std::cin >> std::ws, conf_line);
            while(conf_line.compare("y") != 0 && conf_line.compare("n") != 0) {
                std::cerr << "ERROR: The entered value of '" << conf_line << "' is not a recognized entry\n";
                std::cout << "Please enter either 'y' or 'n' to confirm whether '" << vertex_count << "' is the expected number of UNIQUE verticies within the graph to be processed: ";
                std::getline(std::cin >> std::ws, conf_line);
            }
            if (conf_line.compare("n") == 0) {
                std::cout << "\nUnintended vertex count entry confirmed.\n";
                std::cout << "You may restart the program at any time to re-enter the intended number of unique verticies within the graph to be processed. Goodbye!\n";
                return -1;
            } else {
                std::cout << "Confirmation of '" << vertex_count << "' unique verticies within the graph to be processed received!\n";
            }
        }
    }

    if (response.compare("n") == 0) {
        // Handle estimation of total number of unique verticies through line count output of `read_name` text file
        std::cout << "Estimating number of unique verticies from '" << read_name << "...\n";
        int approx_output = 0;
        approx_output = approximate_graph_vertex_count(vertex_count, read_name);
        if (approx_output < 0) {
            return -1;
        }
    }
    std::cout << '\n';
    return 0;
}


int get_shortest_path(main_hashmap<double>&& main, const std::string& graph_filename, const std::string& path_filename) {
    // Provide User with All Possible Verticies Extracted From User-Provided Graph File
    std::cout << '\n';
    std::cout << "Shortest Path Calculation Selected" << '\n';
    std::cout << "If you wish to exit the program, enter \"exit now\" at any time" << '\n';
    std::cout << '\n';
    std::string source_vertex;
    // Generated sorted list of verticies
    std::list<std::string> sorted_verts = main.get_keys();
    sorted_verts.sort();
    std::cout << "Your Verticies Include: " << sorted_verts << '\n';
    
    // Get User's Requested Source Vertex
    std::cout << "Please Enter The Source Vertex: ";
    std::getline(std::cin >> std::ws, source_vertex);
    while (!main.contains_key(source_vertex) && source_vertex.compare("exit now") != 0) {
        std::cout << '\n' << "Error: Entered Source Vertex of '" << source_vertex << "' not found Within Generated Graph." << '\n';
        std::cout << "Please try again or enter 'exit now' to exit." << '\n';
        std::cout << "Your Verticies Include: " << sorted_verts << '\n';
        std::cout << "Please Enter The Source Vertex: ";
        std::getline(std::cin >> std::ws, source_vertex);
    }
    // Get User Request for Exiting Program    
    if (source_vertex.compare("exit now") == 0) {
        std::cout << "Exiting Program... Goodbye!" << std::endl;
        return 0;
    }

    // Get User's Requested Destination Vertex
    std::string dest_vertex;
    std::cout << '\n' << "Your Verticies Include: " << sorted_verts << '\n';
    std::cout << "Please Enter The Destination Vertex: ";
    std::getline(std::cin >> std::ws, dest_vertex);
    while (!main.contains_key(dest_vertex) && dest_vertex.compare("exit now") != 0) {
        std::cout << '\n' << "Error: Entered Destination Vertex of '" << dest_vertex << "' not found Within Generated Graph. Please try again or enter 'exit now' to exit." << '\n';
        std::cout << "Your Verticies Include: " << sorted_verts << '\n';
        std::cout << "Please Enter The Destination Vertex: ";
        std::getline(std::cin >> std::ws, dest_vertex);
    }
    std::cout << '\n';
    // Get User Request for Exiting Program
    if (dest_vertex.compare("exit now") == 0) {
        std::cout << "Exiting Program... Goodbye!" << std::endl;
        return 0;
    }
    // Generate Shortest Path from user-provided graph file
    int valid_path = 0;
    try {
        valid_path = find_shortest_path(source_vertex, dest_vertex, graph_filename, path_filename, std::move(main));
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return -1;
    }

    if (valid_path < 0) {
        return -1;
    }
    return 0;
}


int get_requested_algorithm (std::string& algorithm_type, main_hashmap<double>&& main, const std::string& graph_filename, const std::string& path_filename, const std::string& MST_filename) {
    // Generate Requested Output based on User Request
    std::cout << "For Calculating the Minimum Spanning Tree, Enter \"M\"" << '\n';
    std::cout << "For Calculating the Shortest Path Between Two Verticies, Enter \"S\"" << '\n';
    std::cout << "To Exit the Program, Enter \"exit now\"" << '\n';
    std::cout << '\n' << "Please Enter Desired Graph Output: ";

    // Handle user input for type of requested calculation
    getline(std::cin >> std::ws, algorithm_type);
    while (algorithm_type.compare("M") != 0 && algorithm_type.compare("S") != 0 && algorithm_type.compare("exit now") != 0) {
        std::cout << "Error: '" << algorithm_type << "' is not an accepted value. Please try again or enter 'exit now' to exit." << '\n';
        std::cout << "Please Enter Desired Graph Output ('M' for Minimum Spanning Tree OR 'S' for Shortest Distance OR 'exit now' to exit): ";
        std::getline(std::cin >> std::ws, algorithm_type);
    }
    // User wishes to exit program
    if (algorithm_type.compare("exit now") == 0) {
        std::cout << "Exiting Program... Goodbye!" << std::endl;
        return -1;
    }

    // User wishes to have MST calculated of provided graph
    if (algorithm_type.compare("M") == 0) {
        std::cout << '\n';
        std::cout << "Minimum Spanning Tree Calculations Selected" << '\n';
        std::string start_vertex = main.get_keys().front();
        int valid_tree = 0;
        try {
            valid_tree = find_MST(start_vertex, graph_filename, MST_filename, std::move(main));
        } catch (std::exception& e) {
            std::cerr << e.what() << '\n';
        }

        if (valid_tree < 0) {
            return -1;
        }
    }

    // User wishes to have shortest path calculated using provided graph
    if (algorithm_type.compare("S") == 0) {
        int path_output = 0;
        try {
            path_output = get_shortest_path(std::move(main), graph_filename, path_filename);
        } catch (std::exception& e) {
            std::cerr << e.what() << '\n';
        }

        if (path_output < 0) {
            return -1;
        }
    }
    return 0;
}