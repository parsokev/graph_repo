#pragma once

#include <iostream>
#include <vector>
#include <iterator>
#include <tuple>
#include <string>
// #include "util/gprintf.h"

template<class Type, size_t N>
class paired_min_heap {
    public:
        paired_min_heap(): heap_size(0), array_size(0) {}
        // paired_min_heap(const Type (&array)[N]): heap_size(0), array_size(N) { fill_heap(array);}
        ~paired_min_heap() {release();}

        std::tuple<std::string, Type> get_min() {
            if (heap_size == 0) {
                
                Type empty_val = static_cast<Type>(-1);
                std::string empty_key = "Empty";
                std::tuple<std::string, Type> min_tuple(empty_key, empty_val);
                return min_tuple;
            }
            return start_heap[0] -> pair;
        }

        int get_heap_size() {
            return heap_size;
        }

        void release() {
            // gprintf("Calling minheap destructor");
            for (int i = 0; i < heap_size; i++) {
                delete start_heap[i];
            }
        }

        void add_node(std::string key, Type data) {
            // std::cout << "Heap is not empty" << '\n';
            // std::cout << "Heap size is " << heap_size << std::endl; 
            vertex_pair *new_val = new vertex_pair;
            Type data_val = static_cast<Type>(data);
            std::string key_val = static_cast<std::string>(key);
            std::tuple<std::string, Type> pair_val(key_val, data_val);
            // std::cout << "Allocated node struct" << '\n';
            // new_val -> data = data_val;
            // new_val -> key = key_val;
            new_val -> pair = pair_val;
            
            // std::cout << "Assigning new val to heap " << new_val -> data << '\n';
            start_heap[heap_size] = new_val;
            // std::cout << "start heap index " << heap_size << " = " << start_heap[heap_size] -> data << '\n';
            // std::cout << "start heap previous = " << start_heap[heap_size - 1] -> data << '\n';
            heap_size++;
            if (heap_size - 1 == 0) {
                return;
            }
            int new_val_index = heap_size - 1;  
            // std::cout << "About to enter while loop" << '\n';
            // std::cout << "new_val_index is " << new_val_index << '\n';
            std::string prox_parent_key;
            Type prox_parent_val;
            std::tuple<std::string, Type> prox_parent_tuple;
            Type next_parent_value;
            std::string next_parent_key;

            int next_parent_index = (new_val_index - 1) / 2;

            std::tuple<std::string, Type> next_parent_tuple = start_heap[next_parent_index] -> pair;
            std::tie(next_parent_key, next_parent_value) = next_parent_tuple;
            // std::cout << "data value is " << data_val << '\n';
            // std::cout << "next_parent index is " << next_parent_index << '\n';
            // std::cout << "next parent value is " << next_parent_value << '\n';
            // std::cout << "Entering while loop" << '\n';

            // square root time complexity
            while (next_parent_index >= 0 && data_val < next_parent_value) {
                // std::cout << "parent_index is " << next_parent_index << '\n';
                // prox_parent_val = next_parent_value;
                // prox_parent_key = next_parent_key;
                prox_parent_tuple = next_parent_tuple;
                std::tie(prox_parent_key, prox_parent_val) = prox_parent_tuple;
                // std::cout << "next_parent_index value is " << start_heap[next_parent_index] -> data << '\n';
                // std::cout << "new_val_index value is " <<start_heap[new_val_index] -> data << '\n';
                // start_heap[next_parent_index] -> data = start_heap[new_val_index] -> data;
                // start_heap[next_parent_index] -> key = start_heap[new_val_index] -> key;
                start_heap[next_parent_index] -> pair = start_heap[new_val_index] -> pair;
                // std::cout << "next parent index value is now " << start_heap[next_parent_index] -> data << '\n';
                // start_heap[new_val_index] -> data = prox_parent_val;
                // start_heap[new_val_index] -> key = prox_parent_key;
                start_heap[new_val_index] -> pair = prox_parent_tuple;

                // data_val = start_heap[next_parent_index] -> data;
                // key_val = start_heap[next_parent_index] -> key;
                pair_val = start_heap[next_parent_index] -> pair;
                std::tie(key_val, data_val) = pair_val;
                
                new_val_index = next_parent_index;
                next_parent_index = (new_val_index - 1) / 2;

                if (next_parent_index >= 0) {
                    // next_parent_value = start_heap[next_parent_index] -> data;
                    // next_parent_key = start_heap[next_parent_index] -> key;
                    next_parent_tuple = start_heap[next_parent_index] -> pair;
                    std::tie(next_parent_key, next_parent_value) = next_parent_tuple;
                }
            // std::cout << "While loop exited" << '\n';
            // std::cout << "First value is " << start_heap[0] -> data << '\n';
            // std::cout << "All done" << std::endl;
            }
        }


