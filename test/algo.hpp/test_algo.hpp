#ifndef TINY_STL__TEST__TEST_ALGO_HPP
#define TINY_STL__TEST__TEST_ALGO_HPP

#include "algo.hpp"

#include "test_algo_helper.hpp"

#include <gtest/gtest.h>

using vector = TestAlgo::vector;
using list = TestAlgo::list;

TEST_F(TestAlgo, AllOf) {
  vector v(10, 1);
  EXPECT_TRUE(
      tiny_stl::all_of(v.begin(), v.end(), [](int val) { return val == 1; }));
}

TEST_F(TestAlgo, AnyOf) {
  vector v(10, 1);
  EXPECT_TRUE(
      tiny_stl::any_of(v.begin(), v.end(), [](int val) { return val == 1; }));
}

TEST_F(TestAlgo, NoneOf) {
  vector v(10, 1);
  EXPECT_FALSE(
      tiny_stl::none_of(v.begin(), v.end(), [](int val) { return val == 1; }));
}

TEST_F(TestAlgo, Count) {
  vector v(10, 1);
  EXPECT_EQ(tiny_stl::count(v.begin(), v.end(), 1), 10);
}

TEST_F(TestAlgo, CountIf) {
  vector v(10, 1);
  EXPECT_EQ(
      tiny_stl::count_if(v.begin(), v.end(), [](int val) { return val == 1; }),
      10);
}

TEST_F(TestAlgo, Find) {
  vector v1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(tiny_stl::find(v1.begin(), v1.end(), 3), v1.begin() + 2);
}

TEST_F(TestAlgo, FindIf) {
  vector v1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(
      tiny_stl::find_if(v1.begin(), v1.end(), [](int val) { return val == 3; }),
      v1.begin() + 2);
}

TEST_F(TestAlgo, FindIfNot) {
  vector v1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(tiny_stl::find_if_not(v1.begin(), v1.end(),
                                  [](int val) { return val == 3; }),
            v1.begin());
}

TEST_F(TestAlgo, Search) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2 = {3, 4};
  EXPECT_EQ(tiny_stl::search(v1.begin(), v1.end(), v2.begin(), v2.end()),
            v1.begin() + 2);
}

TEST_F(TestAlgo, Search_Compare) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2 = {3, 4};
  EXPECT_EQ(tiny_stl::search(v1.begin(), v1.end(), v2.begin(), v2.end(),
                             [](int val1, int val2) { return val1 == val2; }),
            v1.begin() + 2);
}

TEST_F(TestAlgo, SearchN) {
  vector v1 = {1, 2, 3, 3, 5};
  EXPECT_EQ(tiny_stl::search_n(v1.begin(), v1.end(), 2, 3), v1.begin() + 2);
}

TEST_F(TestAlgo, SearchN_Compare) {
  vector v1 = {1, 2, 3, 3, 5};
  EXPECT_EQ(tiny_stl::search_n(v1.begin(), v1.end(), 2, 3,
                               [](int val1, int val2) { return val1 == val2; }),
            v1.begin() + 2);
}

TEST_F(TestAlgo, FindEndDispatch_ForwardIteratorTag) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2 = {3, 4};
  EXPECT_EQ(tiny_stl::find_end_dispatch(v1.begin(), v1.end(), v2.begin(),
                                        v2.end(),
                                        tiny_stl::forward_iterator_tag(),
                                        tiny_stl::forward_iterator_tag()),
            v1.begin() + 2);
}

TEST_F(TestAlgo, FindEndDispatch_BidirectionalIteratorTag) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2 = {3, 4};
  EXPECT_EQ(tiny_stl::find_end_dispatch(v1.begin(), v1.end(), v2.begin(),
                                        v2.end(),
                                        tiny_stl::bidirectional_iterator_tag(),
                                        tiny_stl::bidirectional_iterator_tag()),
            v1.begin() + 2);
}

TEST_F(TestAlgo, FindEnd) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2 = {3, 4};
  EXPECT_EQ(tiny_stl::find_end(v1.begin(), v1.end(), v2.begin(), v2.end()),
            v1.begin() + 2);
}

