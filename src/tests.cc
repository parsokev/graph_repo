#include <gtest/gtest.h>
#include <stdexcept>
#include <tuple>

#include "../includes/pair_minheap.hpp"
#include "../src/gprintf.cpp"
#include "../src/derived_hashmap.cpp"


// ==================================================== PAIRED_MIN_HEAP CLASS TESTING ==================================================================

// Test Suite test_PMNHP: MINIMUM BINARY HEAP OF KEY:VALUE PAIR NODES Functions
// Test paired_min_heap

// Test 1: Test get_heap_size
// Test 2: Test add_node
// Test 3: Test min_percolate/evaluate_children
// Test 4: Test remove_min
// Test 5: Test paired_min_heap constructor(s)


// Test function responsible for reporting the current number of key:value pairs currently stored in heap
TEST(test_PRMNHP, test_get_heap_size) {
    auto test_heap = paired_min_heap<double>(5);
    EXPECT_EQ(test_heap.get_heap_size(), 0);
    test_heap.add_node("first_node", 0);
    EXPECT_EQ(test_heap.get_heap_size(), 1);
    test_heap.add_node("second_node", 3);
    EXPECT_EQ(test_heap.get_heap_size(), 2);
}


// Test function responsible for returning (but not removing) the key:value pair with minimum value currently within heap
TEST(test_PRMNHP, test_get_min) {
    auto test_heap = paired_min_heap<double>(5);
    EXPECT_THROW({
        try {
            test_heap.get_min();
        } catch (const std::exception& e) {
            EXPECT_STREQ("ERROR: Cannot return minimum value of an empty paired_minheap object!\n", e.what());
            throw;
        }
    }, std::exception);
    // Stop test if heap is improperly initialized or fials to report size properly
    ASSERT_EQ(test_heap.get_heap_size(), 0);
    test_heap.add_node("zero_node", 10);
    // Cancel test if ADD_NODE is working improperly
    ASSERT_EQ(test_heap.get_heap_size(), 1);
    test_heap.add_node("first_node", 2);
    EXPECT_EQ(test_heap.get_heap_size(), 2);
    test_heap.add_node("second_node", 3);
    EXPECT_EQ(test_heap.get_heap_size(), 3);
    std::string key;
    double value;
    std::tie(key, value) = test_heap.get_min();
    EXPECT_EQ(key, "first_node");
    EXPECT_EQ(value, 2);
    EXPECT_EQ(test_heap.get_heap_size(), 3);
    test_heap.add_node("third_node", 1);
    EXPECT_EQ(test_heap.get_heap_size(), 4);
    std::tie(key, value) = test_heap.get_min();
    EXPECT_EQ(key, "third_node");
    EXPECT_EQ(value, 1);
    EXPECT_EQ(test_heap.get_heap_size(), 4);
    std::tie(key, value) = test_heap.get_min();
    EXPECT_EQ(key, "third_node");
    EXPECT_EQ(value, 1);
    EXPECT_EQ(test_heap.get_heap_size(), 4);
    std::tie(key, value) = test_heap.get_min();
    EXPECT_EQ(key, "third_node");
    EXPECT_EQ(value, 1);
    EXPECT_EQ(test_heap.get_heap_size(), 4);
}


// Test function responsible for adding new key : value pairs to heap storage
TEST(test_PRMNHP, test_add_node) {
    auto test_heap = paired_min_heap<double>(5);
    EXPECT_EQ(test_heap.get_heap_size(), 0);
    test_heap.add_node("first_node", 5);
    // If heap_size reporter is inconsistent, subsequent tests are fruitless
    ASSERT_EQ(test_heap.get_heap_size(), 1);
    std::string key;
    double value;
    std::tie(key, value) = test_heap.get_min();
    // If first value retrieval fails, subsequent tests are fruitless
    ASSERT_EQ(key, "first_node");
    EXPECT_EQ(value, 5);
    test_heap.add_node("second_node", 3);
    std::tie(key, value) = test_heap.get_min();
    EXPECT_EQ(key, "second_node");
    EXPECT_EQ(value, 3);
    EXPECT_EQ(test_heap.get_heap_size(), 2);
    test_heap.add_node("third_node", 2);
    std::tie(key, value) = test_heap.get_min();
    EXPECT_EQ(key, "third_node");
    EXPECT_EQ(value, 2);
    EXPECT_EQ(test_heap.get_heap_size(), 3);
}


// Test function reponsible for restoring inner storage array to proper minimum heap after removal minumum key:value pair
TEST(test_PRMNHP, test_min_percolate) {
    auto test_heap = paired_min_heap<double>(5);
    test_heap.add_node("first_node", 5);
    test_heap.add_node("second_node", 10);
    test_heap.add_node("third_node", 3);
    test_heap.add_node("fourth_node", 2);
    std::string key;
    double value;
    std::tie(key, value) = test_heap.get_min();
    // If GET_MIN fails to retrieve initially key with minimum value, subsequent tests are fruitless
    ASSERT_EQ("fourth_node", key);
    EXPECT_EQ(value, 2);
    test_heap.min_percolate(0);
    std::tie(key, value) = test_heap.get_min();
    EXPECT_EQ("fourth_node", key);
    EXPECT_EQ(value, 2);
    test_heap.min_percolate(1);
    std::tie(key, value) = test_heap.get_min();
    EXPECT_EQ("fourth_node", key);
    EXPECT_EQ(value, 2);
    test_heap.min_percolate(2);
    std::tie(key, value) = test_heap.get_min();
    EXPECT_EQ("fourth_node", key);
    EXPECT_EQ(value, 2);
    test_heap.min_percolate(3);
    std::tie(key, value) = test_heap.get_min();
    EXPECT_EQ("fourth_node", key);
    EXPECT_EQ(value, 2);
    EXPECT_THROW({
        try {
            test_heap.min_percolate(4);
        } catch (const std::exception& e) {
            EXPECT_STREQ("ERROR: Index to be percolated is outside the bounds of the heap array!", e.what());
            throw;
        }
    }, std::exception);
    EXPECT_THROW({
        try {
            test_heap.min_percolate(-1);
        } catch (const std::exception& e) {
            EXPECT_STREQ("ERROR: Index to be percolated is outside the bounds of the heap array!", e.what());
            throw;
        }
    }, std::exception);
}


// Test function for removing/popping and returning key with minimum value
TEST(test_PRMNHP, test_remove_min) {
    auto test_heap = paired_min_heap<double>(-1);
    ASSERT_EQ(test_heap.get_capacity(), 5);
    test_heap.add_node("first_node", 5);
    test_heap.add_node("second_node", 10);
    test_heap.add_node("third_node", 3);
    test_heap.add_node("fourth_node", 2);
    test_heap.add_node("fifth_node", 0);
    test_heap.add_node("sixth_node", 20);
    EXPECT_EQ(test_heap.get_heap_size(), 6);
    std::string key;
    double value;
    std::string removed_key;
    double removed_value;
    std::tie(key, value) = test_heap.get_min();
    // If GET_MIN fails to retrieve initially key with minimum value, subsequent tests are fruitless
    ASSERT_EQ("fifth_node", key);
    EXPECT_EQ(value, 0);
    std::tie(removed_key, removed_value) = test_heap.remove_min();
    EXPECT_EQ(test_heap.get_heap_size(), 5);
    EXPECT_EQ(removed_key, "fifth_node");
    EXPECT_EQ(removed_value, 0);
    std::tie(removed_key, removed_value) = test_heap.remove_min();
    EXPECT_EQ(test_heap.get_heap_size(), 4);
    EXPECT_EQ(removed_key, "fourth_node");
    EXPECT_EQ(removed_value, 2);
    std::tie(removed_key, removed_value) = test_heap.remove_min();
    EXPECT_EQ(test_heap.get_heap_size(), 3);
    EXPECT_EQ(removed_key, "third_node");
    EXPECT_EQ(removed_value, 3);
    std::tie(removed_key, removed_value) = test_heap.remove_min();
    EXPECT_EQ(test_heap.get_heap_size(), 2);
    EXPECT_EQ(removed_key, "first_node");
    EXPECT_EQ(removed_value, 5);
    std::tie(removed_key, removed_value) = test_heap.remove_min();
    EXPECT_EQ(test_heap.get_heap_size(), 1);
    EXPECT_EQ(removed_key, "second_node");
    EXPECT_EQ(removed_value, 10);
    std::tie(removed_key, removed_value) = test_heap.remove_min();
    EXPECT_EQ(test_heap.get_heap_size(), 0);
    EXPECT_EQ(removed_key, "sixth_node");
    EXPECT_EQ(removed_value, 20);
    EXPECT_THROW({
        try {
            test_heap.remove_min();
        } catch (const std::exception& e) {
            EXPECT_STREQ("ERROR: Cannot remove minimum value from an empty paired_minheap object!", e.what());
            throw;
        }
    }, std::exception);   
}


// Test paired_min_heap constructor for initializing object instance with no preset capacity
TEST(test_PRMNHP, test_zero_initialization_constructor) {
    auto test_heap = paired_min_heap<double>{};
    EXPECT_EQ(test_heap.get_heap_size(), 0);
    EXPECT_EQ(test_heap.get_capacity(), 5);
}


// Test paired_min_heap constructor for initializing object instance with a preset storage capacity
TEST(test_PRMNHP, test_heap_capacity_constructor) {
    auto min_heap = std::make_unique<paired_min_heap<double>>(16);
    // Cease subsequent tests if intialization settings are incorrect
    ASSERT_EQ(min_heap -> get_heap_size(), 0);
    ASSERT_EQ(min_heap -> get_capacity(), 16);
    min_heap -> add_node("Miami", 25.0);
    min_heap -> add_node("Harvard", 2.0);
    min_heap -> add_node("Los Angeles", 15.3);
    min_heap -> add_node("New York", 3.6);
    min_heap -> add_node("Fresno", 10.0);
    min_heap -> add_node("Redding", 1.3);
    min_heap -> add_node("San Francisco", 50.2);
    min_heap -> add_node("Las Vegas", 14.0);
    min_heap -> add_node("Detroit", 70.4);
    min_heap -> add_node("Medford", 14.7);
    min_heap -> add_node("Dallas", 34.1);
    min_heap -> add_node("Phoenix", 24.3);
    min_heap -> add_node("Seattle", 47.6);
    min_heap -> add_node("Portland", 18.9);
    min_heap -> add_node("Orlando", 100.5);
    min_heap -> add_node("Colorado Springs", 56.8);
    // Cease subsequent tests if ADD_NODE is failing
    ASSERT_EQ(min_heap -> get_heap_size(), 16);
    std::string key;
    double value;
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Redding");
    EXPECT_EQ(value, 1.3);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Harvard");
    EXPECT_EQ(value, 2.0);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "New York");
    EXPECT_EQ(value, 3.6);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Fresno");
    EXPECT_EQ(value, 10.0);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Las Vegas");
    EXPECT_EQ(value, 14.0);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Medford");
    EXPECT_EQ(value, 14.7);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Los Angeles");
    EXPECT_EQ(value, 15.3);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Portland");
    EXPECT_EQ(value, 18.9);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Phoenix");
    EXPECT_EQ(value, 24.3);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Miami");
    EXPECT_EQ(value, 25.0);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Dallas");
    EXPECT_EQ(value, 34.1);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Seattle");
    EXPECT_EQ(value, 47.6);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "San Francisco");
    EXPECT_EQ(value, 50.2);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Colorado Springs");
    EXPECT_EQ(value, 56.8);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Detroit");
    EXPECT_EQ(value, 70.4);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Orlando");
    EXPECT_EQ(value, 100.5);
    EXPECT_EQ(min_heap -> get_heap_size(), 0);
    EXPECT_THROW({
        try {
            min_heap ->remove_min();
        } catch (const std::exception& e) {
            EXPECT_STREQ("ERROR: Cannot remove minimum value from an empty paired_minheap object!", e.what());
            throw;
        }
    }, std::exception);
    EXPECT_THROW({
    try {
        min_heap -> get_min();
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: Cannot return minimum value of an empty paired_minheap object!\n", e.what());
        throw;
    }
    }, std::exception);   
}


// Test paired_min_heap constructor for initializing object instance that is passed a vector of key : value pairs
TEST(test_PRMNHP, test_heap_vector_constructor) {
    auto miami = std::make_pair("Miami", 25.0);
    auto harvard = std::make_pair("Harvard", 2.0);
    auto los_angeles = std::make_pair("Los Angeles", 15.3);
    auto new_york = std::make_pair("New York", 3.6);
    auto fresno = std::make_pair("Fresno", 10.0);
    auto redding = std::make_pair("Redding", 1.3);
    auto san_francisco = std::make_pair("San Francisco", 50.2);
    auto las_vegas = std::make_pair("Las Vegas", 14.0);
    auto detroit = std::make_pair("Detroit", 70.4);
    auto medford = std::make_pair("Medford", 14.7);
    auto dallas = std::make_pair("Dallas", 34.1);
    auto phoenix = std::make_pair("Phoenix", 24.3);
    auto seattle = std::make_pair("Seattle", 47.6);
    auto portland = std::make_pair("Portland", 18.9);
    auto orlando = std::make_pair("Orlando", 100.5);
    auto colorado_springs = std::make_pair("Colorado Springs", 56.8);
    std::vector<std::pair<std::string, double>> hash_pairs = {miami, harvard, los_angeles, new_york, fresno, redding, san_francisco, las_vegas, detroit, medford, dallas, phoenix, seattle, portland, orlando, colorado_springs};
    auto min_heap = std::make_unique<paired_min_heap<double>>(hash_pairs);
    // If vector is not properly moved into paired_min_heap, subsequent tests are fruitless
    ASSERT_EQ(min_heap -> get_heap_size(), 16);
    std::string key;
    double value;
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Redding");
    EXPECT_EQ(value, 1.3);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Harvard");
    EXPECT_EQ(value, 2.0);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "New York");
    EXPECT_EQ(value, 3.6);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Fresno");
    EXPECT_EQ(value, 10.0);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Las Vegas");
    EXPECT_EQ(value, 14.0);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Medford");
    EXPECT_EQ(value, 14.7);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Los Angeles");
    EXPECT_EQ(value, 15.3);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Portland");
    EXPECT_EQ(value, 18.9);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Phoenix");
    EXPECT_EQ(value, 24.3);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Miami");
    EXPECT_EQ(value, 25.0);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Dallas");
    EXPECT_EQ(value, 34.1);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Seattle");
    EXPECT_EQ(value, 47.6);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "San Francisco");
    EXPECT_EQ(value, 50.2);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Colorado Springs");
    EXPECT_EQ(value, 56.8);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Detroit");
    EXPECT_EQ(value, 70.4);
    std::tie(key, value) = min_heap -> remove_min();
    EXPECT_EQ(key, "Orlando");
    EXPECT_EQ(value, 100.5);
    EXPECT_EQ(min_heap -> get_heap_size(), 0);
}



