/**
 * @file algobase.hpp
 * @author Liu Yuan (2787141886@qq.com)
 * @brief This file is the header of `algobase.cpp`, which contains some
 * helper functions for algorithms.
 *
 * @details This file contains the following functions:
 * - `max`: return the larger one of the two given values.
 * - 'min': return the smaller one of the two given values.
 * - `iter_swap`: swap the values of the two given iterators.
 * - `unchecked_copy_cat`: copy a range of elements from the given range to the
 * given destination.
 * - `unchecked_copy`: copy a range of elements from the given range to the
 * given destination.
 * - `copy`: copy a range of elements from the given range to the given
 * destination.
 * - `unchecked_copy_backward_cat`: copy a range of elements from the given
 * range to the given destination in reverse order.
 * - `unchecked_copy_backward`: copy a range of elements from the given range to
 * the given destination in reverse order.
 * - `copy_backward`: copy a range of elements from the given range to the given
 * destination in reverse order.
 * - `copy_if`: copy a range of elements from the given range to the given
 * destination if the given predicate is true.
 * - `unchecked_copy_n`: copy a range of elements from the given range to the
 * given destination.
 * - `copy_n`: copy a range of elements from the given range to the given
 * destination.
 * - `unchecked_move_cat`: move a range of elements from the given range to the
 * given destination.
 * - `unchecked_move`: move a range of elements from the given range to the
 * given destination.
 * - `move`: move a range of elements from the given range to the given
 * destination.
 * - `unchecked_move_backward_cat`: move a range of elements from the given
 * range to the given destination in reverse order.
 * - `unchecked_move_backward`: move a range of elements from the given range to
 * the given destination in reverse order.
 * - `move_backward`: move a range of elements from the given range to the given
 * destination in reverse order.
 * - `equal`: check if two ranges are equal.
 * - 'fill_cat': fill a range with the given value.
 * - `fill`: fill a range with the given value.
 * - `lexicographical_compare`: check if the first range is lexicographically
 * less than the second range.
 * - `mismatch`: find the first mismatching pair of elements from two ranges.
 */
#ifndef TINY_STL__INCLUDE__ALGOBASE_HPP
#define TINY_STL__INCLUDE__ALGOBASE_HPP

#include <cstring>

#include "iterator.hpp"
#include "utility.hpp"

