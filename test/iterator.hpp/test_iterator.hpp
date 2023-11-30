#ifndef TINY_STL__TEST__TEST_ITERATOR_HPP
#define TINY_STL__TEST__TEST_ITERATOR_HPP

#include <cstdlib>
#include <gtest/gtest.h>

#include "iterator.hpp"
#include "type_traits.hpp"

#include "test_iterator_helper.hpp"

TEST(Test_Iterator, Tag_Construct) {
  EXPECT_NO_FATAL_FAILURE((tiny_stl::input_iterator_tag()));
  EXPECT_NO_FATAL_FAILURE((tiny_stl::output_iterator_tag()));
  EXPECT_NO_FATAL_FAILURE((tiny_stl::forward_iterator_tag()));
  EXPECT_NO_FATAL_FAILURE((tiny_stl::bidirectional_iterator_tag()));
  EXPECT_NO_FATAL_FAILURE((tiny_stl::random_access_iterator_tag()));
}

TEST(Test_Iterator, Iterator_Construct) {
  using tiny_stl::bidirectional_iterator_tag;
  using tiny_stl::forward_iterator_tag;
  using tiny_stl::input_iterator_tag;
  using tiny_stl::iterator;
  using tiny_stl::output_iterator_tag;
  using tiny_stl::random_access_iterator_tag;

  EXPECT_NO_FATAL_FAILURE((iterator<input_iterator_tag, int>()));
  EXPECT_NO_FATAL_FAILURE((iterator<output_iterator_tag, int>()));
  EXPECT_NO_FATAL_FAILURE((iterator<forward_iterator_tag, int>()));
  EXPECT_NO_FATAL_FAILURE((iterator<bidirectional_iterator_tag, int>()));
  EXPECT_NO_FATAL_FAILURE((iterator<random_access_iterator_tag, int>()));
}

TEST(Test_Iterator, HasIteratorCat) {
  using tiny_stl::has_iterator_cat;

  EXPECT_FALSE((has_iterator_cat<int>::value));
  EXPECT_TRUE((has_iterator_cat<
               tiny_stl::iterator<tiny_stl::input_iterator_tag, int>>::value));
  EXPECT_TRUE((has_iterator_cat<
               tiny_stl::iterator<tiny_stl::output_iterator_tag, int>>::value));
  EXPECT_TRUE(
      (has_iterator_cat<
          tiny_stl::iterator<tiny_stl::forward_iterator_tag, int>>::value));
  EXPECT_TRUE(
      (has_iterator_cat<tiny_stl::iterator<tiny_stl::bidirectional_iterator_tag,
                                           int>>::value));
  EXPECT_TRUE(
      (has_iterator_cat<tiny_stl::iterator<tiny_stl::random_access_iterator_tag,
                                           int>>::value));
}

TEST(Test_Iterator, HasIteratorCatOf) {
  using tiny_stl::bidirectional_iterator_tag;
  using tiny_stl::forward_iterator_tag;
  using tiny_stl::has_iterator_cat_of;
  using tiny_stl::input_iterator_tag;
  using tiny_stl::iterator;
  using tiny_stl::iterator_traits;
  using tiny_stl::output_iterator_tag;
  using tiny_stl::random_access_iterator_tag;

  EXPECT_FALSE((has_iterator_cat_of<int, input_iterator_tag>::value));

  // tags inherited from input_iterator_tag to input_iterator_tag
  EXPECT_TRUE((has_iterator_cat_of<iterator<input_iterator_tag, int>,
                                   input_iterator_tag>::value));
  EXPECT_TRUE((has_iterator_cat_of<iterator<forward_iterator_tag, int>,
                                   input_iterator_tag>::value));
  EXPECT_TRUE((has_iterator_cat_of<iterator<bidirectional_iterator_tag, int>,
                                   input_iterator_tag>::value));
  EXPECT_TRUE((has_iterator_cat_of<iterator<random_access_iterator_tag, int>,
                                   input_iterator_tag>::value));

  // tags inherited from output_iterator_tag to output_iterator_tag
  EXPECT_FALSE((has_iterator_cat_of<iterator<input_iterator_tag, int>,
                                    output_iterator_tag>::value));
  EXPECT_FALSE((has_iterator_cat_of<iterator<forward_iterator_tag, int>,
                                    output_iterator_tag>::value));
  EXPECT_FALSE((has_iterator_cat_of<iterator<bidirectional_iterator_tag, int>,
                                    output_iterator_tag>::value));
  EXPECT_FALSE((has_iterator_cat_of<iterator<random_access_iterator_tag, int>,
                                    output_iterator_tag>::value));

  // input_iterator_tag to tags inherited from input_iterator_tag
  EXPECT_FALSE((has_iterator_cat_of<iterator<input_iterator_tag, int>,
                                    forward_iterator_tag>::value));
  EXPECT_FALSE((has_iterator_cat_of<iterator<input_iterator_tag, int>,
                                    bidirectional_iterator_tag>::value));
  EXPECT_FALSE((has_iterator_cat_of<iterator<input_iterator_tag, int>,
                                    random_access_iterator_tag>::value));

  // output_iterator_tag to tags inherited from input_iterator_tag
  EXPECT_FALSE((has_iterator_cat_of<iterator<output_iterator_tag, int>,
                                    input_iterator_tag>::value));
  EXPECT_FALSE((has_iterator_cat_of<iterator<output_iterator_tag, int>,
                                    forward_iterator_tag>::value));
  EXPECT_FALSE((has_iterator_cat_of<iterator<output_iterator_tag, int>,
                                    bidirectional_iterator_tag>::value));
  EXPECT_FALSE((has_iterator_cat_of<iterator<output_iterator_tag, int>,
                                    random_access_iterator_tag>::value));
}