TEST(test_PRMNHP, test_heap_move_constructor) {
    auto min_heap = std::make_unique<paired_min_heap<double>>(16);
    // Cease further tests if initialization fails
    ASSERT_EQ(min_heap -> get_heap_size(), 0);
    ASSERT_EQ(min_heap -> get_capacity(), 16);
    min_heap -> add_node("Miami", 25.0);
    min_heap -> add_node("Harvard", 2.0);
    min_heap -> add_node("Los Angeles", 15.3);
    min_heap -> add_node("New York", 3.6);
    min_heap -> add_node("Fresno", 10.0);
    min_heap -> add_node("Redding", 1.3);
    min_heap -> add_node("San Francisco", 50.2);
    min_heap -> add_node("Las Vegas", 14.0);
    min_heap -> add_node("Detroit", 70.4);
    min_heap -> add_node("Medford", 14.7);
    min_heap -> add_node("Dallas", 34.1);
    min_heap -> add_node("Phoenix", 24.3);
    min_heap -> add_node("Seattle", 47.6);
    min_heap -> add_node("Portland", 18.9);
    min_heap -> add_node("Orlando", 100.5);
    min_heap -> add_node("Colorado Springs", 56.8);
    // Cease further tests if ADD_NODE fails to perform correctly
    ASSERT_EQ(min_heap -> get_heap_size(), 16);
    auto transfer_heap = std::move(min_heap);
    // Cease further tests if Move constructor fails to perform correctly
    ASSERT_EQ(transfer_heap -> get_heap_size(), 16);
    transfer_heap -> add_node("Ontario", 600.5);
    transfer_heap -> add_node("London", 2000.5);
    // Cease further tests if Move constructor fails or error in referencing
    ASSERT_EQ(transfer_heap -> get_heap_size(), 18);
    std::string key;
    double value;
    std::tie(key, value) = transfer_heap -> remove_min();
    EXPECT_EQ(key, "Redding");
    EXPECT_EQ(value, 1.3);
    std::tie(key, value) = transfer_heap -> remove_min();
    EXPECT_EQ(key, "Harvard");
    EXPECT_EQ(value, 2.0);
    std::tie(key, value) = transfer_heap -> remove_min();
    EXPECT_EQ(key, "New York");
    EXPECT_EQ(value, 3.6);
    std::tie(key, value) = transfer_heap -> remove_min();
    EXPECT_EQ(key, "Fresno");
    EXPECT_EQ(value, 10.0);
    std::tie(key, value) = transfer_heap -> remove_min();
    EXPECT_EQ(key, "Las Vegas");
    EXPECT_EQ(value, 14.0);
    std::tie(key, value) = transfer_heap -> remove_min();
    EXPECT_EQ(key, "Medford");
    EXPECT_EQ(value, 14.7);
    std::tie(key, value) = transfer_heap -> remove_min();
    EXPECT_EQ(key, "Los Angeles");
    EXPECT_EQ(value, 15.3);
    std::tie(key, value) = transfer_heap -> remove_min();
    EXPECT_EQ(key, "Portland");
    EXPECT_EQ(value, 18.9);
    std::tie(key, value) = transfer_heap -> remove_min();
    EXPECT_EQ(key, "Phoenix");
    EXPECT_EQ(value, 24.3);
    std::tie(key, value) = transfer_heap -> remove_min();
    EXPECT_EQ(key, "Miami");
    EXPECT_EQ(value, 25.0);
    std::tie(key, value) = transfer_heap -> remove_min();
    EXPECT_EQ(key, "Dallas");
    EXPECT_EQ(value, 34.1);
    std::tie(key, value) = transfer_heap -> remove_min();
    EXPECT_EQ(key, "Seattle");
    EXPECT_EQ(value, 47.6);
    std::tie(key, value) = transfer_heap -> remove_min();
    EXPECT_EQ(key, "San Francisco");
    EXPECT_EQ(value, 50.2);
    std::tie(key, value) = transfer_heap -> remove_min();
    EXPECT_EQ(key, "Colorado Springs");
    EXPECT_EQ(value, 56.8);
    std::tie(key, value) = transfer_heap -> remove_min();
    EXPECT_EQ(key, "Detroit");
    EXPECT_EQ(value, 70.4);
    std::tie(key, value) = transfer_heap -> remove_min();
    EXPECT_EQ(key, "Orlando");
    EXPECT_EQ(value, 100.5);
    std::tie(key, value) = transfer_heap -> remove_min();
    EXPECT_EQ(key, "Ontario");
    EXPECT_EQ(value, 600.5);
    std::tie(key, value) = transfer_heap -> remove_min();
    EXPECT_EQ(key, "London");
    EXPECT_EQ(value, 2000.5);
    EXPECT_EQ(transfer_heap -> get_heap_size(), 0);
}


// ==================================================== SOA_HASHMAP CLASS TESTING ==================================================================

// Test Suite test_SOAHSMP: OPEN-ADDRESSING HASHMAP Functions
// Test soa_hashmap
// Test 1: Test apply_hash_function
// Test 2: Test is_prime
// Test 3: Test get_next_prime
// Test 4: Test get_size
// Test 5: Test get_capacity
// Test 6: Test add
// Test 7: Test table_load
// Test 8: Test resize_table
// Test 9: Test contains_key
// Test 10: Test clear
// Test 11: Test get_val
// Test 12: Test empty_buckets
// Test 13: Test remove
// Test 14: Test get_keys
// Test 15: soa_hashmap constructors


// Test function responsible for generating hash indexes from string keys for hashmap classes
TEST(test_SOAHSMP, test_apply_hash_function) {
    std::vector<std::string> sample_keys = {"San Francisco", "Santa Barbara", "Santa Cruz", "Sacramento", "Medford", "San Diego", "Redding", "Los Angeles", "San Jose",  "Las Vegas", "Fresno", "Cupertino"};
    bool mismatch = false;
    auto sf_hash = apply_hash_function("San Francsico");
    auto sb_hash = apply_hash_function("Santa Barbara");
    auto sc_hash = apply_hash_function("Santa Cruz");
    auto scr_hash = apply_hash_function("Sacramento");
    auto md_hash = apply_hash_function("Medford");
    auto sd_hash = apply_hash_function("San Diego");
    auto rd_hash = apply_hash_function("Redding");
    auto la_hash = apply_hash_function("Los Angeles");
    auto sj_hash = apply_hash_function("San Jose");
    auto lv_hash = apply_hash_function("Las Vegas");
    auto fr_hash = apply_hash_function("Fresno");
    auto cr_hash = apply_hash_function("Cupertino");
    for (size_t i = 0; i < sample_keys.size(); i++) {
        auto hash_index = apply_hash_function(sample_keys[i]);
        if (hash_index == sf_hash && sample_keys[i].compare("San Francisco") != 0) {
            std::cout << "San Francisco" << '\n';
            mismatch = true;
            break;
        }
        if (hash_index == sb_hash && sample_keys[i].compare("Santa Barbara") != 0) {
            std::cout << "Santa Barbara" << '\n'; 
            mismatch = true;
            break;
        }
        if (hash_index == sc_hash && sample_keys[i].compare("Santa Cruz") != 0) {
            std::cout << "Santa Cruz" << '\n';
            mismatch = true;
            break;
        }
        if (hash_index == scr_hash && sample_keys[i].compare("Sacramento") != 0) {
            std::cout << "Sacramento" << '\n';
            mismatch = true;
            break;
        }
        if (hash_index == md_hash && sample_keys[i].compare("Medford") != 0) {
            std::cout << "Medford" << '\n';
            mismatch = true;
            break;
        }
        if (hash_index == sd_hash && sample_keys[i].compare("San Diego") != 0) {
            std::cout << "San Diego" << '\n';
            mismatch = true;
            break;
        }
        if (hash_index == rd_hash && sample_keys[i].compare("Redding") != 0) {
            std::cout << "Redding" << '\n';
            mismatch = true;
            break;
        }        
        if (hash_index == la_hash && sample_keys[i].compare("Los Angeles") != 0) {
            std::cout << "Los Angeles" << '\n';
            mismatch = true;
            break;
        }
        if (hash_index == sj_hash && sample_keys[i].compare("San Jose") != 0) {
            std::cout << "San Jose" << '\n';
            mismatch = true;
            break;
        }
        if (hash_index == lv_hash && sample_keys[i].compare("Las Vegas") != 0) {
            std::cout << "Las Vegas" << '\n';
            mismatch = true;
            break;
        }
        if (hash_index == fr_hash && sample_keys[i].compare("Fresno") != 0) {
            std::cout << "Fresno" << '\n';
            mismatch = true;
            break;
        }
        if (hash_index == cr_hash && sample_keys[i].compare("Cupertino") != 0) {
            std::cout << "Cupertino" << '\n';
            mismatch = true;
            break;
        }                
    }
    EXPECT_FALSE(mismatch);
}


// Test function responsible for evaluating whether current capacity is a prime value
TEST(test_SOAHSMP, test_is_prime) {
    std::vector<size_t> prime_list = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    bool is_prime_num = true;
    for (size_t i = 0; i < prime_list.size(); i++) {
        if (!is_prime(prime_list[i])) {
            is_prime_num = false;
            break;
        }
    }
    EXPECT_TRUE(is_prime_num);
}


// Test function responsible for determining the next prime value greater than the previous hashmap's current capacity for resizing operations
TEST(test_SOAHSMP, test_get_next_prime) {
    std::vector<size_t> prime_list = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    bool fail_prime = true;
    for (size_t i = 0; i < prime_list.size() - 1; i++) {
        if (get_next_prime(prime_list[i] + 1) != prime_list[i+1]) {
            fail_prime = false;
            break;
        }
    }
    EXPECT_TRUE(fail_prime);
}


// Test function responsible for reporting the current number of key : value pairs stored in soa_hashmap
TEST(test_SOAHSMP, test_shashmap_get_size) {
    auto dtest_hash = soa_hashmap<double>(5);
    auto stest_hash = soa_hashmap<std::string>(5);
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
}


// Test function responsible for reporting the current maximum number of key : value pairs that can be stored within soa_hashmap
TEST(test_SOAHSMP, test_shashmap_get_capacity) {
    auto dtest_hash = soa_hashmap<double>(5);
    auto stest_hash = soa_hashmap<std::string>(10);
    auto xtest_hash = soa_hashmap<double>(1);
    auto ytest_hash = soa_hashmap<std::string>(0);
    auto ztest_hash = soa_hashmap<double>(-1);
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(xtest_hash.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(ytest_hash.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(ztest_hash.get_size(), static_cast<unsigned int>(0));

    EXPECT_EQ(dtest_hash.get_capacity(), static_cast<unsigned int>(5));
    EXPECT_EQ(stest_hash.get_capacity(), static_cast<unsigned int>(10));
    EXPECT_EQ(xtest_hash.get_capacity(), static_cast<unsigned int>(5));
    EXPECT_EQ(ytest_hash.get_capacity(), static_cast<unsigned int>(5));
    EXPECT_EQ(ztest_hash.get_capacity(), static_cast<unsigned int>(5));
}


// Test function responsible for adding new key : value pairs to be stored within soa_hashmap
TEST(test_SOAHSMP, test_shashmap_add) {
    auto dtest_hash = soa_hashmap<double>(5);
    auto stest_hash = soa_hashmap<std::string>(5);
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
    dtest_hash.add("San Francisco", 3.0);
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(1));
    dtest_hash.add("New York", 10.0);
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(2));
    dtest_hash.add("Houston", 15.0);
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(3));
    stest_hash.add("San Francisco", "New York");
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(1));
    stest_hash.add("New York", "Houston");
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(2));
    stest_hash.add("Dallas", "San Antonio");
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(3));
}


// Test function responsible for reporting the currrent load ratio for determining whether the hashmap should be resized
TEST(test_SOAHSMP, test_shashmap_table_load) {
    auto dtest_hash = soa_hashmap<double>(5);
    auto stest_hash = soa_hashmap<std::string>(5);
    auto exp_DTL = static_cast<double>(dtest_hash.get_size()) / static_cast<double>(dtest_hash.get_capacity());
    auto exp_STL = static_cast<double>(stest_hash.get_size()) / static_cast<double>(stest_hash.get_capacity());
    ASSERT_EQ(exp_DTL, dtest_hash.table_load());
    ASSERT_EQ(exp_STL, stest_hash.table_load());
    dtest_hash.add("San Francisco", 3.0);
    dtest_hash.add("New York", 10.0);
    dtest_hash.add("Houston", 15.0);
    dtest_hash.add("Lufkin", 42.0);
    stest_hash.add("San Francisco", "New York");
    stest_hash.add("New York", "Houston");
    stest_hash.add("Dallas", "San Antonio");
    stest_hash.add("Lufkin", "Detriot");
    // Both soa_hashmap instances will have undergone resizing so capacity will adjusted
    exp_DTL = static_cast<double>(dtest_hash.get_size()) / static_cast<double>(dtest_hash.get_capacity());
    exp_STL = static_cast<double>(stest_hash.get_size()) / static_cast<double>(stest_hash.get_capacity());
    EXPECT_EQ(exp_DTL, dtest_hash.table_load());
    EXPECT_EQ(exp_STL, stest_hash.table_load());
}


// Test function responsible for transferring previous underlying storage array into a new array with increase storage capacity
TEST(test_SOAHSMP, test_shashmap_resize_table) {
    auto dtest_hash = soa_hashmap<double>(3);
    auto stest_hash = soa_hashmap<std::string>(3);
    auto init_cap = dtest_hash.get_capacity();
    ASSERT_EQ(init_cap, static_cast<unsigned int>(5));
    dtest_hash.add("San Francisco", 3.0);
    dtest_hash.add("New York", 10.0);
    // Table load threshold exceeded, so resizing must occur
    EXPECT_EQ(get_next_prime(init_cap), dtest_hash.get_capacity());
    dtest_hash.add("Houston", 15.0);
    auto next_cap = dtest_hash.get_capacity();
    // Table load threshold exceeded, so resizing must occur
    EXPECT_EQ(get_next_prime(next_cap), dtest_hash.get_capacity());

    stest_hash.add("San Francisco", "New York");
    stest_hash.add("New York", "Houston");
    // Table load threshold exceeded, so resizing must occur
    EXPECT_EQ(get_next_prime(init_cap), stest_hash.get_capacity());
    stest_hash.add("Dallas", "San Antonio");
    // Table load threshold exceeded, so resizing must occur
    EXPECT_EQ(get_next_prime(next_cap), stest_hash.get_capacity());
}