TEST_F(TestAlgo, FindEndDispatch_Compare_ForwardIteratorTag) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2 = {3, 4};
  EXPECT_EQ(tiny_stl::find_end_dispatch(
                v1.begin(), v1.end(), v2.begin(), v2.end(),
                tiny_stl::forward_iterator_tag(),
                tiny_stl::forward_iterator_tag(),
                [](int val1, int val2) { return val1 == val2; }),
            v1.begin() + 2);
}

TEST_F(TestAlgo, FindEndDispatch_Compare_BidirectionalIteratorTag) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2 = {3, 4};
  EXPECT_EQ(tiny_stl::find_end_dispatch(
                v1.begin(), v1.end(), v2.begin(), v2.end(),
                tiny_stl::bidirectional_iterator_tag(),
                tiny_stl::bidirectional_iterator_tag(),
                [](int val1, int val2) { return val1 == val2; }),
            v1.begin() + 2);
}

TEST_F(TestAlgo, FindEnd_Compare) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2 = {3, 4};
  EXPECT_EQ(tiny_stl::find_end(v1.begin(), v1.end(), v2.begin(), v2.end(),
                               [](int val1, int val2) { return val1 == val2; }),
            v1.begin() + 2);
}

TEST_F(TestAlgo, FindFirstOf) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2 = {3, 4};
  EXPECT_EQ(tiny_stl::find_first_of(v1.begin(), v1.end(), v2.begin(), v2.end()),
            v1.begin() + 2);
}

TEST_F(TestAlgo, FindFirstOf_Compare) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2 = {3, 4};
  EXPECT_EQ(
      tiny_stl::find_first_of(v1.begin(), v1.end(), v2.begin(), v2.end(),
                              [](int val1, int val2) { return val1 == val2; }),
      v1.begin() + 2);
}

TEST_F(TestAlgo, ForEach) {
  vector v1 = {1, 2, 3, 4, 5};
  tiny_stl::for_each(v1.begin(), v1.end(), [](int &val) { ++val; });
  EXPECT_EQ(v1, vector({2, 3, 4, 5, 6}));
}

TEST_F(TestAlgo, AdjacentFind) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(tiny_stl::adjacent_find(v1.begin(), v1.end()), v1.begin() + 2);
}

TEST_F(TestAlgo, AdjacentFind_Compare) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(
      tiny_stl::adjacent_find(v1.begin(), v1.end(),
                              [](int val1, int val2) { return val1 == val2; }),
      v1.begin() + 2);
}

TEST_F(TestAlgo, LBoundDispatch_ForwardIteratorTag) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(tiny_stl::lbound_dispatch(v1.begin(), v1.end(), 3,
                                      tiny_stl::forward_iterator_tag()),
            v1.begin() + 2);
}

TEST_F(TestAlgo, LBoundDispatch_RandomAccessIteratorTag) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(tiny_stl::lbound_dispatch(v1.begin(), v1.end(), 3,
                                      tiny_stl::random_access_iterator_tag()),
            v1.begin() + 2);
}

TEST_F(TestAlgo, LowerBound) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(tiny_stl::lower_bound(v1.begin(), v1.end(), 3), v1.begin() + 2);
}

TEST_F(TestAlgo, LBound_Compare_ForwardIteratorTag) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(tiny_stl::lbound_dispatch(
                v1.begin(), v1.end(), 3, tiny_stl::forward_iterator_tag(),
                [](int val1, int val2) { return val1 < val2; }),
            v1.begin() + 2);
}

TEST_F(TestAlgo, LBound_Compare_RandomAccessIteratorTag) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(tiny_stl::lbound_dispatch(
                v1.begin(), v1.end(), 3, tiny_stl::random_access_iterator_tag(),
                [](int val1, int val2) { return val1 < val2; }),
            v1.begin() + 2);
}

TEST_F(TestAlgo, LowerBound_Compare) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(
      tiny_stl::lower_bound(v1.begin(), v1.end(), 3,
                            [](int val1, int val2) { return val1 < val2; }),
      v1.begin() + 2);
}

TEST_F(TestAlgo, UBoundDispatch_ForwardIteratorTag) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(tiny_stl::ubound_dispatch(v1.begin(), v1.end(), 3,
                                      tiny_stl::forward_iterator_tag()),
            v1.begin() + 4);
}

