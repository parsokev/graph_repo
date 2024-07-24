#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <cassert>
#include <cmath>
#include <string>
#include <typeinfo>
#include <type_traits>

#include "gprintf.hpp"


extern unsigned int apply_hash_function(const std::string& key);

extern unsigned int get_next_prime(unsigned int capacity_val);

extern bool is_prime( unsigned int capacity_val);

template<class Type>
class master_hashmap {
    
    public:
        // template<class Type>
        master_hashmap(unsigned int c): master_size(0), master_capacity(c) {fill_buckets();}
        master_hashmap(): master_size(0), master_capacity(5) {fill_buckets();}
        // master_hashmap(unsigned int c, const Type (&)array[N]): master_size(N), master_capacity(c) {fill_buckets(); fill_array(array);}
        class oa_hashmap {
            public:
                oa_hashmap(unsigned int c): size(0), capacity(c) {fill_buckets();}
                oa_hashmap(): size(0), capacity(5) {fill_buckets();}

                void fill_buckets() {
                    for (unsigned int i = 0; i < capacity; i++) {
                        hash_entry new_val;
                        hash_bucket.insert(hash_bucket.begin() + i, new_val);
                    }
                }

                unsigned int get_size() {
                    return size;
                }

                unsigned int get_capacity() {
                    return capacity;
                }

                std::vector<std::string> get_keys() {
                    return keys;
                }

                void print_keys() {                  
                    std::cout << "[ ";
                    for (unsigned int i = 0; i < keys.size(); i++) {
                        
                        if ( i == keys.size() - 1) {
                            std::cout << keys[i];
                        } else {
                            std::cout << keys[i] << ", ";
                        }
                    }
                    std::cout << " ]";
                }

                auto get_hash_bucket() {

                    return hash_bucket;
                }

                double table_load() {
                    double load_factor = static_cast<double>(size) / static_cast<double>(capacity);
                    return load_factor;
                }

                void resize_table(unsigned int new_capacity) {
                    // std::cout << "Resizing table" << '\n';
                    if (new_capacity < size) {
                        return;
                    }
                    
                    unsigned int prev_cap = capacity;
                    // unsigned int prev_cap = static_cast<unsigned int>(master_hash_bucket.size());
                    // std::cout << "Resizing table" << '\n';
                    // std::cout << "Previous capacity is " << prev_cap << '\n';
                    if (!is_prime(new_capacity)) {
                        new_capacity = get_next_prime(new_capacity);
                    }
                    // std::cout << "New capacity is " << new_capacity << '\n';
                    std::vector<hash_entry> old_heap_bucket {};
                    
                    old_heap_bucket.swap(hash_bucket);


                    capacity = new_capacity;
                    size = 0;
                    keys.clear();
                    assert(keys.empty());
                    
                    for (unsigned int i = 0; i < new_capacity; i++) {
                        hash_entry new_val;
                        hash_bucket.insert(hash_bucket.begin() + i, new_val);
                    }

                    for (unsigned int j = 0; j < prev_cap; j++) {

                        if (old_heap_bucket[j].is_empty != true  && old_heap_bucket[j].is_tombstone == false) {
                            add(old_heap_bucket[j].key, old_heap_bucket[j].value);
                        }
                    }

                }

