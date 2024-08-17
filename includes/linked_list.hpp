#pragma once

#include <iostream>
#include <assert.h>

/**
 * Customized Doubly-linked List Data Structure
 * @tparam T typename of values for dl_list to hold
 * @param head First node in `dl_list`
 * @param tail Last node in `dl_list`
 * @param list_size Number of nodes currenly stored in `dl_list`
 */
template<class T>

class dl_list {

    public:
        dl_list(): head(nullptr), list_size(0) {}
        // dl_list(const T (&array)[N]): head(nullptr), list_size(N) {fill_list(array);}
        ~dl_list() {
            // gprintf("SList Destructor Called");
            release();
        }
        /**
        * Retrieves the current number of nodes stored in `dl_list` instance 
        * @return Value of `list_size` which is current number of nodes in `dl_list`
         */ 
        size_t get_size() {
            return list_size;
        }

        /**
         * Retrieves the value held by the first node (`head`) of the `dl_list` instance
         * @return Value held by first node (fails if method is called by an empty `dl_list`)
         */
        T get_front() {
            /// Notify user of error before assertion fails if no nodes exist
            if (list_size == 0) {
                std::cerr << "ERROR: List is empty!" << '\n';
            }
            assert(list_size > 0);
            return head -> data;
        }

        /**
         * Retrieves the value held by last node (`tail`) of the `dl_list` instance
         * @return Value held by last node (fails if method is called by an empty `dl_list`)
         */
        T get_back() {
            /// Notify user of error before assertion fails if no nodes exist
            if (list_size == 0) {
                std::cerr << "ERROR: List is empty!" << '\n';
            }

            assert(list_size > 0);
            return tail -> data;
        }

        /**
         * Retrieves the value held by the node preceeding the node holding the value of `c`
         *  in the calling `dl_list`.
         * @param c Value of node immediately following the node whose value is to be retrieved.
         * @return Value held by node immediately before the node holding the value of `c`
         * (fails if method is called by an empty `dl_list`)
         */
        T get_prev(T c) {
            slistelem *start = head;
            /// Notify user of error before assertion if no nodes exist
            if (list_size == 0) {
                std::cerr << "ERROR: List is empty!" << '\n';
            }
            assert(list_size > 0);
            /// Returns value held by first node if only one node exists
            if (list_size == 1 || c == head -> data){
                return head -> data;
            }

            while (start) {
                if (start ->data == c) {
                    auto prev = start -> prev;
                    return prev -> data;
                }
                start = start -> next;
            }
            /// Notify user of error before assertion if dl_list does not contain value
            if (!start) {
                std::cerr << "List does not contain '" << c << "' !" << '\n';
            }
            assert(start);
            return static_cast<T>(0);
        }

        /**
         * Retreives the value held by the node immediately preceeding the last node
         *  (`tail`) in the calling `dl_list` instance
         * @return Value held by node in front of the last node in `dl_list`
         * (fails if method is called by an empty `dl_list`)
         */
        T get_before_tail() {
            if (list_size == 0) {
                std::cerr << "List is empty!" << '\n';
            }
            assert(list_size > 0);
            /// Returns value held by first node if only one node exists
            if (list_size == 1 || list_size == 2) {
                return head -> data;
            }

            auto prev = tail -> prev;
            return prev -> data;
        }
        
        /**
         * Inserts a new node holding the value of `c` at the front of the calling `dl_list`
         * @param c Value to be held by node added at front of calling `dl_list`
         */
        void add_to_front(T c) {
            slistelem *start = head;
            slistelem *temp = new slistelem;
            temp -> data = c;
            temp -> prev = nullptr;
            switch(list_size) {
                case 0:
                    temp -> next = nullptr;
                    head = temp;
                    tail = head;
                    break;
                case 1:
                    temp -> next = start;
                    tail = head;
                    tail -> prev = temp;
                    head = temp;
                    break;
                default:
                    temp -> next = start;
                    start -> prev = temp;
                    head = temp;
            }
            list_size++;

        }
        /**
         * Inserts a new node holding the value of `c` at the end of the calling `dl_list`
         * @param c Value to be held by node added at back of calling `dl_list`
         */
        void add_to_back(T c) {
            slistelem *temp = new slistelem;
            temp -> data = c;
            temp -> next = nullptr;
            // Redirect 'next' and 'prev' pointers according to current number of nodes
            switch(list_size) {
                case 0:
                    temp -> prev = nullptr;
                    head = temp;
                    tail = head;
                    break;
                case 1:
                    assert(head == tail);
                    temp -> prev = head;
                    tail = temp;
                    head -> next = tail;
                    break;
                default:
                    auto end = tail;
                    temp -> prev = tail;
                    end -> next = temp;
                    tail = temp;
            }
            list_size++;
        }

        /**
         * Determines whether calling `dl_list` contains a node holding the value of `c`
         * @param c Value held by node to search for within `dl_list` instance
         * @return `true` if a node holding the value of `c` is found, else returns `false`
         */
        bool contains_node(T c) {
            if (list_size == 0) {
                return false;
            }

            slistelem *start = head;
            while (start) {
                if (start ->data == c) {
                    return true;
                }
                start = start -> next;
            }
            return false;
        }