// Test function responsible for evaluating whether key is currently stored within soa_hashmap
TEST(test_SOAHSMP, test_shashmap_contains_key) {
    auto dtest_hash = soa_hashmap<double>(5);
    auto stest_hash = soa_hashmap<std::string>(5);
    dtest_hash.add("San Francisco", 3.0);
    dtest_hash.add("New York", 10.0);
    dtest_hash.add("Houston", 15.0);
    dtest_hash.add("Lufkin", 42.0);

    stest_hash.add("San Francisco", "New York");
    stest_hash.add("New York", "Houston");
    stest_hash.add("Dallas", "San Antonio");
    stest_hash.add("Lufkin", "Detroit");
    EXPECT_TRUE(dtest_hash.contains_key("San Francisco"));
    EXPECT_TRUE(dtest_hash.contains_key("New York"));
    EXPECT_TRUE(dtest_hash.contains_key("Houston"));
    EXPECT_TRUE(dtest_hash.contains_key("Lufkin"));
    EXPECT_FALSE(dtest_hash.contains_key("Dallas"));    

    EXPECT_TRUE(stest_hash.contains_key("San Francisco"));
    EXPECT_TRUE(stest_hash.contains_key("New York"));
    EXPECT_TRUE(stest_hash.contains_key("Dallas"));
    EXPECT_TRUE(stest_hash.contains_key("Lufkin"));
    EXPECT_FALSE(stest_hash.contains_key("Houston")); 
}


// Test function responsible for removing all stored contents within soa_hashmap
TEST(test_SOAHSMP, test_shashmap_clear) {
    auto dtest_hash = soa_hashmap<double>(5);
    auto stest_hash = soa_hashmap<std::string>(5);

    EXPECT_EQ(dtest_hash.empty_buckets(), dtest_hash.get_capacity());
    EXPECT_EQ(stest_hash.empty_buckets(), stest_hash.get_capacity());
    ASSERT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
    ASSERT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
    ASSERT_EQ(dtest_hash.get_capacity(), static_cast<unsigned int>(5));
    ASSERT_EQ(stest_hash.get_capacity(), static_cast<unsigned int>(5));
    ASSERT_EQ(dtest_hash.get_keys().size(), static_cast<size_t>(0));
    ASSERT_EQ(stest_hash.get_keys().size(), static_cast<size_t>(0));

    dtest_hash.add("San Francisco", 3.0);
    dtest_hash.add("New York", 10.0);
    dtest_hash.add("Houston", 15.0);
    dtest_hash.add("Lufkin", 42.0);

    stest_hash.add("San Francisco", "New York");
    stest_hash.add("New York", "Houston");
    stest_hash.add("Dallas", "San Antonio");
    stest_hash.add("Lufkin", "Detroit");

    auto new_capacity = dtest_hash.get_capacity();
    EXPECT_EQ(new_capacity, stest_hash.get_capacity());
    EXPECT_EQ(dtest_hash.get_keys().size(), static_cast<size_t>(4));
    EXPECT_EQ(stest_hash.get_keys().size(), static_cast<size_t>(4));
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(4));
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(4));

    dtest_hash.clear();
    stest_hash.clear();

    EXPECT_EQ(dtest_hash.get_keys().size(), static_cast<size_t>(0));
    EXPECT_EQ(stest_hash.get_keys().size(), static_cast<size_t>(0));
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(dtest_hash.get_capacity(), new_capacity);
    EXPECT_EQ(stest_hash.get_capacity(), new_capacity);
    EXPECT_FALSE(dtest_hash.contains_key("San Francisco"));
    EXPECT_FALSE(dtest_hash.contains_key("New York"));
    EXPECT_FALSE(dtest_hash.contains_key("Houston"));
    EXPECT_FALSE(dtest_hash.contains_key("Lufkin"));    

    EXPECT_FALSE(stest_hash.contains_key("San Francisco"));
    EXPECT_FALSE(stest_hash.contains_key("New York"));
    EXPECT_FALSE(stest_hash.contains_key("Dallas"));
    EXPECT_FALSE(stest_hash.contains_key("Lufkin"));     
}


// Test function responsible for retrieving value associated with key matching string passed in function argument
TEST(test_SOAHSMP, test_get_val) {
    auto dtest_hash = soa_hashmap<double>(5);
    auto stest_hash = soa_hashmap<std::string>(5);
    EXPECT_THROW({
    try {
        dtest_hash.get_val("Tokyo");
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: Hashmap does not currently hold any values to retrieve!", e.what());
        throw;
    }
    }, std::exception);
    EXPECT_THROW({
    try {
        stest_hash.get_val("Tokyo");
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: Hashmap does not currently hold any values to retrieve!", e.what());
        throw;
    }
    }, std::exception);
    dtest_hash.add("San Francisco", 3.0);
    dtest_hash.add("New York", 10.0);
    dtest_hash.add("Houston", 15.0);
    dtest_hash.add("Lufkin", 42.0);
    stest_hash.add("San Francisco", "New York");
    stest_hash.add("New York", "Houston");
    stest_hash.add("Dallas", "San Antonio");
    stest_hash.add("Lufkin", "Detroit");
    EXPECT_EQ(dtest_hash.get_val("New York"), 10.0);
    EXPECT_EQ(dtest_hash.get_val("San Francisco"), 3.0);
    EXPECT_EQ(dtest_hash.get_val("Houston"), 15.0);
    EXPECT_EQ(dtest_hash.get_val("Lufkin"), 42.0);

    EXPECT_EQ(stest_hash.get_val("San Francisco"), "New York");
    EXPECT_EQ(stest_hash.get_val("New York"), "Houston");
    EXPECT_EQ(stest_hash.get_val("Dallas"), "San Antonio");
    EXPECT_EQ(stest_hash.get_val("Lufkin"), "Detroit");
    EXPECT_THROW({
    try {
        dtest_hash.get_val("Tokyo");
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: Value for key 'Tokyo' was not found within the Hashmap!\n", e.what());
        throw;
    }
    }, std::exception);
    EXPECT_THROW({
    try {
        stest_hash.get_val("Tokyo");
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: Value for key 'Tokyo' was not found within the Hashmap!\n", e.what());
        throw;
    }
    }, std::exception);
    dtest_hash.clear();
    stest_hash.clear();
    EXPECT_THROW({
    try {
        dtest_hash.get_val("New York");
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: Hashmap does not currently hold any values to retrieve!", e.what());
        throw;
    }
    }, std::exception);
    EXPECT_THROW({
    try {
        stest_hash.get_val("New York");
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: Hashmap does not currently hold any values to retrieve!", e.what());
        throw;
    }
    }, std::exception);
}


// Test function responsible for reporting the number of empty positions within the underlying storage array of soa_hashmap
TEST(test_SOAHSMP, test_shashmap_empty_buckets) {
    auto dtest_hash = soa_hashmap<double>(5);
    auto stest_hash = soa_hashmap<std::string>(5);
    ASSERT_EQ(stest_hash.empty_buckets(), stest_hash.get_capacity());
    ASSERT_EQ(dtest_hash.empty_buckets(), dtest_hash.get_capacity());
    ASSERT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
    ASSERT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
    ASSERT_EQ(dtest_hash.get_capacity(), static_cast<unsigned int>(5));
    ASSERT_EQ(stest_hash.get_capacity(), static_cast<unsigned int>(5));

    dtest_hash.add("San Francisco", 3.0);
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(1));
    EXPECT_EQ(dtest_hash.get_capacity(), static_cast<unsigned int>(5));
    EXPECT_EQ(dtest_hash.empty_buckets(), dtest_hash.get_capacity() - dtest_hash.get_size());
    dtest_hash.add("New York", 10.0);
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(2));
    EXPECT_EQ(dtest_hash.get_capacity(), static_cast<unsigned int>(5));
    EXPECT_EQ(dtest_hash.empty_buckets(), dtest_hash.get_capacity() - dtest_hash.get_size());
    dtest_hash.add("Houston", 15.0);
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(dtest_hash.get_capacity(), get_next_prime(5));
    EXPECT_EQ(dtest_hash.empty_buckets(), dtest_hash.get_capacity() - dtest_hash.get_size());
    dtest_hash.add("Lufkin", 42.0);
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(4));
    EXPECT_EQ(dtest_hash.empty_buckets(), dtest_hash.get_capacity() - dtest_hash.get_size());

    stest_hash.add("San Francisco", "New York");
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(1));
    EXPECT_EQ(stest_hash.get_capacity(), static_cast<unsigned int>(5));
    EXPECT_EQ(stest_hash.empty_buckets(), stest_hash.get_capacity() - stest_hash.get_size());
    stest_hash.add("New York", "Houston");
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(2));
    EXPECT_EQ(stest_hash.get_capacity(), static_cast<unsigned int>(5));
    EXPECT_EQ(stest_hash.empty_buckets(), stest_hash.get_capacity() - stest_hash.get_size());
    stest_hash.add("Dallas", "San Antonio");
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hash.get_capacity(), get_next_prime(5));
    EXPECT_EQ(stest_hash.empty_buckets(), stest_hash.get_capacity() - stest_hash.get_size());
    stest_hash.add("Lufkin", "Detroit");
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(4));
    EXPECT_EQ(stest_hash.empty_buckets(), stest_hash.get_capacity() - stest_hash.get_size());
}


// Test function responsible for removing a specific key : value pair from the soa_hashmap
TEST(test_SOAHSMP, test_shashmap_remove) {
    auto dtest_hash = soa_hashmap<double>(5);
    auto stest_hash = soa_hashmap<std::string>(5);

    ASSERT_EQ(stest_hash.empty_buckets(), stest_hash.get_capacity());
    ASSERT_EQ(dtest_hash.empty_buckets(), dtest_hash.get_capacity());
    ASSERT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
    ASSERT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
    ASSERT_EQ(dtest_hash.get_capacity(), static_cast<unsigned int>(5));
    ASSERT_EQ(stest_hash.get_capacity(), static_cast<unsigned int>(5));
    ASSERT_EQ(dtest_hash.get_keys().size(), static_cast<size_t>(0));
    ASSERT_EQ(stest_hash.get_keys().size(), static_cast<size_t>(0));

    dtest_hash.add("San Francisco", 3.0);
    dtest_hash.add("New York", 10.0);
    dtest_hash.add("Houston", 15.0);
    dtest_hash.add("Lufkin", 42.0);

    stest_hash.add("San Francisco", "New York");
    stest_hash.add("New York", "Houston");
    stest_hash.add("Dallas", "San Antonio");
    stest_hash.add("Lufkin", "Detroit");

    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(4));
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(4));
    EXPECT_EQ(dtest_hash.get_keys().size(), static_cast<size_t>(4));
    EXPECT_EQ(stest_hash.get_keys().size(), static_cast<size_t>(4));

    EXPECT_FALSE(dtest_hash.contains_key("Billings"));
    EXPECT_FALSE(stest_hash.contains_key("Billings"));

    EXPECT_TRUE(dtest_hash.contains_key("Houston"));
    EXPECT_TRUE(stest_hash.contains_key("Dallas"));
    dtest_hash.remove("Houston");
    stest_hash.remove("Dallas");
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(dtest_hash.get_keys().size(), static_cast<size_t>(3));
    EXPECT_EQ(stest_hash.get_keys().size(), static_cast<size_t>(3));
    EXPECT_FALSE(dtest_hash.contains_key("Houston"));
    EXPECT_FALSE(stest_hash.contains_key("Dallas"));


    EXPECT_TRUE(dtest_hash.contains_key("San Francisco"));
    EXPECT_TRUE(stest_hash.contains_key("San Francisco"));
    dtest_hash.remove("San Francisco");
    stest_hash.remove("San Francisco");
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(2));
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(2));
    EXPECT_EQ(dtest_hash.get_keys().size(), static_cast<size_t>(2));
    EXPECT_EQ(stest_hash.get_keys().size(), static_cast<size_t>(2));
    EXPECT_FALSE(dtest_hash.contains_key("San Francisco"));
    EXPECT_FALSE(stest_hash.contains_key("San Francisco"));


    EXPECT_TRUE(dtest_hash.contains_key("Lufkin"));
    EXPECT_TRUE(stest_hash.contains_key("Lufkin"));
    dtest_hash.remove("Lufkin");
    stest_hash.remove("Lufkin");
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(1));
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(1));
    EXPECT_EQ(dtest_hash.get_keys().size(), static_cast<size_t>(1));
    EXPECT_EQ(stest_hash.get_keys().size(), static_cast<size_t>(1));
    EXPECT_FALSE(dtest_hash.contains_key("Lufkin"));
    EXPECT_FALSE(stest_hash.contains_key("Lufkin"));

    EXPECT_TRUE(dtest_hash.contains_key("New York"));
    EXPECT_TRUE(stest_hash.contains_key("New York"));     
    dtest_hash.remove("New York");
    stest_hash.remove("New York");
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(dtest_hash.get_keys().size(), static_cast<size_t>(0));
    EXPECT_EQ(stest_hash.get_keys().size(), static_cast<size_t>(0));
    EXPECT_FALSE(dtest_hash.contains_key("New York"));
    EXPECT_FALSE(stest_hash.contains_key("New York"));
}


// Test function responsible for retrieving array of all unique keys stored within soa_hashmap
TEST(test_SOAHSMP, test_shashmap_get_keys) {
    auto dtest_hash = soa_hashmap<double>(5);
    auto stest_hash = soa_hashmap<std::string>(5);
    dtest_hash.add("San Francisco", 3.0);
    dtest_hash.add("New York", 10.0);
    dtest_hash.add("Houston", 15.0);
    dtest_hash.add("Concord", 14.0);
    stest_hash.add("San Francisco", "New York");
    stest_hash.add("New York", "Houston");
    stest_hash.add("Dallas", "San Antonio");
    stest_hash.add("Concord", "Nashville");
    ASSERT_EQ(dtest_hash.get_keys().size(), static_cast<unsigned int>(4));
    ASSERT_EQ(stest_hash.get_keys().size(), static_cast<unsigned int>(4));
    dtest_hash.remove("San Francisco");
    stest_hash.remove("San Francisco");
    EXPECT_EQ(dtest_hash.get_keys().size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hash.get_keys().size(), static_cast<unsigned int>(3));
    dtest_hash.remove("New York");
    stest_hash.remove("New York");
    EXPECT_EQ(dtest_hash.get_keys().size(), static_cast<unsigned int>(2));
    EXPECT_EQ(stest_hash.get_keys().size(), static_cast<unsigned int>(2));
    dtest_hash.remove("Concord");
    stest_hash.remove("Concord");
    EXPECT_EQ(dtest_hash.get_keys().size(), static_cast<unsigned int>(1));
    EXPECT_EQ(stest_hash.get_keys().size(), static_cast<unsigned int>(1));
    EXPECT_EQ(dtest_hash.get_keys().front(), "Houston");
    EXPECT_EQ(stest_hash.get_keys().front(), "Dallas");
    dtest_hash.remove("Houston");
    stest_hash.remove("Dallas");
    EXPECT_EQ(dtest_hash.get_keys().size(), static_cast<unsigned int>(0));
    EXPECT_EQ(stest_hash.get_keys().size(), static_cast<unsigned int>(0));
    dtest_hash.add("Houston", 36.0);
    stest_hash.add("Dallas", "Kansas City");
    EXPECT_EQ(dtest_hash.get_keys().size(), static_cast<unsigned int>(1));
    EXPECT_EQ(stest_hash.get_keys().size(), static_cast<unsigned int>(1));
    EXPECT_EQ(dtest_hash.get_keys().front(), "Houston");
    EXPECT_EQ(stest_hash.get_keys().front(), "Dallas");
    EXPECT_EQ(dtest_hash.get_val("Houston"), 36.0);
    EXPECT_EQ(stest_hash.get_val("Dallas"), "Kansas City");
    dtest_hash.add("Houston", 45.0);
    stest_hash.add("Dallas", "Yorkshire");
    EXPECT_EQ(dtest_hash.get_keys().size(), static_cast<unsigned int>(1));
    EXPECT_EQ(stest_hash.get_keys().size(), static_cast<unsigned int>(1));
    EXPECT_EQ(dtest_hash.get_val("Houston"), 45.0);
    EXPECT_EQ(stest_hash.get_val("Dallas"), "Yorkshire");
}