        void fill_heap(const Type *array) {
            for (size_t i = 0; i < array_size; i++) {
                
                Type conv_val = static_cast<Type>(array[i]);
                add_node(conv_val);
            }
        }


        void min_percolate(int index) {
            int heap_length = heap_size - 1;
            int left_child_index = (index * 2) + 1;
            int right_child_index = (index * 2) + 2;
            int max_loops_req = heap_size / 2;
            int rem_index = index;
            for (int i = 0; i < max_loops_req; i++) {
                Type next_element_val;
                std::string next_element_key;
                Type proxy_val;
                std::string proxy_key;
                // Type next_element_val = start_heap[rem_index] -> data;
                // std::string next_element_key = start_heap[rem_index] -> key;
                std::tuple<std::string, Type> next_element_tuple = start_heap[rem_index] -> pair;
                std::tie(next_element_key, next_element_val) = next_element_tuple;

                // Type proxy_val = next_element_val;
                // std::string proxy_key = next_element_key;
                std::tuple<std::string, Type> proxy_tuple = next_element_tuple;
                std::tie(proxy_key, proxy_val) = proxy_tuple;
                // check if  next expected left child exists and update index if it exists
                if ( left_child_index >= 0 && left_child_index <= heap_length && start_heap[left_child_index] != nullptr) {
                    left_child_index = (rem_index * 2) + 1;
                }
                // check if next expected right child exists and update index if it exists
                if ( right_child_index >= 0 && right_child_index <= heap_length && start_heap[right_child_index] != nullptr) {
                    right_child_index = (rem_index * 2) + 2;
                }
                int end_check = evaluate_children(left_child_index, right_child_index, next_element_val, proxy_tuple, rem_index);
                if (end_check == 0) {
                    break;
                }
            }
            // std::cout << "Percolation complete!" << std::endl; 
        }

        int evaluate_children(int left_child_index, int right_child_index, Type& next_element_val, std::tuple<std::string, Type>& proxy_tuple, int& rem_index) {
            int heap_length = heap_size - 1;
            if (left_child_index >= 0 && left_child_index <= heap_length) {
                    if (right_child_index >= 0 && right_child_index <= heap_length) {
                        Type left_child_value;
                        std::string left_child_key;
                        Type right_child_value;
                        std::string right_child_key;
                        // Type left_child_value = start_heap[left_child_index] -> data;
                        // std::string left_child_key = start_heap[left_child_index] -> key;
                        std::tuple<std::string, Type> left_child_tuple = start_heap[left_child_index] -> pair;
                        std::tie(left_child_key, left_child_value) = left_child_tuple;

                        // Type right_child_value = start_heap[right_child_index] -> data;
                        // std::string right_child_key = start_heap[right_child_index] -> key;
                        std::tuple<std::string, Type> right_child_tuple = start_heap[left_child_index] -> pair;
                        std::tie(right_child_key, right_child_value) = right_child_tuple;
                        
                        if (left_child_value < right_child_value && next_element_val > left_child_value) {
                            
                            // start_heap[rem_index] -> data = left_child_value;
                            // start_heap[rem_index] -> key = left_child_key;
                            start_heap[rem_index] -> pair = left_child_tuple;
                            

                            // start_heap[left_child_index] -> data = proxy_val;
                            // start_heap[left_child_index] -> key = proxy_key;
                            start_heap[left_child_index] -> pair = proxy_tuple;
                            rem_index = left_child_index;

                        } else if (right_child_value < left_child_value && next_element_val > right_child_value) {
                            
                            // start_heap[rem_index] -> data = right_child_value;
                            // start_heap[rem_index] -> key = right_child_key;
                            start_heap[rem_index] -> pair = right_child_tuple;

                            // start_heap[right_child_index] -> data = proxy_val;
                            // start_heap[right_child_index] -> key = proxy_key;
                            start_heap[right_child_index] -> pair = proxy_tuple;
                            rem_index = right_child_index;

                        } else if (right_child_value == left_child_value && next_element_val > left_child_value) {
                            
                            // start_heap[rem_index] -> data = left_child_value;
                            // start_heap[rem_index] -> key = left_child_key;
                            start_heap[rem_index] -> pair = left_child_tuple;

                            // start_heap[left_child_index] -> data = proxy_val;
                            // start_heap[left_child_index] -> key = proxy_key;
                            start_heap[left_child_index] -> pair = proxy_tuple;
                            rem_index = left_child_index;
                        } 
                        
                    } else {
                        Type left_child_value;
                        std::string left_child_key;
                        // Type left_child_value = start_heap[left_child_index] -> data;
                        // std::string left_child_key = start_heap[left_child_index] -> key;
                        std::tuple<std::string, Type> left_child_tuple = start_heap[left_child_index] -> pair;
                        std::tie(left_child_key, left_child_value) = left_child_tuple;
                        if (next_element_val > left_child_value) {
                            
                            // start_heap[rem_index] -> data = left_child_value;
                            // start_heap[rem_index] -> key = left_child_key;
                            start_heap[rem_index] -> pair = left_child_tuple;

                            // start_heap[left_child_index] -> data = proxy_val;
                            // start_heap[left_child_index] -> key = proxy_key;
                            start_heap[left_child_index] -> pair = proxy_tuple;
                            rem_index = left_child_index;
                        } 
                    }
                // check for right child
            } else if (right_child_index >= 0 && right_child_index <= heap_length && start_heap[right_child_index] != nullptr) {
                Type right_child_value;
                std::string right_child_key;
                // Type right_child_value = start_heap[right_child_index] -> data;
                // std::string right_child_key = start_heap[right_child_index] -> key;
                std::tuple<std::string, Type> right_child_tuple = start_heap[right_child_index] -> pair;
                std::tie(right_child_key, right_child_value) = right_child_tuple;
                if (next_element_val > right_child_value) {
                    
                    // start_heap[rem_index] -> data = right_child_value;
                    // start_heap[rem_index] -> key = right_child_key;
                    start_heap[rem_index] -> pair = right_child_tuple;

                    // start_heap[right_child_index] -> data = proxy_val;
                    // start_heap[right_child_index] -> key = proxy_key;
                    start_heap[right_child_index] -> pair = proxy_tuple;
                    rem_index = right_child_index;
                    
                }
                // reached bottom
            } else {
                return 0;
            }
            return 1;
        }

