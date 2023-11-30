#include <gtest/gtest.h>

#include "type_traits.hpp/test_type_traits.hpp"
#include "iterator.hpp/test_iterator.hpp"

int main(int arc, char *argv[]) {
  testing::InitGoogleTest(&arc, argv);

  return RUN_ALL_TESTS();
}