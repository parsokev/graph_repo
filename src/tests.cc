#include <gtest/gtest.h>
#include <stdexcept>
#include <tuple>

#include "../includes/pair_minheap.hpp"
#include "../src/gprintf.cpp"
#include "../src/derived_hashmap.cpp"

// Test Suite test_PMNHP: MINIMUM BINARY HEAP OF KEY:VALUE PAIR NODES Functions
// Test paired_min_heap

// Test 1: Test get_heap_size
// Test 2: Test add_node
// Test 3: Test min_percolate/evaluate_children
// Test 4: Test remove_min
// Test 5: Test paired_min_heap constructor(s)

TEST(test_PRMNHP, test_get_heap_size) {
    auto test_heap = paired_min_heap<double>(5);
    EXPECT_EQ(test_heap.get_heap_size(), 0);
    test_heap.add_node("first_node", 0);
    test_heap.add_node("second_node", 3);
    EXPECT_EQ(test_heap.get_heap_size(), 2);
}

TEST(test_PRMNHP, test_add_node) {
    auto test_heap = paired_min_heap<double>(5);
    EXPECT_EQ(test_heap.get_heap_size(), 0);
    test_heap.add_node("first_node", 5);
    EXPECT_EQ(test_heap.get_heap_size(), 1);
    std::string key;
    double value;
    std::tie(key, value) = test_heap.get_min();
    EXPECT_EQ(key, "first_node");
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

TEST(test_PRMNHP, test_get_min) {
    auto test_heap = paired_min_heap<double>(5);
    test_heap.add_node("first_node", 0);
    test_heap.add_node("second_node", 3);
    std::string key;
    double value;
    std::tie(key, value) = test_heap.get_min();
    EXPECT_EQ(key, "first_node");
    EXPECT_EQ(value, 0);
    EXPECT_EQ(test_heap.get_heap_size(), 2);
}

TEST(test_PRMNHP, test_min_percolate) {
    auto test_heap = paired_min_heap<double>(5);
    test_heap.add_node("first_node", 5);
    test_heap.add_node("second_node", 10);
    test_heap.add_node("third_node", 3);
    test_heap.add_node("fourth_node", 2);
    std::string key;
    double value;
    std::tie(key, value) = test_heap.get_min();
    EXPECT_EQ("fourth_node", key);
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
            EXPECT_STREQ("Index to be percolated is outside the bounds of the heap array!", e.what());
            throw;
        }
    }, std::exception);
    EXPECT_THROW({
        try {
            test_heap.min_percolate(-1);
        } catch (const std::exception& e) {
            EXPECT_STREQ("Index to be percolated is outside the bounds of the heap array!", e.what());
            throw;
        }
    }, std::exception);
    // ASSERT_DEATH(test_heap.min_percolate(4), "Passed index is out of bounds of array!");
    // ASSERT_DEATH(test_heap.min_percolate(-1), "Passed index is out of bounds of array!");
}

TEST(test_PRMNHP, test_remove_min) {
    auto test_heap = paired_min_heap<double>(5);
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
    EXPECT_EQ("fifth_node", key);
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
            EXPECT_STREQ("Cannot remove minimum value from an empty paired_minheap object!", e.what());
            throw;
        }
    }, std::exception);
    // ASSERT_DEATH(test_heap.remove_min(), "Heap is empty!");    
}


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
    std::vector<std::pair<std::string, double>> heap_vals = {miami, harvard, los_angeles, new_york, fresno, redding, san_francisco, las_vegas, detroit, medford, dallas, phoenix, seattle, portland, orlando, colorado_springs};
    auto min_heap = make_unique<paired_min_heap<double>>(heap_vals);
    ASSERT_EQ(min_heap -> get_heap_size(), 16);
    std::string key;
    double value;
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Redding");
    ASSERT_EQ(value, 1.3);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Harvard");
    ASSERT_EQ(value, 2.0);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "New York");
    ASSERT_EQ(value, 3.6);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Fresno");
    ASSERT_EQ(value, 10.0);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Las Vegas");
    ASSERT_EQ(value, 14.0);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Medford");
    ASSERT_EQ(value, 14.7);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Los Angeles");
    ASSERT_EQ(value, 15.3);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Portland");
    ASSERT_EQ(value, 18.9);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Phoenix");
    ASSERT_EQ(value, 24.3);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Miami");
    ASSERT_EQ(value, 25.0);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Dallas");
    ASSERT_EQ(value, 34.1);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Seattle");
    ASSERT_EQ(value, 47.6);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "San Francisco");
    ASSERT_EQ(value, 50.2);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Colorado Springs");
    ASSERT_EQ(value, 56.8);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Detroit");
    ASSERT_EQ(value, 70.4);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Orlando");
    ASSERT_EQ(value, 100.5);
    ASSERT_EQ(min_heap -> get_heap_size(), 0);
}

TEST(test_PRMNHP, test_heap_capacity_constructor) {
    auto min_heap = std::make_unique<paired_min_heap<double>>(16);
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
    ASSERT_EQ(min_heap -> get_heap_size(), 16);

    std::string key;
    double value;
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Redding");
    ASSERT_EQ(value, 1.3);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Harvard");
    ASSERT_EQ(value, 2.0);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "New York");
    ASSERT_EQ(value, 3.6);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Fresno");
    ASSERT_EQ(value, 10.0);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Las Vegas");
    ASSERT_EQ(value, 14.0);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Medford");
    ASSERT_EQ(value, 14.7);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Los Angeles");
    ASSERT_EQ(value, 15.3);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Portland");
    ASSERT_EQ(value, 18.9);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Phoenix");
    ASSERT_EQ(value, 24.3);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Miami");
    ASSERT_EQ(value, 25.0);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Dallas");
    ASSERT_EQ(value, 34.1);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Seattle");
    ASSERT_EQ(value, 47.6);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "San Francisco");
    ASSERT_EQ(value, 50.2);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Colorado Springs");
    ASSERT_EQ(value, 56.8);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Detroit");
    ASSERT_EQ(value, 70.4);
    std::tie(key, value) = min_heap -> remove_min();
    ASSERT_EQ(key, "Orlando");
    ASSERT_EQ(value, 100.5);
    ASSERT_EQ(min_heap -> get_heap_size(), 0);
    // std::tie(key, value) = min_heap -> remove_min();

    // std::cout << min_heap << '\n';
    // std::tie(key, value) = min_heap -> remove_min();

    // std::cout << min_heap << '\n';
    // std::tie(key, value) = min_heap -> remove_min();
}