TEST_F(TestAlgo, UBoundDispatch_RandomAccessIteratorTag) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(tiny_stl::ubound_dispatch(v1.begin(), v1.end(), 3,
                                      tiny_stl::random_access_iterator_tag()),
            v1.begin() + 4);
}

TEST_F(TestAlgo, UpperBound) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(tiny_stl::upper_bound(v1.begin(), v1.end(), 3), v1.begin() + 4);
}

TEST_F(TestAlgo, UBound_Compare_ForwardIteratorTag) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(tiny_stl::ubound_dispatch(
                v1.begin(), v1.end(), 3, tiny_stl::forward_iterator_tag(),
                [](int val1, int val2) { return val1 < val2; }),
            v1.begin() + 4);
}

TEST_F(TestAlgo, UBound_Compare_RandomAccessIteratorTag) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(tiny_stl::ubound_dispatch(
                v1.begin(), v1.end(), 3, tiny_stl::random_access_iterator_tag(),
                [](int val1, int val2) { return val1 < val2; }),
            v1.begin() + 4);
}

TEST_F(TestAlgo, UpperBound_Compare) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(
      tiny_stl::upper_bound(v1.begin(), v1.end(), 3,
                            [](int val1, int val2) { return val1 < val2; }),
      v1.begin() + 4);
}

TEST_F(TestAlgo, BinarySearch) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_TRUE(tiny_stl::binary_search(v1.begin(), v1.end(), 3));
}

TEST_F(TestAlgo, BinarySearch_Compare) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_TRUE(tiny_stl::binary_search(
      v1.begin(), v1.end(), 3, [](int val1, int val2) { return val1 < val2; }));
}

TEST_F(TestAlgo, ERangeDispatch_ForwardIterator) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(tiny_stl::erange_dispatch(v1.begin(), v1.end(), 3,
                                      tiny_stl::forward_iterator_tag()),
            tiny_stl::make_pair(v1.begin() + 2, v1.begin() + 4));
}

TEST_F(TestAlgo, ERangeDispatch_RandomAccessIterator) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(tiny_stl::erange_dispatch(v1.begin(), v1.end(), 3,
                                      tiny_stl::random_access_iterator_tag()),
            tiny_stl::make_pair(v1.begin() + 2, v1.begin() + 4));
}

TEST_F(TestAlgo, EqualRange) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(tiny_stl::equal_range(v1.begin(), v1.end(), 3),
            tiny_stl::make_pair(v1.begin() + 2, v1.begin() + 4));
}

TEST_F(TestAlgo, ERange_Compare_ForwardIterator) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(tiny_stl::erange_dispatch(
                v1.begin(), v1.end(), 3, tiny_stl::forward_iterator_tag(),
                [](int val1, int val2) { return val1 < val2; }),
            tiny_stl::make_pair(v1.begin() + 2, v1.begin() + 4));
}

TEST_F(TestAlgo, ERange_Compare_RandomAccessIterator) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(tiny_stl::erange_dispatch(
                v1.begin(), v1.end(), 3, tiny_stl::random_access_iterator_tag(),
                [](int val1, int val2) { return val1 < val2; }),
            tiny_stl::make_pair(v1.begin() + 2, v1.begin() + 4));
}

TEST_F(TestAlgo, EqualRange_Compare) {
  vector v1 = {1, 2, 3, 3, 4, 5};
  EXPECT_EQ(
      tiny_stl::equal_range(v1.begin(), v1.end(), 3,
                            [](int val1, int val2) { return val1 < val2; }),
      tiny_stl::make_pair(v1.begin() + 2, v1.begin() + 4));
}

TEST_F(TestAlgo, Generate) {
  vector v1(10);
  tiny_stl::generate(v1.begin(), v1.end(), []() { return 1; });
  EXPECT_EQ(v1, vector(10, 1));
}

TEST_F(TestAlgo, GenerateN) {
  vector v1(10);
  tiny_stl::generate_n(v1.begin(), 10, []() { return 1; });
  EXPECT_EQ(v1, vector(10, 1));
}

TEST_F(TestAlgo, Includes) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2 = {2, 3};
  EXPECT_TRUE(tiny_stl::includes(v1.begin(), v1.end(), v2.begin(), v2.end()));
}