                void add(std::string key, Type value) {
                    double tl = table_load();
                    if (tl >= 0.5) {
                        resize_table(capacity * 2);
                    }
                    unsigned int hash_func_val = apply_hash_function(key);
                    // std::cout << key << "'s returned hash function value is " << hash_func_val << '\n';
                    unsigned int hash_index = hash_func_val % capacity;
                    unsigned int j = 0;
                    unsigned int next_index = hash_index + (j * j);
                    // std::cout << "next index is " << next_index << '\n'; 
                    if (next_index >= capacity) {
                        next_index = (hash_index + (j * j)) % capacity;
                    }

                    while (hash_bucket[next_index].is_empty != true) {
                        
                        
                        if (hash_bucket[next_index].key.compare(key) == 0) {
                            // std::cout << "Found matching key of " << key << '\n';
                            hash_bucket[next_index].value = value;
                            hash_bucket[next_index].is_empty = false;
                            if (hash_bucket[next_index].is_tombstone) {
                                hash_bucket[next_index].is_tombstone = false;
                                size++;
                            }
                            return;
                        }
                        j++;
                        next_index = hash_index + (j * j);
                        if(next_index >= capacity ) {
                            next_index = (hash_index + (j*j)) % capacity;
                        }
                    }
                    // std::cout << "Adding " << key << "with value " << value << " to index " << next_index << '\n';
                    hash_entry new_val;
                    
                    new_val.key = key;
                    new_val.value = value;
                    new_val.is_empty = false;
                    hash_bucket[next_index] = new_val;

                    // std::cout << hash_bucket[next_index].value << '\n';
                    keys.push_back(key);
                    size++;

                }


                Type get_val(std::string key) {
                    if (size == 0) {
                        gprintf("Key %s contains no values!", key.c_str());
                        // return hash_bucket[0].value;
                        // std::cerr << "Key " << key << " contains no values!!" << '\n';
                    }              
                    assert(size != 0);
                    // if (size == 0) {
                    //     gprintf("Key %s contains no values!", key.c_str());
                    //     return hash_bucket[0].value;
                    //     // std::cerr << "Key " << key << " contains no values!!" << '\n';
                    // }
                    unsigned int hash_func_val = apply_hash_function(key);
                    unsigned int hash_index = hash_func_val % capacity;

                    unsigned int j = 0;
                    unsigned int next_index = hash_index + (j * j);
                    if (next_index >= capacity) {
                        next_index = (hash_index + (j * j)) % capacity;
                    }
                    while (hash_bucket[next_index].is_empty != true) {
                        if (hash_bucket[next_index].key.compare(key) == 0) {
                            if (hash_bucket[next_index].key.compare(key) == 0 && !hash_bucket[next_index].is_tombstone) {
                                break;
                                // return hash_bucket[next_index].value;
                            }
                        }
                        j++;
                        next_index = hash_index + (j * j);
                        if(next_index >= capacity ) {
                            next_index = (hash_index + (j*j)) % capacity;
                        }
                    }

                    if (hash_bucket[next_index].key.compare(key) != 0) {
                        gprintf("Hashmap for key %s was not found!", key.c_str());
                    }
                    
                    assert(hash_bucket[next_index].key.compare(key) == 0);
                    // std::cerr << "Hashmap for key " << key << " was not found!" << '\n';
                    return hash_bucket[next_index].value;
                }


                int empty_buckets() {
                    int empty_bucket_count = 0;
                    if (size == 0) {
                        empty_bucket_count = capacity;
                        return empty_bucket_count;
                    }

                    for (int i = 0; i < capacity; i++) {
                        if (hash_bucket[i].is_empty == true) {
                            empty_bucket_count++;
                        }
                    }
                    return empty_bucket_count;
                }

                bool contains_key(std::string key) {
                    if (size == 0) {
                        return false;
                    }

                    unsigned int j = 0;
                    unsigned int hash_func_val = apply_hash_function(key);
                    unsigned int hash_index = hash_func_val % capacity;
                    unsigned int next_index = hash_index + (j * j);
                    if (next_index >= capacity) {
                        next_index = (hash_index + (j * j)) % capacity;
                    }
                    
                    while (hash_bucket[next_index].is_empty != true) {
                        
                        if (hash_bucket[next_index].key.compare(key) == 0 && !hash_bucket[next_index].is_tombstone) {
                            return true;
                        }
                        j++;
                        next_index = hash_index + (j * j);
                        if (next_index >= capacity) {
                            next_index = (hash_index + (j * j)) % capacity;
                        }
                    }
                    return false;
                }

