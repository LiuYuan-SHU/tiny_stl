#ifndef TINY_STL__TEST__TEST_ALGOBASE_HPP
#define TINY_STL__TEST__TEST_ALGOBASE_HPP

#include "algobase.hpp"

#include <gtest/gtest.h>
#include <string>

TEST(Algobase, Max) {
  int left = 3, right = 4;
  std::string str1 = "1", str2 = "2";
  EXPECT_EQ(tiny_stl::max(left, right), right);
  EXPECT_EQ(tiny_stl::max(str1, str2), str2);
}

TEST(Algobase, Max_Compare) {
  int left = 3, right = 4;
  std::string str1 = "1", str2 = "2";
  EXPECT_EQ(tiny_stl::max(left, right, std::greater<int>()), left);
  EXPECT_EQ(tiny_stl::max(str1, str2, std::greater<std::string>()), str1);
}

TEST(Algobase, Min) {
  int left = 3, right = 4;
  std::string str1 = "1", str2 = "2";
  EXPECT_EQ(tiny_stl::min(left, right), left);
  EXPECT_EQ(tiny_stl::min(str1, str2), str1);
}

TEST(Algobase, Min_Compare) {
  int left = 3, right = 4;
  std::string str1 = "1", str2 = "2";
  EXPECT_EQ(tiny_stl::min(left, right, std::greater<int>()), right);
  EXPECT_EQ(tiny_stl::min(str1, str2, std::greater<std::string>()), str2);
}

TEST(Algobase, IterSwap) {
  int left = 3, right = 4;
  std::string str1 = "1", str2 = "2";
  tiny_stl::iter_swap(&left, &right);
  tiny_stl::iter_swap(&str1, &str2);
  EXPECT_EQ(left, 4);
  EXPECT_EQ(right, 3);
  EXPECT_EQ(str1, "2");
  EXPECT_EQ(str2, "1");
}

TEST(Algobase, UncheckedCopyCat_InputIteratorTag) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[5];
  tiny_stl::unchecked_copy_cat(arr1, arr1 + 5, arr2,
                               tiny_stl::input_iterator_tag());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(Algobase, UncheckedCopyCat_RandomAccessIteratorTag) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[5];
  tiny_stl::unchecked_copy_cat(arr1, arr1 + 5, arr2,
                               tiny_stl::random_access_iterator_tag());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(Algobase, UncheckedCopy_TrailingCopyConstructible) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[5];
  tiny_stl::unchecked_copy(arr1, arr1 + 5, arr2);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(Algobase, UncheckedCopyBackwardCat_Bidirectional) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[5];
  tiny_stl::unchecked_copy_backward_cat(arr1, arr1 + 5, arr2 + 5,
                                        tiny_stl::bidirectional_iterator_tag());
}

TEST(Algobase, UncheckedCopyBackwardCat_RandomAccess) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[5];
  tiny_stl::unchecked_copy_backward_cat(arr1, arr1 + 5, arr2 + 5,
                                        tiny_stl::random_access_iterator_tag());
}

TEST(Algobase, UncheckedCopyBackward_TrailingCopyConstructible) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[5];
  tiny_stl::unchecked_copy_backward(arr1, arr1 + 5, arr2 + 5);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(Algobase, CopyIf) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[5];
  tiny_stl::copy_if(arr1, arr1 + 5, arr2, [](int i) { return i % 2 == 0; });
  for (int i = 0; i < 2; ++i) {
    EXPECT_EQ(arr2[i], 2 + i * 2);
  }
}

TEST(Algobase, UncheckedCopyN_InputIteratorTag) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[5];
  tiny_stl::unchecked_copy_n(arr1, 5, arr2, tiny_stl::input_iterator_tag());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(Algobase, UncheckedCopyN_RandomAccessIteratorTag) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[5];
  tiny_stl::unchecked_copy_n(arr1, 5, arr2,
                             tiny_stl::random_access_iterator_tag());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(Algobase, UncheckedMoveCat_InputIteratorTag) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[5];
  tiny_stl::unchecked_move_cat(arr1, arr1 + 5, arr2,
                               tiny_stl::input_iterator_tag());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(Algobase, UncheckedMoveCat_RandomAccessIteratorTag) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[5];
  tiny_stl::unchecked_move_cat(arr1, arr1 + 5, arr2,
                               tiny_stl::random_access_iterator_tag());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(Algobase, UncheckedMove_TrailingMoveConstructible) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[5];
  tiny_stl::unchecked_move(arr1, arr1 + 5, arr2);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(Algobase, UncheckedMoveBackwardCat_Bidirectional) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[5];
  tiny_stl::unchecked_move_backward_cat(arr1, arr1 + 5, arr2 + 5,
                                        tiny_stl::bidirectional_iterator_tag());
}

TEST(Algobase, UncheckedMoveBackwardCat_RandomAccess) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[5];
  tiny_stl::unchecked_move_backward_cat(arr1, arr1 + 5, arr2 + 5,
                                        tiny_stl::random_access_iterator_tag());
}

TEST(Algobase, UncheckedMoveBackward_TrailingMoveConstructible) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[5];
  tiny_stl::unchecked_move_backward(arr1, arr1 + 5, arr2 + 5);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(Algobase, Equal) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[] = {1, 2, 3, 4, 5};
  EXPECT_TRUE(tiny_stl::equal(arr1, arr1 + 5, arr2));
}