TEST(Test_Iterator, IsInputIterator) {
  using tiny_stl::is_input_iterator;
  using tiny_stl::iterator;

  EXPECT_TRUE(
      (is_input_iterator<iterator<tiny_stl::input_iterator_tag, int>>::value));
  EXPECT_FALSE(
      (is_input_iterator<iterator<tiny_stl::output_iterator_tag, int>>::value));
  EXPECT_TRUE((
      is_input_iterator<iterator<tiny_stl::forward_iterator_tag, int>>::value));
  EXPECT_TRUE((is_input_iterator<
               iterator<tiny_stl::bidirectional_iterator_tag, int>>::value));
  EXPECT_TRUE((is_input_iterator<
               iterator<tiny_stl::random_access_iterator_tag, int>>::value));
}

TEST(Test_Iterator, IsOutputIterator) {
  using tiny_stl::is_output_iterator;
  using tiny_stl::iterator;

  EXPECT_FALSE(
      (is_output_iterator<iterator<tiny_stl::input_iterator_tag, int>>::value));
  EXPECT_TRUE((
      is_output_iterator<iterator<tiny_stl::output_iterator_tag, int>>::value));
  EXPECT_FALSE((is_output_iterator<
                iterator<tiny_stl::forward_iterator_tag, int>>::value));
  EXPECT_FALSE((is_output_iterator<
                iterator<tiny_stl::bidirectional_iterator_tag, int>>::value));
  EXPECT_FALSE((is_output_iterator<
                iterator<tiny_stl::random_access_iterator_tag, int>>::value));
}

TEST(Test_Iterator, IsForwardIterator) {
  using tiny_stl::is_forward_iterator;
  using tiny_stl::iterator;

  EXPECT_FALSE((
      is_forward_iterator<iterator<tiny_stl::input_iterator_tag, int>>::value));
  EXPECT_FALSE((is_forward_iterator<
                iterator<tiny_stl::output_iterator_tag, int>>::value));
  EXPECT_TRUE((is_forward_iterator<
               iterator<tiny_stl::forward_iterator_tag, int>>::value));
  EXPECT_TRUE((is_forward_iterator<
               iterator<tiny_stl::bidirectional_iterator_tag, int>>::value));
  EXPECT_TRUE((is_forward_iterator<
               iterator<tiny_stl::random_access_iterator_tag, int>>::value));
}

TEST(Test_Iterator, IsBidirectionalIterator) {
  using tiny_stl::is_bidirectional_iterator;
  using tiny_stl::iterator;

  EXPECT_FALSE((is_bidirectional_iterator<
                iterator<tiny_stl::input_iterator_tag, int>>::value));
  EXPECT_FALSE((is_bidirectional_iterator<
                iterator<tiny_stl::output_iterator_tag, int>>::value));
  EXPECT_FALSE((is_bidirectional_iterator<
                iterator<tiny_stl::forward_iterator_tag, int>>::value));
  EXPECT_TRUE((is_bidirectional_iterator<
               iterator<tiny_stl::bidirectional_iterator_tag, int>>::value));
  EXPECT_TRUE((is_bidirectional_iterator<
               iterator<tiny_stl::random_access_iterator_tag, int>>::value));
}