        void fill_list(const T *array) {
            for (size_t i = 0; i < list_size; i++) {
                // add_to_front(&arr[i]);
                T conv_val = static_cast<T>(array[i]);
                add_to_front(conv_val);
            }
        }

        /**
         * Removes first node found in `dl_list` holding value of `c`, if found
         * @param c Value held by node to be removed from calling `dl_list`
         * @return `true` if a node holding value of `c` was found and removed, else `false`
         */
        bool remove(T c) {
            /// Returns false if dl_list is empty or has a single node holding a value other than `c`
            if (list_size == 0 || (list_size == 1 && head -> data != c)) {
                return false;
            }
            /*
            * To ensure nodes can hold values of multiple data types, the data held by 'removed' head
            * nodes are simply overridden instead of reassigned by hardcoded type-specific value.
            * 
            * 'Empty' head nodes have 'is_empty' assigned to false for identification and are
            * ignored by decrementing list_size to 0
            */ 
            if (list_size == 1 && head -> data == c) {
                head -> is_empty = true;
                head -> prev = head;
                head -> next = nullptr;
                tail = head;
                list_size--;
                return true;
            }

            auto start = head;
            auto prev = start -> next;
            if (start -> data == c) {
                delete start;
                head = prev;
                head -> prev = nullptr;
                if (head -> next == nullptr) {
                    tail = head;
                }
                list_size--;
                // std::cout << c << " removed" << '\n';
                return true;
            }

            while(start -> next) {
                auto front = start -> prev;
                prev = start;
                start = start -> next;
                if (start -> data == c) {
                    delete start;
                    prev -> prev = front;
                    prev -> next = start -> next;
                    if (start -> next == nullptr) {
                        tail = prev;
                    }
                    list_size--;
                    // std::cout << c << " removed" << '\n';
                    return true;
                }
            }
            return false;
        }


        /**
         * Removes last node (`tail`) in calling `dl_list` instance
         * @return `true` if `tail` node exists in `dl_list` and is removed, else `false`
         */
        bool remove_back() {
            bool is_removed = false;
            switch (list_size) {
                case 0:
                    break;
                case 1:
                    head -> is_empty = true;
                    tail = head;
                    list_size--;
                    is_removed = true;
                    break;
                case 2:
                    delete tail;
                    head -> next = nullptr;
                    tail = head;
                    list_size--;
                    is_removed = true;
                    break;
                default:
                    // auto end = tail;
                    auto prev = tail -> prev;
                    delete tail;
                    prev -> next = nullptr;
                    tail = prev;
                    list_size--;
                    is_removed = true;
            }
            return is_removed;
        }

        /**
         * `dl_list` destructor method for freeing all memory allocated for instance of `dl_list`
         */
        void release() {
            if (list_size == 0) {
                delete head;
                return;
            }
            slistelem *start = head;
            slistelem *prev;
            while(start -> next) {
                prev = start -> next;
                // std::cout << "Deleting " << start -> data << '\n';
                delete start;
                start = prev; 
            }
            // std::cout << "Deleting " << start -> data << '\n';
            delete start; 
            // std::cout << "List deallocated" << std::endl;
        }
        /**
         * Prints valid formats for `dl_list` class instance declarations
         */
        void print_usage () {
            std::cerr << "USAGE: " << '\n';
            std::cerr << '\t' << "EMPTY dl_list  -> " << "dl_list<typename> mx; OR auto mx = dl_list<typename> {};" << '\n';
            // std::cerr << '\t' << "double arr[] = {}        -> " << "slist mc = dl_list<double, std::size(arr)>(arr);" << '\n';
            // std::cerr << '\t' << "double arr_buf[buf_size] -> " << "slist mh = dl_list<double, sizeof(arr_buf) / sizeof(double)>(arr_buf);" << std::endl;
        }

        void print_nodes() {
            if (list_size == 0) {
                std::cout << "[]" << '\n';
                return;
            }

            slistelem *start = head;
            while (start) {
                std::cout << start -> data;
                start = start -> next;
                if (start) {
                    std::cout << " -> ";
                }
            }
            std::cout << '\n';
        }

        /**
         * Overloading function for printing the contents of any `dl_list` instance to output streams 
         */
        friend std::ostream& operator<<(std::ostream& out, const dl_list& ll) {
            slistelem *start = ll.head;
            if (ll.list_size == 0) {
                out << "[]";
                return out;
            }
            out << "[ ";
            while (start) {
                out << start -> data;
                start = start -> next;
                if (start) {
                    out << ", ";
                }
            }
            out << " ]";
            return out;

        }
    private:

        /**
         *  Node elements of `dl_list`
         * @param data Value held by this node
         * @param next Pointer referencing node immediately after this node
         * @param prev Pointer referencing node immediately before this node
         * @param is_empty Boolean value indicating whether node holds a value
         */
        struct slistelem{
            /// @brief Value held by this node
            T data;
            /// @brief Pointer referencing node immediately after this node
            slistelem *next = nullptr;
            /// @brief Pointer referencing node immediately before this node
            slistelem *prev = nullptr;
            /// @brief Boolean value indicating whether node holds a value
            bool is_empty = false;
        };
        /// @brief First element in `dl_list`
        slistelem *head = new slistelem;
        /// @brief Last element in `dl_list`
        slistelem *tail = head;
        /// @brief Current number of elements held in `dl_list`
        size_t list_size;
};