// Test constructor for initializing soa_hashmap class object instance with a pre-defined capacity value
TEST(test_SOAHSMP, test_shashmap_capacity_constructor) {
    auto dtest_hash = soa_hashmap<double>(-1);
    ASSERT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
    ASSERT_EQ(dtest_hash.get_capacity(), static_cast<unsigned int>(5));
    auto orig_hash = std::make_unique<soa_hashmap<double>>(10);
    EXPECT_EQ(orig_hash -> get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(orig_hash -> get_capacity(), static_cast<unsigned int>(10));
    orig_hash -> add("Miami", 25.0);
    EXPECT_EQ(orig_hash -> get_size(), static_cast<unsigned int>(1));
    orig_hash -> add("Harvard", 2.0);
    EXPECT_EQ(orig_hash -> get_size(), static_cast<unsigned int>(2));
    orig_hash -> add("Los Angeles", 15.3);
    EXPECT_EQ(orig_hash -> get_size(), static_cast<unsigned int>(3));
    orig_hash -> add("New York", 3.6);
    EXPECT_EQ(orig_hash -> get_size(), static_cast<unsigned int>(4));
    orig_hash -> add("Fresno", 10.0);
    EXPECT_EQ(orig_hash -> get_size(), static_cast<unsigned int>(5));
    orig_hash -> add("Redding", 1.3);
    EXPECT_EQ(orig_hash -> get_size(), static_cast<unsigned int>(6));
    orig_hash -> add("San Francisco", 50.2);
    EXPECT_EQ(orig_hash -> get_size(), static_cast<unsigned int>(7));
    orig_hash -> add("Las Vegas", 14.0);
    EXPECT_EQ(orig_hash -> get_size(), static_cast<unsigned int>(8));
    orig_hash -> add("Detroit", 70.4);
    EXPECT_EQ(orig_hash -> get_size(), static_cast<unsigned int>(9));
    orig_hash -> add("Medford", 14.7);
    EXPECT_EQ(orig_hash -> get_size(), static_cast<unsigned int>(10));    
    orig_hash -> add("Dallas", 34.1);
    EXPECT_EQ(orig_hash -> get_size(), static_cast<unsigned int>(11));
    orig_hash -> add("Phoenix", 24.3);
    EXPECT_EQ(orig_hash -> get_size(), static_cast<unsigned int>(12));
    orig_hash -> add("Seattle", 47.6);
    EXPECT_EQ(orig_hash -> get_size(), static_cast<unsigned int>(13));
    orig_hash -> add("Portland", 18.9);
    EXPECT_EQ(orig_hash -> get_size(), static_cast<unsigned int>(14));
    orig_hash -> add("Orlando", 100.5);
    EXPECT_EQ(orig_hash -> get_size(), static_cast<unsigned int>(15));    
    orig_hash -> add("Colorado Springs", 56.8);
    EXPECT_EQ(orig_hash -> get_size(), static_cast<unsigned int>(16));
    EXPECT_EQ(orig_hash -> get_keys().size(), static_cast<unsigned int>(16));
    EXPECT_EQ(orig_hash -> get_val("Miami"), 25.0);
    EXPECT_EQ(orig_hash -> get_val("Harvard"), 2.0);
    EXPECT_EQ(orig_hash -> get_val("Los Angeles"), 15.3);
    EXPECT_EQ(orig_hash -> get_val("New York"), 3.6);
    EXPECT_EQ(orig_hash -> get_val("Fresno"), 10.0);
    EXPECT_EQ(orig_hash -> get_val("Redding"), 1.3);
    EXPECT_EQ(orig_hash -> get_val("San Francisco"), 50.2);
    EXPECT_EQ(orig_hash -> get_val("Las Vegas"), 14.0);
    EXPECT_EQ(orig_hash -> get_val("Detroit"), 70.4);
    EXPECT_EQ(orig_hash -> get_val("Medford"), 14.7);
    EXPECT_EQ(orig_hash -> get_val("Dallas"), 34.1);
    EXPECT_EQ(orig_hash -> get_val("Phoenix"), 24.3);
    EXPECT_EQ(orig_hash -> get_val("Seattle"), 47.6);
    EXPECT_EQ(orig_hash -> get_val("Portland"), 18.9);
    EXPECT_EQ(orig_hash -> get_val("Orlando"), 100.5);
    EXPECT_EQ(orig_hash -> get_val("Colorado Springs"), 56.8);
}

// Test constructor for soa_hashmap class object instance transfers contents of an argument of vector array with key : value pairs into intialized instance
TEST(test_SOAHSMP, test_shashmap_vector_constructer) {
    auto miami = std::make_pair("Miami", 25.0);
    auto harvard = std::make_pair("Harvard", 2.0);
    auto los_angeles = std::make_pair("Los Angeles", 15.3);
    auto new_york = std::make_pair("New York", 3.6);
    auto fresno = std::make_pair("Fresno", 10.0);
    auto redding = std::make_pair("Redding", 1.3);
    auto san_francisco = std::make_pair("San Francisco", 50.2);
    auto las_vegas = std::make_pair("Las Vegas", 14.0);
    auto detroit = std::make_pair("Detroit", 70.4);
    auto medford = std::make_pair("Medford", 14.7);
    auto dallas = std::make_pair("Dallas", 34.1);
    auto phoenix = std::make_pair("Phoenix", 24.3);
    auto seattle = std::make_pair("Seattle", 47.6);
    auto portland = std::make_pair("Portland", 18.9);
    auto orlando = std::make_pair("Orlando", 100.5);
    auto colorado_springs = std::make_pair("Colorado Springs", 56.8);

    std::vector<std::pair<std::string, double>> hash_pairs = {miami, harvard, los_angeles, new_york, fresno, redding, san_francisco, las_vegas, detroit, medford, dallas, phoenix, seattle, portland, orlando, colorado_springs};
    auto vector_size = hash_pairs.size();
    auto exist_hash = std::make_unique<soa_hashmap<double>>(hash_pairs);
    EXPECT_EQ(exist_hash -> get_size(), static_cast<unsigned int>(vector_size));
    EXPECT_EQ(hash_pairs.size(), static_cast<size_t>(0));
    EXPECT_EQ(exist_hash -> get_keys().size(), static_cast<size_t>(vector_size));
    EXPECT_EQ(exist_hash -> get_val("Miami"), 25.0);
    EXPECT_EQ(exist_hash -> get_val("Harvard"), 2.0);
    EXPECT_EQ(exist_hash -> get_val("Los Angeles"), 15.3);
    EXPECT_EQ(exist_hash -> get_val("New York"), 3.6);
    EXPECT_EQ(exist_hash -> get_val("Fresno"), 10.0);
    EXPECT_EQ(exist_hash -> get_val("Redding"), 1.3);
    EXPECT_EQ(exist_hash -> get_val("San Francisco"), 50.2);
    EXPECT_EQ(exist_hash -> get_val("Las Vegas"), 14.0);
    EXPECT_EQ(exist_hash -> get_val("Detroit"), 70.4);
    EXPECT_EQ(exist_hash -> get_val("Medford"), 14.7);
    EXPECT_EQ(exist_hash -> get_val("Dallas"), 34.1);
    EXPECT_EQ(exist_hash -> get_val("Phoenix"), 24.3);
    EXPECT_EQ(exist_hash -> get_val("Seattle"), 47.6);
    EXPECT_EQ(exist_hash -> get_val("Portland"), 18.9);
    EXPECT_EQ(exist_hash -> get_val("Orlando"), 100.5);
    EXPECT_EQ(exist_hash -> get_val("Colorado Springs"), 56.8);
}


// Test move constructor for transferring contents/ownership between different soa_hashmap class object instances
TEST(test_SOAHSMP, test_shashmap_move_constructor) {
    auto miami = std::make_pair("Miami", 25.0);
    auto harvard = std::make_pair("Harvard", 2.0);
    auto los_angeles = std::make_pair("Los Angeles", 15.3);
    auto new_york = std::make_pair("New York", 3.6);
    auto fresno = std::make_pair("Fresno", 10.0);
    auto redding = std::make_pair("Redding", 1.3);
    auto san_francisco = std::make_pair("San Francisco", 50.2);
    auto las_vegas = std::make_pair("Las Vegas", 14.0);
    auto detroit = std::make_pair("Detroit", 70.4);
    auto medford = std::make_pair("Medford", 14.7);
    auto dallas = std::make_pair("Dallas", 34.1);
    auto phoenix = std::make_pair("Phoenix", 24.3);
    auto seattle = std::make_pair("Seattle", 47.6);
    auto portland = std::make_pair("Portland", 18.9);
    auto orlando = std::make_pair("Orlando", 100.5);
    auto colorado_springs = std::make_pair("Colorado Springs", 56.8);

    std::vector<std::pair<std::string, double>> hash_pairs = {miami, harvard, los_angeles, new_york, fresno, redding, san_francisco, las_vegas, detroit, medford, dallas, phoenix, seattle, portland, orlando, colorado_springs};
    auto vector_size = hash_pairs.size();
    auto exist_hash = std::make_unique<soa_hashmap<double>>(hash_pairs);
    EXPECT_EQ(exist_hash -> get_size(), static_cast<unsigned int>(vector_size));
    EXPECT_EQ(hash_pairs.size(), static_cast<size_t>(0));
    EXPECT_EQ(exist_hash -> get_keys().size(), static_cast<size_t>(vector_size));
    EXPECT_EQ(exist_hash -> get_val("Miami"), 25.0);
    EXPECT_EQ(exist_hash -> get_val("Harvard"), 2.0);
    EXPECT_EQ(exist_hash -> get_val("Los Angeles"), 15.3);
    EXPECT_EQ(exist_hash -> get_val("New York"), 3.6);
    EXPECT_EQ(exist_hash -> get_val("Fresno"), 10.0);
    EXPECT_EQ(exist_hash -> get_val("Redding"), 1.3);
    EXPECT_EQ(exist_hash -> get_val("San Francisco"), 50.2);
    EXPECT_EQ(exist_hash -> get_val("Las Vegas"), 14.0);
    EXPECT_EQ(exist_hash -> get_val("Detroit"), 70.4);
    EXPECT_EQ(exist_hash -> get_val("Medford"), 14.7);
    EXPECT_EQ(exist_hash -> get_val("Dallas"), 34.1);
    EXPECT_EQ(exist_hash -> get_val("Phoenix"), 24.3);
    EXPECT_EQ(exist_hash -> get_val("Seattle"), 47.6);
    EXPECT_EQ(exist_hash -> get_val("Portland"), 18.9);
    EXPECT_EQ(exist_hash -> get_val("Orlando"), 100.5);
    EXPECT_EQ(exist_hash -> get_val("Colorado Springs"), 56.8);
    auto transfer_hash = std::move(exist_hash);
    EXPECT_EQ(transfer_hash -> get_size(), static_cast<unsigned int>(vector_size));
    EXPECT_EQ(transfer_hash-> get_keys().size(), vector_size);
    EXPECT_EQ(transfer_hash -> get_val("Miami"), 25.0);
    EXPECT_EQ(transfer_hash -> get_val("Harvard"), 2.0);
    EXPECT_EQ(transfer_hash -> get_val("Los Angeles"), 15.3);
    EXPECT_EQ(transfer_hash -> get_val("New York"), 3.6);
    EXPECT_EQ(transfer_hash -> get_val("Fresno"), 10.0);
    EXPECT_EQ(transfer_hash -> get_val("Redding"), 1.3);
    EXPECT_EQ(transfer_hash -> get_val("San Francisco"), 50.2);
    EXPECT_EQ(transfer_hash -> get_val("Las Vegas"), 14.0);
    EXPECT_EQ(transfer_hash -> get_val("Detroit"), 70.4);
    EXPECT_EQ(transfer_hash-> get_val("Medford"), 14.7);
    EXPECT_EQ(transfer_hash -> get_val("Dallas"), 34.1);
    EXPECT_EQ(transfer_hash -> get_val("Phoenix"), 24.3);
    EXPECT_EQ(transfer_hash -> get_val("Seattle"), 47.6);
    EXPECT_EQ(transfer_hash -> get_val("Portland"), 18.9);
    EXPECT_EQ(transfer_hash -> get_val("Orlando"), 100.5);
    EXPECT_EQ(transfer_hash -> get_val("Colorado Springs"), 56.8);
}




// ==================================================== MAIN_HASHMAP CLASS TESTING ==================================================================

// Test Suite test_MHSMP: HASHMAP CONTAINING OPEN-ADDRESSING HASHMAP(S) Functions

// Test main_hashmap
// Test 1: Test get_size
// Test 2: Test get_capacity
// Test 3: Test add
// Test 4: Test table_load
// Test 4: Test resize_table
// Test 5: Test contains_key
// Test 6: Test clear
// Test 7: Test get_val
// Test 8: Test empty_buckets
// Test 9: Test remove
// Test 10: Test get_keys
// Test 10: Test get_hash_key
// Test 11: Test get_key_by_val
// Test 12: Test main_hashmap constructors

// Test function responsible for reporting the current number of key : value pairs stored in main_hashmap
TEST(test_MHSMP, test_mhashmap_get_size) {
    auto dtest_hash = main_hashmap<double>(5);
    auto stest_hash = main_hashmap<std::string>(5);
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
}


// Test function responsible for reporting the current maximum number of key : value pairs that can be stored within main_hashmap
TEST(test_MHSMP, test_mhashmap_get_capacity) {
    auto dtest_hash = main_hashmap<double>(5);
    auto stest_hash = main_hashmap<std::string>(10);
    auto xtest_hash = main_hashmap<double>(1);
    auto ytest_hash = main_hashmap<std::string>(0);
    auto ztest_hash = main_hashmap<double>(-1);
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(xtest_hash.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(ytest_hash.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(ztest_hash.get_size(), static_cast<unsigned int>(0));

    EXPECT_EQ(dtest_hash.get_capacity(), static_cast<unsigned int>(5));
    EXPECT_EQ(stest_hash.get_capacity(), static_cast<unsigned int>(10));
    EXPECT_EQ(xtest_hash.get_capacity(), static_cast<unsigned int>(5));
    EXPECT_EQ(ytest_hash.get_capacity(), static_cast<unsigned int>(5));
    EXPECT_EQ(ztest_hash.get_capacity(), static_cast<unsigned int>(5));
}


// Test function responsible for adding new key : value pairs to be stored within main_hashmap
TEST(test_MHSMP, test_mhashmap_add) {
    auto dtest_hash = soa_hashmap<double>(5);
    auto stest_hash = soa_hashmap<std::string>(5);
    auto dtest_hashmap = main_hashmap<double>(5);
    auto stest_hashmap = main_hashmap<std::string>(5);
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(dtest_hashmap.get_keys().size(), static_cast<size_t>(0));
    EXPECT_EQ(stest_hashmap.get_keys().size(), static_cast<size_t>(0));
    dtest_hash.add("San Francisco", 3.0);
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(1));
    dtest_hash.add("New York", 10.0);
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(2));
    dtest_hash.add("Houston", 15.0);
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(3));
    stest_hash.add("San Francisco", "New York");
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(1));
    stest_hash.add("New York", "Houston");
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(2));
    stest_hash.add("Dallas", "San Antonio");
    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(3));
    dtest_hashmap.add("dtest_hash", std::move(dtest_hash));
    stest_hashmap.add("stest_hash", std::move(stest_hash));
    EXPECT_EQ(dtest_hashmap.get_size(), static_cast<unsigned int>(1));
    EXPECT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(1));
    EXPECT_EQ(dtest_hashmap.get_keys().size(), static_cast<size_t>(1));
    EXPECT_EQ(stest_hashmap.get_keys().size(), static_cast<size_t>(1));
}