namespace tiny_stl {

#ifdef max
#pragma message("#undefining macro max")
#undef max
#endif

#ifdef min
#pragma message("#undefining macro min")
#undef min
#endif

/**
 * @brief Return the larger one of the two given values.
 *
 * @tparam T The type of the two given values.
 * @param left The first value.
 * @param right The second value.
 * @return const T& The larger one of the two given values.
 */
template <class T> const T &max(const T &left, const T &right) {
  return left > right ? left : right;
}

/**
 * @brief Return the larger one of the two given values, the larger
 * one is determined by the given compare function.
 *
 * @tparam T The type of the two given values.
 * @tparam Compare The type of the compare function.
 * @param left The first value.
 * @param right The second value.
 * @param compare The compare function.
 * @return const T& The larger one of the two given values.
 */
template <class T, class Compare>
const T &max(const T &left, const T &right, Compare compare) {
  return compare(left, right) ? right : left;
}

/**
 * @brief Return the smaller one of the two given values.
 *
 * @tparam T The type of the two given values.
 * @param left The first value.
 * @param right The second value.
 * @return const T& The smaller one of the two given values.
 */
template <class T> const T &min(const T &left, const T &right) {
  return left < right ? left : right;
}

/**
 * @brief Return the smaller one of the two given values, the smaller
 * one is determined by the given compare function.
 *
 * @tparam T The type of the two given values.
 * @tparam Compare The type of the compare function.
 * @param left The first value.
 * @param right The second value.
 * @param compare The compare function.
 * @return const T& The smaller one of the two given values.
 */
template <class T, class Compare>
const T &min(const T &left, const T &right, Compare compare) {
  return compare(right, left) ? right : left;
}

/**
 * @brief Swap the values of the two given iterators.
 *
 * @tparam ForwardIter1 The type of the first iterator.
 * @tparam ForwardIter2 The type of the second iterator.
 * @param left The first iterator.
 * @param right The second iterator.
 */
template <class ForwardIter1, class ForwardIter2>
void iter_swap(ForwardIter1 left, ForwardIter2 right) {
  tiny_stl::swap(*left, *right);
}

/**
 * @brief Copy a range of elements from the given range to the given
 * destination, the range is specified by the iterators of tag
 * `tiny_stl::input_iterator_tag`.
 *
 * @tparam InputIter The type of the given range.
 * @tparam OutputIter The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The begin iterator of the given destination.
 * @return OutputIter The end iterator of the given destination.
 */
template <class InputIter, class OutputIter>
OutputIter unchecked_copy_cat(InputIter first, InputIter last, OutputIter dest,
                              tiny_stl::input_iterator_tag) {
  for (; first != last; ++first, ++dest) {
    *dest = *first;
  }

  return dest;
}

/**
 * @brief Copy a range of elements from the given range to the given
 * destination, the range is specified by the iterators of tag
 * `tiny_stl::random_access_iterator_tag`.
 *
 * @tparam RandomAccessIter The type of the given range.
 * @tparam OutputIter The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The begin iterator of the given destination.
 * @return OutputIter The end iterator of the given destination.
 */
template <class RandomAccessIter, class OutputIter>
OutputIter unchecked_copy_cat(RandomAccessIter first, RandomAccessIter last,
                              OutputIter dest,
                              tiny_stl::random_access_iterator_tag) {
  for (auto n = last - first; n > 0; --n, ++first, ++dest) {
    *dest = *first;
  }
  return dest;
}

/**
 * @brief Copy a range of elements from the given range to the given
 * destination, the range is specified by the iterators whose tag will
 * be deduced by `tiny_stl::iterator_category`.
 *
 * @tparam InputIter The type of the given range.
 * @tparam OutputIter The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The begin iterator of the given destination.
 * @return OutputIter The end iterator of the given destination.
 */
template <class InputIter, class OutputIter>
OutputIter unchecked_copy(InputIter first, InputIter last, OutputIter dest) {
  unchecked_copy_cat(first, last, dest, tiny_stl::iterator_category(first));
}

/**
 * @brief Copy a range of elements from the given range to the given
 * destination, the value is trivially copyable.
 * @note The type of two given ranges must be the same.
 * @warning Though the function is called as `memmove`, it is not
 * "moving" the data, it is actually copying the data.
 *
 * @tparam T The type of the given range.
 * @tparam U The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The begin iterator of the given destination.
 * @return U* The end iterator of the given destination.
 */
template <class T, class U>
typename std::enable_if_t<std::is_same_v<typename std::remove_const_t<T>, U> &&
                              std::is_trivially_copy_constructible_v<U>,
                          U *>
unchecked_copy(T *first, T *last, U *dest) {
  const auto n = static_cast<size_t>(last - first);
  if (n != 0) {
    std::memmove(dest, first, n * sizeof(U));
  }

  return dest + n;
}

/**
 * @brief Copy a range of elements from the given range to the given
 * destination.
 *
 * @tparam InputIter The type of the given range.
 * @tparam OutputIter The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The begin iterator of the given destination.
 * @return OutputIter The end iterator of the given destination.
 */
template <class InputIter, class OutputIter>
OutputIter copy(InputIter first, InputIter last, OutputIter dest) {
  return unchecked_copy(first, last, dest);
}

/**
 * @brief Copy a range of elements from the given range to the given
 * destination in reverse order *backward*, the range is specified by the
 * iterators of tag `tiny_stl::bidirectional_iterator_tag`.
 *
 * @tparam BidirectionalIter1 The type of the given range.
 * @tparam BidirectionalIter2 The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The end iterator of the given destination.
 * @return BidirectionalIter2 The begin iterator of the given destination.
 */
template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2
unchecked_copy_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last,
                            BidirectionalIter2 dest,
                            tiny_stl::bidirectional_iterator_tag) {
  while (last != first) {
    *(--dest) = *(--last);
  }
  return dest;
}

/**
 * @brief Copy a range of elements from the given range to the given
 * destination in reverse order *backward*, the range is specified by the
 * iterators of tag `tiny_stl::random_access_iterator_tag`.
 *
 * @tparam RandomAccessIter The type of the given range.
 * @tparam BidirectionalIter The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The end iterator of the given destination.
 * @return BidirectionalIter The begin iterator of the given destination.
 */
