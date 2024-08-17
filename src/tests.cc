#include <gtest/gtest.h>
#include "../includes/linked_list.hpp"
#include "../includes/pair_minheap.hpp"
#include "../includes/gprintf.hpp"
// #include "../includes/master_hashmap.hpp"
// #include "../src/master_hashmap.cpp"
#include "../src/derived_hashmap.cpp"
#include "../includes/derived_hashmap.hpp"
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
// Test 8: Test get_hash_bucket
// Test 9: Test table_load
// Test 10: Test resize_table


// Test 12: Test add
// Test 13: Test get_val
// Test 14: Test empty_buckets
// Test 15: Test contains_key
// Test 16: Test remove
// Test 17: Test clear
// Test 18: Test fill_hash_table
// Test 19: Test oa_hashmap constructor

TEST(test_SOAHSMP, test_apply_hash_function) {
    std::vector<std::string> sample_keys = {"San Francisco", "San Antonio", "Santa Cruz", "San Antonio", "San Francisco", "Santa Cruz"};
    bool mismatch = false;
    auto sf_hash = apply_hash_function("San Francsico");
    auto sa_hash = apply_hash_function("San Antonio");
    auto sc_hash = apply_hash_function("Santa Cruz");
    for (size_t i = 0; i < sample_keys.size(); i++) {
        auto hash_index = apply_hash_function(sample_keys[i]);
        if (hash_index == sf_hash && sample_keys[i].compare("San Francisco") != 0) {
            mismatch = true;
            break;
        }

        if (hash_index == sa_hash && sample_keys[i].compare("San Antonio") != 0) {
            mismatch = true;
            break;
        }

        if (hash_index == sc_hash && sample_keys[i].compare("Santa Cruz") != 0) {
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

TEST(test_SOAHSMP, test_get_size) {
    auto dtest_hash = soa_hashmap<double>(5);
    auto stest_hash = soa_hashmap<std::string>(5);
    EXPECT_EQ(dtest_hash.get_size(), static_cast<size_t>(0));
    EXPECT_EQ(stest_hash.get_size(), static_cast<size_t>(0));
}

TEST(test_SOAHSMP, test_get_capacity) {
    auto dtest_hash = soa_hashmap<double>(5);
    auto stest_hash = soa_hashmap<std::string>(5);
    EXPECT_EQ(dtest_hash.get_size(), static_cast<size_t>(0));
    EXPECT_EQ(stest_hash.get_size(), static_cast<size_t>(0));
    EXPECT_EQ(dtest_hash.get_capacity(), static_cast<size_t>(5));
    EXPECT_EQ(dtest_hash.get_capacity(), static_cast<size_t>(5));
}

TEST(test_SOAHSMP, test_get_keys) {
    auto dtest_hash = soa_hashmap<double>(5);
    auto stest_hash = soa_hashmap<std::string>(5);
    dtest_hash.add("San Francisco", 3.0);
    dtest_hash.add("New York", 10.0);
    dtest_hash.add("Houston", 15.0);

    stest_hash.add("San Francisco", "New York");
    stest_hash.add("New York", "Houston");
    stest_hash.add("Dallas", "San Antonio");
    EXPECT_EQ(dtest_hash.get_keys().size(), static_cast<size_t>(3));
    EXPECT_EQ(dtest_hash.get_keys().size(), static_cast<size_t>(3));
}


TEST(test_SOAHSMP, test_get_hashbucket) {
    auto dtest_hash = soa_hashmap<double>(5);
    auto stest_hash = soa_hashmap<std::string>(5);
    dtest_hash.add("San Francisco", 3.0);
    dtest_hash.add("New York", 10.0);
    dtest_hash.add("Houston", 15.0);

    stest_hash.add("San Francisco", "New York");
    stest_hash.add("New York", "Houston");
    stest_hash.add("Dallas", "San Antonio");
    auto double_hashbucket = dtest_hash.get_hash_bucket();
    EXPECT_EQ(double_hashbucket.size(), dtest_hash.get_capacity());

    auto string_hashbucket = stest_hash.get_hash_bucket();
    EXPECT_EQ(string_hashbucket.size(), stest_hash.get_capacity());
}

TEST(test_SOAHSMP, test_table_load) {
    auto dtest_hash = soa_hashmap<double>(5);
    auto stest_hash = soa_hashmap<std::string>(5);
    auto exp_DTL = static_cast<double>(dtest_hash.get_size()) / static_cast<double>(dtest_hash.get_capacity());
    auto exp_STL = static_cast<double>(stest_hash.get_size()) / static_cast<double>(stest_hash.get_capacity());
    EXPECT_EQ(exp_DTL, dtest_hash.table_load());
    EXPECT_EQ(exp_STL, stest_hash.table_load());
    dtest_hash.add("San Francisco", 3.0);
    dtest_hash.add("New York", 10.0);
    dtest_hash.add("Houston", 15.0);
    dtest_hash.add("Lufkin", 42.0);
    stest_hash.add("San Francisco", "New York");
    stest_hash.add("New York", "Houston");
    stest_hash.add("Dallas", "San Antonio");
    stest_hash.add("Lufkin", "Detriot");
    exp_DTL = static_cast<double>(dtest_hash.get_size()) / static_cast<double>(dtest_hash.get_capacity());
    exp_STL = static_cast<double>(stest_hash.get_size()) / static_cast<double>(stest_hash.get_capacity());
    EXPECT_EQ(exp_DTL, dtest_hash.table_load());
    EXPECT_EQ(exp_STL, stest_hash.table_load());
}

TEST(test_SOAHSMP, test_resize_table) {
    auto dtest_hash = soa_hashmap<double>(3);
    auto stest_hash = soa_hashmap<std::string>(3);
    auto init_cap = dtest_hash.get_capacity();
    EXPECT_EQ(init_cap, static_cast<size_t>(3));
    dtest_hash.add("San Francisco", 3.0);
    dtest_hash.add("New York", 10.0);
    EXPECT_EQ(get_next_prime(init_cap), dtest_hash.get_capacity());
    dtest_hash.add("Houston", 15.0);
    auto next_cap = dtest_hash.get_capacity();
    EXPECT_EQ(get_next_prime(next_cap), dtest_hash.get_capacity());
    dtest_hash.add("Lufkin", 42.0);
    stest_hash.add("San Francisco", "New York");
    stest_hash.add("New York", "Houston");
    EXPECT_EQ(get_next_prime(init_cap), stest_hash.get_capacity());
    stest_hash.add("Dallas", "San Antonio");
    EXPECT_EQ(get_next_prime(next_cap), stest_hash.get_capacity());
    stest_hash.add("Lufkin", "Detriot");
}



// TEST(test_SOAHSMP, test_constructor) {
//     auto dtest_hash = soa_hashmap<double>(5);
//     auto stest_hash = soa_hashmap<std::string>(5);
// }



TEST(test_MHSMP, test_constructor) {
    auto dtest_hash = soa_hashmap<double>(5);
    auto dtest_hash2 = soa_hashmap<double>(5);
    auto dtest_hash3 = soa_hashmap<double>(5);
    auto dtest_hashmap = main_hashmap<double>(5);

    auto stest_hash = soa_hashmap<std::string>(5);
    auto stest_hash2 = soa_hashmap<std::string>(5);
    auto stest_hash3 = soa_hashmap<std::string>(5);
    auto stest_hashmap = main_hashmap<std::string>(5);

    dtest_hash.add("San Francisco", 3.0);
    dtest_hash.add("New York", 10.0);
    dtest_hash.add("Houston", 15.0);

    dtest_hash2.add("Dallas", 56.0);
    dtest_hash2.add("Santa Fe", 70.2);
    dtest_hash2.add("Seattle", 45.6);

    dtest_hash3.add("Chicago", 180.3);
    dtest_hash3.add("Oklahoma City", 78.5);
    dtest_hash3.add("Denver", 96.2);

    dtest_hashmap.add_key("Miami", dtest_hash);
    dtest_hashmap.add_key("Las Vegas", dtest_hash2);
    dtest_hashmap.add_key("Orlando", dtest_hash3);

    stest_hash.add("San Francisco", "New York");
    stest_hash.add("New York", "Houston");
    stest_hash.add("Dallas", "San Antonio");

    stest_hash2.add("Santa Fe", "Seattle");
    stest_hash2.add("Chicago", "Santa Fe");
    stest_hash2.add("Oklahoma City", "Portland");

    stest_hash3.add("Denver", "Colorado Springs");
    stest_hash3.add("Miami", "Sacramento");
    stest_hash3.add("Chicago", "San Antonio");

    stest_hashmap.add_key("Los Angeles", stest_hash);
    stest_hashmap.add_key("Cupertino", stest_hash2);
    stest_hashmap.add_key("Nashville", stest_hash3);

    EXPECT_EQ(dtest_hash.get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(dtest_hash2.get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(dtest_hash3.get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(dtest_hashmap.get_size(), static_cast<unsigned int>(3));

    EXPECT_EQ(stest_hash.get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hash2.get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hash3.get_size(), static_cast<unsigned int>(3));
    EXPECT_EQ(stest_hashmap.get_size(), static_cast<unsigned int>(3));
    std::cout << stest_hashmap << '\n';
    std::cout << dtest_hashmap << '\n';
}


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