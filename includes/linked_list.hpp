#pragma once

#include <iostream>
#include <assert.h>
// #include "util/gprintf.h"
template<class T, size_t N>
class dl_list {
    public:
        dl_list(): head(nullptr), list_size(0) {}
        // dl_list(const T (&array)[N]): head(nullptr), list_size(N) {fill_list(array);}
        ~dl_list() {
            // gprintf("SList Destructor Called");
            release();
        }

        size_t get_size() {
            return list_size;
        }
        
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

        void add_to_back(T c) {
            // slistelem *start = tail;
            slistelem *temp = new slistelem;
            temp -> data = c;
            temp -> next = nullptr;
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



        bool contains_node(T c) {
            slistelem *start = head;
            // auto prev = head -> prev;
            while (start) {
                if (start ->data == c) {
                    return true;
                }
                // prev = start -> prev;
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

        bool remove(T c) {
            if (head -> next == nullptr && head -> data != c) {
                return false;
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

        T get_front() {
            return head -> data;
        }

        T get_back() {
            return tail -> data;
        }

        T get_prev(T c) {
            slistelem *start = head;
            // auto prev = head -> prev;
            while (start) {
                if (start ->data == c) {
                    auto prev = start -> prev;
                    return prev -> data;
                }
                // prev = start -> prev;
                start = start -> next;
            }

            return static_cast<T>(0);
        
        }

        T get_before_tail() {
            auto prev = tail -> prev;
            return prev -> data;
        }

        bool remove_back() {
            
            bool is_removed = false;
            switch (list_size) {
                case 0:
                    break;
                case 1:
                    head -> data = "";
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

        void release() {
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

        void print_usage () {
            std::cerr << "USAGE: " << '\n';
            std::cerr << '\t' << "EMPTY slist              -> " << "slist<double, 0> mx;" << '\n';
            std::cerr << '\t' << "double arr[] = {}        -> " << "slist mc = slist<double, std::size(arr)>(arr);" << '\n';
            std::cerr << '\t' << "double arr_buf[buf_size] -> " << "slist mh = slist<double, sizeof(arr_buf) / sizeof(double)>(arr_buf);" << std::endl;
        }

        friend std::ostream& operator<<(std::ostream& out, const dl_list& ll) {
            slistelem *start = ll.head;
            while (start) {
                if (start -> data.compare("") == 0) {
                    out << "[]";
                    return out;
                }
                out << start -> data;
                start = start -> next;
                if (start) {
                    out << " -> ";
                }
            }
            // out << "NULL";
            return out;

        }
    private:
        
        struct slistelem{
            T data;
            slistelem *next = nullptr;
            slistelem *prev = nullptr;
        };
        slistelem *head = new slistelem;
        slistelem *tail = head;
        size_t list_size;
};