#include <gtest/gtest.h>

#include "algobase.hpp/test_algobase.hpp"
#include "allocator.hpp"
#include "construct.hpp/test_construct.hpp"
#include "iterator.hpp/test_iterator.hpp"
#include "memory.hpp/test_memory.hpp"
#include "type_traits.hpp/test_type_traits.hpp"
#include "uninitialized.hpp/test_uninitialized.hpp"
#include "utility.hpp/test_utility.hpp"
#include "heap_algo.hpp/test_heap_algo.hpp"
#include "functional.hpp/test_functional.hpp"
#include "algo.hpp/test_algo.hpp"

int main(int arc, char *argv[]) {
  testing::InitGoogleTest(&arc, argv);

  return RUN_ALL_TESTS();
}