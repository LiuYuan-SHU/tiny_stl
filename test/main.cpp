#include <gtest/gtest.h>

#include "algobase.hpp/test_algobase.hpp"
#include "construct.hpp/test_construct.hpp"
#include "iterator.hpp/test_iterator.hpp"
#include "type_traits.hpp/test_type_traits.hpp"
#include "utility.hpp/test_utility.hpp"

int main(int arc, char *argv[]) {
  testing::InitGoogleTest(&arc, argv);

  return RUN_ALL_TESTS();
}