template <class RandomAccessIter, class BidirectionalIter>
BidirectionalIter
unchecked_copy_backward_cat(RandomAccessIter first, RandomAccessIter last,
                            BidirectionalIter dest,
                            tiny_stl::random_access_iterator_tag) {
  for (auto n = last - first; n > 0; --n) {
    *(--dest) = *(--last);
  }
  return dest;
}

/**
 * @brief Copy a range of elements from the given range to the given
 * destination in reverse order *backward*, the range is specified by the
 * iterators whose tag will be deduced by `tiny_stl::iterator_category`.
 *
 * @tparam BidirectionalIter1 The type of the given range.
 * @tparam BidirectionalIter2 The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The end iterator of the given destination.
 * @return BidirectionalIter2 The begin iterator of the given destination.
 */
template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2 unchecked_copy_backward(BidirectionalIter1 first,
                                           BidirectionalIter1 last,
                                           BidirectionalIter2 dest) {
  unchecked_copy_backward_cat(first, last, dest,
                              tiny_stl::iterator_category(first));
}

/**
 * @brief Copy a range of elements from the given range to the given
 * destination in reverse order *backward*, the value is trivially copyable.
 * @note The type of two given ranges must be the same.
 * @note Though the function is called as `memmove`, it is not
 * "moving" the data, it is actually copying the data.
 *
 * @tparam T The type of the given range.
 * @tparam U The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The end iterator of the given destination.
 * @return U* The begin iterator of the given destination.
 */
template <class T, class U>
typename std::enable_if_t<std::is_same_v<typename std::remove_const_t<T>, U> &&
                              std::is_trivially_copyable_v<U>,
                          U *>
unchecked_copy_backward(T *first, T *last, U *dest) {
  auto n = static_cast<size_t>(last - first);
  if (n != 0) {
    dest -= n;
    std::memmove(dest, first, n * sizeof(U));
  }
  return dest;
}

/**
 * @brief Copy a range of elements from the given range to the given
 * destination in reverse order *backward*.
 *
 * @tparam BidirectionalIter1 The type of the given range.
 * @tparam BidirectionalIter2 The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The end iterator of the given destination.
 * @return BidirectionalIter2 The begin iterator of the given destination.
 */
template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2 copy_backward(BidirectionalIter1 first,
                                 BidirectionalIter1 last,
                                 BidirectionalIter2 dest) {
  return unchecked_copy_backward(first, last, dest);
}

/**
 * @brief Copy a range of elements from the given range to the given
 * destination if the given predicate is true.
 *
 * @tparam InputIter The type of the given range.
 * @tparam OutputIter The type of the given destination.
 * @tparam UnaryPredict The type of the given predicate.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The begin iterator of the given destination.
 * @param predict The given predicate.
 * @return OutputIter The end iterator of the given destination.
 */
template <class InputIter, class OutputIter, class UnaryPredict>
OutputIter copy_if(InputIter first, InputIter last, OutputIter dest,
                   UnaryPredict predict) {
  for (; first != last; ++first) {
    if (predict(*first)) {
      *(dest++) = *first;
    }
  }

  return dest;
}

/**
 * @brief Copy a range of elements from the given range to the given
 * destination, the range is specified by the iterators of tag
 * `tiny_stl::input_iterator_tag`.
 *
 * @tparam InputIter The type of the given range.
 * @tparam Size The type of the given size.
 * @tparam OutputIter The type of the given destination.
 * @param from The begin iterator of the given range.
 * @param n The size of the given range.
 * @param to The begin iterator of the given destination.
 * @return tiny_stl::pair<InputIter, OutputIter> The end iterator of the given
 * range and the end iterator of the given destination.
 */
template <class InputIter, class Size, class OutputIter>
tiny_stl::pair<InputIter, OutputIter>
unchecked_copy_n(InputIter from, Size n, OutputIter to,
                 tiny_stl::input_iterator_tag) {
  for (; n > 0; --n) {
    *(to++) = *(from++);
  }
  return tiny_stl::pair<InputIter, OutputIter>(from, to);
}