// Test function responsible for reporting the currrent load ratio for determining whether the hashmap should be resized
TEST(test_MHSMP, test_mhashmap_table_load) {
    auto dtest_hash1 = soa_hashmap<double>(5);
    auto stest_hash1 = soa_hashmap<std::string>(5);
    auto dtest_hash2 = soa_hashmap<double>(5);
    auto stest_hash2 = soa_hashmap<std::string>(5);
    auto dtest_hash3 = soa_hashmap<double>(5);
    auto stest_hash3 = soa_hashmap<std::string>(5);
    auto dtest_hash4 = soa_hashmap<double>(5);
    auto stest_hash4 = soa_hashmap<std::string>(5);
    auto dtest_hashmap = main_hashmap<double>(5);
    auto stest_hashmap = main_hashmap<std::string>(5);
    auto exp_DTL = static_cast<double>(dtest_hashmap.get_size()) / static_cast<double>(dtest_hashmap.get_capacity());
    auto exp_STL = static_cast<double>(stest_hashmap.get_size()) / static_cast<double>(stest_hashmap.get_capacity());
    ASSERT_EQ(exp_DTL, dtest_hashmap.table_load());
    ASSERT_EQ(exp_STL, stest_hashmap.table_load());
    dtest_hashmap.add("San Francisco", std::move(dtest_hash1));
    dtest_hashmap.add("New York", std::move(dtest_hash2));
    dtest_hashmap.add("Houston", std::move(dtest_hash3));
    dtest_hashmap.add("Lufkin", std::move(dtest_hash4));
    stest_hashmap.add("San Francisco", std::move(stest_hash1));
    stest_hashmap.add("New York", std::move(stest_hash2));
    stest_hashmap.add("Dallas", std::move(stest_hash3));
    stest_hashmap.add("Lufkin", std::move(stest_hash4));
    // Both soa_hashmap instances will have undergone resizing so capacity will adjusted
    exp_DTL = static_cast<double>(dtest_hashmap.get_size()) / static_cast<double>(dtest_hashmap.get_capacity());
    exp_STL = static_cast<double>(stest_hashmap.get_size()) / static_cast<double>(stest_hashmap.get_capacity());
    EXPECT_EQ(exp_DTL, dtest_hashmap.table_load());
    EXPECT_EQ(exp_STL, stest_hashmap.table_load());
}


// Test function responsible for transferring previous underlying storage array into a new array with increase storage capacity
TEST(test_MHSMP, test_mhashmap_resize_table) {
    auto dtest_hash1 = soa_hashmap<double>(5);
    auto stest_hash1 = soa_hashmap<std::string>(5);
    auto dtest_hash2 = soa_hashmap<double>(5);
    auto stest_hash2 = soa_hashmap<std::string>(5);
    auto dtest_hash3 = soa_hashmap<double>(5);
    auto stest_hash3 = soa_hashmap<std::string>(5);

    auto dtest_hashmap = main_hashmap<double>(5);
    auto stest_hashmap = main_hashmap<std::string>(5);
    auto init_cap = dtest_hashmap.get_capacity();
    ASSERT_EQ(init_cap, static_cast<unsigned int>(5));
    dtest_hashmap.add("San Francisco", std::move(dtest_hash1));
    dtest_hashmap.add("New York", std::move(dtest_hash2));
    // Table load threshold exceeded, so resizing must occur
    EXPECT_EQ(get_next_prime(init_cap), dtest_hashmap.get_capacity());
    dtest_hashmap.add("Houston", std::move(dtest_hash3));
    auto next_cap = dtest_hashmap.get_capacity();
    // Table load threshold exceeded, so resizing must occur
    EXPECT_EQ(get_next_prime(next_cap), dtest_hashmap.get_capacity());

    stest_hashmap.add("San Francisco", std::move(stest_hash1));
    stest_hashmap.add("New York", std::move(stest_hash2));
    // Table load threshold exceeded, so resizing must occur
    EXPECT_EQ(get_next_prime(init_cap), stest_hashmap.get_capacity());
    stest_hashmap.add("Dallas", std::move(stest_hash3));
    // Table load threshold exceeded, so resizing must occur
    EXPECT_EQ(get_next_prime(next_cap), stest_hashmap.get_capacity());
}


// Test function responsible for evaluating whether key is currently stored within main_hashmap
TEST(test_MHSMP, test_mhashmap_contains_key) {
    auto dtest_hash1 = soa_hashmap<double>(5);
    auto stest_hash1 = soa_hashmap<std::string>(5);
    auto dtest_hash2 = soa_hashmap<double>(5);
    auto stest_hash2 = soa_hashmap<std::string>(5);
    auto dtest_hash3 = soa_hashmap<double>(5);
    auto stest_hash3 = soa_hashmap<std::string>(5);
    auto dtest_hash4 = soa_hashmap<double>(5);
    auto stest_hash4 = soa_hashmap<std::string>(5);

    auto dtest_hashmap = main_hashmap<double>(5);
    auto stest_hashmap = main_hashmap<std::string>(5);
    dtest_hashmap.add("San Francisco", std::move(dtest_hash1));
    dtest_hashmap.add("New York", std::move(dtest_hash2));
    dtest_hashmap.add("Houston", std::move(dtest_hash3));
    dtest_hashmap.add("Lufkin", std::move(dtest_hash4));

    stest_hashmap.add("San Francisco", std::move(stest_hash1));
    stest_hashmap.add("New York", std::move(stest_hash2));
    stest_hashmap.add("Dallas", std::move(stest_hash3));
    stest_hashmap.add("Lufkin", std::move(stest_hash4));
    EXPECT_TRUE(dtest_hashmap.contains_key("San Francisco"));
    EXPECT_TRUE(dtest_hashmap.contains_key("New York"));
    EXPECT_TRUE(dtest_hashmap.contains_key("Houston"));
    EXPECT_TRUE(dtest_hashmap.contains_key("Lufkin"));
    EXPECT_FALSE(dtest_hashmap.contains_key("Dallas"));    

    EXPECT_TRUE(stest_hashmap.contains_key("San Francisco"));
    EXPECT_TRUE(stest_hashmap.contains_key("New York"));
    EXPECT_TRUE(stest_hashmap.contains_key("Dallas"));
    EXPECT_TRUE(stest_hashmap.contains_key("Lufkin"));
    EXPECT_FALSE(stest_hashmap.contains_key("Houston")); 
}


// Test function responsible for removing all stored contents within main_hashmap
TEST(test_MHSMP, test_mhashmap_clear) {
    auto dtest_hash1 = soa_hashmap<double>(5);
    auto stest_hash1 = soa_hashmap<std::string>(5);
    auto dtest_hash2 = soa_hashmap<double>(5);
    auto stest_hash2 = soa_hashmap<std::string>(5);
    auto dtest_hash3 = soa_hashmap<double>(5);
    auto stest_hash3 = soa_hashmap<std::string>(5);
    auto dtest_hash4 = soa_hashmap<double>(5);
    auto stest_hash4 = soa_hashmap<std::string>(5);

    auto dtest_hashmap = main_hashmap<double>(5);
    auto stest_hashmap = main_hashmap<std::string>(5);

    EXPECT_EQ(dtest_hashmap.empty_buckets(), dtest_hashmap.get_capacity());
    EXPECT_EQ(stest_hashmap.empty_buckets(), stest_hashmap.get_capacity());
    ASSERT_EQ(dtest_hashmap.get_size(), static_cast<unsigned int>(0));
    ASSERT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(0));
    ASSERT_EQ(dtest_hashmap.get_capacity(), static_cast<unsigned int>(5));
    ASSERT_EQ(stest_hashmap.get_capacity(), static_cast<unsigned int>(5));
    ASSERT_EQ(dtest_hashmap.get_keys().size(), static_cast<size_t>(0));
    ASSERT_EQ(stest_hashmap.get_keys().size(), static_cast<size_t>(0));

    dtest_hashmap.add("San Francisco", std::move(dtest_hash1));
    dtest_hashmap.add("New York", std::move(dtest_hash2));
    dtest_hashmap.add("Houston", std::move(dtest_hash3));
    dtest_hashmap.add("Lufkin", std::move(dtest_hash4));

    stest_hashmap.add("San Francisco", std::move(stest_hash1));
    stest_hashmap.add("New York", std::move(stest_hash2));
    stest_hashmap.add("Dallas", std::move(stest_hash3));
    stest_hashmap.add("Lufkin", std::move(stest_hash4));

    auto new_capacity = dtest_hashmap.get_capacity();
    EXPECT_EQ(new_capacity, stest_hashmap.get_capacity());
    EXPECT_EQ(dtest_hashmap.get_keys().size(), static_cast<size_t>(4));
    EXPECT_EQ(stest_hashmap.get_keys().size(), static_cast<size_t>(4));
    EXPECT_EQ(dtest_hashmap.get_size(), static_cast<unsigned int>(4));
    EXPECT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(4));

    dtest_hashmap.clear();
    stest_hashmap.clear();

    EXPECT_EQ(dtest_hashmap.get_keys().size(), static_cast<size_t>(0));
    EXPECT_EQ(stest_hashmap.get_keys().size(), static_cast<size_t>(0));
    EXPECT_EQ(dtest_hashmap.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(dtest_hashmap.get_capacity(), new_capacity);
    EXPECT_EQ(stest_hashmap.get_capacity(), new_capacity);
    EXPECT_FALSE(dtest_hashmap.contains_key("San Francisco"));
    EXPECT_FALSE(dtest_hashmap.contains_key("New York"));
    EXPECT_FALSE(dtest_hashmap.contains_key("Houston"));
    EXPECT_FALSE(dtest_hashmap.contains_key("Lufkin"));    

    EXPECT_FALSE(stest_hashmap.contains_key("San Francisco"));
    EXPECT_FALSE(stest_hashmap.contains_key("New York"));
    EXPECT_FALSE(stest_hashmap.contains_key("Dallas"));
    EXPECT_FALSE(stest_hashmap.contains_key("Lufkin"));     
}


// Test function responsible for retrieving values associated with keys found within individual soa_hashmap objects stored within main_hashmap class object
TEST(test_MHSMP, test_mhashmap_get_val) {
    auto dtest_hash = std::make_unique<soa_hashmap<double>>(5);
    auto dtest_hash2 = std::make_unique<soa_hashmap<double>>(5);
    auto dtest_hash3 = std::make_unique<soa_hashmap<double>>(5);
    auto empty_dhash = std::make_unique<soa_hashmap<double>>(5);
    auto dtest_hashmap = std::make_unique<main_hashmap<double>>(5);

    auto stest_hash = std::make_unique<soa_hashmap<std::string>>(5);
    auto stest_hash2 = std::make_unique<soa_hashmap<std::string>>(5);
    auto stest_hash3 = std::make_unique<soa_hashmap<std::string>>(5);
    auto empty_shash = std::make_unique<soa_hashmap<std::string>>(5);
    auto stest_hashmap = std::make_unique<main_hashmap<std::string>>(5);

    dtest_hash -> add("San Francisco", 3.0);
    dtest_hash -> add("New York", 10.0);
    dtest_hash -> add("Houston", 15.0);

    dtest_hash2 -> add("Dallas", 56.0);
    dtest_hash2 -> add("Santa Fe", 70.2);
    dtest_hash2 -> add("Seattle", 45.6);

    dtest_hash3 -> add("Chicago", 180.3);
    dtest_hash3 -> add("Oklahoma City", 78.5);
    dtest_hash3 -> add("Denver", 96.2);

    EXPECT_THROW({
    try {
        dtest_hashmap -> get_val("No Where", "No Place");
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: Cannot return key values from an empty main_hashmap object!", e.what());
        throw;
    }
    }, std::exception);

    EXPECT_THROW({
    try {
        stest_hashmap -> get_val("No Where", "No Place");
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: Cannot return key values from an empty main_hashmap object!", e.what());
        throw;
    }
    }, std::exception);

    dtest_hashmap -> add("Miami", std::move(*dtest_hash));
    dtest_hashmap -> add("Las Vegas", std::move(*dtest_hash2));
    dtest_hashmap -> add("Orlando", std::move(*dtest_hash3));

    stest_hash -> add("San Francisco", "New York");
    stest_hash -> add("New York", "Houston");
    stest_hash -> add("Dallas", "San Antonio");

    stest_hash2 -> add("Santa Fe", "Seattle");
    stest_hash2 -> add("Chicago", "Santa Fe");
    stest_hash2 -> add("Oklahoma City", "Portland");

    stest_hash3 -> add("Denver", "Colorado Springs");
    stest_hash3 -> add("Miami", "Sacramento");
    stest_hash3 -> add("Chicago", "San Antonio");

    stest_hashmap -> add("Los Angeles", std::move(*stest_hash));
    stest_hashmap -> add("Cupertino", std::move(*stest_hash2));
    stest_hashmap -> add("Nashville", std::move(*stest_hash3));

    EXPECT_EQ(stest_hashmap -> get_val("Los Angeles", "San Francisco"), "New York");
    EXPECT_EQ(stest_hashmap -> get_val("Los Angeles", "New York"), "Houston");
    EXPECT_EQ(stest_hashmap -> get_val("Los Angeles", "Dallas"), "San Antonio");
    EXPECT_EQ(stest_hashmap -> get_val("Cupertino", "Santa Fe"), "Seattle");
    EXPECT_EQ(stest_hashmap -> get_val("Cupertino", "Chicago"), "Santa Fe");
    EXPECT_EQ(stest_hashmap -> get_val("Cupertino", "Oklahoma City"), "Portland");
    EXPECT_EQ(stest_hashmap -> get_val("Nashville", "Denver"), "Colorado Springs");
    EXPECT_EQ(stest_hashmap -> get_val("Nashville", "Miami"), "Sacramento");
    EXPECT_EQ(stest_hashmap -> get_val("Nashville", "Chicago"), "San Antonio");

    EXPECT_EQ(dtest_hashmap -> get_val("Miami", "San Francisco"), 3.0);
    EXPECT_EQ(dtest_hashmap -> get_val("Miami", "New York"), 10.0);
    EXPECT_EQ(dtest_hashmap -> get_val("Miami", "Houston"), 15.0);
    EXPECT_EQ(dtest_hashmap -> get_val("Las Vegas", "Dallas"), 56.0);
    EXPECT_EQ(dtest_hashmap -> get_val("Las Vegas", "Santa Fe"), 70.2);
    EXPECT_EQ(dtest_hashmap -> get_val("Las Vegas", "Seattle"), 45.6);
    EXPECT_EQ(dtest_hashmap -> get_val("Orlando", "Chicago"), 180.3);
    EXPECT_EQ(dtest_hashmap -> get_val("Orlando", "Oklahoma City"), 78.5);
    EXPECT_EQ(dtest_hashmap -> get_val("Orlando", "Denver"), 96.2);
    EXPECT_EQ(dtest_hashmap -> get_key_by_value("Las Vegas", 70.2), "Santa Fe");
    EXPECT_EQ(stest_hashmap -> get_key_by_value("Nashville", "Sacramento"), "Miami");
    EXPECT_THROW({
    try {
        dtest_hashmap -> get_val("Miami", "NOM");
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: The Existing Hashmap 'Miami' does not contain the key 'NOM'!", e.what());
        throw;
    }
    }, std::exception);
    EXPECT_THROW({
    try {
        stest_hashmap -> get_val("Los Angeles", "NOM");
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: The Existing Hashmap 'Los Angeles' does not contain the key 'NOM'!", e.what());
        throw;
    }
    }, std::exception);
    EXPECT_THROW({
    try {
        dtest_hashmap -> get_val("NOM", "NOM");
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: The key 'NOM' does not exist in calling main_hashmap object!", e.what());
        throw;
    }
    }, std::exception);
    EXPECT_THROW({
    try {
        stest_hashmap -> get_val("NOM", "NOM");
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: The key 'NOM' does not exist in calling main_hashmap object!", e.what());
        throw;
    }
    }, std::exception);
}


