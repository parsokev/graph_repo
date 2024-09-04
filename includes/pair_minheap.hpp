#pragma once

#include <iostream>
#include <vector>
#include <iterator>
#include <tuple>
#include <string>
#include <cassert>
#include <memory>
#include <utility>

#include "gprintf.hpp"
#include "derived_hashmap.hpp"
#include "graph_ops.hpp"


/**
 * Customized class that utilizes its underlying storage array `start_heap` as an array representation of
 * a proper binary minimum heap structure.
 * @tparam Type typename of values for each nodes value to hold
 * @param heap_size Number of `vertex_pair` objects currently stored in `paired_min_heap`
 * @param capacity Number of `vertex_pair` objects that `paired_min_heap` has currently preallocated memory for storage
 * @param vertex_pair Node-like struct objects containing a key : value pair, `value_pair`
 * @param start_heap Underlying data storage array for storing `vertex_pair` objects
 */
template<class Type>
class paired_min_heap {
    public:
        /// Constructor for initialization with provided pre-allocation size
        paired_min_heap(unsigned int i): heap_size(0), capacity(i) {fill_heap();}
        
        /// Default zero-initializtion constructor
        paired_min_heap(): heap_size(0), capacity(5) {fill_heap();}

        /// Constructor for initialization with provided vector of key: value pairs
        paired_min_heap(std::vector<std::pair<std::string, Type>>& heap_array): heap_size(0), capacity(0) {
            start_heap.reserve(heap_array.size());
            capacity = static_cast<unsigned int>(heap_array.size());
            std::string key;
            Type value;
            for (size_t s = 0; s < heap_array.size(); s++) {
                std::tie(key, value) = heap_array[s];
                add_node(key, value);
            }
            heap_array.clear();
        }

        /// Move Constructor for paired_min_heap objects
        paired_min_heap(paired_min_heap<Type>&& old_min_heap): heap_size{std::exchange(old_min_heap.heap_size, 0)},
        capacity{std::exchange(old_min_heap.capacity, 0)},
        start_heap{std::exchange(old_min_heap.start_heap, nullptr)} {}

        /// Move operator overloading function for transferring ownership between paired_min_heap objects
        paired_min_heap<Type>& operator=(paired_min_heap<Type>&& old_min_heap) {
            heap_size = std::exchange(old_min_heap.heap_size, 0);
            capacity = std::exchange(old_min_heap.capacity, 0);
            start_heap = std::exchange(old_min_heap.start_heap, nullptr);
            return *this;
        }

        /**
         * Preallocates memory within the underlying vector-type storage array, `start_heap` of the newly-initialized
         * `paired_min_heap` object to store the user-provided number of `vertex_pair` objects (`capacity`)
         */
        void fill_heap() {
            if (capacity < 5) {
                capacity = 5;
            }
            start_heap.reserve(static_cast<size_t>(capacity));
        }

        /**
         * Retreives the tuple containing the key : value pair with the minimum value within calling `paired_min_heap`
         * @return Tuple of (key, value) whose value is the smallest of all currently held in `paired_min_heap` instance.
         * Fails if calling `paired_min_heap` instance is empty.
         */
        std::pair<std::string, Type> get_min() {
            /// Notify user of error type before assertion
            if (heap_size == 0) {
                std::cerr << "Heap is empty!" << '\n';
            }
            assert(heap_size > 0);
            return start_heap[0] -> value_pair;
        }

        /**
         * Retrieves the current number of key : value pairs currently stored in the `paired_min_heap` instance
         * @return Number of tuples currently held within `paired_min_heap`'s underlying storage array
         */
        int get_heap_size() {
            return heap_size;
        }