/**
 * @brief Copy a range of elements from the given range to the given
 * destination, the range is specified by the iterators of tag
 * `tiny_stl::random_access_iterator_tag`.
 *
 * @tparam RandomAccessIter The type of the given range.
 * @tparam Size The type of the given size.
 * @tparam OutputIter The type of the given destination.
 * @param from The begin iterator of the given range.
 * @param n The size of the given range.
 * @param to The begin iterator of the given destination.
 * @return tiny_stl::pair<RandomAccessIter, OutputIter> The end iterator of the
 * given range and the end iterator of the given destination.
 */
template <class RandomAccessIter, class Size, class OutputIter>
tiny_stl::pair<RandomAccessIter, OutputIter>
unchecked_copy_n(RandomAccessIter from, Size n, OutputIter to,
                 tiny_stl::random_access_iterator_tag) {
  auto last = from + n;
  return tiny_stl::pair<RandomAccessIter, OutputIter>(
      last, tiny_stl::copy(from, last, to));
}

/**
 * @brief Copy a range of elements from the given range to the given
 * destination, the range is specified by the iterators whose tag will
 * be deduced by `tiny_stl::iterator_category`.
 *
 * @tparam InputIter The type of the given range.
 * @tparam Size The type of the given size.
 * @tparam OutputIter The type of the given destination.
 * @param from The begin iterator of the given range.
 * @param n The size of the given range.
 * @param to The begin iterator of the given destination.
 * @return tiny_stl::pair<InputIter, OutputIter> The end iterator of the given
 * range and the end iterator of the given destination.
 */
template <class InputIter, class Size, class OutputIter>
tiny_stl::pair<InputIter, OutputIter> copy_n(InputIter from, Size n,
                                             OutputIter to) {
  unchecked_copy_n(from, n, to, tiny_stl::iterator_category(from));
}

/**
 * @brief Move a range of elements from the given range to the given
 * destination, the range is specified by the iterators of tag
 * `tiny_stl::input_iterator_tag`.
 *
 * @tparam InputIter The type of the given range.
 * @tparam OutputIter The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The begin iterator of the given destination.
 * @return OutputIter The end iterator of the given destination.
 */
template <class InputIter, class OutputIter>
OutputIter unchecked_move_cat(InputIter first, InputIter last, OutputIter dest,
                              tiny_stl::input_iterator_tag) {
  for (; first != last; ++first, ++dest) {
    *dest = tiny_stl::move(*first);
  }
  return dest;
}

/**
 * @brief Move a range of elements from the given range to the given
 * destination, the range is specified by the iterators of tag
 * `tiny_stl::random_access_iterator_tag`.
 *
 * @tparam RandomAccessIter The type of the given range.
 * @tparam OutputIter The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The begin iterator of the given destination.
 * @return OutputIter The end iterator of the given destination.
 */
template <class RandomAccessIter, class OutputIter>
OutputIter unchecked_move_cat(RandomAccessIter first, RandomAccessIter last,
                              OutputIter dest,
                              tiny_stl::random_access_iterator_tag) {
  for (auto n = last - first; n > 0; --n) {
    *(dest++) = tiny_stl::move(*(first++));
  }
  return dest;
}

/**
 * @brief Move a range of elements from the given range to the given
 * destination, the range is specified by the iterators whose tag will
 * be deduced by `tiny_stl::iterator_category`.
 *
 * @tparam InputIter The type of the given range.
 * @tparam OutputIter The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The begin iterator of the given destination.
 * @return OutputIter The end iterator of the given destination.
 */
template <class InputIter, class OutputIer>
OutputIer unchecked_move(InputIter first, InputIter last, OutputIer dest) {
  return unchecked_move_cat(first, last, dest,
                            tiny_stl::iterator_category(first));
}

/**
 * @brief Move a range of elements from the given range to the given
 * destination, the value is trivially move assignable.
 * @note The type of two given ranges must be the same.
 *
 * @tparam T The type of the given range.
 * @tparam U The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The begin iterator of the given destination.
 * @return U* The end iterator of the given destination.
 */
template <class T, class U>
typename std::enable_if_t<std::is_same_v<typename std::remove_const_t<T>, U> &&
                              std::is_trivially_move_assignable_v<T>,
                          U *>
