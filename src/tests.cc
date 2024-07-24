#include <gtest/gtest.h>
#include "../includes/linked_list.hpp"

TEST(test1, Testassert) {
    EXPECT_STRNE("Hello", "World");
    EXPECT_EQ(7 * 6, 42);
}

TEST(test1, TestList) {
    auto test_list = dl_list<std::string, 0> {};
    test_list.add_to_back("first node");
    auto list_size = test_list.get_size();
    decltype (list_size) exp_size = 1;
    EXPECT_EQ(list_size, exp_size);
    EXPECT_TRUE(test_list.contains_node("first node"));
}