        /**
         * Retrieves current storage capacity of calling `paired_min_heap` object's underlying vector-type storage array
         * , `start_heap`
         * @return Current maximum number of `vertex_pair` objects that `start_heap` has preallocated memory for storing
         */
        unsigned int get_capacity() {
            return static_cast<unsigned int>(start_heap.capacity());
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
            Type data_val = data;
            std::string key_val = key;
            auto pair_val = make_pair(key_val, data_val);
            std::unique_ptr<vertex_pair> new_pair = std::make_unique<vertex_pair>(std::move(pair_val));

            #ifdef NDEBUG
            #else
            std::cerr << "ADDED NODE: " << std::get<0>(new_pair -> value_pair) << " : " << std::get<1>(new_pair -> value_pair) << '\n';
            #endif
            start_heap.emplace_back(std::move(new_pair));
            heap_size++;

            /// If newly added node is only stored node, no further processing is necessary
            if (heap_size - 1 == 0) {
                return;
            }
        
            int new_val_index = heap_size - 1;
            #ifdef NDEBUG
            #else
            std::cerr << " STARTING HEAP : " << '\n';
            std::cerr << "[ ";
            for (unsigned int k = 0; k < static_cast<unsigned int>(start_heap.size()); k++) {

                if (k == static_cast<unsigned int>(start_heap.size() - 1)) {
                    std::cerr << std::get<0>(start_heap[k] -> value_pair) << " : " << std::get<1>(start_heap[k] -> value_pair);
                } else {
                    std::cerr << std::get<0>(start_heap[k] -> value_pair) << " : " << std::get<1>(start_heap[k] -> value_pair) << ", ";
                }
            }
            std::cerr << " ]" << '\n';
            #endif  
            /// Initialize tuple to temporarily store key : pair values during swapping operations
            /**
             * Calculate index position of parent node of newly added node according to array representation and
             * and extract key : pair value from its stored tuple
             */
            int next_parent_index = (new_val_index - 1) / 2;

            auto next_parent_pair = start_heap[static_cast<size_t>(next_parent_index)] -> value_pair;
            auto prox_parent_pair = next_parent_pair;

            /**
             * If the calculated index position of the parent node of the newly added node
             * is not the first index position of the `start_heap` array (0), the newly added node
             * will continue swapping index positions with each updated parent node while its new
             * index position is not 0 and its data value is less than that of its current parent
            */
            #ifdef NDEBUG
            #else
            std::cerr << "STARTING PARENT INDEX AND NEWLY ADDED INDEX VALUES:" << '\n';
            std::cerr << "Calculated next_parent_index is " << next_parent_index << std::get<1>(start_heap[static_cast<size_t>(next_parent_index)] -> value_pair) << '\n';
            std::cerr << "Calculated new_val_index is " << new_val_index <<'\n';
            std::cerr << "next_parent_index value is " << std::get<1>(start_heap[static_cast<size_t>(next_parent_index)] -> value_pair) << '\n';
            std::cerr << "ENTERING WHILE LOOP FOR POSITION SWAPPING" << '\n';
            #endif

            size_t i = 0;
            while (next_parent_index >= 0 && data_val < std::get<1>(next_parent_pair)){
                #ifdef NDEBUG
                #else
                std::cerr << "LOOP NUMBER: " << i << '\n';
                std::cerr << "next_parent_index is " << next_parent_index << '\n';
                std::cerr << "new_val_index is " << new_val_index << '\n';
                std::cerr << "next_parent_index value is " << std::get<1>(start_heap[static_cast<size_t>(next_parent_index)] -> value_pair) << '\n';
                std::cerr << "next_parent_pair value is " << std::get<0>(next_parent_pair) << " : "  << std::get<1>(next_parent_pair)<< '\n';
                std::cerr << "prox_parent_pair value is " << std::get<0>(prox_parent_pair) << " : "  << std::get<1>(prox_parent_pair)<< '\n';
                #endif
                /// Initiate swapping operation with parent using temporary pair
                prox_parent_pair = next_parent_pair;
                
                #ifdef NDEBUG
                #else
                std::cerr << "Swapping " << std::get<0>(start_heap[static_cast<size_t>(next_parent_index)] -> value_pair) << " : " << std::get<1>(start_heap[static_cast<size_t>(next_parent_index)] -> value_pair);
                std::cerr << " with " << std::get<0>(start_heap[static_cast<size_t>(new_val_index)] -> value_pair) << " : " << std::get<1>(start_heap[static_cast<size_t>(new_val_index)] -> value_pair) << '\n';
                #endif
                
                std::swap(start_heap[static_cast<size_t>(next_parent_index)], start_heap[static_cast<size_t>(new_val_index)]);
                data_val = std::get<1>(start_heap[static_cast<size_t>(next_parent_index)] -> value_pair);
                
                /// Recalculate and update new parent node's index position
                new_val_index = next_parent_index;
                next_parent_index = (new_val_index - 1) / 2;
                #ifdef NDEBUG

                #else
                std::cerr << "Updated PARENT INDEX to " << next_parent_index << "and Updated Position of ADDED NODE INDEX to " << new_val_index << '\n';
                #endif
                /// Update parent node's value with next index while it remains within bounds
                if (next_parent_index >= 0) {
                    #ifdef NDEBUG
                    #else
                    std::cerr << "Updating next_parent_pair to " << std::get<0>(start_heap[static_cast<size_t>(next_parent_index)] -> value_pair) << " : ";
                    std::cerr << std::get<1>(start_heap[static_cast<size_t>(next_parent_index)] -> value_pair) << '\n';
                    #endif

                    next_parent_pair = start_heap[static_cast<size_t>(next_parent_index)] -> value_pair;
                }
                #ifdef NDEBUG
                #else
                std::cerr << " UPDATED HEAP at END of LOOP " << i << " : " << '\n';
                std::cerr << "[ ";
                for (unsigned int k = 0; k < static_cast<unsigned int>(start_heap.size()); k++) {
 
                    if (k == static_cast<unsigned int>(start_heap.size() - 1)) {
                        std::cerr << std::get<0>(start_heap[k] -> value_pair) << " : " << std::get<1>(start_heap[k] -> value_pair);
                    } else {
                        std::cerr << std::get<0>(start_heap[k] -> value_pair) << " : " << std::get<1>(start_heap[k] -> value_pair) << ", ";
                    }
                }
                std::cerr << " ]" << '\n';
                #endif
                i++;
            }
                /// If calculated parent index is out of bounds, newly added node is at front index now
        }
        