        std::tuple<std::string, Type> get_vertex(std::string key, Type value){
            return std::make_tuple(key, value);
        }

        std::tuple<std::string, Type> remove_min() {
            // std::cout << "Got to min call" << '\n';
            Type root_val;
            std::string root_key;
            std::tuple<std::string, Type> root_tuple = get_min();
            std::tie(root_key, root_val) = root_tuple;
            // std::cout << "Exited min call" << '\n';
            if (root_val == -1 && (root_key.compare("Empty") == 0) && heap_size == 0) {
                std::cout << "Heap is empty!" << std::endl;
                return root_tuple;
            }
            // std::cout << "Not caught on root call" << '\n';
            delete start_heap[0];
            start_heap[0] = start_heap[heap_size - 1];
            heap_size--;
            // std::cout << "Got to heapsize check in with heap_size of " << heap_size << '\n';
            if (heap_size == 1) {
                return root_tuple;
            }
            // std::cout << "Entering minpercolate" << '\n';
            min_percolate(0);
            return root_tuple;
        }

        void print_usage () {
            
            std::cout << "USAGE: " << '\n';
            std::cout << '\t' << "EMPTY minheap               -> " << "min_heap<double, 0> mx;" << '\n';
            std::cout << '\t' << "double arr[] = {}        -> " << "min_heap mc = min_heap<double, std::size(arr)>(arr);" << '\n';
            std::cout << '\t' << "double arr_buf[buf_size] -> " << "min_heap mh = min_heap<double, sizeof(arr_buf) / sizeof(double)>(arr_buf);" << '\n';
        }

        friend std::ostream& operator<<(std::ostream& out, const paired_min_heap& mh) {
            out << "[ ";
            for (int i = 0; i < mh.heap_size; i++) {
                std::string key_val;
                Type data_val;
                std::tie(key_val, data_val) = mh.start_heap[i] -> pair;
                if (i == mh.heap_size - 1) {
                    // out << mh.start_heap[i] -> pair;
                    out << key_val << " : " << data_val;
                    // out << mh.start_heap[i] -> key << " : " << mh.start_heap[i] -> data;
                } else {
                    // out << mh.start_heap[i] -> pair << ", ";
                    out << key_val << " : " << data_val << ", ";
                    // out << mh.start_heap[i] -> key << " : " << mh.start_heap[i] -> data << ", ";
                }
            }
            out << " ]";
            return out;
        }

    private:
        int heap_size;
        size_t array_size;
        struct vertex_pair {
            // Type data;
            // std::string key;
            std::tuple<std::string, Type> pair;
        }; 

        vertex_pair *start_heap[BUFSIZ];
        
};