TEST(test_PRMNHP, test_heap_move_constructor) {
    auto min_heap = std::make_unique<paired_min_heap<double>>(16);
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
    ASSERT_EQ(min_heap -> get_heap_size(), 16);
    auto transfer_heap = std::move(min_heap);
    ASSERT_EQ(transfer_heap -> get_heap_size(), 16);
    transfer_heap -> add_node("Ontario", 600.5);
    transfer_heap -> add_node("London", 2000.5);
    ASSERT_EQ(transfer_heap -> get_heap_size(), 18);
    std::string key;
    double value;
    std::tie(key, value) = transfer_heap -> remove_min();
    ASSERT_EQ(key, "Redding");
    ASSERT_EQ(value, 1.3);
    std::tie(key, value) = transfer_heap -> remove_min();
    ASSERT_EQ(key, "Harvard");
    ASSERT_EQ(value, 2.0);
    std::tie(key, value) = transfer_heap -> remove_min();
    ASSERT_EQ(key, "New York");
    ASSERT_EQ(value, 3.6);
    std::tie(key, value) = transfer_heap -> remove_min();
    ASSERT_EQ(key, "Fresno");
    ASSERT_EQ(value, 10.0);
    std::tie(key, value) = transfer_heap -> remove_min();
    ASSERT_EQ(key, "Las Vegas");
    ASSERT_EQ(value, 14.0);
    std::tie(key, value) = transfer_heap -> remove_min();
    ASSERT_EQ(key, "Medford");
    ASSERT_EQ(value, 14.7);
    std::tie(key, value) = transfer_heap -> remove_min();
    ASSERT_EQ(key, "Los Angeles");
    ASSERT_EQ(value, 15.3);
    std::tie(key, value) = transfer_heap -> remove_min();
    ASSERT_EQ(key, "Portland");
    ASSERT_EQ(value, 18.9);
    std::tie(key, value) = transfer_heap -> remove_min();
    ASSERT_EQ(key, "Phoenix");
    ASSERT_EQ(value, 24.3);
    std::tie(key, value) = transfer_heap -> remove_min();
    ASSERT_EQ(key, "Miami");
    ASSERT_EQ(value, 25.0);
    std::tie(key, value) = transfer_heap -> remove_min();
    ASSERT_EQ(key, "Dallas");
    ASSERT_EQ(value, 34.1);
    std::tie(key, value) = transfer_heap -> remove_min();
    ASSERT_EQ(key, "Seattle");
    ASSERT_EQ(value, 47.6);
    std::tie(key, value) = transfer_heap -> remove_min();
    ASSERT_EQ(key, "San Francisco");
    ASSERT_EQ(value, 50.2);
    std::tie(key, value) = transfer_heap -> remove_min();
    ASSERT_EQ(key, "Colorado Springs");
    ASSERT_EQ(value, 56.8);
    std::tie(key, value) = transfer_heap -> remove_min();
    ASSERT_EQ(key, "Detroit");
    ASSERT_EQ(value, 70.4);
    std::tie(key, value) = transfer_heap -> remove_min();
    ASSERT_EQ(key, "Orlando");
    ASSERT_EQ(value, 100.5);
    std::tie(key, value) = transfer_heap -> remove_min();
    ASSERT_EQ(key, "Ontario");
    ASSERT_EQ(value, 600.5);
    std::tie(key, value) = transfer_heap -> remove_min();
    ASSERT_EQ(key, "London");
    ASSERT_EQ(value, 2000.5);
    ASSERT_EQ(transfer_heap -> get_heap_size(), 0);
}

// Test Suite test_SOAHSMP: OPEN-ADDRESSING HASHMAP Functions
// Test soa_hashmap
// Test 1: Test apply_hash_function
// Test 2: Test is_prime
// Test 3: Test get_next_prime
// Test 4: Test get_size
// Test 5: Test get_capacity
// Test 6: Test add
// Test 7: Test get_keys
// Test 8: Test get_hash_bucket
// Test 9: Test table_load
// Test 10: Test resize_table
// Test 11: Test contains_key
// Test 12: Test get_val
// Test 13: Test empty_buckets
// Test 14: Test remove
// Test 15: Test clear


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


/// SOA_HASHMAP CONSTRUCTOR TESTS-----------------------------------


TEST(test_SOAHSMP, test_zero_initilization_constructor) {
    auto dtest_hash = soa_hashmap<double>(1);
    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(dtest_hash.get_capacity(), static_cast<unsigned int>(5));
    auto orig_heap = std::make_unique<soa_hashmap<double>>(10);
    EXPECT_EQ(orig_heap -> get_size(), static_cast<unsigned int>(0));
    EXPECT_EQ(orig_heap -> get_capacity(), static_cast<unsigned int>(10));
    orig_heap -> add("Miami", 25.0);
    EXPECT_EQ(orig_heap -> get_size(), static_cast<unsigned int>(1));
    orig_heap -> add("Harvard", 2.0);
    EXPECT_EQ(orig_heap -> get_size(), static_cast<unsigned int>(2));
    orig_heap -> add("Los Angeles", 15.3);
    EXPECT_EQ(orig_heap -> get_size(), static_cast<unsigned int>(3));
    orig_heap -> add("New York", 3.6);
    EXPECT_EQ(orig_heap -> get_size(), static_cast<unsigned int>(4));
    orig_heap -> add("Fresno", 10.0);
    EXPECT_EQ(orig_heap -> get_size(), static_cast<unsigned int>(5));
    orig_heap -> add("Redding", 1.3);
    EXPECT_EQ(orig_heap -> get_size(), static_cast<unsigned int>(6));
    orig_heap -> add("San Francisco", 50.2);
    EXPECT_EQ(orig_heap -> get_size(), static_cast<unsigned int>(7));
    orig_heap -> add("Las Vegas", 14.0);
    EXPECT_EQ(orig_heap -> get_size(), static_cast<unsigned int>(8));
    orig_heap -> add("Detroit", 70.4);
    EXPECT_EQ(orig_heap -> get_size(), static_cast<unsigned int>(9));
    orig_heap -> add("Medford", 14.7);
    EXPECT_EQ(orig_heap -> get_size(), static_cast<unsigned int>(10));    
    orig_heap -> add("Dallas", 34.1);
    EXPECT_EQ(orig_heap -> get_size(), static_cast<unsigned int>(11));
    orig_heap -> add("Phoenix", 24.3);
    EXPECT_EQ(orig_heap -> get_size(), static_cast<unsigned int>(12));
    orig_heap -> add("Seattle", 47.6);
    EXPECT_EQ(orig_heap -> get_size(), static_cast<unsigned int>(13));
    orig_heap -> add("Portland", 18.9);
    EXPECT_EQ(orig_heap -> get_size(), static_cast<unsigned int>(14));
    orig_heap -> add("Orlando", 100.5);
    EXPECT_EQ(orig_heap -> get_size(), static_cast<unsigned int>(15));    
    orig_heap -> add("Colorado Springs", 56.8);
    EXPECT_EQ(orig_heap -> get_size(), static_cast<unsigned int>(16));
}

