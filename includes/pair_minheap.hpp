#pragma once

#include <iostream>
#include <vector>
#include <iterator>
#include <tuple>
#include <string>
#include <assert.h>
#include "../includes/gprintf.hpp"
/**
 * Customized class that utilizes its underlying storage array `start_heap` as an array representation of
 * a proper binary minimum heap structure.
 * @tparam Type typename of values for each nodes value to hold
 * @param heap_size Number of nodes currently stored in `paired_min_heap`
 * @param array_size
 * @param vertex_pair Node containing a tuple of a key : value pair
 */
template<class Type>
class paired_min_heap {
    public:
        paired_min_heap(): heap_size(0), array_size(0) {}
        // paired_min_heap(const Type (&array)[N]): heap_size(0), array_size(N) { fill_heap(array);}
        ~paired_min_heap() {release();}

        /**
         * Retreives the tuple containing the key : value pair with the minimum value within calling `paired_min_heap`
         * @return Tuple of (key, value) whose value is the smallest of all currently held in `paired_min_heap` instance.
         * Fails if calling `paired_min_heap` instance is empty.
         */
        std::tuple<std::string, Type> get_min() {
            /// Notify user of error type before assertion
            if (heap_size == 0) {
                std::cerr << "Heap is empty!" << '\n';
            }
            assert(heap_size > 0);
            return start_heap[0] -> pair;
        }

        /**
         * Retrieves the current number of key : value pairs currently stored in the `paired_min_heap` instance
         * @return Number of tuples currently held within `paired_min_heap`'s underlying storage array
         */
        int get_heap_size() {
            return heap_size;
        }

        /**
         * Determines if the calling `paired_min_heap` instance is empty
         * @return `true` if does not contain at least one key : value pair, else returns `false`
         */
        bool is_empty() {
            if (heap_size == 0) {
                return true;
            }
            return false;
        }

        /**
         * Inserts a new key : value pair as a tuple of (`key`, `data`) into the underlying storage array of the
         * `paired_min_heap` instance and rearranges the array contents until it is restored to reflect the
         * array representation of a proper minimum heap.
         * @param key String value representing the identity of the node to be inserted
         * @param value Data whose value will be used to determine the "minimum" value
         */
        void add_node(std::string key, Type data) {
            /// Fill new node with tuple of key : value pair and add to end of start_heap
            vertex_pair *new_val = new vertex_pair;
            Type data_val = data;
            std::string key_val = key;
            std::tuple<std::string, Type> pair_val(key_val, data_val);
            new_val -> pair = pair_val;
            start_heap[heap_size] = new_val;
            heap_size++;
            /// If newly added node is only stored node, no further processing is necessary
            if (heap_size - 1 == 0) {
                return;
            }
            int new_val_index = heap_size - 1;  
            /// Initialize tuple to temporarily store key : pair values during swapping operations
            std::string prox_parent_key;
            Type prox_parent_val;
            std::tuple<std::string, Type> prox_parent_tuple;
            /**
             * Calculate index position of parent node of newly added node according to array representation and
             * and extract key : pair value from its stored tuple
             */
            Type next_parent_value;
            std::string next_parent_key;
            int next_parent_index = (new_val_index - 1) / 2;
            std::tuple<std::string, Type> next_parent_tuple = start_heap[next_parent_index] -> pair;
            std::tie(next_parent_key, next_parent_value) = next_parent_tuple;
            /**
             * If the calculated index position of the parent node of the newly added node
             * is not the first index position of the `start_heap` array (0), the newly added node
             * will continue swapping index positions with each updated parent node while its new
             * index position is not 0 and its data value is less than that of its current parent
            */ 
            while (next_parent_index >= 0 && data_val < next_parent_value) {
                /// Initiate swapping operation with parent using temporary tuple
                prox_parent_tuple = next_parent_tuple;
                std::tie(prox_parent_key, prox_parent_val) = prox_parent_tuple;
                start_heap[next_parent_index] -> pair = start_heap[new_val_index] -> pair;
                start_heap[new_val_index] -> pair = prox_parent_tuple;
                pair_val = start_heap[next_parent_index] -> pair;
                std::tie(key_val, data_val) = pair_val;
                /// Recalculate and update new parent node's index position
                new_val_index = next_parent_index;
                next_parent_index = (new_val_index - 1) / 2;
                /// Update parent node's value with next index while it remains within bounds
                if (next_parent_index >= 0) {
                    next_parent_tuple = start_heap[next_parent_index] -> pair;
                    std::tie(next_parent_key, next_parent_value) = next_parent_tuple;
                }
                /// If calculated parent index is out of bounds, newly added node is at front index now
            }
        }


