#pragma once

#include <iostream>
#include <iterator>
#include <vector>
#include "gprintf.hpp"

template<class Type_Name, size_t N>
class min_heap {
    public:
        min_heap(): heap_size(0), array_size(0) {}
        min_heap (const Type_Name (&array)[N]): heap_size(0), array_size(N) { fill_heap(array);}
        ~min_heap() {release();}

        Type_Name get_min() {
            if (heap_size == 0) {
                Type_Name empty_val = static_cast<Type_Name>(-1);
                return empty_val;
            }
            return start_heap[0] -> data;
        }

        int get_heap_size() {
            return heap_size;
        }

        void release() {
            gprintf("Calling minheap destructor...\n");
            for (int i = 0; i < heap_size; i++) {
                delete start_heap[i];
            }
        }

        void add_node(Type_Name data) {
            // std::cout << "Heap is not empty" << '\n';
            // std::cout << "Heap size is " << heap_size << std::endl; 
            heap_node *new_val = new heap_node;
            Type_Name data_val = static_cast<Type_Name>(data);
            // std::cout << "Allocated node struct" << '\n';
            new_val -> data = data_val;
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
            
            Type_Name prox_parent_val;
            int next_parent_index = (new_val_index - 1) / 2;
            Type_Name next_parent_value = start_heap[next_parent_index] -> data;
            // std::cout << "data value is " << data_val << '\n';
            // std::cout << "next_parent index is " << next_parent_index << '\n';
            // std::cout << "next parent value is " << next_parent_value << '\n';
            // std::cout << "Entering while loop" << '\n';

            // square root time complexity
            while (next_parent_index >= 0 && data_val < next_parent_value) {
                // std::cout << "parent_index is " << next_parent_index << '\n';
                prox_parent_val = next_parent_value;
                // std::cout << "next_parent_index value is " << start_heap[next_parent_index] -> data << '\n';
                // std::cout << "new_val_index value is " <<start_heap[new_val_index] -> data << '\n';
                start_heap[next_parent_index] -> data = start_heap[new_val_index] -> data;
                // std::cout << "next parent index value is now " << start_heap[next_parent_index] -> data << '\n';
                start_heap[new_val_index] -> data = prox_parent_val;
                data_val = start_heap[next_parent_index] -> data;
                new_val_index = next_parent_index;
                next_parent_index = (new_val_index - 1) / 2;

                if (next_parent_index >= 0) {
                    next_parent_value = start_heap[next_parent_index] -> data;
                }
            // std::cout << "While loop exited" << '\n';
            // std::cout << "First value is " << start_heap[0] -> data << '\n';
            // std::cout << "All done" << std::endl;
            }
        }


        void fill_heap(const Type_Name *array) {
            for (size_t i = 0; i < array_size; i++) {
                
                Type_Name conv_val = static_cast<Type_Name>(array[i]);
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
                Type_Name next_element = start_heap[rem_index] -> data;
                Type_Name proxy_val = next_element;
                // check if  next expected left child exists and update index if it exists
                if ( left_child_index >= 0 && left_child_index <= heap_length && start_heap[left_child_index] != nullptr) {
                    left_child_index = (rem_index * 2) + 1;
                }
                // check if next expected right child exists and update index if it exists
                if ( right_child_index >= 0 && right_child_index <= heap_length && start_heap[right_child_index] != nullptr) {
                    right_child_index = (rem_index * 2) + 2;
                }
                int end_check = evaluate_children(left_child_index, right_child_index, next_element, proxy_val, rem_index);
                if (end_check == 0) {
                    break;
                }
            }
            std::cout << "Percolation complete!" << std::endl; 
        }

        int evaluate_children(int left_child_index, int right_child_index, double& next_element, double& proxy_val, int& rem_index) {
            int heap_length = heap_size - 1;
            if (left_child_index >= 0 && left_child_index <= heap_length) {
                    if (right_child_index >= 0 && right_child_index <= heap_length) {
                        double left_child_value = start_heap[left_child_index] -> data;
                        double right_child_value = start_heap[right_child_index] -> data;

                        
                        if (left_child_value < right_child_value && next_element > left_child_value) {
                            
                            start_heap[rem_index] -> data = left_child_value;
                            start_heap[left_child_index] -> data = proxy_val;
                            rem_index = left_child_index;

                        } else if (right_child_value < left_child_value && next_element > right_child_value) {
                            
                            start_heap[rem_index] -> data = right_child_value;
                            start_heap[right_child_index] -> data = proxy_val;
                            rem_index = right_child_index;

                        } else if (right_child_value == left_child_value && next_element > left_child_value) {
                            
                            start_heap[rem_index] -> data = left_child_value;
                            start_heap[left_child_index] -> data = proxy_val;
                            rem_index = left_child_index;
                        } 
                        
                    } else {
                        
                        double left_child_value = start_heap[left_child_index] -> data;
                        if (next_element > left_child_value) {
                            
                            start_heap[rem_index] -> data = left_child_value;
                            start_heap[left_child_index] -> data = proxy_val;
                            rem_index = left_child_index;
                        } 
                    }
                // check for right child
            } else if (right_child_index >= 0 && right_child_index <= heap_length && start_heap[right_child_index] != nullptr) {
                double right_child_value = start_heap[right_child_index] -> data;
                
                if (next_element > right_child_value) {
                    
                    start_heap[rem_index] -> data = right_child_value;
                    start_heap[right_child_index] -> data = proxy_val;
                    rem_index = right_child_index;
                    
                }
                // reached bottom
            } else {
                return 0;
            }
            return 1;
        }

        Type_Name remove_min() {
            // std::cout << "Got to min call" << '\n';
            Type_Name root = get_min();
            // std::cout << "Exited min call" << '\n';
            if (root == -1 && heap_size == 0) {
                std::cout << "Heap is empty!" << std::endl;
                return root;
            }
            // std::cout << "Not caught on root call" << '\n';
            delete start_heap[0];
            start_heap[0] = start_heap[heap_size - 1];
            heap_size--;
            // std::cout << "Got to heapsize check in with heap_size of " << heap_size << '\n';
            if (heap_size == 1) {
                return root;
            }
            // std::cout << "Entering minpercolate" << '\n';
            min_percolate(0);
            return root;
        }

        void print_usage () {
            
            std::cout << "USAGE: " << '\n';
            std::cout << '\t' << "EMPTY minheap               -> " << "min_heap<double, 0> mx;" << '\n';
            std::cout << '\t' << "double arr[] = {}        -> " << "min_heap mc = min_heap<double, std::size(arr)>(arr);" << '\n';
            std::cout << '\t' << "double arr_buf[buf_size] -> " << "min_heap mh = min_heap<double, sizeof(arr_buf) / sizeof(double)>(arr_buf);" << '\n';
        }

        friend std::ostream& operator<<(std::ostream& out, const min_heap& mh) {
            out << "[ ";
            for (int i = 0; i < mh.heap_size; i++) {
                if (i == mh.heap_size - 1) {
                    out << mh.start_heap[i] -> data;
                } else {
                    out << mh.start_heap[i] -> data << ", ";
                }
            }
            out << " ]";
            return out;
        }

    private:
        int heap_size;
        size_t array_size;
        struct heap_node{
            Type_Name data;
        };
        heap_node *start_heap[BUFSIZ];
        
};


// extern min_heap<D>& build_heap(D& array);

