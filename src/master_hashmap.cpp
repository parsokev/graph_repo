#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include "../includes/master_hashmap.hpp"
#include "../includes/pair_minheap.hpp"


void prefill_hash_keys(master_hashmap<double>& master_hash, std::vector<std::string>& key_list, unsigned int vertex_count) {
    for (unsigned int i = 0; i < key_list.size(); i++) {
        auto new_hash  = master_hashmap<double>::oa_hashmap(vertex_count);
        master_hash.add_key(key_list[i], new_hash);
    }    
}

unsigned int apply_hash_function(const std::string& key) {
    unsigned int hash = 0;
    unsigned int index = 0;
    // const std::string::size_type string_size = key.size();

    int string_length = static_cast<int>(key.size());
    for (int i = 0; i < string_length; i++) {
        unsigned int c = static_cast<unsigned int>(key.data()[i]);
        hash += (index + 1) * c;
        index++;
    }
    return hash;

}

bool is_prime( unsigned int capacity_val) {
    
    if (capacity_val == 2 || capacity_val == 3) {
        return true;
    }

    if (capacity_val == 1 || capacity_val % 2 == 0) {
        return false;
    }
    double d_capacity = static_cast<double>(capacity_val);
    double factor = 3.0;
    while (pow(factor, 2.0) <= d_capacity) {
        unsigned int int_cap = static_cast<unsigned int>(d_capacity);
        unsigned int int_factor = static_cast< unsigned int>(factor);
        if (int_cap % int_factor == 0 ) {
            return false;
        }
        factor += 2;
    }
    return true;
}

unsigned int get_next_prime(unsigned int capacity_val) {
    if (capacity_val % 2 == 0){
        capacity_val += 1;
    }
    
    while (!is_prime(capacity_val)) {
        capacity_val += 2;
    }
    return capacity_val;
}

