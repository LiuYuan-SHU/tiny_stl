#ifndef TINY_STL__TEST__TEST_HEAP_ALGO_HPP
#define TINY_STL__TEST__TEST_HEAP_ALGO_HPP

#include "heap_algo.hpp"

#include <algorithm>
#include <gtest/gtest.h>

TEST(HeapAlgo, PushHeapAux) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7};
  tiny_stl::push_heap_aux(arr, 6, 0, 8);
  EXPECT_EQ(8, arr[0]);
}

TEST(HeapAlgo, PushHeapD) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7};
  tiny_stl::push_heap_d(
      arr, arr + 7, tiny_stl::distance_type(std::decay_t<decltype(arr)>(0)));
  EXPECT_EQ(7, arr[0]);
}

TEST(HeapAlgo, PushHeap) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7};
  tiny_stl::push_heap(arr, arr + 7);
  EXPECT_EQ(7, arr[0]);
}

TEST(HeapAlgo, PushHeapAux_Compare) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7};
  tiny_stl::push_heap_aux(arr, 6, 0, 8, std::less<int>());
  EXPECT_EQ(8, arr[0]);
}

TEST(HeapAlgo, PushHeapD_Compare) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7};
  tiny_stl::push_heap_d(arr, arr + 7,
                        tiny_stl::distance_type(std::decay_t<decltype(arr)>(0)),
                        std::less<int>());
  EXPECT_EQ(7, arr[0]);
}

TEST(HeapAlgo, PushHeap_Compare) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7};
  tiny_stl::push_heap(arr, arr + 7, std::less<int>());
  EXPECT_EQ(7, arr[0]);
}

TEST(HeapAlgo, AdjustHeap) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7};
  tiny_stl::adjust_heap(arr, 0, 7, 8);
  EXPECT_EQ(8, arr[0]);
}

TEST(HeapAlgo, PopHeapAux) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7};
  tiny_stl::pop_heap_aux(std::decay_t<decltype(arr)>(arr), arr + 6, arr + 6, 7,
                         (ptrdiff_t *)(0));
  EXPECT_EQ(7, arr[0]);
}

TEST(HeapAlgo, PopHeap) {
  int arr[] = {7, 3, 5, 1, 2, 4, 6};
  tiny_stl::pop_heap(arr, arr + 7);
  EXPECT_EQ(7, arr[6]);
}

TEST(HeapAlgo, AdjustHeap_Compare) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7};
  tiny_stl::adjust_heap(arr, 0, 7, 8, std::less<int>());
  EXPECT_EQ(8, arr[0]);
}

TEST(HeapAlgo, PopHeapAux_Compare) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7};
  tiny_stl::pop_heap_aux(std::decay_t<decltype(arr)>(arr), arr + 6, arr + 6, 7,
                         (ptrdiff_t *)(0), std::less<int>());
  EXPECT_EQ(7, arr[0]);
}

TEST(HeapAlgo, PopHeap_Compare) {
  int arr[] = {7, 3, 5, 1, 2, 4, 6};
  tiny_stl::pop_heap(arr, arr + 7, std::less<int>());
  EXPECT_EQ(7, arr[6]);
}

TEST(HeapAlgo, SortHeap) {
  int arr[] = {7, 3, 5, 1, 2, 4, 6};
  tiny_stl::sort_heap(arr, arr + 7);
  for (int i = 0; i < 7; ++i) {
    EXPECT_EQ(i + 1, arr[i]);
  }
}

TEST(HeapAlgo, SortHeap_Compare) {
  int arr[] = {7, 3, 5, 1, 2, 4, 6};
  tiny_stl::sort_heap(arr, arr + 7, std::less<int>());
  for (int i = 0; i < 7; ++i) {
    EXPECT_EQ(i + 1, arr[i]);
  }
}

TEST(HeapAlgo, MakeHeapAux) {
  int arr[] = {7, 3, 5, 1, 2, 4, 6};
  tiny_stl::make_heap_aux(arr, arr + 7, (ptrdiff_t *)(0));
  EXPECT_TRUE(std::is_heap(arr, arr + 7));
}

TEST(HeapAlgo, MakeHeap) {
  int arr[] = {7, 3, 5, 1, 2, 4, 6};
  tiny_stl::make_heap(arr, arr + 7);
  EXPECT_TRUE(std::is_heap(arr, arr + 7));
}

TEST(HeapAlgo, MakeHeapAux_Compare) {
  int arr[] = {7, 3, 5, 1, 2, 4, 6};
  tiny_stl::make_heap_aux(arr, arr + 7, (ptrdiff_t *)(0), std::less<int>());
  EXPECT_TRUE(std::is_heap(arr, arr + 7, std::less<int>()));
}

TEST(HeapAlgo, MakeHeap_Compare) {
  int arr[] = {7, 3, 5, 1, 2, 4, 6};
  tiny_stl::make_heap(arr, arr + 7, std::less<int>());
  EXPECT_TRUE(std::is_heap(arr, arr + 7, std::less<int>()));
}

#endif // ! TINY_STL__TEST__TEST_HEAP_ALGO_HPP