                void remove( std::string key) {
                    if (size == 0) {
                        return;
                    }
                    unsigned int hash_func_val = apply_hash_function(key);
                    unsigned int hash_index = hash_func_val % capacity;

                    int j = 0;
                    unsigned int next_index = hash_index + (j * j);
                    if (next_index >= capacity) {
                        next_index = (hash_index + (j * j)) % capacity;
                    }
                    
                    while(hash_bucket[next_index].is_empty != true) {
                        
                        if (hash_bucket[next_index].key.compare(key) == 0 && !hash_bucket[next_index].is_tombstone) {
                            hash_bucket[next_index].is_tombstone = true;
                            size--;
                            return;
                        }
                        j++;
                        next_index = hash_index + (j * j);
                        if (next_index >= capacity) {
                            next_index = (hash_index + (j *j)) % capacity;
                        }
                    }
                    return;
                }

                void clear() {
                    hash_bucket.clear();
                    keys.clear();
                    assert(hash_bucket.empty());
                    assert(keys.empty());
                    for (unsigned int i = 0; i < capacity; i++) {
                        hash_entry new_val;
                        hash_bucket.insert(hash_bucket.begin() + i, new_val);
                    }
                    size = 0;
                }

                friend std::ostream& operator<<(std::ostream& out, const oa_hashmap& hmp) {
                    out << "{ ";
                    unsigned int key_counter = 0;
                    for (unsigned int i = 0; i < hmp.capacity; i++) {
                        if (hmp.hash_bucket[i].is_empty != true && !hmp.hash_bucket[i].is_tombstone) {
                            key_counter++;
                            
                            out << hmp.hash_bucket[i].key << " : " << hmp.hash_bucket[i].value;
                            if ( key_counter != hmp.size) {
                                out << ", ";
                            }
                        }
                    }
                    out << " }";
                    return out;

                }

        
                void fill_hash_table(oa_hashmap& hash, std::string exception_val) {
                    
                    auto key_list = hash.get_keys();
                    for (unsigned int i = 0; i < key_list.size(); i++) {
                        if (key_list[i].compare(exception_val) != 0) {
                            this->add(key_list[i], hash.get_val(key_list[i]));
                            // std::cout << "Key is" << key_list[i] << " : " << hash.get_val(key_list[i]) << '\n';
                        }
                        // entry.add(hash_val.get_key(i), hash_val);
                    }
                }
                    
            private:
                unsigned int size;
                unsigned int capacity;
                struct hash_entry {
                    std::string key;
                    Type value;
                    bool is_tombstone = false;
                    bool is_empty = true;
                };

                std::vector<hash_entry> hash_bucket{};
                std::vector<std::string> keys {};
          
              
        };

        void fill_buckets() {
            for (unsigned int i = 0; i < master_capacity; i++) {
                hash_table new_val;
                master_hash_bucket.insert(master_hash_bucket.begin() + i, new_val);
            }
        }


        unsigned int get_size() {
            return master_size;
        }

        unsigned int get_capacity() {
            return master_capacity;
        }

        double table_load() {
            double load_factor = static_cast<double>(master_size) / static_cast<double>(master_capacity);
            return load_factor;
        }

        void resize_table(unsigned int new_capacity) {
            
            if (new_capacity < master_size) {
                return;
            }
            
            unsigned int prev_cap = master_capacity;
            // unsigned int prev_cap = static_cast<unsigned int>(master_hash_bucket.size());
            // std::cout << "Resizing table" << '\n';
            // std::cout << "Previous capacity is " << prev_cap << '\n';
            if (!is_prime(new_capacity)) {
                new_capacity = get_next_prime(new_capacity);
            }
            // std::cout << "New capacity is " << new_capacity << '\n';
            
            std::vector<hash_table> old_heap_bucket {};
            old_heap_bucket.swap(master_hash_bucket);

            master_capacity = new_capacity;
            master_size = 0;
            master_keys.clear();
            assert(master_keys.empty());
            // const int bucket_size = static_cast<int>(old_heap_bucket.size());
            // std::cout << "old heap bucket contains :" << '\n';
            // std::cout << "{ ";
            // for (int i = 0; i < bucket_size; i++) {
            //     if (old_heap_bucket[i].is_empty != true && i != bucket_size - 1) {
            //         std::cout << "index " << i << ": " << old_heap_bucket[i].key << " : " << old_heap_bucket[i].value << ", ";
            //     }
            //     if (old_heap_bucket[i].is_empty != true && i == bucket_size - 1) {
            //         std::cout << "index " << i << ": " << old_heap_bucket[i].key << " : " << old_heap_bucket[i].value;
            //     }
                
            // }
            // std::cout << " }" << '\n';
            
            for (unsigned int i = 0; i < new_capacity; i++) {
                hash_table new_val;
                master_hash_bucket.insert(master_hash_bucket.begin() + i, new_val);
            }

            for (unsigned int j = 0; j < prev_cap; j++) {

                if (old_heap_bucket[j].is_empty != true  && old_heap_bucket[j].is_tombstone == false) {
                    add_key(old_heap_bucket[j].master_key, old_heap_bucket[j].entry);
                }
            }
        }