unchecked_move(T *first, T *last, U *dest) {
  const size_t n = static_cast<size_t>(last - first);
  if (n != 0) {
    std::memmove(dest, first, n * sizeof(U));
  }
  return dest + n;
}

/**
 * @brief Move a range of elements from the given range to the given
 * destination.
 *
 * @tparam InputIter The type of the given range.
 * @tparam OutputIer The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The begin iterator of the given destination.
 * @return OutputIer The end iterator of the given destination.
 */
template <class InputIer, class OutputIer>
OutputIer move(InputIer first, InputIer last, OutputIer dest) {
  return unchecked_move(first, last, dest);
}

/**
 * @brief Move a range of elements from the given range to the given
 * destination in reverse order *backward*, the range is specified by the
 * iterators of tag `tiny_stl::bidirectional_iterator_tag`.
 *
 * @tparam BidirectionalIter1 The type of the given range.
 * @tparam BidirectionalIter2 The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The end iterator of the given destination.
 * @return BidirectionalIter2 The begin iterator of the given destination.
 */
template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2
unchecked_move_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last,
                            BidirectionalIter2 dest,
                            tiny_stl::bidirectional_iterator_tag) {
  while (first != last) {
    *(--dest) = tiny_stl::move(*(--last));
  }
  return dest;
}

/**
 * @brief Move a range of elements from the given range to the given
 * destination in reverse order *backward*, the range is specified by the
 * iterators of tag `tiny_stl::random_access_iterator_tag`.
 *
 * @tparam RandomAccessIter The type of the given range.
 * @tparam BidirectionalIter The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The end iterator of the given destination.
 * @return BidirectionalIter The begin iterator of the given destination.
 */
template <class RandomAccessIter, class BidirectionalIter>
BidirectionalIter
unchecked_move_backward_cat(RandomAccessIter first, RandomAccessIter last,
                            BidirectionalIter dest,
                            tiny_stl::random_access_iterator_tag) {
  for (auto n = last - first; n > 0; --n) {
    *(--dest) = tiny_stl::move(*(--last));
  }
  return dest;
}

/**
 * @brief Move a range of elements from the given range to the given
 * destination in reverse order *backward*, the range is specified by the
 * iterators whose tag will be deduced by `tiny_stl::iterator_category`.
 *
 * @tparam BidirectionalIter1 The type of the given range.
 * @tparam BidirectionalIter2 The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The end iterator of the given destination.
 * @return BidirectionalIter2 The begin iterator of the given destination.
 */
template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2 unchecked_move_backward(BidirectionalIter1 first,
                                           BidirectionalIter1 last,
                                           BidirectionalIter2 dest) {
  return unchecked_move_backward_cat(first, last, dest,
                                     tiny_stl::iterator_category(first));
}

/**
 * @brief Move a range of elements from the given range to the given
 * destination in reverse order *backward*, the value is trivially move
 * assignable.
 * @note The type of two given ranges must be the same.
 *
 * @tparam T The type of the given range.
 * @tparam U The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The end iterator of the given destination.
 * @return U* The begin iterator of the given destination.
 */
template <class T, class U>
typename std::enable_if_t<std::is_same_v<typename std::remove_const_t<T>, U> &&
                              std::is_trivially_move_assignable_v<T>,
                          U *>
unchecked_move_backward(T *first, T *last, U *dest) {
  const size_t n = static_cast<size_t>(last - first);
  if (n != 0) {
    dest -= n;
    std::memmove(dest, first, n * sizeof(U));
  }
  return dest;
}

/**
 * @brief Move a range of elements from the given range to the given
 * destination in reverse order *backward*.
 *
 * @tparam BidirectionalIter1 The type of the given range.
 * @tparam BidirectionalIter2 The type of the given destination.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param dest The end iterator of the given destination.
 * @return BidirectionalIter2 The begin iterator of the given destination.
 */
template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2 move_backward(BidirectionalIter1 first,
                                 BidirectionalIter1 last,
                                 BidirectionalIter2 dest) {
  return unchecked_move_backward(first, last, dest);
}

