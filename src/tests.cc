#include <gtest/gtest.h>
#include "../includes/linked_list.hpp"
#include "../includes/pair_minheap.hpp"
#include "../includes/gprintf.hpp"
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
// Test 12: Test dl_list constructor
// Test 13: Test dl_list destructor

TEST(test_DL, test_dl_constructor) {
    auto test_list = dl_list<std::string> {};
    EXPECT_EQ(test_list.get_size(), static_cast<size_t>(0));
}

TEST(test_DL, test_get_size) {
    auto test_list = dl_list<std::string> {};
    auto list_size = test_list.get_size();
    decltype (list_size) exp_size = 0;
    EXPECT_EQ(list_size, exp_size);
    test_list.add_to_back("last_node");
    list_size = test_list.get_size();
    exp_size++;
    EXPECT_EQ(list_size, exp_size);
}


TEST(test_DL, test_add_to_back) {
    auto test_list = dl_list<std::string> {};
    test_list.add_to_back("last_node");
    auto list_size = test_list.get_size();
    decltype (list_size) exp_size = 1;
    EXPECT_EQ(list_size, exp_size);
    EXPECT_TRUE(test_list.contains_node("last_node"));
}

TEST(test_DL, test_add_to_front) {
    auto test_list = dl_list<std::string> {};
    test_list.add_to_back("last_node");
    test_list.add_to_front("front_node");
    auto list_size = test_list.get_size();
    decltype (list_size) exp_size = 2;
    EXPECT_EQ(list_size, exp_size);
    EXPECT_TRUE(test_list.contains_node("front_node"));
    EXPECT_TRUE(test_list.contains_node("last_node"));
}

TEST(test_DL, test_get_front) {
    auto test_list = dl_list<std::string> {};
    test_list.add_to_back("last_node");
    test_list.add_to_front("front_node");
    test_list.add_to_front("new_front");
    auto front_node = test_list.get_front();
    EXPECT_EQ(front_node, "new_front");
}

TEST(test_DL, test_get_back) {
    auto test_list = dl_list<std::string> {};
    test_list.add_to_back("last_node");
    test_list.add_to_front("front_node");
    test_list.add_to_back("new_back");
    test_list.add_to_front("new_front");
    auto new_size = test_list.get_size();
    auto back_node = test_list.get_back();
    decltype (new_size) exp_size = 4;
    EXPECT_EQ(new_size, exp_size);
    EXPECT_EQ(back_node, "new_back");
}

TEST(test_DL, test_get_prev) {
    auto test_list = dl_list<std::string> {};
    test_list.add_to_back("last_node");
    test_list.add_to_front("front_node");
    auto old_front = test_list.get_front();
    auto old_back = test_list.get_back();
    test_list.add_to_back("new_back");
    test_list.add_to_front("new_front");
    auto new_front = test_list.get_front();
    auto new_back = test_list.get_back();
    auto second_from_back = test_list.get_prev(new_back);
    auto front_of_front = test_list.get_prev(new_front);
    // auto non_existant_val = test_list.get_prev("should_create_error");
    auto front = test_list.get_prev(old_front);
    auto middle = test_list.get_prev(old_back);
    EXPECT_EQ(second_from_back, "last_node");
    EXPECT_EQ(front_of_front, "new_front");
    EXPECT_EQ(front, "new_front");
    EXPECT_EQ(middle, "front_node");
}


TEST(test_DL, test_get_before_tail) {
    auto test_list = dl_list<std::string> {};
    test_list.add_to_back("last_node");
    auto old_tail = test_list.get_before_tail();
    test_list.add_to_front("front_node");
    auto second_tail = test_list.get_before_tail();
    test_list.add_to_back("new_back");
    auto third_tail = test_list.get_before_tail();
    test_list.add_to_back("newer_back");
    auto fourth_tail = test_list.get_before_tail();
    EXPECT_EQ(old_tail, "last_node");
    EXPECT_EQ(second_tail, "front_node");
    EXPECT_EQ(third_tail, "last_node");
    EXPECT_EQ(fourth_tail, "new_back");
}

TEST(test_DL, test_remove) {
    auto test_list = dl_list<std::string> {};
    test_list.add_to_back("last_node");
    test_list.add_to_front("front_node");
    test_list.add_to_back("new_back");
    test_list.add_to_front("new_front");
    // N_F -> F_N -> L_N -> N_B
    auto is_removed = test_list.remove("new_back");
    EXPECT_TRUE(is_removed);
    auto failed = test_list.remove("no_node");
    EXPECT_FALSE(failed);
    EXPECT_FALSE(test_list.contains_node("new_back"));
    EXPECT_EQ(test_list.get_back(), "last_node");
    EXPECT_EQ(test_list.get_before_tail(), "front_node");
    EXPECT_EQ(test_list.get_size(), static_cast<size_t>(3));
    auto removed_front = test_list.remove("new_front");
    EXPECT_EQ(test_list.get_front(), "front_node");
    EXPECT_EQ(test_list.get_size(), static_cast<size_t>(2));
    EXPECT_EQ(test_list.get_prev("front_node"), "front_node");
    EXPECT_TRUE(test_list.remove("front_node"));
    EXPECT_EQ(test_list.get_size(), static_cast<size_t>(1));
    EXPECT_EQ(test_list.get_back(), "last_node");
    EXPECT_EQ(test_list.get_front(), "last_node");
    EXPECT_EQ(test_list.get_prev("last_node"), "last_node");
    EXPECT_EQ(test_list.get_before_tail(), "last_node");
    EXPECT_TRUE(test_list.remove("last_node"));
    EXPECT_EQ(test_list.get_size(), static_cast<size_t>(0));
    EXPECT_FALSE(test_list.remove(""));
}