TEST(Test_Iterator, IsRandomAccessIterator) {
  using tiny_stl::is_random_iterator;
  using tiny_stl::iterator;

  EXPECT_FALSE(
      (is_random_iterator<iterator<tiny_stl::input_iterator_tag, int>>::value));
  EXPECT_FALSE((
      is_random_iterator<iterator<tiny_stl::output_iterator_tag, int>>::value));
  EXPECT_FALSE((is_random_iterator<
                iterator<tiny_stl::forward_iterator_tag, int>>::value));
  EXPECT_FALSE((is_random_iterator<
                iterator<tiny_stl::bidirectional_iterator_tag, int>>::value));
  EXPECT_TRUE((is_random_iterator<
               iterator<tiny_stl::random_access_iterator_tag, int>>::value));
}

TEST(Test_Iterator, IsIterator) {
  using tiny_stl::is_iterator;
  using tiny_stl::iterator;

  EXPECT_FALSE((is_iterator<int>::value));
  EXPECT_TRUE(
      (is_iterator<iterator<tiny_stl::input_iterator_tag, int>>::value));
  EXPECT_TRUE(
      (is_iterator<iterator<tiny_stl::output_iterator_tag, int>>::value));
  EXPECT_TRUE(
      (is_iterator<iterator<tiny_stl::forward_iterator_tag, int>>::value));
  EXPECT_TRUE((
      is_iterator<iterator<tiny_stl::bidirectional_iterator_tag, int>>::value));
  EXPECT_TRUE((
      is_iterator<iterator<tiny_stl::random_access_iterator_tag, int>>::value));
}

TEST(Test_Iterator, IteratorCategory) {
  using tiny_stl::iterator;
  using tiny_stl::iterator_category;

  iterator<tiny_stl::input_iterator_tag, int> input_iterator;
  iterator<tiny_stl::output_iterator_tag, int> output_iterator;
  iterator<tiny_stl::forward_iterator_tag, int> forward_iterator;
  iterator<tiny_stl::bidirectional_iterator_tag, int> bidirectional_iterator;
  iterator<tiny_stl::random_access_iterator_tag, int> random_access_iterator;

  EXPECT_TRUE((std::is_same_v<decltype(iterator_category(input_iterator)),
                              tiny_stl::input_iterator_tag>));
  EXPECT_TRUE((std::is_same_v<decltype(iterator_category(output_iterator)),
                              tiny_stl::output_iterator_tag>));
  EXPECT_TRUE((std::is_same_v<decltype(iterator_category(forward_iterator)),
                              tiny_stl::forward_iterator_tag>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(iterator_category(bidirectional_iterator)),
                      tiny_stl::bidirectional_iterator_tag>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(iterator_category(random_access_iterator)),
                      tiny_stl::random_access_iterator_tag>));
}

TEST(Test_Iterator, DistanceType) {
  using tiny_stl::distance_type;
  using tiny_stl::iterator;

  iterator<tiny_stl::input_iterator_tag, int> input_iterator;
  iterator<tiny_stl::output_iterator_tag, int> output_iterator;
  iterator<tiny_stl::forward_iterator_tag, int> forward_iterator;
  iterator<tiny_stl::bidirectional_iterator_tag, int> bidirectional_iterator;
  iterator<tiny_stl::random_access_iterator_tag, int> random_access_iterator;

  EXPECT_TRUE((std::is_same_v<decltype(distance_type(input_iterator)),
                              std::ptrdiff_t *>));
  EXPECT_TRUE((std::is_same_v<decltype(distance_type(output_iterator)),
                              std::ptrdiff_t *>));
  EXPECT_TRUE((std::is_same_v<decltype(distance_type(forward_iterator)),
                              std::ptrdiff_t *>));
  EXPECT_TRUE((std::is_same_v<decltype(distance_type(bidirectional_iterator)),
                              std::ptrdiff_t *>));
  EXPECT_TRUE((std::is_same_v<decltype(distance_type(random_access_iterator)),
                              std::ptrdiff_t *>));
}