/// SOA_HASHMAP EMPTY OR ZERO INITIALIZATION CONSTRUCTOR

    // std::cout << orig_heap -> get_val("Miami") << '\n';
    // std::cout << orig_heap -> get_val("Harvard") << '\n';
    // std::cout << orig_heap -> get_val("Los Angeles") << '\n';
    // std::cout << orig_heap -> get_val("New York") << '\n';
    // std::cout << orig_heap -> get_val("Fresno") << '\n';
    // std::cout << orig_heap -> get_val("Redding") << '\n';
    // std::cout << orig_heap -> get_val("San Francisco") << '\n';
    // std::cout << orig_heap -> get_val("Las Vegas") << '\n';
    // std::cout << orig_heap -> get_val("Detroit") << '\n';
    // std::cout << orig_heap -> get_val("Medford") << '\n';
    // std::cout << orig_heap -> get_val("Dallas") << '\n';
    // std::cout << orig_heap -> get_val("Phoenix") << '\n';
    // std::cout << orig_heap -> get_val("Seattle") << '\n';
    // std::cout << orig_heap -> get_val("Portland") << '\n';
    // std::cout << orig_heap -> get_val("Orlando") << '\n';
    // std::cout << orig_heap -> get_val("Colorado Springs") << '\n';
    // std::cout << "Minheap created using traditional adding of values: " << '\n';
    // std:: cout << *orig_heap << '\n';
    // std::cout << "Beginning Removal Process...\n";
    // orig_heap -> remove("Miami");
    // std::cout << *orig_heap << '\n';
    // orig_heap -> remove("Harvard");
    // std::cout << *orig_heap << '\n';
    // orig_heap -> remove("Los Angeles");
    // std::cout << *orig_heap << '\n';
    // orig_heap -> remove("New York");
    // std::cout << *orig_heap << '\n';
    // orig_heap -> remove("Fresno");
    // std::cout << *orig_heap << '\n';
    // orig_heap -> remove("Redding");
    // std::cout << *orig_heap << '\n';
    // orig_heap -> remove("San Francisco");
    // std::cout << *orig_heap << '\n';
    // orig_heap -> remove("Las Vegas");
    // std::cout << *orig_heap << '\n';
    // orig_heap -> remove("Detroit");
    // std::cout << *orig_heap << '\n';
    // orig_heap -> remove("Medford");
    // std::cout << *orig_heap << '\n';
    // orig_heap -> remove("Dallas");
    // std::cout << *orig_heap << '\n';
    // orig_heap -> remove("Phoenix");
    // std::cout << *orig_heap << '\n';
    // orig_heap -> remove("Seattle");
    // std::cout << *orig_heap << '\n';
    // orig_heap -> remove("Portland");
    // std::cout << *orig_heap << '\n';
    // orig_heap -> remove("Orlando");
    // std::cout << *orig_heap << '\n';
    // orig_heap -> remove("Colorado Springs");
    // std::cout << *orig_heap << '\n';