        std::vector<std::string> get_master_keys() {
            return master_keys;
        }

        void print_master_keys() {
            std::cout << "[ ";
            for (unsigned int i = 0; i < master_keys.size(); i++) {
                
                if ( i == master_keys.size() - 1) {
                    std::cout << master_keys[i];
                } else {
                    std::cout << master_keys[i] << ", ";
                }
            }
            std::cout << " ]";
        }

        auto get_master_hash_bucket() {
            return master_hash_bucket;
        }

        void add_key(std::string key, oa_hashmap& hash_list) {
            double tl = table_load();
            if (tl >= 0.5) {
                resize_table(master_capacity * 2);
            }
            unsigned int hash_func_val = apply_hash_function(key);
            // std::cout << key << "'s returned hash function value is " << hash_func_val << '\n';
            unsigned int hash_index = hash_func_val % master_capacity;
            unsigned int j = 0;
            unsigned int next_index = hash_index + (j * j);

            if (next_index >= master_capacity) {
                next_index = (hash_index + (j * j)) % master_capacity;
            }

            while (master_hash_bucket[next_index].is_empty != true) {
                
                
                if (master_hash_bucket[next_index].master_key.compare(key) == 0) {
                    // std::cout << "Found matching key of " << key << '\n';

                    
                    master_hash_bucket[next_index].entry = hash_list;
                    master_hash_bucket[next_index].is_empty = false;
                    if (master_hash_bucket[next_index].is_tombstone) {
                        master_hash_bucket[next_index].is_tombstone = false;
                        master_size++;
                    }
                    return;
                }
                j++;
                next_index = hash_index + (j * j);
                if(next_index >= master_capacity ) {
                    next_index = (hash_index + (j*j)) % master_capacity;
                }
            }
            // std::cout << "Adding " << key << "with value " << value << "to index " << next_index << '\n';
            hash_table new_val;
            new_val.master_key = key;
            
            new_val.entry = hash_list;
            new_val.is_empty = false;
            
            master_hash_bucket[next_index] = new_val;
            master_keys.push_back(key);
            master_size++;
        }

        oa_hashmap& get_key_list(std::string key) {
            
            
            if (master_size == 0) {
                gprintf("Master Hashmap %s is empty!", key.c_str());
                // std::cerr << "Hashmap for key " << key << " is empty!" << '\n';
                // return master_hash_bucket[0].entry;
            }
            assert(master_size != 0);

            unsigned int hash_func_val = apply_hash_function(key);
            unsigned int hash_index = hash_func_val % master_capacity;

            unsigned int j = 0;
            unsigned int next_index = hash_index + (j * j);
            if (next_index >= master_capacity) {
                next_index = (hash_index + (j * j)) % master_capacity;
            }
            while (master_hash_bucket[next_index].is_empty != true) {
                hash_table target_val = master_hash_bucket[next_index];
                if (master_hash_bucket[next_index].master_key.compare(key) == 0) {
                    break;
                    // return master_hash_bucket[next_index].entry;
                }
                j++;
                next_index = hash_index + (j * j);
                if(next_index >= master_capacity ) {
                    next_index = (hash_index + (j*j)) % master_capacity;
                }
            }
            if (master_hash_bucket[next_index].master_key.compare(key) != 0) {
                gprintf("Master Hashmap does not contain a hashmap for %s!", key.c_str());
            }
            assert(master_hash_bucket[next_index].master_key.compare(key) == 0);
            // std::cerr << "Hashmap for key " << key << " was not found!" << '\n';
            return master_hash_bucket[next_index].entry;
        }

