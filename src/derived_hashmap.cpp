#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include "../includes/derived_hashmap.hpp"


unsigned int apply_hash_function(const std::string& key) {
    unsigned int hash = 0;
    unsigned int index = 0;
    int string_length = static_cast<int>(key.size());
    // Produce integer sum from ascii character codes of string characters
    for (int i = 0; i < string_length; i++) {
        unsigned int c = static_cast<unsigned int>(key.data()[i]);
        // Multiply by incrementing index to introduce further variation
        hash += (index + 1) * c;
        index++;
    }
    return hash;
}

bool is_prime( unsigned int capacity_val) {
    // base case for the prime values of 2 and 3
    if (capacity_val == 2 || capacity_val == 3) {
        return true;
    }
    // base case for non-prime values that are inherently even or 1
    if (capacity_val == 1 || capacity_val % 2 == 0) {
        return false;
    }
    double d_capacity = static_cast<double>(capacity_val);
    double factor = 3.0;
    // Check for factors of capacity_val to determine if it is prime
    while (pow(factor, 2.0) <= d_capacity) {
        unsigned int int_cap = static_cast<unsigned int>(d_capacity);
        unsigned int int_factor = static_cast< unsigned int>(factor);
        if (int_cap % int_factor == 0 ) {
            return false;
        }
        factor += 2;
    }
    // If no other factors found, it is prime
    return true;
}

unsigned int get_next_prime(unsigned int capacity_val) {
    // Increment by value of 1 if passed value is even
    if (capacity_val % 2 == 0){
        capacity_val += 1;
    }
    // Continue incrementing value by 2 until value is found to be prime
    while (!is_prime(capacity_val)) {
        capacity_val += 2;
    }
    return capacity_val;
}