/// SOA HASHMAP VECTOR INTIALIZATION CONSTRUCTOR
    // auto miami = std::make_pair("Miami", 25.0);
    // auto harvard = std::make_pair("Harvard", 2.0);
    // auto los_angeles = std::make_pair("Los Angeles", 15.3);
    // auto new_york = std::make_pair("New York", 3.6);
    // auto fresno = std::make_pair("Fresno", 10.0);
    // auto redding = std::make_pair("Redding", 1.3);
    // auto san_francisco = std::make_pair("San Francisco", 50.2);
    // auto las_vegas = std::make_pair("Las Vegas", 14.0);
    // auto detroit = std::make_pair("Detroit", 70.4);
    // auto medford = std::make_pair("Medford", 14.7);
    // auto dallas = std::make_pair("Dallas", 34.1);
    // auto phoenix = std::make_pair("Phoenix", 24.3);
    // auto seattle = std::make_pair("Seattle", 47.6);
    // auto portland = std::make_pair("Portland", 18.9);
    // auto orlando = std::make_pair("Orlando", 100.5);
    // auto colorado_springs = std::make_pair("Colorado Springs", 56.8);

    // std::vector<std::pair<std::string, double>> heap_vals = {miami, harvard, los_angeles, new_york, fresno, redding, san_francisco, las_vegas, detroit, medford, dallas, phoenix, seattle, portland, orlando, colorado_springs};
    // auto exist_heap = std::make_unique<soa_hashmap<double>>(heap_vals);
    // std::cout << exist_heap -> get_val("Miami") << '\n';
    // std::cout << exist_heap -> get_val("Harvard") << '\n';
    // std::cout << exist_heap -> get_val("Los Angeles") << '\n';
    // std::cout << exist_heap -> get_val("New York") << '\n';
    // std::cout << exist_heap -> get_val("Fresno") << '\n';
    // std::cout << exist_heap -> get_val("Redding") << '\n';
    // std::cout << exist_heap -> get_val("San Francisco") << '\n';
    // std::cout << exist_heap -> get_val("Las Vegas") << '\n';
    // std::cout << exist_heap -> get_val("Detroit") << '\n';
    // std::cout << exist_heap -> get_val("Medford") << '\n';
    // std::cout << exist_heap -> get_val("Dallas") << '\n';
    // std::cout << exist_heap -> get_val("Phoenix") << '\n';
    // std::cout << exist_heap -> get_val("Seattle") << '\n';
    // std::cout << exist_heap -> get_val("Portland") << '\n';
    // std::cout << exist_heap -> get_val("Orlando") << '\n';
    // std::cout << exist_heap -> get_val("Colorado Springs") << '\n';
    // std::cout << "Minheap constructed from vector list argument" << '\n';
    // std::cout << *exist_heap << '\n';
    // std::cout << "Beginning Removal Process...\n";
    // exist_heap -> remove("Miami");
    // std::cout << *exist_heap << '\n';
    // exist_heap -> remove("Harvard");
    // std::cout << *exist_heap << '\n';
    // exist_heap -> remove("Los Angeles");
    // std::cout << *exist_heap << '\n';
    // exist_heap -> remove("New York");
    // std::cout << *exist_heap << '\n';
    // exist_heap -> remove("Fresno");
    // std::cout << *exist_heap << '\n';
    // exist_heap -> remove("Redding");
    // std::cout << *exist_heap << '\n';
    // exist_heap -> remove("San Francisco");
    // std::cout << *exist_heap << '\n';
    // exist_heap -> remove("Las Vegas");
    // std::cout << *exist_heap << '\n';
    // exist_heap -> remove("Detroit");
    // std::cout << *exist_heap << '\n';
    // exist_heap -> remove("Medford");
    // std::cout << *exist_heap << '\n';
    // exist_heap -> remove("Dallas");
    // std::cout << *exist_heap << '\n';
    // exist_heap -> remove("Phoenix");
    // std::cout << *exist_heap << '\n';
    // exist_heap -> remove("Seattle");
    // std::cout << *exist_heap << '\n';
    // exist_heap -> remove("Portland");
    // std::cout << *exist_heap << '\n';
    // exist_heap -> remove("Orlando");
    // std::cout << *exist_heap << '\n';
    // exist_heap -> remove("Colorado Springs");
    // std::cout << *exist_heap << '\n';

/// SOA_HASHMAP MOVE CONSTRUCTOR TESTS
    // auto min_heap = std::move(exist_heap);
    // std::cout << *min_heap << '\n';
    // std::cout << min_heap -> get_val("Miami") << '\n';
    // std::cout << min_heap -> get_val("Harvard") << '\n';
    // std::cout << min_heap -> get_val("Los Angeles") << '\n';
    // std::cout << min_heap -> get_val("New York") << '\n';
    // std::cout << min_heap -> get_val("Fresno") << '\n';
    // std::cout << min_heap -> get_val("Redding") << '\n';
    // std::cout << min_heap -> get_val("San Francisco") << '\n';
    // std::cout << min_heap -> get_val("Las Vegas") << '\n';
    // std::cout << min_heap -> get_val("Detroit") << '\n';
    // std::cout << min_heap -> get_val("Medford") << '\n';
    // std::cout << min_heap -> get_val("Dallas") << '\n';
    // std::cout << min_heap -> get_val("Phoenix") << '\n';
    // std::cout << min_heap -> get_val("Seattle") << '\n';
    // std::cout << min_heap -> get_val("Portland") << '\n';
    // std::cout << min_heap -> get_val("Orlando") << '\n';
    // std::cout << min_heap -> get_val("Colorado Springs") << '\n';
    // std::cout << "Min heap created from argument existing paired min heap: \n" << *min_heap << '\n';
    // std::cout << "Beginning Removal Process...\n";
    // min_heap -> remove("Miami");
    // std::cout << *min_heap << '\n';
    // min_heap -> remove("Harvard");
    // std::cout << *min_heap << '\n';
    // min_heap -> remove("Los Angeles");
    // std::cout << *min_heap << '\n';
    // min_heap -> remove("New York");
    // std::cout << *min_heap << '\n';
    // min_heap -> remove("Fresno");
    // std::cout << *min_heap << '\n';
    // min_heap -> remove("Redding");
    // std::cout << *min_heap << '\n';
    // min_heap -> remove("San Francisco");
    // std::cout << *min_heap << '\n';
    // min_heap -> remove("Las Vegas");
    // std::cout << *min_heap << '\n';
    // min_heap -> remove("Detroit");
    // std::cout << *min_heap << '\n';
    // min_heap -> remove("Medford");
    // std::cout << *min_heap << '\n';
    // min_heap -> remove("Dallas");
    // std::cout << *min_heap << '\n';
    // min_heap -> remove("Phoenix");
    // std::cout << *min_heap << '\n';
    // min_heap -> remove("Seattle");
    // std::cout << *min_heap << '\n';
    // min_heap -> remove("Portland");
    // std::cout << *min_heap << '\n';
    // min_heap -> remove("Orlando");
    // std::cout << *min_heap << '\n';
    // min_heap -> remove("Colorado Springs");
    // std::cout << *min_heap << '\n';


// TEST(test_SOAHSMP, test_get_size) {
//     auto dtest_hash = soa_hashmap<double>(5);
//     auto stest_hash = soa_hashmap<std::string>(5);
//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
// }

// TEST(test_SOAHSMP, test_get_capacity) {
//     auto dtest_hash = soa_hashmap<double>(5);
//     auto stest_hash = soa_hashmap<std::string>(5);
//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
//     EXPECT_EQ(dtest_hash.get_capacity(), static_cast<unsigned int>(5));
//     EXPECT_EQ(dtest_hash.get_capacity(), static_cast<unsigned int>(5));
// }

