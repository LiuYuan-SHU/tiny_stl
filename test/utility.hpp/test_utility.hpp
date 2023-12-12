#ifndef TINY_STL__TEST__TEST_UTILITY_HPP
#define TINY_STL__TEST__TEST_UTILITY_HPP

#include "utility.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <string>
#include <vector>


TEST(Test_Utility, Move) {
  std::vector<int> vec = {1, 2, 3, 4, 5};
  std::vector<int> vec2 = tiny_stl::move(vec);
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec2.size(), 5);
}

TEST(Test_Utility, Forward) {
  std::vector<int> vec = {1, 3, 2, 5, 4};
  std::vector<int> vec2 = tiny_stl::forward<std::vector<int>>(vec);
  sort(vec2.begin(), vec2.end());
  EXPECT_FALSE(vec == vec2);
}

TEST(Test_Utility, Swap) {
  std::vector<int> vec = {1, 2, 3, 4, 5};
  std::vector<int> vec2 = {5, 4, 3, 2, 1};
  tiny_stl::swap(vec, vec2);
  EXPECT_EQ(vec, std::vector<int>({5, 4, 3, 2, 1}));
  EXPECT_EQ(vec2, std::vector<int>({1, 2, 3, 4, 5}));
}

TEST(Test_Utility, SwapRange) {
  std::vector<int> vec = {1, 2, 3, 4, 5};
  std::vector<int> vec2 = {5, 4, 3, 2, 1};
  tiny_stl::swap_range(vec.begin(), vec.begin() + 3, vec2.begin());
  EXPECT_EQ(vec, std::vector<int>({5, 4, 3, 4, 5}));
  EXPECT_EQ(vec2, std::vector<int>({1, 2, 3, 2, 1}));
}

TEST(Test_Utility, SwapArray) {
  int a[5] = {1, 2, 3, 4, 5};
  int b[5] = {5, 4, 3, 2, 1};
  tiny_stl::swap(a, b);
  EXPECT_EQ(a[0], 5);
  EXPECT_EQ(a[1], 4);
  EXPECT_EQ(a[2], 3);
  EXPECT_EQ(a[3], 2);
  EXPECT_EQ(a[4], 1);
  EXPECT_EQ(b[0], 1);
  EXPECT_EQ(b[1], 2);
  EXPECT_EQ(b[2], 3);
  EXPECT_EQ(b[3], 4);
  EXPECT_EQ(b[4], 5);
}

TEST(Test_Utility, Pair_Ctor_Default) {
  tiny_stl::pair<int, int> p;
  EXPECT_EQ(p.first, 0);
  EXPECT_EQ(p.second, 0);
}

TEST(Test_Utility, Pair_Ctor) {
  tiny_stl::pair<int, int> p(1, 2);
  EXPECT_EQ(p.first, 1);
  EXPECT_EQ(p.second, 2);
}

TEST(Test_Utility, Pair_CopyCtor) {
  tiny_stl::pair<int, int> p(1, 2);
  tiny_stl::pair<int, int> p2(p);
  EXPECT_EQ(p2.first, 1);
  EXPECT_EQ(p2.second, 2);
}

TEST(Test_Utility, Pair_MoveCtor) {
  tiny_stl::pair<int, int> p(1, 2);
  tiny_stl::pair<int, int> p2(tiny_stl::move(p));
  EXPECT_EQ(p2.first, 1);
  EXPECT_EQ(p2.second, 2);
}

TEST(Test_Utility, Pair_CopyAssign) {
  tiny_stl::pair<int, int> p(1, 2);
  tiny_stl::pair<int, int> p2;
  p2 = p;
  EXPECT_EQ(p2.first, 1);
  EXPECT_EQ(p2.second, 2);
}

TEST(Test_Utility, Pair_MoveAssign) {
  tiny_stl::pair<int, int> p(1, 2);
  tiny_stl::pair<int, int> p2;
  p2 = tiny_stl::move(p);
  EXPECT_EQ(p2.first, 1);
  EXPECT_EQ(p2.second, 2);
}

TEST(Test_Utility, Pair_Swap) {
  tiny_stl::pair<int, int> p(1, 2);
  tiny_stl::pair<int, int> p2(3, 4);
  p.swap(p2);
  EXPECT_EQ(p.first, 3);
  EXPECT_EQ(p.second, 4);
  EXPECT_EQ(p2.first, 1);
  EXPECT_EQ(p2.second, 2);

  tiny_stl::swap(p, p2);
  EXPECT_EQ(p.first, 1);
  EXPECT_EQ(p.second, 2);
  EXPECT_EQ(p2.first, 3);
  EXPECT_EQ(p2.second, 4);
}

TEST(Test_Utility, Pair_Operator_Equal) {
  tiny_stl::pair<int, int> p(1, 2);
  tiny_stl::pair<int, int> p2(1, 2);
  EXPECT_TRUE(p == p2);
}

TEST(Test_Utility, Pair_Operator_NotEqual) {
  tiny_stl::pair<int, int> p(1, 2);
  tiny_stl::pair<int, int> p2(1, 3);
  EXPECT_TRUE(p != p2);
}

TEST(Test_Utility, Pair_Operator_Less) {
  tiny_stl::pair<int, int> p(1, 2);
  tiny_stl::pair<int, int> p2(1, 3);
  EXPECT_TRUE(p < p2);
}

TEST(Test_Utility, Pair_Operator_Greater) {
  tiny_stl::pair<int, int> p(1, 2);
  tiny_stl::pair<int, int> p2(1, 3);
  EXPECT_TRUE(p2 > p);
}

TEST(Test_Utility, Pair_Operator_LessEqual) {
  tiny_stl::pair<int, int> p(1, 2);
  tiny_stl::pair<int, int> p2(1, 3);
  tiny_stl::pair<int, int> p3(1, 2);
  EXPECT_TRUE(p <= p2);
  EXPECT_TRUE(p <= p3);
}

TEST(Test_Utility, Pair_Operator_GreaterEqual) {
  tiny_stl::pair<int, int> p(1, 2);
  tiny_stl::pair<int, int> p2(1, 3);
  tiny_stl::pair<int, int> p3(1, 2);
  EXPECT_TRUE(p2 >= p);
  EXPECT_TRUE(p3 >= p);
}

TEST(Test_Utility, MakePair) {
  auto p = tiny_stl::make_pair(1, 2);
  EXPECT_EQ(p.first, 1);
  EXPECT_EQ(p.second, 2);
}

#endif // !TINY_STL__TEST__TEST_UTILITY_HPP
