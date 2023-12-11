#ifndef TINY_STL__TEST__TEST_FUNCTIONAL_HPP
#define TINY_STL__TEST__TEST_FUNCTIONAL_HPP

#include "functional.hpp"

#include <gtest/gtest.h>

TEST(Functional, Plus) {
  tiny_stl::plus<int> plus;
  EXPECT_EQ(plus(1, 2), 3);
}

TEST(Functional, Minus) {
  tiny_stl::minus<int> minus;
  EXPECT_EQ(minus(1, 2), -1);
}

TEST(Functional, Multiplies) {
  tiny_stl::multiplies<int> multiplies;
  EXPECT_EQ(multiplies(1, 2), 2);
}

TEST(Functional, Divides) {
  tiny_stl::divides<int> divides;
  EXPECT_EQ(divides(1, 2), 0);
}

TEST(Functional, Modulus) {
  tiny_stl::modulus<int> modulus;
  EXPECT_EQ(modulus(1, 2), 1);
}

TEST(Functional, Negate) {
  tiny_stl::negate<int> negate;
  EXPECT_EQ(negate(1), -1);
}

TEST(Functional, Identity_element) {
  tiny_stl::plus<int> plus;
  EXPECT_EQ(tiny_stl::identity_element(plus), 0);
  tiny_stl::multiplies<int> multiplies;
  EXPECT_EQ(tiny_stl::identity_element(multiplies), 1);
}

TEST(Functional, Equal_to) {
  tiny_stl::equal_to<int> equal_to;
  EXPECT_EQ(equal_to(1, 2), false);
  EXPECT_EQ(equal_to(1, 1), true);
}

TEST(Functional, Not_equal_to) {
  tiny_stl::not_equal_to<int> not_equal_to;
  EXPECT_EQ(not_equal_to(1, 2), true);
  EXPECT_EQ(not_equal_to(1, 1), false);
}

TEST(Functional, Greater) {
  tiny_stl::greater<int> greater;
  EXPECT_EQ(greater(1, 2), false);
  EXPECT_EQ(greater(2, 1), true);
}

TEST(Functional, Less) {
  tiny_stl::less<int> less;
  EXPECT_EQ(less(1, 2), true);
  EXPECT_EQ(less(2, 1), false);
}

TEST(Functional, Greater_equal) {
  tiny_stl::greater_equal<int> greater_equal;
  EXPECT_EQ(greater_equal(1, 2), false);
  EXPECT_EQ(greater_equal(2, 1), true);
  EXPECT_EQ(greater_equal(1, 1), true);
}

TEST(Functional, Less_equal) {
  tiny_stl::less_equal<int> less_equal;
  EXPECT_EQ(less_equal(1, 2), true);
  EXPECT_EQ(less_equal(2, 1), false);
  EXPECT_EQ(less_equal(1, 1), true);
}

TEST(Functional, Logical_and) {
  tiny_stl::logical_and<int> logical_and;
  EXPECT_EQ(logical_and(1, 2), true);
  EXPECT_EQ(logical_and(0, 1), false);
}

TEST(Functional, Logical_or) {
  tiny_stl::logical_or<int> logical_or;
  EXPECT_EQ(logical_or(1, 2), true);
  EXPECT_EQ(logical_or(0, 1), true);
  EXPECT_EQ(logical_or(0, 0), false);
}

TEST(Functional, Logical_not) {
  tiny_stl::logical_not<int> logical_not;
  EXPECT_EQ(logical_not(1), false);
  EXPECT_EQ(logical_not(0), true);
}

TEST(Functional, Identity) {
  tiny_stl::identity<int> identity;
  EXPECT_EQ(identity(1), 1);
}

TEST(Functional, Select1st) {
  tiny_stl::select1st<std::pair<int, int>> select1st;
  EXPECT_EQ(select1st(tiny_stl::pair<int, int>(1, 2)), 1);
}

TEST(Functional, Select2nd) {
  tiny_stl::select2nd<std::pair<int, int>> select2nd;
  EXPECT_EQ(select2nd(tiny_stl::pair<int, int>(1, 2)), 2);
}

TEST(Functional, Project1st) {
  tiny_stl::project1st<int, int> project1st;
  EXPECT_EQ(project1st(1, 2), 1);
}

TEST(Functional, Project2nd) {
  tiny_stl::project2nd<int, int> project2nd;
  EXPECT_EQ(project2nd(1, 2), 2);
}

TEST(Functional, Hash_Ptr) {
  tiny_stl::hash<int *> hash;
  int* a = (int*)1;
  EXPECT_EQ(hash(a), 1);
}

TEST(Functional, Hash_Integral) {
  tiny_stl::hash<bool> hash_bool;
  tiny_stl::hash<char> hash_char;
  tiny_stl::hash<signed char> hash_signed_char;
  tiny_stl::hash<unsigned char> hash_unsigned_char;
  tiny_stl::hash<short> hash_short;
  tiny_stl::hash<unsigned short> hash_unsigned_short;
  tiny_stl::hash<int> hash_int;
  tiny_stl::hash<unsigned int> hash_unsigned_int;
  tiny_stl::hash<long> hash_long;
  tiny_stl::hash<unsigned long> hash_unsigned_long;
  tiny_stl::hash<long long> hash_long_long;
  tiny_stl::hash<unsigned long long> hash_unsigned_long_long;
  EXPECT_EQ(hash_bool(true), 1);
  EXPECT_EQ(hash_char('a'), 97);
  EXPECT_EQ(hash_signed_char('a'), 97);
  EXPECT_EQ(hash_unsigned_char('a'), 97);
  EXPECT_EQ(hash_short(1), 1);
  EXPECT_EQ(hash_unsigned_short(1), 1);
  EXPECT_EQ(hash_int(1), 1);
  EXPECT_EQ(hash_unsigned_int(1), 1);
  EXPECT_EQ(hash_long(1), 1);
  EXPECT_EQ(hash_unsigned_long(1), 1);
  EXPECT_EQ(hash_long_long(1), 1);
  EXPECT_EQ(hash_unsigned_long_long(1), 1);
}

TEST(Functional, Hash_Float) {
  tiny_stl::hash<float> hash_float;
  tiny_stl::hash<double> hash_double;
  tiny_stl::hash<long double> hash_long_double;
  EXPECT_EQ(hash_float(1.0f), 1065353216);
  EXPECT_EQ(hash_double(1.0), 4607182418800017408);
  EXPECT_EQ(hash_long_double(1.0l), 4607182418800017408);

}

#endif // ! TINY_STL__TEST__TEST_FUNCTIONAL_HPP