        /**
         * Performs percolation of node placed at index position of `index` within underlying storage array of `paired_min_heap` instance.
         * Upon completion of function, the contents of the underlying array of the calling `paired_min_heap` instance will be restored to
         * the array representation of a proper binary minimum heap.
         * @param index 
         */
        void min_percolate(int index) {
            
            int heap_length = heap_size - 1;
            /// Notify user of error type before assertion
            if (index > heap_length || index < 0) {
                std::cerr << "Passed index is out of bounds of array!" << '\n';
            }
            assert(index <= heap_length && index >= 0);
            /// Calculate left child and right child index positions according to array representation of binary minimum heap
            int left_child_index = (index * 2) + 1;
            int right_child_index = (index * 2) + 2;
            // Calculate maximum depth of current heap, which will be equal to maximum number of possible swapping operations
            int max_loops_req = heap_size / 2;
            int perc_index = index;
            // For loop iterates until percolating node has either reached maximum depth or cannot swap downward further in heap
            for (int i = 0; i < max_loops_req; i++) {
                /// Extract and store key:value pair for current position of percolating node
                std::tuple<std::string, Type> perc_element_tuple = start_heap[perc_index] -> pair;

                // Check if position of next expected left child exists and update index if it does
                if ( left_child_index >= 0 && left_child_index <= heap_length && start_heap[left_child_index] != nullptr) {
                    left_child_index = (perc_index * 2) + 1;
                }
                // Check if position of next expected right child exists and update index if it does
                if ( right_child_index >= 0 && right_child_index <= heap_length && start_heap[right_child_index] != nullptr) {
                    right_child_index = (perc_index * 2) + 2;
                }
                // #ifdef NDEBUG
                // #else
                // gprintf("PERCOLATING...");
                // #endif
                /// Pass index position and key:pair value of percolating node along with index positions of its children to helper function 
                int end_check = evaluate_children(left_child_index, right_child_index, perc_element_tuple, perc_index);
                /**
                 * If swapping function returns 0, percolation is complete and the loop is exited. Otherwise, percolation continues
                 * from updated index postion of percolating node until it reaches a position where it cannot proceed further downward
                */
                if (end_check == 0) {
                    break;
                }
            }
            // std::cout << "Percolation complete!" << std::endl; 
        }
        /**
         * Swaps positions of percolating node at index position of `perc_index` containing the key:value pair within `perc_tuple`
         * with the child node containing the minimum value if this child node has a greater value than the percolating node.
         * @param left_child_index Calculated index position of left child of percolating node
         * @param right_child_index Calculated index position of right child of percolating node
         * @param perc_tuple Tuple containing the key:value pair of the percolating node
         * @param perc_index Index position of percolating node within array representation of binary minimum heap `paired_min_heap`
         * @return 1 if percolating node has swapped positions (percolation is not complete), else 0 (percolation is complete)
         */
        int evaluate_children(int left_child_index, int right_child_index, std::tuple<std::string, Type>& perc_tuple, int& perc_index) {
            int heap_length = heap_size - 1;
            std::string perc_key;
            Type perc_val;
            std::tie(perc_key, perc_val) = perc_tuple;
            /// Check if percolating node has any children
            if (left_child_index >= 0 && left_child_index <= heap_length) {
                    /// Percolating node has a left child 
                    if (right_child_index >= 0 && right_child_index <= heap_length) {
                        /// Percolating node has both a left child node and right child node
                        Type left_child_value;
                        std::string left_child_key;
                        std::tuple<std::string, Type> left_child_tuple = start_heap[left_child_index] -> pair;
                        std::tie(left_child_key, left_child_value) = left_child_tuple;

                        Type right_child_value;
                        std::string right_child_key;
                        std::tuple<std::string, Type> right_child_tuple = start_heap[right_child_index] -> pair;
                        std::tie(right_child_key, right_child_value) = right_child_tuple;
                        // #ifdef NDEBUG
                        // #else
                        // gprintf("LEFT CHILD NODE IS %.2lf and RIGHT_CHILD_NODE IS %.2lf", left_child_value, right_child_value);
                        // #endif
                        /// If left child node has the minimum value and value of percolating node is greater than it
                        if (left_child_value < right_child_value && perc_val > left_child_value) {
                            /// Percolating node swaps positions with left child
                            start_heap[perc_index] -> pair = left_child_tuple;
                            start_heap[left_child_index] -> pair = perc_tuple;
                            perc_index = left_child_index;
                        /// If right child node has the minimum value and value of percolating node is greater than it
                        } else if (right_child_value < left_child_value && perc_val > right_child_value) {
                            /// Percolating node swaps positions with right child
                            start_heap[perc_index] -> pair = right_child_tuple;
                            start_heap[right_child_index] -> pair = perc_tuple;
                            perc_index = right_child_index;
                        /// If both child nodes contain same value and value of percolating node is greater than this value
                        } else if (right_child_value == left_child_value && perc_val > left_child_value) {
                            /// Percolating node swaps postions with left child 
                            start_heap[perc_index] -> pair = left_child_tuple;
                            start_heap[left_child_index] -> pair = perc_tuple;
                            perc_index = left_child_index;
                        } 
                    /// Percolating node has a left child but does not have a right child
                    } else {
                        Type left_child_value;
                        std::string left_child_key;
                        std::tuple<std::string, Type> left_child_tuple = start_heap[left_child_index] -> pair;
                        std::tie(left_child_key, left_child_value) = left_child_tuple;
                        /// If value of percolating node is greater than value of left child node
                        if (perc_val > left_child_value) {
                            /// Percolating node swaps postions with left child
                            start_heap[perc_index] -> pair = left_child_tuple;
                            start_heap[left_child_index] -> pair = perc_tuple;
                            perc_index = left_child_index;
                        } 
                    }
            /// If percolating node has a right child but does not have left child
            } else if (right_child_index >= 0 && right_child_index <= heap_length && start_heap[right_child_index] != nullptr) {
                Type right_child_value;
                std::string right_child_key;
                std::tuple<std::string, Type> right_child_tuple = start_heap[right_child_index] -> pair;
                std::tie(right_child_key, right_child_value) = right_child_tuple;
                /// If value of percolating node is greater than value of right child node
                if (perc_val > right_child_value) {
                    /// Percolating node swaps positions with right child
                    start_heap[perc_index] -> pair = right_child_tuple;
                    start_heap[right_child_index] -> pair = perc_tuple;
                    perc_index = right_child_index;
                }
            /// If percolating node has no child nodes or was unable to swap positions, returns 0 to indicate percolation is complete
            } else {
                return 0;
            }
            /// If percolating node has swapped positions this iteration, return 1 to indicate percolation is not complete
            return 1;
        }

