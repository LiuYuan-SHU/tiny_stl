#ifndef TINY_STL__TEST__ITERATOR__TEST_ITERATOR_HELPER_HPP
#define TINY_STL__TEST__ITERATOR__TEST_ITERATOR_HELPER_HPP

#include <gtest/gtest.h>

#include "iterator.hpp"

using tiny_stl::advance;
using tiny_stl::advance_dispatch;
using tiny_stl::distance;
using tiny_stl::distance_dispatch;
using tiny_stl::iterator;
using tiny_stl::iterator_traits;
using tiny_stl::reverse_iterator;

class TestIterator : public ::testing::Test {
public:
  struct node_test {
    int data;
    node_test *next;
  };
  struct iterator_test_node
      : public iterator<tiny_stl::input_iterator_tag, node_test> {
  private:
    node_test *ptr;

  public:
    iterator_test_node(node_test *ptr = nullptr) : ptr(ptr) {}

    bool operator==(const iterator_test_node &other) {
      return this->ptr == other.ptr;
    }
    bool operator!=(const iterator_test_node &other) {
      return !(this->operator==(other));
    }
    iterator_test_node &operator++() {
      this->ptr = this->ptr->next;
      return *this;
    }
  };

  struct iterator_test_arr
      : public iterator<tiny_stl::random_access_iterator_tag, int> {
  private:
    int *ptr;

  public:
    iterator_test_arr(int *ptr = nullptr) : ptr(ptr) {}
    iterator_test_arr &operator+=(ptrdiff_t n) {
      this->ptr += n;
      return *this;
    }
    bool operator==(const iterator_test_arr &other) {
      return this->ptr == other.ptr;
    }
    ptrdiff_t operator-(const iterator_test_arr &other) {
      return this->ptr - other.ptr;
    }
    int *&operator--() { return --this->ptr; }
  };

protected:
  void SetUp() override {
    node4 = node_test{4, nullptr};
    node3 = node_test{3, &node4};
    node2 = node_test{2, &node3};
    node1 = node_test{1, &node2};

    begin_node = iterator_test_node(&node1);
    end_node = iterator_test_node(&node4);

    for (int i = 0; i < 5; ++i) {
      arr[i] = i;
    }

    begin_arr = iterator_test_arr(arr);
    end_arr = iterator_test_arr(arr + 5);
    mid_arr = iterator_test_arr(arr + 2);
  }

public:
  node_test node1, node2, node3, node4;
  iterator_test_node begin_node, end_node;
  constexpr static int distance_node = 3;

  int arr[5];
  iterator_test_arr begin_arr, end_arr, mid_arr;
  constexpr static int distance_arr = 5;
  constexpr static int fdistance_mid_arr = -2;
  constexpr static int bdistance_mid_arr = 3;
};

class TestReverseIterator : public TestIterator {
private:
  void SetUp() {
    TestIterator::SetUp();

    rbegin_arr = reverse_iterator<iterator_test_arr>(end_arr);
    rend_arr = reverse_iterator<iterator_test_arr>(begin_arr);
    rmid_arr = reverse_iterator<iterator_test_arr>(mid_arr);
  }

public:
  reverse_iterator<iterator_test_arr> rbegin_arr, rend_arr, rmid_arr;
};

#endif // !TINY_STL__TEST__ITERATOR__TEST_ITERATOR_HELPER_HPP