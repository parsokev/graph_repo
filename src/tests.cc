#include <gtest/gtest.h>
#include "../includes/linked_list.hpp"


// Test Suite test_DL: DOUBLY-LINKED lIST Functions
// Test dl_list
// Test 1: Test add_to_front
// Test 2: Test add_to_back
// Test 3: Test get_size
// Test 4: Test get_front
// Test 5: Test get_back
// Test 6: Test get_prev
// Test 7: Test get_before_tail
// Test 7: Test contains_node
// Test 8: Test remove
// Test 9: Test remove_back
// Test 10: Test fill_list
// Test 11: Test print_usage?
// Test 12: Test dl_list constructor
// Test 13: Test dl_list destructor

TEST(test_DL, Testassert) {
    EXPECT_STRNE("Hello", "World");
    EXPECT_EQ(7 * 6, 42);
}

TEST(test_DL, TestList) {
    auto test_list = dl_list<std::string, 0> {};
    test_list.add_to_back("first node");
    auto list_size = test_list.get_size();
    decltype (list_size) exp_size = 1;
    EXPECT_EQ(list_size, exp_size);
    EXPECT_TRUE(test_list.contains_node("first node"));
}

// Test Suite test_OAHSMP: OPEN-ADDRESSING HASHMAP Functions
// Test oa_hashmap
// Test 1: Test apply_hash_function
// Test 2: Test get_next_prime
// Test 3: Test is_prime
// Test 4: Test fill_buckets
// Test 5: Test get_size
// Test 6: Test get_capacity
// Test 7: Test get_keys
// Test 8: Test print_keys
// Test 9: Test get_hash_bucket
// Test 10: Test table_load
// Test 11: Test resize_table
// Test 12: Test add
// Test 13: Test get_val
// Test 14: Test empty_buckets
// Test 15: Test contains_key
// Test 16: Test remove
// Test 17: Test clear
// Test 18: Test fill_hash_table
// Test 19: Test oa_hashmap constructor

// Test Suite test_MHSMP: HASHMAP CONTAINING OPEN-ADDRESSING HASHMAP(S) Functions
// Test master_hashmap
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
// Test 18: Test master_hashmap constructor

// Test Suite test_PMNHP: MINIMUM BINARY HEAP OF KEY:VALUE PAIR NODES Functions
// Test paired_min_heap
// Test 1: Test get_min
// Test 2: Test get_heap_size
// Test 3: Test add_node
// Test 4: Test fill_heap
// Test 5: Test min_percolate
// Test 6: Test evaluate_children
// Test 7: Test get_vertex
// Test 8: Test remove_min
// Test 9: Test paired_min_heap constructor

// Test Suite test_graph_funcs: GRAPH ALGORITHM Functions
// Test functions involved in graph operations
// Test 1: Test build_adjacency_list
// Test 2: Test apply_dijkstras_algorithm
// Test 3: Test apply_prims_algorithm


// Test Suite test_graph_interface: User Defined Input Functions
// Test 1: Test acceptance of user input for filename
// Test 2: Test acceptance of user input for vertex count
// Test 3: Test acceptance of user input for algorithm type