TEST_F(TestAlgo, Includes_Compare) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2 = {2, 3};
  EXPECT_TRUE(
      tiny_stl::includes(v1.begin(), v1.end(), v2.begin(), v2.end(),
                         [](int val1, int val2) { return val1 == val2; }));
}

TEST_F(TestAlgo, IsHeap) {
  vector v1 = {1, 2, 3, 4, 5};
  EXPECT_FALSE(tiny_stl::is_heap(v1.begin(), v1.end()));

  vector v2 = {7, 3, 6, 2, 1, 4, 5};
  EXPECT_TRUE(tiny_stl::is_heap(v2.begin(), v2.end()));
}

TEST_F(TestAlgo, IsHeap_Compare) {
  vector v1 = {1, 2, 3, 4, 5};
  EXPECT_FALSE(tiny_stl::is_heap(
      v1.begin(), v1.end(), [](int val1, int val2) { return val1 < val2; }));

  vector v2 = {7, 3, 6, 2, 1, 4, 5};
  EXPECT_TRUE(tiny_stl::is_heap(
      v2.begin(), v2.end(), [](int val1, int val2) { return val1 < val2; }));
}

TEST_F(TestAlgo, IsSorted) {
  vector v1 = {1, 2, 3, 4, 5};
  EXPECT_TRUE(tiny_stl::is_sorted(v1.begin(), v1.end()));

  vector v2 = {7, 3, 6, 2, 1, 4, 5};
  EXPECT_FALSE(tiny_stl::is_sorted(v2.begin(), v2.end()));
}

TEST_F(TestAlgo, IsSorted_Compare) {
  vector v1 = {1, 2, 3, 4, 5};
  EXPECT_TRUE(tiny_stl::is_sorted(
      v1.begin(), v1.end(), [](int val1, int val2) { return val1 < val2; }));

  vector v2 = {7, 3, 6, 2, 1, 4, 5};
  EXPECT_FALSE(tiny_stl::is_sorted(
      v2.begin(), v2.end(), [](int val1, int val2) { return val1 < val2; }));
}

TEST_F(TestAlgo, Median) {
  int arr_1[] = {1, 2, 3};
  int arr_2[] = {3, 2, 1};
  int arr_3[] = {1, 3, 2};
  EXPECT_EQ(tiny_stl::median(arr_1[0], arr_1[1], arr_1[2]), 2);
  EXPECT_EQ(tiny_stl::median(arr_2[0], arr_2[1], arr_2[2]), 2);
  EXPECT_EQ(tiny_stl::median(arr_3[0], arr_3[1], arr_3[2]), 2);
}

TEST_F(TestAlgo, Median_Compare) {
  int arr_1[] = {1, 2, 3};
  int arr_2[] = {3, 2, 1};
  int arr_3[] = {1, 3, 2};
  EXPECT_EQ(tiny_stl::median(arr_1[0], arr_1[1], arr_1[2],
                             [](int val1, int val2) { return val1 < val2; }),
            2);
  EXPECT_EQ(tiny_stl::median(arr_2[0], arr_2[1], arr_2[2],
                             [](int val1, int val2) { return val1 < val2; }),
            2);
  EXPECT_EQ(tiny_stl::median(arr_3[0], arr_3[1], arr_3[2],
                             [](int val1, int val2) { return val1 < val2; }),
            2);
}

TEST_F(TestAlgo, MaxElement) {
  vector v1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(tiny_stl::max_element(v1.begin(), v1.end()), v1.end() - 1);
}

TEST_F(TestAlgo, MaxElement_Compare) {
  vector v1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(
      tiny_stl::max_element(v1.begin(), v1.end(),
                            [](int val1, int val2) { return val1 < val2; }),
      v1.end() - 1);
}

TEST_F(TestAlgo, MinElement) {
  vector v1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(tiny_stl::min_element(v1.begin(), v1.end()), v1.begin());
}

TEST_F(TestAlgo, MinElement_Compare) {
  vector v1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(
      tiny_stl::min_element(v1.begin(), v1.end(),
                            [](int val1, int val2) { return val1 < val2; }),
      v1.begin());
}