// Test function responsible for reporting the number of empty positions within the underlying storage array of main_hashmap
TEST(test_MHSMP, test_mhashmap_empty_buckets) {
    auto dtest_hash1 = soa_hashmap<double>(5);
    auto stest_hash1 = soa_hashmap<std::string>(5);
    auto dtest_hash2 = soa_hashmap<double>(5);
    auto stest_hash2 = soa_hashmap<std::string>(5);
    auto dtest_hash3 = soa_hashmap<double>(5);
    auto stest_hash3 = soa_hashmap<std::string>(5);
    auto dtest_hash4 = soa_hashmap<double>(5);
    auto stest_hash4 = soa_hashmap<std::string>(5);

    auto dtest_hashmap = main_hashmap<double>(5);
    auto stest_hashmap = main_hashmap<std::string>(5);
    ASSERT_EQ(stest_hashmap.empty_buckets(), stest_hashmap.get_capacity());
    ASSERT_EQ(dtest_hashmap.empty_buckets(), dtest_hashmap.get_capacity());
    ASSERT_EQ(dtest_hashmap.get_size(), static_cast<unsigned int>(0));
    ASSERT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(0));
    ASSERT_EQ(dtest_hashmap.get_capacity(), static_cast<unsigned int>(5));
    ASSERT_EQ(stest_hashmap.get_capacity(), static_cast<unsigned int>(5));

    dtest_hashmap.add("San Francisco", std::move(dtest_hash1));
    EXPECT_EQ(dtest_hashmap.get_size(), static_cast<unsigned int>(1));
    EXPECT_EQ(dtest_hashmap.get_capacity(), static_cast<unsigned int>(5));
    EXPECT_EQ(dtest_hashmap.empty_buckets(), dtest_hashmap.get_capacity() - dtest_hashmap.get_size());
    dtest_hashmap.add("New York", std::move(dtest_hash2));
    EXPECT_EQ(dtest_hashmap.get_size(), static_cast<unsigned int>(2));
    EXPECT_EQ(dtest_hashmap.get_capacity(), static_cast<unsigned int>(5));
    EXPECT_EQ(dtest_hashmap.empty_buckets(), dtest_hashmap.get_capacity() - dtest_hashmap.get_size());
    dtest_hashmap.add("Houston", std::move(dtest_hash3));
    EXPECT_EQ(dtest_hashmap.get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(dtest_hashmap.get_capacity(), get_next_prime(5));
    EXPECT_EQ(dtest_hashmap.empty_buckets(), dtest_hashmap.get_capacity() - dtest_hashmap.get_size());
    dtest_hashmap.add("Lufkin", std::move(dtest_hash3));
    EXPECT_EQ(dtest_hashmap.get_size(), static_cast<unsigned int>(4));
    EXPECT_EQ(dtest_hashmap.empty_buckets(), dtest_hashmap.get_capacity() - dtest_hashmap.get_size());

    stest_hashmap.add("San Francisco", std::move(stest_hash1));
    EXPECT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(1));
    EXPECT_EQ(stest_hashmap.get_capacity(), static_cast<unsigned int>(5));
    EXPECT_EQ(stest_hashmap.empty_buckets(), stest_hashmap.get_capacity() - stest_hashmap.get_size());
    stest_hashmap.add("New York", std::move(stest_hash2));
    EXPECT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(2));
    EXPECT_EQ(stest_hashmap.get_capacity(), static_cast<unsigned int>(5));
    EXPECT_EQ(stest_hashmap.empty_buckets(), stest_hashmap.get_capacity() - stest_hashmap.get_size());
    stest_hashmap.add("Dallas", std::move(stest_hash3));
    EXPECT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hashmap.get_capacity(), get_next_prime(5));
    EXPECT_EQ(stest_hashmap.empty_buckets(), stest_hashmap.get_capacity() - stest_hashmap.get_size());
    stest_hashmap.add("Lufkin", std::move(stest_hash4));
    EXPECT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(4));
    EXPECT_EQ(stest_hashmap.empty_buckets(), stest_hashmap.get_capacity() - stest_hashmap.get_size());
}


// Test function responsible for removing a specific key : value pair from the main_hashmap
TEST(test_MHSMP, test_mhashmap_remove) {
    auto dtest_hash1 = soa_hashmap<double>(5);
    auto stest_hash1 = soa_hashmap<std::string>(5);
    auto dtest_hash2 = soa_hashmap<double>(5);
    auto stest_hash2 = soa_hashmap<std::string>(5);
    auto dtest_hash3 = soa_hashmap<double>(5);
    auto stest_hash3 = soa_hashmap<std::string>(5);
    auto dtest_hash4 = soa_hashmap<double>(5);
    auto stest_hash4 = soa_hashmap<std::string>(5);

    auto dtest_hashmap = main_hashmap<double>(5);
    auto stest_hashmap = main_hashmap<std::string>(5);

    ASSERT_EQ(stest_hashmap.empty_buckets(), stest_hashmap.get_capacity());
    ASSERT_EQ(dtest_hashmap.empty_buckets(), dtest_hashmap.get_capacity());
    ASSERT_EQ(dtest_hashmap.get_size(), static_cast<unsigned int>(0));
    ASSERT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(0));
    ASSERT_EQ(dtest_hashmap.get_capacity(), static_cast<unsigned int>(5));
    ASSERT_EQ(stest_hashmap.get_capacity(), static_cast<unsigned int>(5));
    ASSERT_EQ(dtest_hashmap.get_keys().size(), static_cast<size_t>(0));
    ASSERT_EQ(stest_hashmap.get_keys().size(), static_cast<size_t>(0));

    dtest_hashmap.add("San Francisco", std::move(dtest_hash1));
    dtest_hashmap.add("New York", std::move(dtest_hash2));
    dtest_hashmap.add("Houston", std::move(dtest_hash3));
    dtest_hashmap.add("Lufkin", std::move(dtest_hash4));

    stest_hashmap.add("San Francisco", std::move(stest_hash1));
    stest_hashmap.add("New York", std::move(stest_hash2));
    stest_hashmap.add("Dallas", std::move(stest_hash3));
    stest_hashmap.add("Lufkin", std::move(stest_hash4));

    EXPECT_EQ(dtest_hashmap.get_size(), static_cast<unsigned int>(4));
    EXPECT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(4));
    EXPECT_EQ(dtest_hashmap.get_keys().size(), static_cast<size_t>(4));
    EXPECT_EQ(stest_hashmap.get_keys().size(), static_cast<size_t>(4));

    EXPECT_FALSE(dtest_hashmap.contains_key("Billings"));
    EXPECT_FALSE(stest_hashmap.contains_key("Billings"));

    EXPECT_TRUE(dtest_hashmap.contains_key("Houston"));
    EXPECT_TRUE(stest_hashmap.contains_key("Dallas"));
    dtest_hashmap.remove("Houston");
    stest_hashmap.remove("Dallas");
    EXPECT_EQ(dtest_hashmap.get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(dtest_hashmap.get_keys().size(), static_cast<size_t>(3));
    EXPECT_EQ(stest_hashmap.get_keys().size(), static_cast<size_t>(3));
    EXPECT_FALSE(dtest_hashmap.contains_key("Houston"));
    EXPECT_FALSE(stest_hashmap.contains_key("Dallas"));


    EXPECT_TRUE(dtest_hashmap.contains_key("San Francisco"));
    EXPECT_TRUE(stest_hashmap.contains_key("San Francisco"));
    dtest_hashmap.remove("San Francisco");
    stest_hashmap.remove("San Francisco");
    EXPECT_EQ(dtest_hashmap.get_size(), static_cast<unsigned int>(2));
    EXPECT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(2));
    EXPECT_EQ(dtest_hashmap.get_keys().size(), static_cast<size_t>(2));
    EXPECT_EQ(stest_hashmap.get_keys().size(), static_cast<size_t>(2));
    EXPECT_FALSE(dtest_hashmap.contains_key("San Francisco"));
    EXPECT_FALSE(stest_hashmap.contains_key("San Francisco"));


    EXPECT_TRUE(dtest_hashmap.contains_key("Lufkin"));
    EXPECT_TRUE(stest_hashmap.contains_key("Lufkin"));
    dtest_hashmap.remove("Lufkin");
    stest_hashmap.remove("Lufkin");
    EXPECT_EQ(dtest_hashmap.get_size(), static_cast<unsigned int>(1));
    EXPECT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(1));
    EXPECT_EQ(dtest_hashmap.get_keys().size(), static_cast<size_t>(1));
    EXPECT_EQ(stest_hashmap.get_keys().size(), static_cast<size_t>(1));
    EXPECT_FALSE(dtest_hashmap.contains_key("Lufkin"));
    EXPECT_FALSE(stest_hashmap.contains_key("Lufkin"));

    EXPECT_TRUE(dtest_hashmap.contains_key("New York"));
    EXPECT_TRUE(stest_hashmap.contains_key("New York"));     
    dtest_hashmap.remove("New York");
    stest_hashmap.remove("New York");
    EXPECT_EQ(dtest_hashmap.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(dtest_hashmap.get_keys().size(), static_cast<size_t>(0));
    EXPECT_EQ(stest_hashmap.get_keys().size(), static_cast<size_t>(0));
    EXPECT_FALSE(dtest_hashmap.contains_key("New York"));
    EXPECT_FALSE(stest_hashmap.contains_key("New York"));
}


// Test function responsible for retrieving array of all unique keys stored within main_hashmap
TEST(test_MHSMP, test_mhashmap_get_keys) {
    auto dtest_hash1 = soa_hashmap<double>(5);
    auto stest_hash1 = soa_hashmap<std::string>(5);
    auto dtest_hash2 = soa_hashmap<double>(5);
    auto stest_hash2 = soa_hashmap<std::string>(5);
    auto dtest_hash3 = soa_hashmap<double>(5);
    auto stest_hash3 = soa_hashmap<std::string>(5);
    auto dtest_hash4 = soa_hashmap<double>(5);
    auto stest_hash4 = soa_hashmap<std::string>(5);
    auto dtest_hash5 = soa_hashmap<double>(5);
    auto stest_hash5 = soa_hashmap<std::string>(5);
    auto dtest_hash6 = soa_hashmap<double>(5);
    auto stest_hash6 = soa_hashmap<std::string>(5);

    auto dtest_hashmap = main_hashmap<double>(5);
    auto stest_hashmap = main_hashmap<std::string>(5);
    dtest_hashmap.add("San Francisco", std::move(dtest_hash1));
    dtest_hashmap.add("New York", std::move(dtest_hash2));
    dtest_hashmap.add("Houston", std::move(dtest_hash3));
    dtest_hashmap.add("Concord", std::move(dtest_hash4));
    stest_hashmap.add("San Francisco", std::move(stest_hash1));
    stest_hashmap.add("New York", std::move(stest_hash2));
    stest_hashmap.add("Dallas", std::move(stest_hash3));
    stest_hashmap.add("Concord", std::move(stest_hash4));
    ASSERT_EQ(dtest_hashmap.get_keys().size(), static_cast<unsigned int>(4));
    ASSERT_EQ(stest_hashmap.get_keys().size(), static_cast<unsigned int>(4));
    dtest_hashmap.remove("San Francisco");
    stest_hashmap.remove("San Francisco");
    EXPECT_EQ(dtest_hashmap.get_keys().size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hashmap.get_keys().size(), static_cast<unsigned int>(3));
    dtest_hashmap.remove("New York");
    stest_hashmap.remove("New York");
    EXPECT_EQ(dtest_hashmap.get_keys().size(), static_cast<unsigned int>(2));
    EXPECT_EQ(stest_hashmap.get_keys().size(), static_cast<unsigned int>(2));
    dtest_hashmap.remove("Concord");
    stest_hashmap.remove("Concord");
    EXPECT_EQ(dtest_hashmap.get_keys().size(), static_cast<unsigned int>(1));
    EXPECT_EQ(stest_hashmap.get_keys().size(), static_cast<unsigned int>(1));
    EXPECT_EQ(dtest_hashmap.get_keys().front(), "Houston");
    EXPECT_EQ(stest_hashmap.get_keys().front(), "Dallas");
    dtest_hashmap.remove("Houston");
    stest_hashmap.remove("Dallas");
    EXPECT_EQ(dtest_hashmap.get_keys().size(), static_cast<unsigned int>(0));
    EXPECT_EQ(stest_hashmap.get_keys().size(), static_cast<unsigned int>(0));
    dtest_hash5.add("Miami", 36.0);
    stest_hash5.add("Orlando", "Kansas City");
    dtest_hashmap.add("Houston", std::move(dtest_hash5));
    stest_hashmap.add("Dallas", std::move(stest_hash5));
    EXPECT_EQ(dtest_hashmap.get_keys().size(), static_cast<unsigned int>(1));
    EXPECT_EQ(stest_hashmap.get_keys().size(), static_cast<unsigned int>(1));
    EXPECT_EQ(dtest_hashmap.get_keys().front(), "Houston");
    EXPECT_EQ(stest_hashmap.get_keys().front(), "Dallas");
    EXPECT_EQ(dtest_hashmap.get_val("Houston", "Miami"), 36.0);
    EXPECT_EQ(stest_hashmap.get_val("Dallas", "Orlando"), "Kansas City");
    dtest_hash6.add("Miami", 45.0);
    stest_hash6.add("Orlando", "Yorkshire");
    dtest_hashmap.add("Houston", std::move(dtest_hash6));
    stest_hashmap.add("Dallas", std::move(stest_hash6));
    EXPECT_EQ(dtest_hashmap.get_keys().size(), static_cast<unsigned int>(1));
    EXPECT_EQ(stest_hashmap.get_keys().size(), static_cast<unsigned int>(1));
    EXPECT_EQ(dtest_hashmap.get_val("Houston", "Miami"), 45.0);
    EXPECT_EQ(stest_hashmap.get_val("Dallas", "Orlando"), "Yorkshire");
}


