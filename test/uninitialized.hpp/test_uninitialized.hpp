#ifndef TINY_STL__TEST__TEST_UNINItiALIZED_HPP
#define TINY_STL__TEST__TEST_UNINItiALIZED_HPP

#include "uninitialized.hpp"

#include <gtest/gtest.h>

TEST(Uninitialized, UncheckedUninitCopy_TriviallyCopyAssignable) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[sizeof(arr1) / sizeof(int)];
  tiny_stl::unchecked_uninit_copy(arr1, arr1 + 5, arr2, std::true_type());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(Uninitialized, UncheckedUninitCopy_NotTriviallyCopyAssignable) {
  std::string arr1[] = {"1", "2", "3", "4", "5"};
  std::string arr2[sizeof(arr1) / sizeof(std::string)];
  tiny_stl::unchecked_uninit_copy(arr1, arr1 + 5, arr2, std::false_type());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(Uninitialized, UncheckedUninitCopyN_TriviallyCopyAssignable) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[sizeof(arr1) / sizeof(int)];
  tiny_stl::unchecked_uninit_copy_n(arr1, 3, arr2, std::true_type());
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(Uninitialized, UncheckedUninitCopyN_NotTriviallyCopyAssignable) {
  std::string arr1[] = {"1", "2", "3", "4", "5"};
  std::string arr2[sizeof(arr1) / sizeof(std::string)];
  tiny_stl::unchecked_uninit_copy_n(arr1, 3, arr2, std::false_type());
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(Uninitialized, UncheckedUninitFill_TriviallyCopyAssignable) {
  int arr1[] = {1, 2, 3, 4, 5};
  tiny_stl::unchecked_uninit_fill(arr1, arr1 + 5, 1, std::true_type());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], 1);
  }
}

TEST(Uninitialized, UncheckedUninitFill_NotTriviallyCopyAssignable) {
  std::string arr1[] = {"1", "2", "3", "4", "5"};
  tiny_stl::unchecked_uninit_fill(arr1, arr1 + 5, "1", std::false_type());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], "1");
  }
}

TEST(Uninitialized, UncheckedUninitFillN_TriviallyCopyAssignable) {
  int arr1[] = {1, 2, 3, 4, 5};
  tiny_stl::unchecked_uninit_fill_n(arr1, 3, 1, std::true_type());
  int result[] = {1, 1, 1, 4, 5};
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], result[i]);
  }
}

TEST(Uninitialized, UncheckedUninitFillN_NotTriviallyCopyAssignable) {
  std::string arr1[] = {"1", "2", "3", "4", "5"};
  tiny_stl::unchecked_uninit_fill_n(arr1, 3, "1", std::false_type());
  std::string result[] = {"1", "1", "1", "4", "5"};
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], result[i]);
  }
}

TEST(Uninitialized, UninitializedMove_TriviallyMoveAssignable) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[sizeof(arr1) / sizeof(int)];
  tiny_stl::unchecked_uninit_move(arr1, arr1 + 5, arr2, std::true_type());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(Uninitialized, UninitializedMove_NotTriviallyMoveAssignable) {
  std::string arr1[] = {"1", "2", "3", "4", "5"};
  std::string arr2[sizeof(arr1) / sizeof(std::string)];
  tiny_stl::unchecked_uninit_move(arr1, arr1 + 5, arr2, std::false_type());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(Uninitialized, UninitializedMoveN_TriviallyMoveAssignable) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[sizeof(arr1) / sizeof(int)];
  tiny_stl::unchecked_uninit_move_n(arr1, 3, arr2, std::true_type());
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(Uninitialized, UninitializedMoveN_NotTriviallyMoveAssignable) {
  std::string arr1[] = {"1", "2", "3", "4", "5"};
  std::string arr2[sizeof(arr1) / sizeof(std::string)];
  tiny_stl::unchecked_uninit_move_n(arr1, 3, arr2, std::false_type());
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

#endif // ! TINY_STL__TEST__TEST_UNINItiALIZED_HPP
