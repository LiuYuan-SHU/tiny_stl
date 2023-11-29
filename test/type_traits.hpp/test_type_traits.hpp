#ifndef TINY_STL__TEST__TEST_TYPE_TRAITS_HPP
#define TINY_STL__TEST__TEST_TYPE_TRAITS_HPP

#include <gtest/gtest.h>

#include "type_traits.hpp"

TEST(Test_TypeTraits, IntegralConstant_Constructor) {
  using tiny_stl::integral_constant;

  EXPECT_NO_FATAL_FAILURE((integral_constant<int, 1>()));
  EXPECT_NO_FATAL_FAILURE((integral_constant<bool, true>{}));
  EXPECT_NO_FATAL_FAILURE((integral_constant<bool, false>{}));
}

TEST(Test_TypeTraits, IntegralConstant_Value) {
  using tiny_stl::integral_constant;

  EXPECT_EQ((integral_constant<int, 1>::value), 1);
  EXPECT_EQ((integral_constant<bool, true>::value), true);
  EXPECT_EQ((integral_constant<bool, false>::value), false);
}

TEST(Test_CompileTimeConstantBool, Constructor) {
  using tiny_stl::compile_time_constant_bool;

  EXPECT_NO_FATAL_FAILURE((compile_time_constant_bool<true>()));
  EXPECT_NO_FATAL_FAILURE((compile_time_constant_bool<false>()));
}

TEST(Test_CompileTimeConstantBool, Value) {
  using tiny_stl::compile_time_constant_bool;

  EXPECT_EQ((compile_time_constant_bool<true>::value), true);
  EXPECT_EQ((compile_time_constant_bool<false>::value), false);
}

TEST(Test_IsPair, IsPair) {
  using tiny_stl::is_pair;
  using tiny_stl::pair;

  EXPECT_FALSE((is_pair<int>::value));
  EXPECT_TRUE((is_pair<pair<int, int>>::value));
}

#endif // !TINY_STL__TEST__TEST_TYPE_TRAITS_HPP