// Test function responsible for retrieving/accessing a specified soa_hashmap object stored within main_hashmap
TEST(test_MHSMP, test_get_hash_key) {
    auto dtest_hash = std::make_unique<soa_hashmap<double>>(5);
    auto dtest_hash2 = std::make_unique<soa_hashmap<double>>(5);
    auto dtest_hash3 = std::make_unique<soa_hashmap<double>>(5);
    auto dtest_hashmap = std::make_unique<main_hashmap<double>>(5);

    auto stest_hash = std::make_unique<soa_hashmap<std::string>>(5);
    auto stest_hash2 = std::make_unique<soa_hashmap<std::string>>(5);
    auto stest_hash3 = std::make_unique<soa_hashmap<std::string>>(5);
    auto stest_hashmap = std::make_unique<main_hashmap<std::string>>(5);
    EXPECT_THROW({
    try {
        dtest_hashmap -> get_hash_key("No Where");
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: Cannot return hash keys from an empty main_hashmap object!", e.what());
        throw;
    }
    }, std::exception);

    EXPECT_THROW({
    try {
        stest_hashmap -> get_hash_key("No Where");
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: Cannot return hash keys from an empty main_hashmap object!", e.what());
        throw;
    }
    }, std::exception);
    dtest_hash -> add("San Francisco", 3.0);
    dtest_hash -> add("New York", 10.0);
    dtest_hash -> add("Houston", 15.0);
    dtest_hash -> add("Colombus", 35.6);

    dtest_hash2 -> add("Dallas", 56.0);
    dtest_hash2 -> add("Santa Fe", 70.2);
    dtest_hash2 -> add("Seattle", 45.6);
    dtest_hash2 -> add("Tampa", 125.2);

    dtest_hash3 -> add("Chicago", 180.3);
    dtest_hash3 -> add("Oklahoma City", 78.5);
    dtest_hash3 -> add("Denver", 96.2);
    dtest_hash3 -> add("Atlanta", 478.4);

    ASSERT_EQ(dtest_hash -> get_size(), static_cast<unsigned int>(4));
    ASSERT_EQ(dtest_hash2 -> get_size(), static_cast<unsigned int>(4));
    ASSERT_EQ(dtest_hash3 -> get_size(), static_cast<unsigned int>(4));

    dtest_hashmap -> add("Miami", std::move(*dtest_hash));
    dtest_hashmap -> add("Las Vegas", std::move(*dtest_hash2));
    dtest_hashmap -> add("Orlando", std::move(*dtest_hash3));

    stest_hash -> add("San Francisco", "New York");
    stest_hash -> add("New York", "Houston");
    stest_hash -> add("Dallas", "San Antonio");
    stest_hash -> add("Atlanta", "Junction City");

    stest_hash2 -> add("Santa Fe", "Seattle");
    stest_hash2 -> add("Chicago", "Santa Fe");
    stest_hash2 -> add("Oklahoma City", "Portland");
    stest_hash2 -> add("Salem", "Providence");

    stest_hash3 -> add("Denver", "Colorado Springs");
    stest_hash3 -> add("Miami", "Sacramento");
    stest_hash3 -> add("Chicago", "San Antonio");
    stest_hash3 -> add("Flagstaff", "Grant's Pass");
    ASSERT_EQ(stest_hash -> get_size(), static_cast<unsigned int>(4));
    ASSERT_EQ(stest_hash2 -> get_size(), static_cast<unsigned int>(4));
    ASSERT_EQ(stest_hash3 -> get_size(), static_cast<unsigned int>(4));

    stest_hashmap -> add("Los Angeles", std::move(*stest_hash));
    stest_hashmap -> add("Cupertino", std::move(*stest_hash2));
    stest_hashmap -> add("Nashville", std::move(*stest_hash3));

    ASSERT_EQ(dtest_hashmap -> get_size(), static_cast<unsigned int>(3));
    ASSERT_EQ(stest_hashmap -> get_size(), static_cast<unsigned int>(3));

    EXPECT_EQ(dtest_hashmap -> get_hash_key("Miami").get_val("San Francisco"), 3.0);
    EXPECT_EQ(dtest_hashmap -> get_hash_key("Miami").get_val("New York"), 10.0);
    EXPECT_EQ(dtest_hashmap -> get_hash_key("Miami").get_val("Houston"), 15.0);
    EXPECT_EQ(dtest_hashmap -> get_hash_key("Miami").get_val("Colombus"), 35.6);
    EXPECT_EQ(dtest_hashmap -> get_hash_key("Las Vegas").get_val("Dallas"), 56.0);
    EXPECT_EQ(dtest_hashmap -> get_hash_key("Las Vegas").get_val("Santa Fe"), 70.2);
    EXPECT_EQ(dtest_hashmap -> get_hash_key("Las Vegas").get_val("Seattle"), 45.6);
    EXPECT_EQ(dtest_hashmap -> get_hash_key("Las Vegas").get_val("Tampa"), 125.2);
    EXPECT_EQ(dtest_hashmap -> get_hash_key("Orlando").get_val("Chicago"), 180.3);
    EXPECT_EQ(dtest_hashmap -> get_hash_key("Orlando").get_val("Oklahoma City"), 78.5);
    EXPECT_EQ(dtest_hashmap -> get_hash_key("Orlando").get_val("Denver"), 96.2);
    EXPECT_EQ(dtest_hashmap -> get_hash_key("Orlando").get_val("Atlanta"), 478.4);

    EXPECT_EQ(stest_hashmap -> get_hash_key("Los Angeles").get_val("San Francisco"), "New York");
    EXPECT_EQ(stest_hashmap -> get_hash_key("Los Angeles").get_val("New York"), "Houston");
    EXPECT_EQ(stest_hashmap -> get_hash_key("Los Angeles").get_val("Dallas"), "San Antonio");
    EXPECT_EQ(stest_hashmap -> get_hash_key("Los Angeles").get_val("Atlanta"), "Junction City");
    EXPECT_EQ(stest_hashmap -> get_hash_key("Cupertino").get_val("Santa Fe"), "Seattle");
    EXPECT_EQ(stest_hashmap -> get_hash_key("Cupertino").get_val("Chicago"), "Santa Fe");
    EXPECT_EQ(stest_hashmap -> get_hash_key("Cupertino").get_val("Oklahoma City"), "Portland");
    EXPECT_EQ(stest_hashmap -> get_hash_key("Cupertino").get_val("Salem"), "Providence");
    EXPECT_EQ(stest_hashmap -> get_hash_key("Nashville").get_val("Denver"), "Colorado Springs");
    EXPECT_EQ(stest_hashmap -> get_hash_key("Nashville").get_val("Miami"), "Sacramento");
    EXPECT_EQ(stest_hashmap -> get_hash_key("Nashville").get_val("Chicago"), "San Antonio");
    EXPECT_EQ(stest_hashmap -> get_hash_key("Nashville").get_val("Flagstaff"), "Grant's Pass");
    EXPECT_TRUE(dtest_hashmap -> get_hash_key("Miami").contains_key("Colombus"));
    EXPECT_TRUE(stest_hashmap -> get_hash_key("Los Angeles").contains_key("Atlanta"));

    dtest_hashmap -> get_hash_key("Miami").remove("Colombus");
    stest_hashmap -> get_hash_key("Los Angeles").remove("Atlanta");
    EXPECT_EQ(dtest_hashmap -> get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hashmap -> get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(dtest_hashmap -> get_hash_key("Miami").get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hashmap -> get_hash_key("Los Angeles").get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(dtest_hashmap -> get_hash_key("Miami").get_keys().size(), static_cast<size_t>(3));
    EXPECT_EQ(stest_hashmap -> get_hash_key("Los Angeles").get_keys().size(), static_cast<size_t>(3));
    EXPECT_FALSE(dtest_hashmap -> get_hash_key("Miami").contains_key("Colombus"));
    EXPECT_FALSE(stest_hashmap -> get_hash_key("Los Angeles").contains_key("Atlanta"));

    dtest_hashmap -> remove("Orlando");
    stest_hashmap -> remove("Nashville");
    EXPECT_EQ(dtest_hashmap -> get_size(), static_cast<unsigned int>(2));
    EXPECT_EQ(stest_hashmap -> get_size(), static_cast<unsigned int>(2));

    EXPECT_THROW({
    try {
        dtest_hashmap -> get_hash_key("Orlando");
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: Main Hashmap does not contain an existing hashmap named 'Orlando'!", e.what());
        throw;
    }
    }, std::exception);

    EXPECT_THROW({
    try {
        stest_hashmap -> get_hash_key("Nashville");
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: Main Hashmap does not contain an existing hashmap named 'Nashville'!", e.what());
        throw;
    }
    }, std::exception);
}


// Test function responsible for retrieving the key associated with a specified value from within a specified soa_hashmap object stored within main_hashmap
TEST(test_MHSMP, test_get_key_by_val) {
    auto dtest_hash = std::make_unique<soa_hashmap<double>>(5);
    auto dtest_hash2 = std::make_unique<soa_hashmap<double>>(5);
    auto dtest_hash3 = std::make_unique<soa_hashmap<double>>(5);
    auto dtest_hashmap = std::make_unique<main_hashmap<double>>(5);

    auto stest_hash = std::make_unique<soa_hashmap<std::string>>(5);
    auto stest_hash2 = std::make_unique<soa_hashmap<std::string>>(5);
    auto stest_hash3 = std::make_unique<soa_hashmap<std::string>>(5);
    auto stest_hashmap = std::make_unique<main_hashmap<std::string>>(5);
    EXPECT_THROW({
    try {
        dtest_hashmap -> get_key_by_value("No Where", 10.5);
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: Cannot return keys associated to a value when main_hashmap is empty!", e.what());
        throw;
    }
    }, std::exception);

    EXPECT_THROW({
    try {
        stest_hashmap -> get_key_by_value("No Where", "No Place");
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: Cannot return keys associated to a value when main_hashmap is empty!", e.what());
        throw;
    }
    }, std::exception);
    dtest_hash -> add("San Francisco", 3.0);
    dtest_hash -> add("New York", 10.0);
    dtest_hash -> add("Houston", 15.0);
    dtest_hash -> add("Colombus", 35.6);

    dtest_hash2 -> add("Dallas", 56.0);
    dtest_hash2 -> add("Santa Fe", 70.2);
    dtest_hash2 -> add("Seattle", 45.6);
    dtest_hash2 -> add("Tampa", 125.2);

    dtest_hash3 -> add("Chicago", 180.3);
    dtest_hash3 -> add("Oklahoma City", 78.5);
    dtest_hash3 -> add("Denver", 96.2);
    dtest_hash3 -> add("Atlanta", 478.4);

    ASSERT_EQ(dtest_hash -> get_size(), static_cast<unsigned int>(4));
    ASSERT_EQ(dtest_hash2 -> get_size(), static_cast<unsigned int>(4));
    ASSERT_EQ(dtest_hash3 -> get_size(), static_cast<unsigned int>(4));

    dtest_hashmap -> add("Miami", std::move(*dtest_hash));
    dtest_hashmap -> add("Las Vegas", std::move(*dtest_hash2));
    dtest_hashmap -> add("Orlando", std::move(*dtest_hash3));

    stest_hash -> add("San Francisco", "New York");
    stest_hash -> add("New York", "Houston");
    stest_hash -> add("Dallas", "San Antonio");
    stest_hash -> add("Atlanta", "Junction City");

    stest_hash2 -> add("Santa Fe", "Seattle");
    stest_hash2 -> add("Chicago", "Santa Fe");
    stest_hash2 -> add("Oklahoma City", "Portland");
    stest_hash2 -> add("Salem", "Providence");

    stest_hash3 -> add("Denver", "Colorado Springs");
    stest_hash3 -> add("Miami", "Sacramento");
    stest_hash3 -> add("Chicago", "San Antonio");
    stest_hash3 -> add("Flagstaff", "Grant's Pass");
    ASSERT_EQ(stest_hash -> get_size(), static_cast<unsigned int>(4));
    ASSERT_EQ(stest_hash2 -> get_size(), static_cast<unsigned int>(4));
    ASSERT_EQ(stest_hash3 -> get_size(), static_cast<unsigned int>(4));

    stest_hashmap -> add("Los Angeles", std::move(*stest_hash));
    stest_hashmap -> add("Cupertino", std::move(*stest_hash2));
    stest_hashmap -> add("Nashville", std::move(*stest_hash3));

    ASSERT_EQ(dtest_hashmap -> get_size(), static_cast<unsigned int>(3));
    ASSERT_EQ(stest_hashmap -> get_size(), static_cast<unsigned int>(3));

    EXPECT_EQ(dtest_hashmap -> get_key_by_value("Miami", 3.0), "San Francisco");
    EXPECT_EQ(dtest_hashmap -> get_key_by_value("Miami", 10.0), "New York");
    EXPECT_EQ(dtest_hashmap -> get_key_by_value("Miami", 15.0), "Houston");
    EXPECT_EQ(dtest_hashmap -> get_key_by_value("Miami", 35.6), "Colombus");
    EXPECT_EQ(dtest_hashmap -> get_key_by_value("Las Vegas", 56.0), "Dallas");
    EXPECT_EQ(dtest_hashmap -> get_key_by_value("Las Vegas", 70.2), "Santa Fe");
    EXPECT_EQ(dtest_hashmap -> get_key_by_value("Las Vegas", 45.6), "Seattle");
    EXPECT_EQ(dtest_hashmap -> get_key_by_value("Las Vegas", 125.2), "Tampa");
    EXPECT_EQ(dtest_hashmap -> get_key_by_value("Orlando", 180.3), "Chicago");
    EXPECT_EQ(dtest_hashmap -> get_key_by_value("Orlando", 78.5), "Oklahoma City");
    EXPECT_EQ(dtest_hashmap -> get_key_by_value("Orlando", 96.2), "Denver");
    EXPECT_EQ(dtest_hashmap -> get_key_by_value("Orlando", 478.4), "Atlanta");

    EXPECT_EQ(stest_hashmap -> get_key_by_value("Los Angeles", "New York"), "San Francisco");
    EXPECT_EQ(stest_hashmap -> get_key_by_value("Los Angeles", "Houston"), "New York");
    EXPECT_EQ(stest_hashmap -> get_key_by_value("Los Angeles", "San Antonio"), "Dallas");
    EXPECT_EQ(stest_hashmap -> get_key_by_value("Los Angeles", "Junction City"), "Atlanta");
    EXPECT_EQ(stest_hashmap -> get_key_by_value("Cupertino", "Seattle"), "Santa Fe");
    EXPECT_EQ(stest_hashmap -> get_key_by_value("Cupertino", "Santa Fe"), "Chicago");
    EXPECT_EQ(stest_hashmap -> get_key_by_value("Cupertino", "Portland"), "Oklahoma City");
    EXPECT_EQ(stest_hashmap -> get_key_by_value("Cupertino", "Providence"), "Salem");
    EXPECT_EQ(stest_hashmap -> get_key_by_value("Nashville", "Colorado Springs"), "Denver");
    EXPECT_EQ(stest_hashmap -> get_key_by_value("Nashville", "Sacramento"), "Miami");
    EXPECT_EQ(stest_hashmap -> get_key_by_value("Nashville", "San Antonio"), "Chicago");
    EXPECT_EQ(stest_hashmap -> get_key_by_value("Nashville", "Grant's Pass"), "Flagstaff");

    dtest_hashmap -> get_hash_key("Miami").remove("Colombus");
    stest_hashmap -> get_hash_key("Los Angeles").remove("Atlanta");
    EXPECT_EQ(dtest_hashmap -> get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hashmap -> get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(dtest_hashmap -> get_hash_key("Miami").get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hashmap -> get_hash_key("Los Angeles").get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(dtest_hashmap -> get_hash_key("Miami").get_keys().size(), static_cast<size_t>(3));
    EXPECT_EQ(stest_hashmap -> get_hash_key("Los Angeles").get_keys().size(), static_cast<size_t>(3));
    EXPECT_FALSE(dtest_hashmap -> get_hash_key("Miami").contains_key("Colombus"));
    EXPECT_FALSE(stest_hashmap -> get_hash_key("Los Angeles").contains_key("Atlanta"));

    EXPECT_THROW({
    try {
        dtest_hashmap -> get_key_by_value("Miami", 10.5);
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: The Existing Hashmap 'Miami' does not contain any keys with the entered value!", e.what());
        throw;
    }
    }, std::exception);

    EXPECT_THROW({
    try {
        stest_hashmap -> get_key_by_value("Los Angeles", "No Place");
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: The Existing Hashmap 'Los Angeles' does not contain any keys with the entered value!", e.what());
        throw;
    }
    }, std::exception);

    dtest_hashmap -> remove("Orlando");
    stest_hashmap -> remove("Nashville");
    EXPECT_EQ(dtest_hashmap -> get_size(), static_cast<unsigned int>(2));
    EXPECT_EQ(stest_hashmap -> get_size(), static_cast<unsigned int>(2));

    EXPECT_THROW({
    try {
        dtest_hashmap -> get_key_by_value("Orlando", 3.0);
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: The Main Hashmap does not contain any existing hashmaps with key of 'Orlando'!", e.what());
        throw;
    }
    }, std::exception);

    EXPECT_THROW({
    try {
        stest_hashmap -> get_key_by_value("Nashville", "Chicago");
    } catch (const std::exception& e) {
        EXPECT_STREQ("ERROR: The Main Hashmap does not contain any existing hashmaps with key of 'Nashville'!", e.what());
        throw;
    }
    }, std::exception);
}


// Test constructor for initializing main_hashmap class object instances with pre-defined storage capacity values
TEST(test_MHSMP, test_mhashmap_capacity_constructor) {
    auto dtest_hash = std::make_unique<soa_hashmap<double>>(5);
    auto dtest_hash2 = std::make_unique<soa_hashmap<double>>(5);
    auto dtest_hash3 = std::make_unique<soa_hashmap<double>>(5);
    auto dtest_hashmap = std::make_unique<main_hashmap<double>>(5);

    auto stest_hash = std::make_unique<soa_hashmap<std::string>>(5);
    auto stest_hash2 = std::make_unique<soa_hashmap<std::string>>(5);
    auto stest_hash3 = std::make_unique<soa_hashmap<std::string>>(5);
    auto stest_hashmap = std::make_unique<main_hashmap<std::string>>(5);

    dtest_hash -> add("San Francisco", 3.0);
    dtest_hash -> add("New York", 10.0);
    dtest_hash -> add("Houston", 15.0);

    dtest_hash2 -> add("Dallas", 56.0);
    dtest_hash2 -> add("Santa Fe", 70.2);
    dtest_hash2 -> add("Seattle", 45.6);

    dtest_hash3 -> add("Chicago", 180.3);
    dtest_hash3 -> add("Oklahoma City", 78.5);
    dtest_hash3 -> add("Denver", 96.2);
    EXPECT_EQ(dtest_hash -> get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(dtest_hash2 -> get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(dtest_hash3 -> get_size(), static_cast<unsigned int>(3));

    dtest_hashmap -> add("Miami", std::move(*dtest_hash));
    dtest_hashmap -> add("Las Vegas", std::move(*dtest_hash2));
    dtest_hashmap -> add("Orlando", std::move(*dtest_hash3));

    stest_hash -> add("San Francisco", "New York");
    stest_hash -> add("New York", "Houston");
    stest_hash -> add("Dallas", "San Antonio");

    stest_hash2 -> add("Santa Fe", "Seattle");
    stest_hash2 -> add("Chicago", "Santa Fe");
    stest_hash2 -> add("Oklahoma City", "Portland");

    stest_hash3 -> add("Denver", "Colorado Springs");
    stest_hash3 -> add("Miami", "Sacramento");
    stest_hash3 -> add("Chicago", "San Antonio");
    EXPECT_EQ(stest_hash -> get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hash2 -> get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hash3 -> get_size(), static_cast<unsigned int>(3));

    stest_hashmap -> add("Los Angeles", std::move(*stest_hash));
    stest_hashmap -> add("Cupertino", std::move(*stest_hash2));
    stest_hashmap -> add("Nashville", std::move(*stest_hash3));


    EXPECT_EQ(dtest_hashmap -> get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hashmap -> get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hashmap -> get_val("Los Angeles", "San Francisco"), "New York");
    EXPECT_EQ(stest_hashmap -> get_val("Los Angeles", "New York"), "Houston");
    EXPECT_EQ(stest_hashmap -> get_val("Los Angeles", "Dallas"), "San Antonio");
    EXPECT_EQ(stest_hashmap -> get_val("Cupertino", "Santa Fe"), "Seattle");
    EXPECT_EQ(stest_hashmap -> get_val("Cupertino", "Chicago"), "Santa Fe");
    EXPECT_EQ(stest_hashmap -> get_val("Cupertino", "Oklahoma City"), "Portland");
    EXPECT_EQ(stest_hashmap -> get_val("Nashville", "Denver"), "Colorado Springs");
    EXPECT_EQ(stest_hashmap -> get_val("Nashville", "Miami"), "Sacramento");
    EXPECT_EQ(stest_hashmap -> get_val("Nashville", "Chicago"), "San Antonio");

    EXPECT_EQ(dtest_hashmap -> get_val("Miami", "San Francisco"), 3.0);
    EXPECT_EQ(dtest_hashmap -> get_val("Miami", "New York"), 10.0);
    EXPECT_EQ(dtest_hashmap -> get_val("Miami", "Houston"), 15.0);
    EXPECT_EQ(dtest_hashmap -> get_val("Las Vegas", "Dallas"), 56.0);
    EXPECT_EQ(dtest_hashmap -> get_val("Las Vegas", "Santa Fe"), 70.2);
    EXPECT_EQ(dtest_hashmap -> get_val("Las Vegas", "Seattle"), 45.6);
    EXPECT_EQ(dtest_hashmap -> get_val("Orlando", "Chicago"), 180.3);
    EXPECT_EQ(dtest_hashmap -> get_val("Orlando", "Oklahoma City"), 78.5);
    EXPECT_EQ(dtest_hashmap -> get_val("Orlando", "Denver"), 96.2);
}


// Test move constructor for transfering ownership/resources between different main_hashmap class object instances
TEST(test_MHSMP, test_mhashmap_move_constructor) {
    auto dtest_hash = std::make_unique<soa_hashmap<double>>(5);
    auto dtest_hash2 = std::make_unique<soa_hashmap<double>>(5);
    auto dtest_hash3 = std::make_unique<soa_hashmap<double>>(5);
    auto dtest_hashmap = std::make_unique<main_hashmap<double>>(5);

    auto stest_hash = std::make_unique<soa_hashmap<std::string>>(5);
    auto stest_hash2 = std::make_unique<soa_hashmap<std::string>>(5);
    auto stest_hash3 = std::make_unique<soa_hashmap<std::string>>(5);
    auto stest_hashmap = std::make_unique<main_hashmap<std::string>>(5);

    dtest_hash -> add("San Francisco", 3.0);
    dtest_hash -> add("New York", 10.0);
    dtest_hash -> add("Houston", 15.0);

    dtest_hash2 -> add("Dallas", 56.0);
    dtest_hash2 -> add("Santa Fe", 70.2);
    dtest_hash2 -> add("Seattle", 45.6);

    dtest_hash3 -> add("Chicago", 180.3);
    dtest_hash3 -> add("Oklahoma City", 78.5);
    dtest_hash3 -> add("Denver", 96.2);
    EXPECT_EQ(dtest_hash -> get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(dtest_hash2 -> get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(dtest_hash3 -> get_size(), static_cast<unsigned int>(3));

    dtest_hashmap -> add("Miami", std::move(*dtest_hash));
    dtest_hashmap -> add("Las Vegas", std::move(*dtest_hash2));
    dtest_hashmap -> add("Orlando", std::move(*dtest_hash3));

    stest_hash -> add("San Francisco", "New York");
    stest_hash -> add("New York", "Houston");
    stest_hash -> add("Dallas", "San Antonio");

    stest_hash2 -> add("Santa Fe", "Seattle");
    stest_hash2 -> add("Chicago", "Santa Fe");
    stest_hash2 -> add("Oklahoma City", "Portland");

    stest_hash3 -> add("Denver", "Colorado Springs");
    stest_hash3 -> add("Miami", "Sacramento");
    stest_hash3 -> add("Chicago", "San Antonio");
    EXPECT_EQ(stest_hash -> get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hash2 -> get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hash3 -> get_size(), static_cast<unsigned int>(3));

    stest_hashmap -> add("Los Angeles", std::move(*stest_hash));
    stest_hashmap -> add("Cupertino", std::move(*stest_hash2));
    stest_hashmap -> add("Nashville", std::move(*stest_hash3));


    EXPECT_EQ(dtest_hashmap -> get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hashmap -> get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hashmap -> get_val("Los Angeles", "San Francisco"), "New York");
    EXPECT_EQ(stest_hashmap -> get_val("Los Angeles", "New York"), "Houston");
    EXPECT_EQ(stest_hashmap -> get_val("Los Angeles", "Dallas"), "San Antonio");
    EXPECT_EQ(stest_hashmap -> get_val("Cupertino", "Santa Fe"), "Seattle");
    EXPECT_EQ(stest_hashmap -> get_val("Cupertino", "Chicago"), "Santa Fe");
    EXPECT_EQ(stest_hashmap -> get_val("Cupertino", "Oklahoma City"), "Portland");
    EXPECT_EQ(stest_hashmap -> get_val("Nashville", "Denver"), "Colorado Springs");
    EXPECT_EQ(stest_hashmap -> get_val("Nashville", "Miami"), "Sacramento");
    EXPECT_EQ(stest_hashmap -> get_val("Nashville", "Chicago"), "San Antonio");

    EXPECT_EQ(dtest_hashmap -> get_val("Miami", "San Francisco"), 3.0);
    EXPECT_EQ(dtest_hashmap -> get_val("Miami", "New York"), 10.0);
    EXPECT_EQ(dtest_hashmap -> get_val("Miami", "Houston"), 15.0);
    EXPECT_EQ(dtest_hashmap -> get_val("Las Vegas", "Dallas"), 56.0);
    EXPECT_EQ(dtest_hashmap -> get_val("Las Vegas", "Santa Fe"), 70.2);
    EXPECT_EQ(dtest_hashmap -> get_val("Las Vegas", "Seattle"), 45.6);
    EXPECT_EQ(dtest_hashmap -> get_val("Orlando", "Chicago"), 180.3);
    EXPECT_EQ(dtest_hashmap -> get_val("Orlando", "Oklahoma City"), 78.5);
    EXPECT_EQ(dtest_hashmap -> get_val("Orlando", "Denver"), 96.2);

    auto dtransfer_hashmap = std::move(*dtest_hashmap);
    auto stransfer_hashmap = std::move(*stest_hashmap);

    EXPECT_EQ(dtransfer_hashmap.get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(dtransfer_hashmap.get_keys().size(), static_cast<size_t>(3));
    EXPECT_EQ(stransfer_hashmap.get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stransfer_hashmap.get_keys().size(), static_cast<size_t>(3));

    EXPECT_EQ(stransfer_hashmap.get_val("Los Angeles", "San Francisco"), "New York");
    EXPECT_EQ(stransfer_hashmap.get_val("Los Angeles", "New York"), "Houston");
    EXPECT_EQ(stransfer_hashmap.get_val("Los Angeles", "Dallas"), "San Antonio");
    EXPECT_EQ(stransfer_hashmap.get_val("Cupertino", "Santa Fe"), "Seattle");
    EXPECT_EQ(stransfer_hashmap.get_val("Cupertino", "Chicago"), "Santa Fe");
    EXPECT_EQ(stransfer_hashmap.get_val("Cupertino", "Oklahoma City"), "Portland");
    EXPECT_EQ(stransfer_hashmap.get_val("Nashville", "Denver"), "Colorado Springs");
    EXPECT_EQ(stransfer_hashmap.get_val("Nashville", "Miami"), "Sacramento");
    EXPECT_EQ(stransfer_hashmap.get_val("Nashville", "Chicago"), "San Antonio");

    EXPECT_EQ(dtransfer_hashmap.get_val("Miami", "San Francisco"), 3.0);
    EXPECT_EQ(dtransfer_hashmap.get_val("Miami", "New York"), 10.0);
    EXPECT_EQ(dtransfer_hashmap.get_val("Miami", "Houston"), 15.0);
    EXPECT_EQ(dtransfer_hashmap.get_val("Las Vegas", "Dallas"), 56.0);
    EXPECT_EQ(dtransfer_hashmap.get_val("Las Vegas", "Santa Fe"), 70.2);
    EXPECT_EQ(dtransfer_hashmap.get_val("Las Vegas", "Seattle"), 45.6);
    EXPECT_EQ(dtransfer_hashmap.get_val("Orlando", "Chicago"), 180.3);
    EXPECT_EQ(dtransfer_hashmap.get_val("Orlando", "Oklahoma City"), 78.5);
    EXPECT_EQ(dtransfer_hashmap.get_val("Orlando", "Denver"), 96.2);
}

