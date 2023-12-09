#ifndef TINY_STL__TEST__TEST_CONSTRUCT_HPP
#define TINY_STL__TEST__TEST_CONSTRUCT_HPP

#include "construct.hpp"

#include <gtest/gtest.h>
#include <type_traits>

TEST(Construct, Construct_Inplace_Empty) {
  int *ptr = new int(3);
  EXPECT_EQ(*ptr, 3);
  tiny_stl::construct(ptr);
  EXPECT_EQ(*ptr, 0);
  delete ptr;
}

TEST(Construct, Construct_Inplace_SingleParam) {
  int *ptr = new int(3);
  EXPECT_EQ(*ptr, 3);
  tiny_stl::construct(ptr, 4);
  EXPECT_EQ(*ptr, 4);
  delete ptr;
}

TEST(Construct, Construct_Inplace_MultiParam) {
  struct A {
    int a;
    int b;
    A(int a, int b) : a(a), b(b) {}
  };
  A *ptr = new A(3, 4);
  EXPECT_EQ(ptr->a, 3);
  EXPECT_EQ(ptr->b, 4);
  tiny_stl::construct(ptr, 5, 6);
  EXPECT_EQ(ptr->a, 5);
  EXPECT_EQ(ptr->b, 6);
  delete ptr;
}

TEST(Construct, Destroy_One) {
  int *ptr = new int(3);
  EXPECT_EQ(*ptr, 3);
  static_assert(std::is_trivially_destructible_v<int>,
                "type of int is trivial");
  tiny_stl::destroy_one(ptr, std::is_trivially_destructible<int>{});
  EXPECT_EQ(*ptr, 3);
  delete ptr;
}

TEST(Construct, Destroy_One_NonTrivial) {
  struct A {
    int a;
    int b;
    A(int a, int b) : a(a), b(b) {}
    ~A() { a = b = 0; }
  };
  A *ptr = new A(3, 4);
  EXPECT_EQ(ptr->a, 3);
  EXPECT_EQ(ptr->b, 4);
  static_assert(!std::is_trivially_destructible_v<A>,
                "type of A is not trivial");
  tiny_stl::destroy_one(ptr, std::is_trivially_destructible<A>{});
  EXPECT_EQ(ptr->a, 0);
  EXPECT_EQ(ptr->b, 0);
  delete ptr;
}

TEST(Construct, Destroy_Cat) {
  int *ptr = new int[3]{1, 2, 3};
  EXPECT_EQ(ptr[0], 1);
  EXPECT_EQ(ptr[1], 2);
  EXPECT_EQ(ptr[2], 3);
  static_assert(std::is_trivially_destructible_v<int>,
                "type of int is trivial");
  tiny_stl::destroy_cat(ptr, ptr + 3, std::is_trivially_destructible<int>{});
  EXPECT_EQ(ptr[0], 1);
  EXPECT_EQ(ptr[1], 2);
  EXPECT_EQ(ptr[2], 3);
  delete[] ptr;
}

TEST(Construct, Destroy_Cat_NonTrivial) {
  struct A {
    int a;
    int b;
    A(int a, int b) : a(a), b(b) {}
    ~A() { a = b = 0; }
  };
  A *ptr = new A[3]{{1, 2}, {3, 4}, {5, 6}};
  EXPECT_EQ(ptr[0].a, 1);
  EXPECT_EQ(ptr[0].b, 2);
  EXPECT_EQ(ptr[1].a, 3);
  EXPECT_EQ(ptr[1].b, 4);
  EXPECT_EQ(ptr[2].a, 5);
  EXPECT_EQ(ptr[2].b, 6);
  static_assert(!std::is_trivially_destructible_v<A>,
                "type of A is not trivial");
  tiny_stl::destroy_cat(ptr, ptr + 3, std::is_trivially_destructible<A>{});
  EXPECT_EQ(ptr[0].a, 0);
  EXPECT_EQ(ptr[0].b, 0);
  EXPECT_EQ(ptr[1].a, 0);
  EXPECT_EQ(ptr[1].b, 0);
  EXPECT_EQ(ptr[2].a, 0);
  EXPECT_EQ(ptr[2].b, 0);
  delete[] ptr;
}

TEST(Construct, Destroy_Trailing) {
  int *ptr = new int[3]{1, 2, 3};
  EXPECT_EQ(ptr[0], 1);
  EXPECT_EQ(ptr[1], 2);
  EXPECT_EQ(ptr[2], 3);
  static_assert(std::is_trivially_destructible_v<int>,
                "type of int is trivial");
  tiny_stl::destroy(ptr, ptr + 3);
  EXPECT_EQ(ptr[0], 1);
  EXPECT_EQ(ptr[1], 2);
  EXPECT_EQ(ptr[2], 3);
  delete[] ptr;
}

TEST(Construct, Destroy_NonTrailing) {
  struct A {
    int a;
    int b;
    A(int a, int b) : a(a), b(b) {}
    ~A() { a = b = 0; }
  };
  A *ptr = new A[3]{{1, 2}, {3, 4}, {5, 6}};
  EXPECT_EQ(ptr[0].a, 1);
  EXPECT_EQ(ptr[0].b, 2);
  EXPECT_EQ(ptr[1].a, 3);
  EXPECT_EQ(ptr[1].b, 4);
  EXPECT_EQ(ptr[2].a, 5);
  EXPECT_EQ(ptr[2].b, 6);
  static_assert(!std::is_trivially_destructible_v<A>,
                "type of A is not trivial");
  tiny_stl::destroy(ptr, ptr + 3);
  EXPECT_EQ(ptr[0].a, 0);
  EXPECT_EQ(ptr[0].b, 0);
  EXPECT_EQ(ptr[1].a, 0);
  EXPECT_EQ(ptr[1].b, 0);
  EXPECT_EQ(ptr[2].a, 0);
  EXPECT_EQ(ptr[2].b, 0);
  delete[] ptr;
}

#endif // TINY_STL__TEST__TEST_CONSTRUCT_HPP