// TEST(test_SOAHSMP, test_add) {
//     auto dtest_hash = soa_hashmap<double>(5);
//     auto stest_hash = soa_hashmap<std::string>(5);
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
//     dtest_hash.add("San Francisco", 3.0);
//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(1));
//     dtest_hash.add("New York", 10.0);
//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(2));
//     dtest_hash.add("Houston", 15.0);
//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(3));
//     stest_hash.add("San Francisco", "New York");
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(1));
//     stest_hash.add("New York", "Houston");
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(2));
//     stest_hash.add("Dallas", "San Antonio");
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(3));
// }

// TEST(test_SOAHSMP, test_get_keys) {
//     auto dtest_hash = soa_hashmap<double>(5);
//     auto stest_hash = soa_hashmap<std::string>(5);
//     dtest_hash.add("San Francisco", 3.0);
//     dtest_hash.add("New York", 10.0);
//     dtest_hash.add("Houston", 15.0);

//     stest_hash.add("San Francisco", "New York");
//     stest_hash.add("New York", "Houston");
//     stest_hash.add("Dallas", "San Antonio");
//     EXPECT_EQ(dtest_hash.get_keys().size(), static_cast<unsigned int>(3));
//     EXPECT_EQ(dtest_hash.get_keys().size(), static_cast<unsigned int>(3));
// }


// TEST(test_SOAHSMP, test_get_hashbucket) {
//     auto dtest_hash = soa_hashmap<double>(5);
//     auto stest_hash = soa_hashmap<std::string>(5);
//     dtest_hash.add("San Francisco", 3.0);
//     dtest_hash.add("New York", 10.0);
//     dtest_hash.add("Houston", 15.0);

//     stest_hash.add("San Francisco", "New York");
//     stest_hash.add("New York", "Houston");
//     stest_hash.add("Dallas", "San Antonio");
//     auto double_hashbucket = dtest_hash.get_hash_bucket();
//     EXPECT_EQ(double_hashbucket.size(), dtest_hash.get_capacity());

//     auto string_hashbucket = stest_hash.get_hash_bucket();
//     EXPECT_EQ(string_hashbucket.size(), stest_hash.get_capacity());
// }

// TEST(test_SOAHSMP, test_table_load) {
//     auto dtest_hash = soa_hashmap<double>(5);
//     auto stest_hash = soa_hashmap<std::string>(5);
//     auto exp_DTL = static_cast<double>(dtest_hash.get_size()) / static_cast<double>(dtest_hash.get_capacity());
//     auto exp_STL = static_cast<double>(stest_hash.get_size()) / static_cast<double>(stest_hash.get_capacity());
//     EXPECT_EQ(exp_DTL, dtest_hash.table_load());
//     EXPECT_EQ(exp_STL, stest_hash.table_load());
//     dtest_hash.add("San Francisco", 3.0);
//     dtest_hash.add("New York", 10.0);
//     dtest_hash.add("Houston", 15.0);
//     dtest_hash.add("Lufkin", 42.0);
//     stest_hash.add("San Francisco", "New York");
//     stest_hash.add("New York", "Houston");
//     stest_hash.add("Dallas", "San Antonio");
//     stest_hash.add("Lufkin", "Detriot");
//     exp_DTL = static_cast<double>(dtest_hash.get_size()) / static_cast<double>(dtest_hash.get_capacity());
//     exp_STL = static_cast<double>(stest_hash.get_size()) / static_cast<double>(stest_hash.get_capacity());
//     EXPECT_EQ(exp_DTL, dtest_hash.table_load());
//     EXPECT_EQ(exp_STL, stest_hash.table_load());
// }

// TEST(test_SOAHSMP, test_resize_table) {
//     auto dtest_hash = soa_hashmap<double>(3);
//     auto stest_hash = soa_hashmap<std::string>(3);
//     auto init_cap = dtest_hash.get_capacity();
//     EXPECT_EQ(init_cap, static_cast<unsigned int>(5));
//     dtest_hash.add("San Francisco", 3.0);
//     dtest_hash.add("New York", 10.0);
//     EXPECT_EQ(get_next_prime(init_cap), dtest_hash.get_capacity());
//     dtest_hash.add("Houston", 15.0);
//     auto next_cap = dtest_hash.get_capacity();
//     EXPECT_EQ(get_next_prime(next_cap), dtest_hash.get_capacity());
//     dtest_hash.add("Lufkin", 42.0);
//     stest_hash.add("San Francisco", "New York");
//     stest_hash.add("New York", "Houston");
//     EXPECT_EQ(get_next_prime(init_cap), stest_hash.get_capacity());
//     stest_hash.add("Dallas", "San Antonio");
//     EXPECT_EQ(get_next_prime(next_cap), stest_hash.get_capacity());
//     stest_hash.add("Lufkin", "Detriot");
// }

// TEST(test_SOAHSMP, test_contains_key) {
//     auto dtest_hash = soa_hashmap<double>(5);
//     auto stest_hash = soa_hashmap<std::string>(5);
//     dtest_hash.add("San Francisco", 3.0);
//     dtest_hash.add("New York", 10.0);
//     dtest_hash.add("Houston", 15.0);
//     dtest_hash.add("Lufkin", 42.0);
//     stest_hash.add("San Francisco", "New York");
//     stest_hash.add("New York", "Houston");
//     stest_hash.add("Dallas", "San Antonio");
//     stest_hash.add("Lufkin", "Detroit");
//     EXPECT_TRUE(dtest_hash.contains_key("San Francisco"));
//     EXPECT_TRUE(dtest_hash.contains_key("New York"));
//     EXPECT_TRUE(dtest_hash.contains_key("Houston"));
//     EXPECT_TRUE(dtest_hash.contains_key("Lufkin"));    

//     EXPECT_TRUE(stest_hash.contains_key("San Francisco"));
//     EXPECT_TRUE(stest_hash.contains_key("New York"));
//     EXPECT_TRUE(stest_hash.contains_key("Dallas"));
//     EXPECT_TRUE(stest_hash.contains_key("Lufkin")); 
// }