/**
 * @brief Check if two ranges are equal.
 *
 * @tparam InputIter1 The type of the first range.
 * @tparam InputIter2 The type of the second range.
 * @param first1 The begin iterator of the first range.
 * @param last1 The end iterator of the first range.
 * @param first2 The begin iterator of the second range.
 * @return true If two ranges are equal.
 * @return false If two ranges are not equal.
 */
template <class InputIter1, class InputIter2>
bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2) {
  for (; first1 != last1; ++first1, ++first2) {
    if (*first1 != *first2) {
      return false;
    }
  }

  return true;
}

/**
 * @brief Check if two ranges are equal, the value is trivially
 * comparable.
 * @note The type of two given ranges must be the same.
 *
 * @tparam T The type of the first range.
 * @tparam U The type of the second range.
 * @param first1 The begin iterator of the first range.
 * @param last1 The end iterator of the first range.
 * @param first2 The begin iterator of the second range.
 * @return true If two ranges are equal.
 * @return false If two ranges are not equal.
 */
template <class InputIter1, class InputIter2, class Compare>
bool equal(InputIter1 first1, InputIter1 last1, InputIter2 dest2,
           Compare compare) {
  for (; first1 != last1; ++first1, ++dest2) {
    if (!compare(*first1, *dest2)) {
      return false;
    }
  }

  return true;
}

/**
 * @brief Fill a range with the given value, the range is specified by
 * the iterators of tag `tiny_stl::input_iterator_tag`.
 *
 * @tparam InputIter The type of the given range.
 * @tparam T The type of the given value.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param value The given value.
 */
template <class OutputIter, class Size, class T>
OutputIter unchecked_fill_n(OutputIter first, Size n, const T &value) {
  for (; n > 0; --n) {
    *(first++) = value;
  }

  return first;
}

/**
 * @brief Fill a range with the given value, the value is trivially
 * copyable.
 *
 * @tparam T The type of the given range.
 * @tparam U The type of the given value.
 * @param first The begin iterator of the given range.
 * @param n The size of the given range.
 * @param value The given value.
 * @return T* The end iterator of the given range.
 */
template <class T, class Size, class U>
typename std::enable_if_t<std::is_integral_v<T> && sizeof(T) == 1 &&
                              !std::is_same_v<T, bool> &&
                              std::is_integral_v<U> && sizeof(U) == 1,
                          T *>
unchecked_fill_n(T *first, Size n, U value) {
  if (n > 0) {
    std::memset(first, (unsigned char)value, (size_t)n);
  }
  return first + n;
}

/**
 * @brief Fill a range with the given value.
 *
 * @tparam OutputIter The type of the given range.
 * @tparam Size The type of the given size.
 * @tparam T The type of the given value.
 * @param first The begin iterator of the given range.
 * @param n The size of the given range.
 * @param value The given value.
 * @return OutputIter The end iterator of the given range.
 */
template <class OutputIter, class Size, class T>
OutputIter fill_n(OutputIter first, Size n, const T &value) {
  return unchecked_fill_n(first, n, value);
}

/**
 * @brief Fill a range with the given value, the range is specified by
 * the iterators of tag `tiny_stl::forward_iterator_tag`.
 *
 * @tparam InputIter The type of the given range.
 * @tparam T The type of the given value.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param value The given value.
 */
template <class ForwardIter, class T>
void fill_cat(ForwardIter first, ForwardIter last, const T &value,
              tiny_stl::forward_iterator_tag) {
  for (; first != last; ++first) {
    *first = value;
  }
}

/**
 * @brief Fill a range with the given value, the range is specified by
 * the iterators of tag `tiny_stl::random_access_iterator_tag`.
 *
 * @tparam RandomAccessIter The type of the given range.
 * @tparam T The type of the given value.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param value The given value.
 */
template <class RandomAccessIter, class T>
void fill_cat(RandomAccessIter first, RandomAccessIter last, const T &value,
              tiny_stl::random_access_iterator_tag) {
  fill_n(first, last - first, value);
}

/**
 * @brief Fill a range with the given value, the range is specified by
 * the iterators whose tag will be deduced by `tiny_stl::iterator_category`.
 *
 * @tparam ForwardIter The type of the given range.
 * @tparam T The type of the given value.
 * @param first The begin iterator of the given range.
 * @param last The end iterator of the given range.
 * @param value The given value.
 */
