
#pragma once
#include <iostream>
#include <vector>
#include <iterator>


template <class T, size_t N>
class vector_minheap {
    public:
        vector_minheap(): heap_size(0), array_size(0) {}
        // vector_minheap(T **array, int i): heap_size(0), array_size(i) {fill_heap(*array);} 
        // vector_minheap(T array[], int i): heap_size(0), array_size(i) {fill_heap(array);}
        vector_minheap(const T (&array)[N]): heap_size(0), array_size(N) {fill_heap(array);}
        T get_min() {
            if (heap_size == 0) {
                T empty_val = static_cast<T>(-1);
                return empty_val;
            }
            return vector_heap[0].data;
        }

        int get_heap_size() {
            return heap_size;
        }

        void fill_heap(const T *array) {
            for (size_t i = 0; i < array_size; i++) {
                T conv_val = static_cast<T>(array[i]);
                add_node(conv_val);
            }
        }

        auto return_size() {
            return vector_heap.size();
        }

        void release() {
            std::cout << "Calling minheap destructor" << '\n';
            for (int i = 0; i < heap_size; i++) {
                delete vector_heap[i];
            }
        }

        void add_node(T data) {
            // std::cout << "Heap is not empty" << '\n';
            // std::cout << "Heap size is " << heap_size << std::endl;
            it = vector_heap.begin() + heap_size;

            T data_val = static_cast<T>(data);

            // std::cout << "Allocated node struct" << '\n';
            
            
            heap_elem new_val;
            new_val.data = data_val;
            std::cout << "Assigning new val to heap " << data_val << '\n';
            vector_heap.insert(it, new_val);
            // vector_heap[heap_size].data = data_val;
            std::cout << "Assignment successfull " << '\n';
            std::cout << "start heap index " << heap_size << " = " << vector_heap[heap_size].data << '\n';
            // std::cout << "start heap previous = " << vector_heap[heap_size - 1] -> data << '\n';
            heap_size++;
            if (heap_size - 1 == 0) {
                return;
            }
            int new_val_index = heap_size - 1;  
            // std::cout << "About to enter while loop" << '\n';
            // std::cout << "new_val_index is " << new_val_index << '\n';
            
            T prox_parent_val;
            int next_parent_index = (new_val_index - 1) / 2;
            T next_parent_value = vector_heap[next_parent_index].data;
            // std::cout << "data value is " << data_val << '\n';
            // std::cout << "next_parent index is " << next_parent_index << '\n';
            // std::cout << "next parent value is " << next_parent_value << '\n';
            // std::cout << "Entering while loop" << '\n';

            // square root time complexity
            while (next_parent_index >= 0 && data_val < next_parent_value) {
                // std::cout << "parent_index is " << next_parent_index << '\n';
                prox_parent_val = next_parent_value;
                // std::cout << "next_parent_index value is " << vector_heap[next_parent_index] -> data << '\n';
                // std::cout << "new_val_index value is " <<vector_heap[new_val_index] -> data << '\n';
                vector_heap[next_parent_index].data = vector_heap[new_val_index].data;
                // std::cout << "next parent index value is now " << vector_heap[next_parent_index] -> data << '\n';
                vector_heap[new_val_index].data = prox_parent_val;
                data_val = vector_heap[next_parent_index].data;
                new_val_index = next_parent_index;
                next_parent_index = (new_val_index - 1) / 2;

                if (next_parent_index >= 0) {
                    next_parent_value = vector_heap[next_parent_index].data;
                }
            // std::cout << "While loop exited" << '\n';
            // std::cout << "First value is " << vector_heap[0] -> data << '\n';
            // std::cout << "All done" << std::endl;
            }
        }

        void min_percolate(int index) {
            int heap_length = heap_size - 1;
            int left_child_index = (index * 2) + 1;
            int right_child_index = (index * 2) + 2;
            int max_loops_req = heap_size / 2;
            int rem_index = index;
            for (int i = 0; i < max_loops_req; i++) {
                T next_element = vector_heap[rem_index].data;
                T proxy_val = next_element;
                // check if  next expected left child exists and update index if it exists
                if ( left_child_index >= 0 && left_child_index <= heap_length) {
                    left_child_index = (rem_index * 2) + 1;
                }
                // check if next expected right child exists and update index if it exists
                if ( right_child_index >= 0 && right_child_index <= heap_length) {
                    right_child_index = (rem_index * 2) + 2;
                }
                int end_check = evaluate_children(left_child_index, right_child_index, next_element, proxy_val, rem_index);
                if (end_check == 0) {
                    break;
                }
            }
            std::cout << "Percolation complete!" << std::endl; 
        }