        Type get_key_val(std::string master_key, std::string target_key) {
            if (master_size == 0) {
                gprintf("The Master Hashmap %s is empty!", master_key.c_str());
                // std::cerr << "The hashmap " <<  master_key << " is empty!" << '\n';
                // return master_hash_bucket[0].entry.get_val(target_key); 
            }

            assert(master_size != 0);
            
            unsigned int hash_func_val = apply_hash_function(master_key);
            unsigned int hash_index = hash_func_val % master_capacity;

            unsigned int j = 0;
            unsigned int next_index = hash_index + (j * j);
            if (next_index >= master_capacity) {
                next_index = (hash_index + (j * j)) % master_capacity;
            }
            while (master_hash_bucket[next_index].is_empty != true) {
                hash_table target_val = master_hash_bucket[next_index];
                if (master_hash_bucket[next_index].master_key.compare(master_key) == 0) {
                    // oa_hashmap target_val = master_hash_bucket[next_index].entry;
                    // std::cout << target_val << '\n';
                    break;
                    // return master_hash_bucket[next_index].entry.get_val(target_key);
                }
                j++;
                next_index = hash_index + (j * j);
                if(next_index >= master_capacity ) {
                    next_index = (hash_index + (j*j)) % master_capacity;
                }
            }
            if (master_hash_bucket[next_index].master_key.compare(master_key) != 0) {
                gprintf("The key %s does not exist in %s", target_key.c_str(), master_key.c_str());
            }
            assert(master_hash_bucket[next_index].master_key.compare(master_key) == 0);
            // gprintf("The key %s does not exist in %s", target_key.c_str(), master_key.c_str());
            // std::cerr << "The key " << target_key << " does not exist in " <<  master_key << '\n';
            return master_hash_bucket[next_index].entry.get_val(master_key);
        }
        

        std::string get_key_by_val(std::string master_key, Type value) {
            // std::string failure = "";
            if (master_size == 0) {
                gprintf(" Master Hashmap %s is empty!", master_key.c_str());                
                // return failure;
            }

            assert(master_size != 0);

            unsigned int hash_func_val = apply_hash_function(master_key);
            unsigned int hash_index = hash_func_val % master_capacity;

            unsigned int j = 0;
            unsigned int next_index = hash_index + (j * j);
            if (next_index >= master_capacity) {
                next_index = (hash_index + (j * j)) % master_capacity;
            }
            unsigned int l = 0;
            auto entry_hash = master_hash_bucket[next_index].entry.get_hash_bucket();
            while (master_hash_bucket[next_index].is_empty != true) {
                // hash_table target_val = master_hash_bucket[next_index];
                if (master_hash_bucket[next_index].master_key.compare(master_key) == 0) {
                    // oa_hashmap target_val = master_hash_bucket[next_index].entry;
                    // std::cout << target_val << '\n';
                    entry_hash = master_hash_bucket[next_index].entry.get_hash_bucket();
                    // auto entry_hash = master_hash_bucket[next_index].entry.get_hash_bucket();
                    unsigned int entry_capacity = static_cast<unsigned int>(master_hash_bucket[next_index].entry.get_capacity());
                    
                    for (unsigned int k = 0; k <  entry_capacity; k++) {
                        if (entry_hash[k].is_empty != true && !entry_hash[k].is_tombstone) {
                            if (entry_hash[k].value == value) {
                                l = k;
                                break;
                                // return entry_hash[k].key;
                            }
                        }
                    }

                }
                j++;
                next_index = hash_index + (j * j);
                if(next_index >= master_capacity ) {
                    next_index = (hash_index + (j*j)) % master_capacity;
                }
            }
            if (entry_hash[l].value != value) {
                gprintf("Master Hashmap does not contain any keys of %s with argument value!", master_key.c_str());
            }
            assert(entry_hash[l].value == value);
            // gprintf("Hashmap for key %s was not found!", master_key.c_str());
            
            return entry_hash[l].key;
        }
    
        