// TEST(test_SOAHSMP, test_get_val) {
//     auto dtest_hash = soa_hashmap<double>(5);
//     auto stest_hash = soa_hashmap<std::string>(5);
//     dtest_hash.add("San Francisco", 3.0);
//     dtest_hash.add("New York", 10.0);
//     dtest_hash.add("Houston", 15.0);
//     dtest_hash.add("Lufkin", 42.0);
//     stest_hash.add("San Francisco", "New York");
//     stest_hash.add("New York", "Houston");
//     stest_hash.add("Dallas", "San Antonio");
//     stest_hash.add("Lufkin", "Detroit");
//     EXPECT_EQ(dtest_hash.get_val("New York"), 10.0);
//     EXPECT_EQ(dtest_hash.get_val("San Francisco"), 3.0);
//     EXPECT_EQ(dtest_hash.get_val("Houston"), 15.0);
//     EXPECT_EQ(dtest_hash.get_val("Lufkin"), 42.0);

//     EXPECT_EQ(stest_hash.get_val("San Francisco"), "New York");
//     EXPECT_EQ(stest_hash.get_val("New York"), "Houston");
//     EXPECT_EQ(stest_hash.get_val("Dallas"), "San Antonio");
//     EXPECT_EQ(stest_hash.get_val("Lufkin"), "Detroit");
// }

// TEST(test_SOAHSMP, test_empty_buckets) {
//     auto dtest_hash = soa_hashmap<double>(5);
//     auto stest_hash = soa_hashmap<std::string>(5);
//     EXPECT_EQ(stest_hash.empty_buckets(), stest_hash.get_capacity());
//     EXPECT_EQ(dtest_hash.empty_buckets(), dtest_hash.get_capacity());
//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
//     EXPECT_EQ(dtest_hash.get_capacity(), static_cast<unsigned int>(5));
//     EXPECT_EQ(stest_hash.get_capacity(), static_cast<unsigned int>(5));

//     dtest_hash.add("San Francisco", 3.0);
//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(1));
//     EXPECT_EQ(dtest_hash.get_capacity(), static_cast<unsigned int>(5));
//     EXPECT_EQ(dtest_hash.empty_buckets(), dtest_hash.get_capacity() - dtest_hash.get_size());
//     dtest_hash.add("New York", 10.0);
//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(2));
//     EXPECT_EQ(dtest_hash.get_capacity(), static_cast<unsigned int>(5));
//     EXPECT_EQ(dtest_hash.empty_buckets(), dtest_hash.get_capacity() - dtest_hash.get_size());
//     dtest_hash.add("Houston", 15.0);
//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(3));
//     EXPECT_EQ(dtest_hash.get_capacity(), get_next_prime(5));
//     EXPECT_EQ(dtest_hash.empty_buckets(), dtest_hash.get_capacity() - dtest_hash.get_size());
//     dtest_hash.add("Lufkin", 42.0);
//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(4));
//     EXPECT_EQ(dtest_hash.empty_buckets(), dtest_hash.get_capacity() - dtest_hash.get_size());

//     stest_hash.add("San Francisco", "New York");
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(1));
//     EXPECT_EQ(stest_hash.get_capacity(), static_cast<unsigned int>(5));
//     EXPECT_EQ(stest_hash.empty_buckets(), stest_hash.get_capacity() - stest_hash.get_size());
//     stest_hash.add("New York", "Houston");
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(2));
//     EXPECT_EQ(stest_hash.get_capacity(), static_cast<unsigned int>(5));
//     EXPECT_EQ(stest_hash.empty_buckets(), stest_hash.get_capacity() - stest_hash.get_size());
//     stest_hash.add("Dallas", "San Antonio");
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(3));
//     EXPECT_EQ(stest_hash.get_capacity(), get_next_prime(5));
//     EXPECT_EQ(stest_hash.empty_buckets(), stest_hash.get_capacity() - stest_hash.get_size());
//     stest_hash.add("Lufkin", "Detroit");
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(4));
//     EXPECT_EQ(stest_hash.empty_buckets(), stest_hash.get_capacity() - stest_hash.get_size());
// }

// TEST(test_SOAHSMP, test_remove) {
//     auto dtest_hash = soa_hashmap<double>(5);
//     auto stest_hash = soa_hashmap<std::string>(5);
//     EXPECT_EQ(stest_hash.empty_buckets(), stest_hash.get_capacity());
//     EXPECT_EQ(dtest_hash.empty_buckets(), dtest_hash.get_capacity());
//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
//     EXPECT_EQ(dtest_hash.get_capacity(), static_cast<unsigned int>(5));
//     EXPECT_EQ(stest_hash.get_capacity(), static_cast<unsigned int>(5));

//     dtest_hash.add("San Francisco", 3.0);
//     dtest_hash.add("New York", 10.0);
//     dtest_hash.add("Houston", 15.0);
//     dtest_hash.add("Lufkin", 42.0);
//     stest_hash.add("San Francisco", "New York");
//     stest_hash.add("New York", "Houston");
//     stest_hash.add("Dallas", "San Antonio");
//     stest_hash.add("Lufkin", "Detroit");

//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(4));
//     EXPECT_FALSE(dtest_hash.contains_key("Billings"));
//     EXPECT_FALSE(stest_hash.contains_key("Billings"));

//     EXPECT_TRUE(dtest_hash.contains_key("Houston"));
//     dtest_hash.remove("Houston");
//     stest_hash.remove("Billings");
//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(3));
//     EXPECT_FALSE(dtest_hash.contains_key("Houston"));

//     EXPECT_TRUE(dtest_hash.contains_key("San Francisco"));
//     dtest_hash.remove("San Francisco");
//     stest_hash.remove("Billings");
//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(2));
//     EXPECT_FALSE(dtest_hash.contains_key("San Francisco"));

//     EXPECT_TRUE(dtest_hash.contains_key("Lufkin"));
//     dtest_hash.remove("Lufkin");
//     stest_hash.remove("Billings");
//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(1));
//     EXPECT_FALSE(dtest_hash.contains_key("Lufkin"));

//     EXPECT_TRUE(dtest_hash.contains_key("New York"));   
//     dtest_hash.remove("New York");
//     stest_hash.remove("Billings");
//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
//     EXPECT_FALSE(dtest_hash.contains_key("New York"));