        /**
         * Retrieves the tuple containing the minimum value and removes it from the calling `paired_min_heap` instance
         * @return Tuple of key : value pair containing the lowest value currently stored within the instance
         */
        std::tuple<std::string, Type> remove_min() {
            Type root_val;
            std::string root_key;
            /// Notfies user of error type before assertion
            if (heap_size == 0) {
                std::cerr << "Heap is empty!" << '\n';
            }
            assert(heap_size > 0);
            /// Retrieves tuple with minimum value (held at index 0)
            std::tuple<std::string, Type> root_tuple = get_min();
            std::tie(root_key, root_val) = root_tuple;
            /// Removes node and replaces it with node at last index position
            delete start_heap[0];
            start_heap[0] = start_heap[heap_size - 1];
            heap_size--;

            /// If replacing node is only remaining node or heap is now empty, no further processing is necessary
            if (heap_size == 0 || heap_size == 1) {
                return root_tuple;
            }
            /// If more than one node remains, percolate replacing node downward to maintain proper min heap
            min_percolate(0);
            return root_tuple;
        }

        void fill_heap(const Type *array) {
            for (size_t i = 0; i < array_size; i++) {
                
                Type conv_val = static_cast<Type>(array[i]);
                add_node(conv_val);
            }
        }

        /**
         * Destructor method of `paired_min_heap` class instances
         * Frees all memory allocated in creation of instance
         */
        void release() {
            // gprintf("Calling minheap destructor");
            for (int i = 0; i < heap_size; i++) {
                delete start_heap[i];
            }
        }        

        /**
         * Prints valid formats for `paired_min_heap` class instance declarations
         */
        void print_usage () {
            
            std::cout << "USAGE: " << '\n';
            std::cout << '\t' << "EMPTY paired_min_heap -> " << "paired_min_heap<typename> mx; OR auto mx = paired_min_heap<typename> {};" << '\n';
            // std::cout << '\t' << "double arr[] = {}        -> " << "min_heap mc = min_heap<double, std::size(arr)>(arr);" << '\n';
            // std::cout << '\t' << "double arr_buf[buf_size] -> " << "min_heap mh = min_heap<double, sizeof(arr_buf) / sizeof(double)>(arr_buf);" << '\n';
        }

        /**
         * Overloading function for printing the contents of any `paired_min_heap` instance to output streams 
         */        
        friend std::ostream& operator<<(std::ostream& out, const paired_min_heap& mh) {
            out << "[ ";
            for (int i = 0; i < mh.heap_size; i++) {
                std::string key_val;
                Type data_val;
                std::tie(key_val, data_val) = mh.start_heap[i] -> pair;
                if (i == mh.heap_size - 1) {
                    out << key_val << " : " << data_val;
                } else {
                    out << key_val << " : " << data_val << ", ";
                }
            }
            out << " ]";
            return out;
        }

    private:
        
        /// @brief Current number of nodes stored in `paired_min_heap` instance
        int heap_size;
        size_t array_size;
        /**
         *  Node elements of `paired_min_heap`
         * @param pair Tuple of a string-type "key" and numerical "value" pair
         */
        struct vertex_pair {
            std::tuple<std::string, Type> pair;
        }; 
        /// @brief  underlying storage array of `paired_min_heap` class instance
        vertex_pair *start_heap[BUFSIZ];
        
};