        int evaluate_children(int left_child_index, int right_child_index, T& next_element, T& proxy_val, int& rem_index) {
            int heap_length = heap_size - 1;
            if (left_child_index >= 0 && left_child_index <= heap_length) {
                    if (right_child_index >= 0 && right_child_index <= heap_length) {
                        T left_child_value = vector_heap[left_child_index].data;
                        T right_child_value = vector_heap[right_child_index].data;

                        
                        if (left_child_value < right_child_value && next_element > left_child_value) {
                            
                            vector_heap[rem_index].data = left_child_value;
                            vector_heap[left_child_index].data = proxy_val;
                            rem_index = left_child_index;

                        } else if (right_child_value < left_child_value && next_element > right_child_value) {
                            
                            vector_heap[rem_index].data = right_child_value;
                            vector_heap[right_child_index].data = proxy_val;
                            rem_index = right_child_index;

                        } else if (right_child_value == left_child_value && next_element > left_child_value) {
                            
                            vector_heap[rem_index].data = left_child_value;
                            vector_heap[left_child_index].data = proxy_val;
                            rem_index = left_child_index;
                        } 
                        
                    } else {
                        
                        T left_child_value = vector_heap[left_child_index].data;
                        if (next_element > left_child_value) {
                            
                            vector_heap[rem_index].data = left_child_value;
                            vector_heap[left_child_index].data = proxy_val;
                            rem_index = left_child_index;
                        } 
                    }
                // check for right child
            } else if (right_child_index >= 0 && right_child_index <= heap_length) {
                T right_child_value = vector_heap[right_child_index].data;
                
                if (next_element > right_child_value) {
                    
                    vector_heap[rem_index].data = right_child_value;
                    vector_heap[right_child_index].data = proxy_val;
                    rem_index = right_child_index;
                    
                }
                // reached bottom
            } else {
                return 0;
            }
            return 1;
        }

        T remove_min() {
            // std::cout << "Got to min call" << '\n';
            T root = get_min();
            // std::cout << "Exited min call" << '\n';
            if (root == -1 && heap_size == 0) {
                std::cout << "Heap is empty!" << std::endl;
                return root;
            }
            // std::cout << "Not caught on root call" << '\n';
            // delete vector_heap[0];
            
            vector_heap[0].data = vector_heap[heap_size - 1].data;
            vector_heap.erase(vector_heap.begin() + heap_size - 1);
            heap_size--;
            // std::cout << "Got to heapsize check in with heap_size of " << heap_size << '\n';
            if (heap_size == 1) {
                return root;
            }
            // std::cout << "Entering minpercolate" << '\n';
            min_percolate(0);
            return root;
        }

        void print_usage() {
            std::cout << "USAGE: " << '\n';
            std::cout << '\t' << "EMPTY vector_minheap      -> " << "vector_minheap<double, 0> vx;" << '\n';
            std::cout << '\t' << "double arr[] = {}        -> " << "vector_minheap vc = vector_minheap<double, std::size(arr)>(arr);" << '\n';
            std::cout << '\t' << "double arr_buf[buf_size] -> " << "vector_minheap vh = vector_minheap<double, sizeof(arr_buf) / sizeof(double)>(arr_buf);" << '\n';
        }

        friend std::ostream& operator<<(std::ostream& out, const vector_minheap& mh) {
            
            out << "[ ";
            for (int i = 0; i < mh.heap_size; i++) {
                if (i == mh.heap_size - 1) {
                    out << mh.vector_heap[i].data;
                } else {
                    out << mh.vector_heap[i].data << ", ";
                }
            }
            out << " ]";
            return out;
        }
    private:
        
        int heap_size;
        size_t array_size;
        struct heap_elem {
            T data;
        };
        
        std::vector<heap_elem> vector_heap{};
        typename std::vector<heap_elem>::iterator it;
        

         
};