TEST(test_DL, test_remove_back) {
    auto test_list = dl_list<std::string> {};
    test_list.add_to_back("last_node");
    test_list.add_to_front("front_node");
    EXPECT_TRUE(test_list.remove_back());
    EXPECT_FALSE(test_list.contains_node("last_node"));
    EXPECT_TRUE(test_list.contains_node("front_node"));
    EXPECT_EQ(test_list.get_size(), static_cast<size_t>(1));
    EXPECT_EQ(test_list.get_back(), "front_node");
    EXPECT_TRUE(test_list.remove_back());
    EXPECT_FALSE(test_list.remove_back());
    EXPECT_EQ(test_list.get_size(), static_cast<size_t>(0));
}

TEST(test_DL, test_contains_node) {
    auto test_list = dl_list<std::string> {};
    test_list.add_to_back("last_node");
    test_list.add_to_front("front_node");
    EXPECT_TRUE(test_list.contains_node("last_node"));
    EXPECT_TRUE(test_list.contains_node("front_node"));
    EXPECT_TRUE(test_list.remove("last_node"));
    EXPECT_TRUE(test_list.remove("front_node"));
    EXPECT_FALSE(test_list.contains_node("last_node"));
    EXPECT_FALSE(test_list.contains_node("front_node"));
    EXPECT_FALSE(test_list.contains_node("no_node"));
    EXPECT_FALSE(test_list.contains_node(""));
    auto num_list = dl_list<double> {};
    num_list.add_to_back(5.0);
    num_list.add_to_front(15.3);
    EXPECT_TRUE(num_list.contains_node(5.0));
    EXPECT_TRUE(num_list.contains_node(15.3));
    EXPECT_FALSE(num_list.contains_node(0));
}

// TEST(test_DL, test_overload_output) {
//     auto test_list = dl_list<std::string> {};
//     test_list.add_to_back("last_node");
//     std::cout << test_list << '\n';
//     EXPECT_EQ(test_list.get_size(), static_cast<size_t>(1));
//     test_list.remove("last_node");
//     std::cout << test_list << std::endl;
//     test_list.add_to_front("front_node");
//     test_list.add_to_back("new_back");
//     test_list.add_to_front("new_front");
//     std::cout << test_list << '\n';
// }

// Test Suite test_PMNHP: MINIMUM BINARY HEAP OF KEY:VALUE PAIR NODES Functions
// Test paired_min_heap
// Test 1: Test get_min/paired_min_heap constructor
// Test 2: Test get_heap_size
// Test 3: Test add_node
// Test 4: Test min_percolate/evaluate_children
// Test 5: Test remove_min

TEST(test_PRMNHP, test_get_heap_size) {
    auto test_heap = paired_min_heap<double> {};
    EXPECT_EQ(test_heap.get_heap_size(), 0);
    test_heap.add_node("first_node", 0);
    test_heap.add_node("second_node", 3);
    EXPECT_EQ(test_heap.get_heap_size(), 2);
}

TEST(test_PRMNHP, test_add_node) {
    auto test_heap = paired_min_heap<double> {};
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
    auto test_heap = paired_min_heap<double> {};
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
    auto test_heap = paired_min_heap<double> {};
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
    ASSERT_DEATH(test_heap.min_percolate(4), "Passed index is out of bounds of array!");
    ASSERT_DEATH(test_heap.min_percolate(-1), "Passed index is out of bounds of array!");
}

TEST(test_PRMNHP, test_remove_min) {
    auto test_heap = paired_min_heap<double> {};
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
    ASSERT_DEATH(test_heap.remove_min(), "Heap is empty!");    
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



// Test Suite test_graph_funcs: GRAPH ALGORITHM Functions
// Test functions involved in graph operations
// Test 1: Test build_adjacency_list
// Test 2: Test apply_dijkstras_algorithm
// Test 3: Test apply_prims_algorithm


// Test Suite test_graph_interface: User Defined Input Functions
// Test 1: Test acceptance of user input for filename
// Test 2: Test acceptance of user input for vertex count
// Test 3: Test acceptance of user input for algorithm type