TEST(Test_Iterator, ValueType) {
  using tiny_stl::iterator;
  using tiny_stl::value_type;

  iterator<tiny_stl::input_iterator_tag, int> input_iterator;
  iterator<tiny_stl::output_iterator_tag, int> output_iterator;
  iterator<tiny_stl::forward_iterator_tag, int> forward_iterator;
  iterator<tiny_stl::bidirectional_iterator_tag, int> bidirectional_iterator;
  iterator<tiny_stl::random_access_iterator_tag, int> random_access_iterator;

  EXPECT_TRUE((std::is_same_v<decltype(value_type(input_iterator)), int *>));
  EXPECT_TRUE((std::is_same_v<decltype(value_type(output_iterator)), int *>));
  EXPECT_TRUE((std::is_same_v<decltype(value_type(forward_iterator)), int *>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(value_type(bidirectional_iterator)), int *>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(value_type(random_access_iterator)), int *>));
}

TEST_F(TestIterator, DistanceDispatch_InputIterator) {
  EXPECT_EQ(distance_dispatch(begin_node, end_node,
                              tiny_stl::iterator_category(begin_node)),
            this->distance_node);
}

TEST_F(TestIterator, DistanceDispatch_RandomAccessIterator) {
  EXPECT_EQ(distance_dispatch(begin_arr, end_arr,
                              tiny_stl::iterator_category(begin_arr)),
            this->distance_arr);
}

TEST_F(TestIterator, Distance) {
  EXPECT_EQ(distance(begin_node, end_node), this->distance_node);
  EXPECT_EQ(distance(begin_arr, end_arr), this->distance_arr);
}

TEST_F(TestIterator, AdvanceDispatch_InputIterator) {
  EXPECT_TRUE((advance_dispatch(begin_node, this->distance_node,
                                tiny_stl::iterator_category(begin_node)),
               this->begin_node) == this->end_node);
}

TEST_F(TestIterator, AdvanceDispatch_BidirectionalIterator) {
  EXPECT_TRUE((advance_dispatch(mid_arr, this->fdistance_mid_arr,
                                tiny_stl::iterator_category(mid_arr)),
               mid_arr) == begin_arr);

  EXPECT_TRUE((advance_dispatch(mid_arr, this->distance_arr,
                                tiny_stl::iterator_category(mid_arr)),
               mid_arr) == end_arr);
}

TEST_F(TestIterator, AdvanceDispatch_RandomAccessIterator) {
  EXPECT_TRUE((advance_dispatch(begin_arr, this->distance_arr,
                                tiny_stl::iterator_category(begin_arr)),
               begin_arr) == end_arr);
}

TEST_F(TestIterator, Advance) {
  EXPECT_TRUE((advance(begin_node, this->distance_node), begin_node) ==
              this->end_node);
  EXPECT_TRUE((advance(mid_arr, this->fdistance_mid_arr), mid_arr) ==
              this->begin_arr);
  EXPECT_TRUE((advance(mid_arr, this->distance_arr), mid_arr) == this->end_arr);
}

TEST(Test_ReverseIterator, Constructor_Empty) {
  EXPECT_NO_FATAL_FAILURE(
      (tiny_stl::reverse_iterator<decltype(TestIterator::begin_arr)>()));
}

TEST(Test_ReverseIterator, Constructor_Iterator) {
  EXPECT_NO_FATAL_FAILURE(
      (tiny_stl::reverse_iterator<TestIterator::iterator_test_arr>(
          TestIterator::iterator_test_arr())));
}

TEST(Test_ReverseIterator, CopyConstructor) {
  tiny_stl::reverse_iterator<TestIterator::iterator_test_arr> r1;
  tiny_stl::reverse_iterator<TestIterator::iterator_test_arr> r2(r1);
}

TEST_F(TestReverseIterator, Base) {
  EXPECT_TRUE(rbegin_arr.base() == end_arr);
  EXPECT_TRUE(rend_arr.base() == begin_arr);
  EXPECT_TRUE(rmid_arr.base() == mid_arr);
}

TEST_F(TestReverseIterator, OperatorStar) {
  EXPECT_EQ(*rbegin_arr, arr[sizeof(arr) / sizeof(arr[0]) - 1]);
  EXPECT_EQ(*rmid_arr, arr[abs(fdistance_mid_arr) - 1]);
}

TEST_F(TestReverseIterator, OperatorArrow) {
  
}

#endif // !TINY_STL__TEST__TEST_ITERATOR_HPP