//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(4));
//     EXPECT_TRUE(stest_hash.contains_key("Lufkin"));
//     stest_hash.remove("Lufkin");
//     stest_hash.remove("Billings");
//     EXPECT_FALSE(stest_hash.contains_key("Lufkin"));
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(3));

//     EXPECT_TRUE(stest_hash.contains_key("Dallas"));
//     stest_hash.remove("Dallas");
//     stest_hash.remove("Billings");
//     EXPECT_FALSE(stest_hash.contains_key("Dallas"));
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(2));

//     EXPECT_TRUE(stest_hash.contains_key("New York"));
//     stest_hash.remove("New York");
//     stest_hash.remove("Billings");
//     EXPECT_FALSE(stest_hash.contains_key("New York"));
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(1));

//     EXPECT_TRUE(stest_hash.contains_key("San Francisco"));
//     stest_hash.remove("San Francisco");
//     stest_hash.remove("Billings");
//     EXPECT_FALSE(stest_hash.contains_key("San Francisco"));
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
//     stest_hash.remove("San Francisco");
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
// }

// TEST(test_SOAHSMP, test_clear) {
//     auto dtest_hash = soa_hashmap<double>(5);
//     auto stest_hash = soa_hashmap<std::string>(5);
//     EXPECT_EQ(stest_hash.empty_buckets(), stest_hash.get_capacity());
//     EXPECT_EQ(dtest_hash.empty_buckets(), dtest_hash.get_capacity());
//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
//     EXPECT_EQ(dtest_hash.get_capacity(), static_cast<unsigned int>(5));
//     EXPECT_EQ(stest_hash.get_capacity(), static_cast<unsigned int>(5));

//     dtest_hash.add("San Francisco", 3.0);
//     dtest_hash.add("New York", 10.0);
//     dtest_hash.add("Houston", 15.0);
//     dtest_hash.add("Lufkin", 42.0);
//     stest_hash.add("San Francisco", "New York");
//     stest_hash.add("New York", "Houston");
//     stest_hash.add("Dallas", "San Antonio");
//     stest_hash.add("Lufkin", "Detroit");
//     auto new_capacity = dtest_hash.get_capacity();
//     EXPECT_EQ(new_capacity, stest_hash.get_capacity());

//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(4));
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(4));
//     dtest_hash.clear();
//     stest_hash.clear();
//     EXPECT_EQ(dtest_hash.get_keys().size(), static_cast<size_t>(0));
//     EXPECT_EQ(stest_hash.get_keys().size(), static_cast<size_t>(0));
//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(0));
//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(0));
//     EXPECT_EQ(dtest_hash.get_capacity(), new_capacity);
//     EXPECT_EQ(stest_hash.get_capacity(), new_capacity);    
// }

// Test Suite test_MHSMP: HASHMAP CONTAINING OPEN-ADDRESSING HASHMAP(S) Functions
// Test main_hashmap
// Test 1: Test fill_buckets
// Test 2: Test get_size
// Test 3: Test get_capacity
// Test 4: Test table_load
// Test 5: Test resize_table
// Test 6: Test get_master_keys
// Test 7: Test print_master_keys
// Test 8: Test get_master_hash_bucket
// Test 9: Test add_key
// Test 10: Test get_key_list
// Test 11: Test get_key_val
// Test 12: Test get_key_by_val
// Test 13: Test empty_buckets
// Test 14: Test contains_key
// Test 15: Test remove
// Test 16: Test clear
// Test 17: Test prefill_hash_keys
// Test 18: Test main_hashmap constructor

// TEST(test_MHSMP, test_constructor) {
//     auto dtest_hash = soa_hashmap<double>(5);
//     auto dtest_hash2 = soa_hashmap<double>(5);
//     auto dtest_hash3 = soa_hashmap<double>(5);
//     auto dtest_hashmap = main_hashmap<double>(5);

//     auto stest_hash = soa_hashmap<std::string>(5);
//     auto stest_hash2 = soa_hashmap<std::string>(5);
//     auto stest_hash3 = soa_hashmap<std::string>(5);
//     auto stest_hashmap = main_hashmap<std::string>(5);

//     dtest_hash.add("San Francisco", 3.0);
//     dtest_hash.add("New York", 10.0);
//     dtest_hash.add("Houston", 15.0);

//     dtest_hash2.add("Dallas", 56.0);
//     dtest_hash2.add("Santa Fe", 70.2);
//     dtest_hash2.add("Seattle", 45.6);

//     dtest_hash3.add("Chicago", 180.3);
//     dtest_hash3.add("Oklahoma City", 78.5);
//     dtest_hash3.add("Denver", 96.2);

//     dtest_hashmap.add_key("Miami", dtest_hash);
//     dtest_hashmap.add_key("Las Vegas", dtest_hash2);
//     dtest_hashmap.add_key("Orlando", dtest_hash3);

//     stest_hash.add("San Francisco", "New York");
//     stest_hash.add("New York", "Houston");
//     stest_hash.add("Dallas", "San Antonio");

//     stest_hash2.add("Santa Fe", "Seattle");
//     stest_hash2.add("Chicago", "Santa Fe");
//     stest_hash2.add("Oklahoma City", "Portland");

//     stest_hash3.add("Denver", "Colorado Springs");
//     stest_hash3.add("Miami", "Sacramento");
//     stest_hash3.add("Chicago", "San Antonio");

//     stest_hashmap.add_key("Los Angeles", stest_hash);
//     stest_hashmap.add_key("Cupertino", stest_hash2);
//     stest_hashmap.add_key("Nashville", stest_hash3);

//     EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(3));
//     EXPECT_EQ(dtest_hash2.get_size(), static_cast<unsigned int>(3));
//     EXPECT_EQ(dtest_hash3.get_size(), static_cast<unsigned int>(3));
//     EXPECT_EQ(dtest_hashmap.get_size(), static_cast<unsigned int>(3));

//     EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(3));
//     EXPECT_EQ(stest_hash2.get_size(), static_cast<unsigned int>(3));
//     EXPECT_EQ(stest_hash3.get_size(), static_cast<unsigned int>(3));
//     EXPECT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(3));
// }