template <class ForwardIter, class T>
void fill(ForwardIter first, ForwardIter last, const T &value) {
  fill_cat(first, last, value, tiny_stl::iterator_category(first));
}

/**
 * @brief Check if the first range is lexicographically less than the
 * second range.
 * @details Once the first mismatching pair of elements is found, the
 * return value will be determined in the following way:
 * - If the first element is less than the second element, return `true`.
 * - If the first element is greater than the second element, return `false`.
 * - If the first range is shorter than the second range, return `true`.
 * - If the first range is longer than the second range, return `false`.
 *
 * @tparam InputIter1 The type of the first range.
 * @tparam InputIter2 The type of the second range.
 * @param first1 The begin iterator of the first range.
 * @param last1 The end iterator of the first range.
 * @param first2 The begin iterator of the second range.
 * @param last2 The end iterator of the second range.
 * @return true If the first range is lexicographically less than the second
 * range.
 * @return false If the first range is not lexicographically less than the
 * second range.
 */
template <class InputIter1, class InputIter2>
bool lexicographical_compare(InputIter1 first1, InputIter1 last1,
                             InputIter2 first2, InputIter2 last2) {
  for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
    if (*first1 < *first2) {
      return true;
    }
    if (*first1 > *first2) {
      return false;
    }
  }
  return first1 == last1 && first2 != last2;
}

/**
 * @brief Check if the first range is lexicographically less than the
 * second range, the value is trivially comparable.
 * @details Once the first mismatching pair of elements is found, the
 * return value will be determined in the following way:
 * - If the first element is less than the second element, return `true`.
 * - If the first element is greater than the second element, return `false`.
 * - If the first range is shorter than the second range, return `true`.
 * - If the first range is longer than the second range, return `false`.
 *
 * @tparam T The type of the first range.
 * @tparam U The type of the second range.
 * @param first1 The begin iterator of the first range.
 * @param last1 The end iterator of the first range.
 * @param first2 The begin iterator of the second range.
 * @param last2 The end iterator of the second range.
 * @return true If the first range is lexicographically less than the second
 * range.
 * @return false If the first range is not lexicographically less than the
 * second range.
 */
template <class InputIter1, class InputIter2, class Compare>
bool lexicographical_compare(InputIter1 first1, InputIter1 last1,
                             InputIter2 first2, InputIter2 last2,
                             Compare compare) {
  for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
    if (compare(*first1, *first2)) {
      return true;
    }
    if (compare(*first2, *first1)) {
      return false;
    }
  }
  return first1 == last1 && first2 != last2;
}

/**
 * @brief Check if the first range is lexicographically less than the
 * second range, the value is trivially comparable.
 * @details Once the first mismatching pair of elements is found, the
 * return value will be determined in the following way:
 * - If the first element is less than the second element, return `true`.
 * - If the first element is greater than the second element, return `false`.
 * - If the first range is shorter than the second range, return `true`.
 * - If the first range is longer than the second range, return `false`.
 * @note This function is a specialization used to compare two ranges of bytes.
 *
 * @param first1 The begin iterator of the first range.
 * @param last1 The end iterator of the first range.
 * @param first2 The begin iterator of the second range.
 * @param last2 The end iterator of the second range.
 * @return true If the first range is lexicographically less than the second
 * range.
 * @return false If the first range is not lexicographically less than the
 * second range.
 */
bool lexicographical_compare(const unsigned char *first1,
                             const unsigned char *last1,
                             const unsigned char *first2,
                             const unsigned char *last2) {
  const auto len1 = last1 - first1;
  const auto len2 = last2 - first2;
  const auto result = std::memcmp(first1, first2, tiny_stl::min(len1, len2));
  return result != 0 ? result < 0 : len1 < len2;
}

template <class InputIter1, class InputIter2>
tiny_stl::pair<InputIter1, InputIter2>
mismatch(InputIter1 first1, InputIter1 last1, InputIter2 first2) {
  while (first1 != last1 && *first1 == *first2) {
    ++first1;
    ++first2;
  }
  return tiny_stl::pair<InputIter1, InputIter2>(first1, first2);
}

} // namespace tiny_stl

#endif // ! TINY_STL__INCLUDE__ALGOBASE_HPP