TEST(Algobase, Equal_Compare) {
  struct node {
    int _id;
    int val;
  };
  node arr1[] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  node arr2[] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  EXPECT_TRUE(tiny_stl::equal(
      arr1, arr1 + 5, arr2,
      [](const node &lhs, const node &rhs) { return lhs._id == rhs._id; }));
}

TEST(Algobase, UncheckedFillN) {
  int arr[5];
  tiny_stl::unchecked_fill_n(arr, 5, 1);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], 1);
  }
}

TEST(Algobase, UncheckedFillN_1Byte) {
  char arr[5];
  tiny_stl::unchecked_fill_n(arr, 5, 'a');
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], 'a');
  }
}

TEST(Algobase, FillCat_ForwardIterator) {
  int arr[5];
  tiny_stl::fill_cat(arr, arr + 5, 1, tiny_stl::forward_iterator_tag());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], 1);
  }
}

TEST(Algobase, FillCat_RandomAccessIterator) {
  int arr[5];
  tiny_stl::fill_cat(arr, arr + 5, 1, tiny_stl::random_access_iterator_tag());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], 1);
  }
}

TEST(Algobase, LexicographicalCompare) {
  int arr_case_less_1[] = {0};
  int arr_case_less_2[] = {1};
  EXPECT_TRUE(
      tiny_stl::lexicographical_compare(arr_case_less_1, arr_case_less_1 + 1,
                                        arr_case_less_2, arr_case_less_2 + 1));
  EXPECT_FALSE(
      tiny_stl::lexicographical_compare(arr_case_less_2, arr_case_less_2 + 1,
                                        arr_case_less_1, arr_case_less_1 + 1));
  int arr_case_length_less_1[] = {0, 1};
  int arr_case_length_less_2[] = {0, 1, 2};
  EXPECT_TRUE(tiny_stl::lexicographical_compare(
      arr_case_length_less_1, arr_case_length_less_1 + 2,
      arr_case_length_less_2, arr_case_length_less_2 + 3));
  EXPECT_FALSE(tiny_stl::lexicographical_compare(
      arr_case_length_less_2, arr_case_length_less_2 + 3,
      arr_case_length_less_1, arr_case_length_less_1 + 2));
}

TEST(Algobase, LexicographicalCompare_Compare) {
  int arr_case_less_1[] = {0};
  int arr_case_less_2[] = {1};
  EXPECT_TRUE(tiny_stl::lexicographical_compare(
      arr_case_less_1, arr_case_less_1 + 1, arr_case_less_2,
      arr_case_less_2 + 1, std::less<int>()));
  EXPECT_FALSE(tiny_stl::lexicographical_compare(
      arr_case_less_2, arr_case_less_2 + 1, arr_case_less_1,
      arr_case_less_1 + 1, std::less<int>()));
  int arr_case_length_less_1[] = {0, 1};
  int arr_case_length_less_2[] = {0, 1, 2};
  EXPECT_TRUE(tiny_stl::lexicographical_compare(
      arr_case_length_less_1, arr_case_length_less_1 + 2,
      arr_case_length_less_2, arr_case_length_less_2 + 3, std::less<int>()));
  EXPECT_FALSE(tiny_stl::lexicographical_compare(
      arr_case_length_less_2, arr_case_length_less_2 + 3,
      arr_case_length_less_1, arr_case_length_less_1 + 2, std::less<int>()));
}

TEST(Algobase, LexicographicalCompare_Char) {
  char arr_case_less_1[] = {'a'};
  char arr_case_less_2[] = {'b'};
  EXPECT_TRUE(tiny_stl::lexicographical_compare(
      arr_case_less_1, arr_case_less_1 + 1, arr_case_less_2,
      arr_case_less_2 + 1, std::less<char>()));
  EXPECT_FALSE(tiny_stl::lexicographical_compare(
      arr_case_less_2, arr_case_less_2 + 1, arr_case_less_1,
      arr_case_less_1 + 1, std::less<char>()));
  char arr_case_length_less_1[] = {'a', 'b'};
  char arr_case_length_less_2[] = {'a', 'b', 'c'};
  EXPECT_TRUE(tiny_stl::lexicographical_compare(
      arr_case_length_less_1, arr_case_length_less_1 + 2,
      arr_case_length_less_2, arr_case_length_less_2 + 3, std::less<char>()));
  EXPECT_FALSE(tiny_stl::lexicographical_compare(
      arr_case_length_less_2, arr_case_length_less_2 + 3,
      arr_case_length_less_1, arr_case_length_less_1 + 2, std::less<char>()));
}

TEST(Algobase, Mismatch) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[] = {1, 2, 3, 4, 5};
  EXPECT_EQ(tiny_stl::mismatch(arr1, arr1 + 5, arr2).first, arr1 + 5);
  EXPECT_EQ(tiny_stl::mismatch(arr1, arr1 + 5, arr2).second, arr2 + 5);

  int arr3[] = {1, 2, 3, 4, 5};
  int arr4[] = {1, 2, 3, 4, 6};
  EXPECT_EQ(tiny_stl::mismatch(arr3, arr3 + 5, arr4).first, arr3 + 4);
  EXPECT_EQ(tiny_stl::mismatch(arr3, arr3 + 5, arr4).second, arr4 + 4);
}

#endif // ! TINY_STL__TEST__TEST_ALGOBASE_HPP