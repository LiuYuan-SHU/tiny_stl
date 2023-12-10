#ifndef TINY_STL__TEST__TEST_MEMORY_HPP
#define TINY_STL__TEST__TEST_MEMORY_HPP

#include "memory.hpp"

#include <gtest/gtest.h>

TEST(Memory, AddressOf) {
  int val;
  EXPECT_EQ(&val, tiny_stl::address_of(val));
}

TEST(Memory, GetRelease_TemporaryBuffer) {
  auto buffer = tiny_stl::get_temporary_buffer<int>(10);
  EXPECT_NEAR(10, buffer.second, 10);
  tiny_stl::release_temporary_buffer(buffer.first);
}

TEST(Memory, TemporaryBuffer) {
  int arr[10];
  tiny_stl::temporary_buffer<int*, int> buffer(arr, arr + 10);
  EXPECT_NEAR(10, buffer.size(), 10);
  EXPECT_EQ(10, buffer.requested_size());
}

TEST(Memory, AutoPtr) {
  int* raw_ptr = new int(10);
  tiny_stl::auto_ptr<int> ptr(raw_ptr);
  EXPECT_EQ(raw_ptr, ptr.get());
  EXPECT_EQ(10, *ptr);
  EXPECT_EQ(raw_ptr, ptr.release());
  EXPECT_EQ(nullptr, ptr.get());
  ptr.reset(raw_ptr);
  EXPECT_EQ(raw_ptr, ptr.get());
  tiny_stl::auto_ptr<int> ptr_2(ptr);
  EXPECT_EQ(nullptr, ptr.get());
  EXPECT_EQ(raw_ptr, ptr_2.get());
  ptr = ptr_2;
  EXPECT_EQ(nullptr, ptr_2.get());
  EXPECT_EQ(raw_ptr, ptr.get());
  ptr.release();
  ptr_2.reset();
  delete raw_ptr;
}

#endif // ! TINY_STL__TEST__TEST_MEMORY_HPP