TEST_F(TestAlgo, SwapRanges) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2 = {6, 7, 8, 9, 10};
  tiny_stl::swap_ranges(v1.begin(), v1.end(), v2.begin());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1[i], 6 + i);
    EXPECT_EQ(v2[i], 1 + i);
  }
}

TEST_F(TestAlgo, Transform) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2(5);
  tiny_stl::transform(v1.begin(), v1.end(), v2.begin(),
                      [](int val) { return val * val; });
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v2[i], (i + 1) * (i + 1));
  }
}

TEST_F(TestAlgo, Transform_Binary) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2 = {1, 2, 3, 4, 5};
  vector v3(5);
  tiny_stl::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(),
                      [](int val1, int val2) { return val1 * val2; });
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v3[i], (i + 1) * (i + 1));
  }
}

TEST_F(TestAlgo, RemoveCopy) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2(5);
  tiny_stl::remove_copy(v1.begin(), v1.end(), v2.begin(), 3);
  EXPECT_EQ(v2, vector({1, 2, 4, 5, 0}));
}

TEST_F(TestAlgo, RemoveCopyIf_Unary) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2(5);
  tiny_stl::remove_copy_if(v1.begin(), v1.end(), v2.begin(),
                           [](int val) { return val == 3; });
  EXPECT_EQ(v2, vector({1, 2, 4, 5, 0}));
}

TEST_F(TestAlgo, Replace) {
  int arr[] = {1, 2, 3, 4, 5};
  tiny_stl::replace(arr, arr + 5, 3, 6);
  EXPECT_EQ(tiny_stl::make_pair(arr, arr + 5),
            tiny_stl::make_pair(arr, arr + 5));
}

TEST_F(TestAlgo, ReplaceCopy) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2(5);
  tiny_stl::replace_copy(v1.begin(), v1.end(), v2.begin(), 3, 6);
  EXPECT_EQ(v2, vector({1, 2, 6, 4, 5}));
}

TEST_F(TestAlgo, ReplaceCopyIf) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2(5);
  tiny_stl::replace_copy_if(
      v1.begin(), v1.end(), v2.begin(), [](int val) { return val == 3; }, 6);
  EXPECT_EQ(v2, vector({1, 2, 6, 4, 5}));
}

TEST_F(TestAlgo, ReplaceIf) {
  int arr[] = {1, 2, 3, 4, 5};
  tiny_stl::replace_if(
      arr, arr + 5, [](int val) { return val == 3; }, 6);
  EXPECT_EQ(tiny_stl::make_pair(arr, arr + 5),
            tiny_stl::make_pair(arr, arr + 5));
}

TEST_F(TestAlgo, ReverseDispatch_BidirectionalIteratorTag) {
  vector v1 = {1, 2, 3, 4, 5};
  tiny_stl::reverse_dispatch(v1.begin(), v1.end(),
                             tiny_stl::bidirectional_iterator_tag());
  EXPECT_EQ(v1, vector({5, 4, 3, 2, 1}));
}

TEST_F(TestAlgo, ReverseDispatch_RandomAccessIteratorTag) {
  vector v1 = {1, 2, 3, 4, 5};
  tiny_stl::reverse_dispatch(v1.begin(), v1.end(),
                             tiny_stl::random_access_iterator_tag());
  EXPECT_EQ(v1, vector({5, 4, 3, 2, 1}));
}

TEST_F(TestAlgo, Reverse) {
  vector v1 = {1, 2, 3, 4, 5};
  tiny_stl::reverse(v1.begin(), v1.end());
  EXPECT_EQ(v1, vector({5, 4, 3, 2, 1}));
}

TEST_F(TestAlgo, ReverseCopy) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2(5);
  tiny_stl::reverse_copy(v1.begin(), v1.end(), v2.begin());
  EXPECT_EQ(v2, vector({5, 4, 3, 2, 1}));
}

TEST_F(TestAlgo, RandomShuffle) {
  vector v1 = {1, 2, 3, 4, 5};
  tiny_stl::random_shuffle(v1.begin(), v1.end());
  EXPECT_NE(v1, vector({1, 2, 3, 4, 5}));
}

TEST_F(TestAlgo, RotateDispatch_ForwardIterator) {
  vector v1 = {1, 2, 3, 4, 5};
  tiny_stl::rotate_dispatch(v1.begin(), v1.begin() + 2, v1.end(),
                            tiny_stl::forward_iterator_tag());
  EXPECT_EQ(v1, vector({3, 4, 5, 1, 2}));
}