        // /**
        //  * Performs percolation of node placed at index position of `index` within underlying storage array of `paired_min_heap` instance.
        //  * Upon completion of function, the contents of the underlying array of the calling `paired_min_heap` instance will be restored to
        //  * the array representation of a proper binary minimum heap.
        //  * @param index 
        //  */
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
                auto perc_element_pair = start_heap[static_cast<size_t>(perc_index)] -> value_pair;

                // Check if position of next expected left child exists and update index if it does
                if ( left_child_index >= 0 && left_child_index <= heap_length) {
                    left_child_index = (perc_index * 2) + 1;
                }
                // Check if position of next expected right child exists and update index if it does
                if ( right_child_index >= 0 && right_child_index <= heap_length) {
                    right_child_index = (perc_index * 2) + 2;
                }
                #ifdef NDEBUG
                #else
                std::cerr << "PERCOLATING..." << '\n';
                #endif
                /// Pass index position and key:pair value of percolating node along with index positions of its children to helper function 
                int end_check = evaluate_children(left_child_index, right_child_index, perc_element_pair, perc_index);
                /**
                 * If swapping function returns 0, percolation is complete and the loop is exited. Otherwise, percolation continues
                 * from updated index postion of percolating node until it reaches a position where it cannot proceed further downward
                */
                if (end_check == 0) {
                    break;
                }
            }
            #ifdef NDEBUG
            #else
            std::cerr << "Percolation Complete!" << '\n';
            #endif

        }
        /**
         * Swaps positions of percolating node at index position of `perc_index` containing the key:value pair within `perc_pair`
         * with the child node containing the minimum value if this child node has a greater value than the percolating node.
         * @param left_child_index Calculated index position of left child of percolating node
         * @param right_child_index Calculated index position of right child of percolating node
         * @param perc_pair Tuple containing the key:value pair of the percolating node
         * @param perc_index Index position of percolating node within array representation of binary minimum heap `paired_min_heap`
         * @return 1 if percolating node has swapped positions (percolation is not complete), else 0 (percolation is complete)
         */
        int evaluate_children(int left_child_index, int right_child_index, std::pair<std::string, Type>& perc_pair, int& perc_index) {
            int heap_length = heap_size - 1;
            /// Check if percolating node has any children
            if (left_child_index >= 0 && left_child_index <= heap_length) {
                    /// Percolating node has a left child 
                    if (right_child_index >= 0 && right_child_index <= heap_length) {
                        /// Percolating node has both a left child node and right child node
                        std::pair<std::string, Type> left_child_pair = start_heap[static_cast<size_t>(left_child_index)] -> value_pair;
                        std::pair<std::string, Type> right_child_pair = start_heap[static_cast<size_t>(right_child_index)] -> value_pair;
                        #ifdef NDEBUG
                        #else
                        std::cerr << "LEFT CHILD NODE IS " << std::get<1>(left_child_pair) << " and RIGHT_CHILD_NODE IS " << std::get<1>(right_child_pair) << '\n';
                        #endif
                        /// If left child node has the minimum value and value of percolating node is greater than it
                        if (std::get<1>(left_child_pair) < std::get<1>(right_child_pair) && std::get<1>(perc_pair) > std::get<1>(left_child_pair)) {
                            /// Percolating node swaps positions with left child
                            std::swap(start_heap[static_cast<size_t>(perc_index)], start_heap[static_cast<size_t>(left_child_index)]);
                            perc_index = left_child_index;
                        /// If right child node has the minimum value and value of percolating node is greater than it
                        } else if (std::get<1>(right_child_pair) < std::get<1>(left_child_pair) && std::get<1>(perc_pair) > std::get<1>(right_child_pair)) {
                            /// Percolating node swaps positions with right child
                            std::swap(start_heap[static_cast<size_t>(perc_index)], start_heap[static_cast<size_t>(right_child_index)]);
                            perc_index = right_child_index;
                        /// If both child nodes contain same value and value of percolating node is greater than this value
                        } else if (std::get<1>(right_child_pair) == std::get<1>(left_child_pair) && std::get<1>(perc_pair) > std::get<1>(left_child_pair)) {
                            /// Percolating node swaps postions with left child
                            std::swap(start_heap[static_cast<size_t>(perc_index)], start_heap[static_cast<size_t>(left_child_index)]); 
                            perc_index = left_child_index;
                        } 
                    /// Percolating node has a left child but does not have a right child
                    } else {
                        std::pair<std::string, Type> left_child_pair = start_heap[static_cast<size_t>(left_child_index)] -> value_pair;
                        /// If value of percolating node is greater than value of left child node
                        if (std::get<1>(perc_pair) > std::get<1>(left_child_pair)) {
                            /// Percolating node swaps postions with left child
                            std::swap(start_heap[static_cast<size_t>(perc_index)], start_heap[static_cast<size_t>(left_child_index)]);
                            perc_index = left_child_index;
                        } 
                    }
            /// If percolating node has a right child but does not have left child
            } else if (right_child_index >= 0 && right_child_index <= heap_length) {
                std::pair<std::string, Type> right_child_pair = start_heap[static_cast<size_t>(right_child_index)] -> value_pair;
                /// If value of percolating node is greater than value of right child node
                if (std::get<1>(perc_pair) > std::get<1>(right_child_pair)) {
                    /// Percolating node swaps positions with right child
                    std::swap(start_heap[static_cast<size_t>(perc_index)], start_heap[static_cast<size_t>(right_child_index)]);
                    perc_index = right_child_index;
                }
            /// If percolating node has no child nodes or was unable to swap positions, returns 0 to indicate percolation is complete
            } else {
                return 0;
            }
            /// If percolating node has swapped positions this iteration, return 1 to indicate percolation is not complete
            return 1;
        }

        // /**
        //  * Retrieves the tuple containing the minimum value and removes it from the calling `paired_min_heap` instance
        //  * @return Tuple of key : value pair containing the lowest value currently stored within the instance
        //  */
        std::pair<std::string, Type> remove_min() {
            /// Notfies user of error type before assertion
            if (heap_size == 0) {
                std::cerr << "Heap is empty!" << std::endl;
            }
            assert(heap_size > 0);
            /// Retrieves tuple with minimum value (held at index 0)
            std::pair<std::string, Type> root_pair = get_min();
            /// Removes node and replaces it with node at last index position
            std::swap(start_heap[0], start_heap[static_cast<size_t>(heap_size - 1)]);
            start_heap.pop_back();
            heap_size--;

            /// If replacing node is only remaining node or heap is now empty, no further processing is necessary
            if (heap_size == 0 || heap_size == 1) {
                return root_pair;
            }
            /// If more than one node remains, percolate replacing node downward to maintain proper min heap
            min_percolate(0);
            return root_pair;
        }
       
        /**
         * Prints valid formats for `paired_min_heap` class instance declarations
         */
        void print_usage () {
            
            std::cout << "USAGE: " << '\n';
            std::cout << '\t' << "EMPTY paired_min_heap -> " << "paired_min_heap<typename> mx; OR auto mx = paired_min_heap<typename> {};" << '\n';
            std::cout << '\t' << "std::vector<std::pair<std::string, typename> arr[] = {}  -> " << "paired_minheap<typename> mc = min_heap<double, std::size(arr)>(arr);" << '\n';
            // std::cout << '\t' << "double arr_buf[buf_size] -> " << "min_heap mh = min_heap<double, sizeof(arr_buf) / sizeof(double)>(arr_buf);" << '\n';
        }

        /**
         * Overloading function for printing the contents of any `paired_min_heap` instance to output streams 
         */        
        friend std::ostream& operator<<(std::ostream& out, const paired_min_heap& mh) {
            out << "[ ";
            for (unsigned int i = 0; i < static_cast<unsigned int>(mh.heap_size); i++) {
                if (i == static_cast<unsigned int>(mh.heap_size - 1)) {
                    out << std::get<0>(mh.start_heap[i] -> value_pair) << " : " << std::get<1>(mh.start_heap[i] -> value_pair);
                } else {
                    out << std::get<0>(mh.start_heap[i] -> value_pair) << " : " << std::get<1>(mh.start_heap[i] -> value_pair) << ", ";
                }
            }
            out << " ]";
            return out;
        }

    private:
        
        /// @brief Current number of nodes stored in `paired_min_heap` instance
        int heap_size;
        unsigned int capacity;
        /**
         *  Node elements of `paired_min_heap`
         * @param value_pair Tuple of a string-type "key" and numerical "value" pair
         */
        struct vertex_pair {
            // std::unique_ptr<std::pair<std::string, Type>> value_pair;
            std::pair<std::string, Type> value_pair;
        }; 
        /// @brief  underlying storage array of `paired_min_heap` class instance
        std::vector<std::unique_ptr<vertex_pair>> start_heap {};
        // std::vector<vertex_pair> start_heap{};
};