// TEST(test_MHSMP, test_fill_buckets) {
//     auto dtest_hash = soa_hashmap<double>(5);
//     auto dtest_hash2 = soa_hashmap<double>(5);
//     auto dtest_hash3 = soa_hashmap<double>(5);
//     auto dtest_hashmap = main_hashmap<double>(1);

//     auto stest_hash = soa_hashmap<std::string>(5);
//     auto stest_hash2 = soa_hashmap<std::string>(5);
//     auto stest_hash3 = soa_hashmap<std::string>(5);
//     auto stest_hashmap = main_hashmap<std::string>(1);
//     EXPECT_EQ(dtest_hashmap.get_capacity(), static_cast<unsigned int>(5));
//     EXPECT_EQ(stest_hashmap.get_capacity(), static_cast<unsigned int>(5));
//     EXPECT_EQ(dtest_hashmap.get_size(), static_cast<unsigned int>(0));
//     EXPECT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(0));
// }

// TEST(test_MHSMP, test_get_key_val) {
//         auto dtest_hash = soa_hashmap<double>(5);
//     auto dtest_hash2 = soa_hashmap<double>(5);
//     auto dtest_hash3 = soa_hashmap<double>(5);
//     auto dtest_hashmap = main_hashmap<double>(5);

//     auto stest_hash = soa_hashmap<std::string>(5);
//     auto stest_hash2 = soa_hashmap<std::string>(5);
//     auto stest_hash3 = soa_hashmap<std::string>(5);
//     auto stest_hashmap = main_hashmap<std::string>(5);

//     dtest_hash.add("San Francisco", 3.0);
//     dtest_hash.add("New York", 10.0);
//     dtest_hash.add("Houston", 15.0);

//     dtest_hash2.add("Dallas", 56.0);
//     dtest_hash2.add("Santa Fe", 70.2);
//     dtest_hash2.add("Seattle", 45.6);

//     dtest_hash3.add("Chicago", 180.3);
//     dtest_hash3.add("Oklahoma City", 78.5);
//     dtest_hash3.add("Denver", 96.2);

//     dtest_hashmap.add_key("Miami", dtest_hash);
//     dtest_hashmap.add_key("Las Vegas", dtest_hash2);
//     dtest_hashmap.add_key("Orlando", dtest_hash3);

//     stest_hash.add("San Francisco", "New York");
//     stest_hash.add("New York", "Houston");
//     stest_hash.add("Dallas", "San Antonio");

//     stest_hash2.add("Santa Fe", "Seattle");
//     stest_hash2.add("Chicago", "Santa Fe");
//     stest_hash2.add("Oklahoma City", "Portland");

//     stest_hash3.add("Denver", "Colorado Springs");
//     stest_hash3.add("Miami", "Sacramento");
//     stest_hash3.add("Chicago", "San Antonio");

//     stest_hashmap.add_key("Los Angeles", stest_hash);
//     stest_hashmap.add_key("Cupertino", stest_hash2);
//     stest_hashmap.add_key("Nashville", stest_hash3);

//     EXPECT_EQ(stest_hashmap.get_key_val("Los Angeles", "San Francisco"), "New York");
//     EXPECT_EQ(stest_hashmap.get_key_val("Los Angeles", "New York"), "Houston");
//     EXPECT_EQ(stest_hashmap.get_key_val("Los Angeles", "Dallas"), "San Antonio");
//     EXPECT_EQ(stest_hashmap.get_key_val("Cupertino", "Santa Fe"), "Seattle");
//     EXPECT_EQ(stest_hashmap.get_key_val("Cupertino", "Chicago"), "Santa Fe");
//     EXPECT_EQ(stest_hashmap.get_key_val("Cupertino", "Oklahoma City"), "Portland");
//     EXPECT_EQ(stest_hashmap.get_key_val("Nashville", "Denver"), "Colorado Springs");
//     EXPECT_EQ(stest_hashmap.get_key_val("Nashville", "Miami"), "Sacramento");
//     EXPECT_EQ(stest_hashmap.get_key_val("Nashville", "Chicago"), "San Antonio");

//     EXPECT_EQ(dtest_hashmap.get_key_val("Miami", "San Francisco"), 3.0);
//     EXPECT_EQ(dtest_hashmap.get_key_val("Miami", "New York"), 10.0);
//     EXPECT_EQ(dtest_hashmap.get_key_val("Miami", "Houston"), 15.0);
//     EXPECT_EQ(dtest_hashmap.get_key_val("Las Vegas", "Dallas"), 56.0);
//     EXPECT_EQ(dtest_hashmap.get_key_val("Las Vegas", "Santa Fe"), 70.2);
//     EXPECT_EQ(dtest_hashmap.get_key_val("Las Vegas", "Seattle"), 45.6);
//     EXPECT_EQ(dtest_hashmap.get_key_val("Orlando", "Chicago"), 180.3);
//     EXPECT_EQ(dtest_hashmap.get_key_val("Orlando", "Oklahoma City"), 78.5);
//     EXPECT_EQ(dtest_hashmap.get_key_val("Orlando", "Denver"), 96.2);
//     EXPECT_EQ(dtest_hashmap.get_key_by_value("Las Vegas", 70.2), "Santa Fe");
//     EXPECT_EQ(stest_hashmap.get_key_by_value("Nashville", "Sacramento"), "Miami");

//     // ASSERT_DEATH(stest_hashmap.get_key_val("Cupertino", "Denver"), "The Existing Hashmap 'Cupertino' does not contain the key 'Denver'!");
//     // ASSERT_DEATH(dtest_hashmap.get_key_val("Cupertino", "Denver"), "The key 'Cupertino' does not exist in calling main_hashmap object!");
// }


// Test Suite test_graph_funcs: GRAPH ALGORITHM Functions
// Test functions involved in graph operations
// Test 1: Test build_adjacency_list
// Test 2: Test apply_dijkstras_algorithm
// Test 3: Test apply_prims_algorithm


// Test Suite test_graph_interface: User Defined Input Functions
// Test 1: Test acceptance of user input for filename
// Test 2: Test acceptance of user input for vertex count
// Test 3: Test acceptance of user input for algorithm type