TEST_F(TestAlgo, RotateDispatch_BidirectionalIterator) {
  vector v1 = {1, 2, 3, 4, 5};
  tiny_stl::rotate_dispatch(v1.begin(), v1.begin() + 2, v1.end(),
                            tiny_stl::bidirectional_iterator_tag());
  EXPECT_EQ(v1, vector({3, 4, 5, 1, 2}));
}

TEST_F(TestAlgo, RGcd) {
  EXPECT_EQ(tiny_stl::rgcd(1, 2), 1);
  EXPECT_EQ(tiny_stl::rgcd(2, 1), 1);
  EXPECT_EQ(tiny_stl::rgcd(2, 2), 2);
  EXPECT_EQ(tiny_stl::rgcd(2, 3), 1);
  EXPECT_EQ(tiny_stl::rgcd(3, 2), 1);
  EXPECT_EQ(tiny_stl::rgcd(3, 3), 3);
}

TEST_F(TestAlgo, RotateDispatch_RandomAccessIterator) {
  vector v1 = {1, 2, 3, 4, 5};
  tiny_stl::rotate_dispatch(v1.begin(), v1.begin() + 2, v1.end(),
                            tiny_stl::random_access_iterator_tag());
  EXPECT_EQ(v1, vector({3, 4, 5, 1, 2}));
}

TEST_F(TestAlgo, Rotate) {
  vector v1 = {1, 2, 3, 4, 5};
  tiny_stl::rotate(v1.begin(), v1.begin() + 2, v1.end());
  EXPECT_EQ(v1, vector({3, 4, 5, 1, 2}));
}

TEST_F(TestAlgo, RotateCopy) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2(5);
  tiny_stl::rotate_copy(v1.begin(), v1.begin() + 2, v1.end(), v2.begin());
  EXPECT_EQ(v2, vector({3, 4, 5, 1, 2}));
}

TEST_F(TestAlgo, IsPermutation) {
  vector v1 = {1, 2, 3, 4, 5};
  vector v2 = {3, 4, 5, 1, 2};
  EXPECT_TRUE(
      tiny_stl::is_permutation(v1.begin(), v1.end(), v2.begin(), v2.end()));
}

TEST_F(TestAlgo, NextPermutation) {
  vector v1 = {1, 2, 3, 4, 5};
  tiny_stl::next_permutation(v1.begin(), v1.end());
  EXPECT_EQ(v1, vector({1, 2, 3, 5, 4}));
}

TEST_F(TestAlgo, NextPermutation_Compare) {
  vector v1 = {1, 2, 3, 4, 5};
  tiny_stl::next_permutation(v1.begin(), v1.end(),
                             [](int val1, int val2) { return val1 < val2; });
  EXPECT_EQ(v1, vector({1, 2, 3, 5, 4}));
}

TEST_F(TestAlgo, PrevPermutation) {
  vector v1 = {1, 2, 3, 4, 5};
  tiny_stl::prev_permutation(v1.begin(), v1.end());
  EXPECT_EQ(v1, vector({5, 4, 3, 2, 1}));
}

TEST_F(TestAlgo, PrevPermutation_Compare) {
  vector v1 = {1, 2, 3, 4, 5};
  tiny_stl::prev_permutation(v1.begin(), v1.end(),
                             [](int val1, int val2) { return val1 < val2; });
  EXPECT_EQ(v1, vector({5, 4, 3, 2, 1}));
}

TEST_F(TestAlgo, Merge) {
  vector v1 = {1, 3, 5, 7, 9};
  vector v2 = {2, 4, 6, 8, 10};
  vector v3(10);
  tiny_stl::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
  EXPECT_EQ(v3, vector({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));
}

TEST_F(TestAlgo, Merge_Compare) {
  vector v1 = {1, 3, 5, 7, 9};
  vector v2 = {2, 4, 6, 8, 10};
  vector v3(10);
  tiny_stl::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin(),
                  [](int val1, int val2) { return val1 < val2; });
  EXPECT_EQ(v3, vector({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));
}

#endif // !TINY_STL__TEST__TEST_ALGO_HPP