        int empty_buckets() {
            int empty_bucket_count = 0;
            if (master_size == 0) {
                empty_bucket_count = master_capacity;
                return empty_bucket_count;
            }

            for (int i = 0; i < master_capacity; i++) {
                if (master_hash_bucket[i].is_empty == true) {
                    empty_bucket_count++;
                }
            }
            return empty_bucket_count;
        }

        bool contains_key(std::string key) {
            if (master_size == 0) {
                return false;
            }

            unsigned int j = 0;
            unsigned int hash_func_val = apply_hash_function(key);
            unsigned int hash_index = hash_func_val % master_capacity;
            unsigned int next_index = hash_index + (j * j);
            if (next_index >= master_capacity) {
                next_index = (hash_index + (j * j)) % master_capacity;
            }
            
            while (master_hash_bucket[next_index].is_empty != true) {
                
                if (master_hash_bucket[next_index].master_key.compare(key) == 0 && !master_hash_bucket[next_index].is_tombstone) {
                    return true;
                }
                j++;
                next_index = hash_index + (j * j);
                if (next_index >= master_capacity) {
                    next_index = (hash_index + (j * j)) % master_capacity;
                }
            }
            return false;
        }

        void remove( std::string key) {
            if (master_size == 0) {
                return;
            }
            unsigned int hash_func_val = apply_hash_function(key);
            unsigned int hash_index = hash_func_val % master_capacity;

            int j = 0;
            unsigned int next_index = hash_index + (j * j);
            if (next_index >= master_capacity) {
                next_index = (hash_index + (j * j)) % master_capacity;
            }
            
            while(master_hash_bucket[next_index].is_empty != true) {
                
                if (master_hash_bucket[next_index].master_key.compare(key) == 0 && !master_hash_bucket[next_index].is_tombstone) {
                    master_hash_bucket[next_index].is_tombstone = true;
                    master_size--;
                    return;
                }
                j++;
                next_index = hash_index + (j * j);
                if (next_index >= master_capacity) {
                    next_index = (hash_index + (j *j)) % master_capacity;
                }
            }
            return;
        }

        void clear() {
            master_keys.clear();
            master_hash_bucket.clear();
            assert(master_hash_bucket.empty());
            assert(master_keys.empty());
            for (unsigned int i = 0; i < master_capacity; i++) {
                hash_table new_val;
                master_hash_bucket.insert(master_hash_bucket.begin() + i, new_val);
            }
            master_size = 0;
        }

        friend std::ostream& operator<<(std::ostream& out, const master_hashmap<Type>& hmp) {
            out << "{ ";
            unsigned int key_counter = 0;
            for (unsigned int i = 0; i < hmp.master_capacity; i++) {
                
                if (hmp.master_hash_bucket[i].is_empty != true && !hmp.master_hash_bucket[i].is_tombstone) {
                    key_counter++;
                    out << hmp.master_hash_bucket[i].master_key << " : " << hmp.master_hash_bucket[i].entry;
                    if ( key_counter != hmp.master_size) {
                        out << ", ";
                    }
                }
            }
            out << " }";
            return out;
        }

    private:
        
        unsigned int master_size;
        unsigned int master_capacity;
        struct hash_table {
            std::string master_key;
            oa_hashmap entry = oa_hashmap();
            
            bool is_tombstone = false;
            bool is_empty = true;
        };
        std::vector<std::string> master_keys {};
        std::vector<hash_table> master_hash_bucket{};
        
};

extern void prefill_hash_keys(master_hashmap<std::string>& master_hash, std::vector<std::string>& key_list, unsigned int vertex_count);