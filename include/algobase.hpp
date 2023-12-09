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

template <class T> const T &max(const T &left, const T &right) {
  return left > right ? left : right;
}

template <class T, class Compare>
const T &max(const T &left, const T &right, Compare compare) {
  return compare(left, right) ? right : left;
}

template <class T> const T &min(const T &left, const T &right) {
  return left < right ? left : right;
}

template <class T, class Compare>
const T &min(const T &left, const T &right, Compare compare) {
  return compare(right, left) ? right : left;
}

template <class ForwardIter1, class ForwardIter2>
void iter_swap(ForwardIter1 left, ForwardIter2 right) {
  tiny_stl::swap(*left, *right);
}

template <class InputIter, class OutputIter>
OutputIter unchecked_copy_cat(InputIter first, InputIter last, OutputIter dest,
                              tiny_stl::input_iterator_tag) {
  for (; first != last; ++first, ++dest) {
    *dest = *first;
  }

  return dest;
}

template <class RandomAccessIter, class OutputIter>
OutputIter unchecked_copy_cat(RandomAccessIter first, RandomAccessIter last,
                              OutputIter dest,
                              tiny_stl::random_access_iterator_tag) {
  for (auto n = last - first; n > 0; --n, ++first, ++dest) {
    *dest = *first;
  }
  return dest;
}

template <class InputIter, class OutputIter>
OutputIter unchecked_copy(InputIter first, InputIter last, OutputIter dest) {
  unchecked_copy_cat(first, last, dest, tiny_stl::iterator_category(first));
}

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

template <class InputIter, class OutputIter>
OutputIter copy(InputIter first, InputIter last, OutputIter dest) {
  return unchecked_copy(first, last, dest);
}

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

template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2 unchecked_copy_backward(BidirectionalIter1 first,
                                           BidirectionalIter1 last,
                                           BidirectionalIter2 dest) {
  unchecked_copy_backward_cat(first, last, dest,
                              tiny_stl::iterator_category(first));
}

template <class T, class U>
typename std::enable_if_t<std::is_same_v<typename std::remove_const_t<T>, U> &&
                              std::is_trivially_copyable_v<U>,
                          U *>
unchecked_copy_backward(T *first, T *last, U *dest) {
  auto n = static_cast<size_t>(last - first);
  if (n != 0) {
    dest -= n;
    std::memcpy(dest, first, n * sizeof(U));
  }
  return dest;
}

template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2 copy_backward(BidirectionalIter1 first,
                                 BidirectionalIter1 last,
                                 BidirectionalIter2 dest) {
  return unchecked_copy_backward(first, last, dest);
}

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

template <class InputIter, class Size, class OutputIter>
tiny_stl::pair<InputIter, OutputIter>
unchecked_copy_n(InputIter from, Size n, OutputIter to,
                 tiny_stl::input_iterator_tag) {
  for (; n > 0; --n) {
    *(to++) = *(from++);
  }
  return tiny_stl::pair<InputIter, OutputIter>(from, to);
}

template <class RandomAccessIter, class Size, class OutputIter>
tiny_stl::pair<RandomAccessIter, OutputIter>
unchecked_copy_n(RandomAccessIter from, Size n, OutputIter to,
                 tiny_stl::random_access_iterator_tag) {
  auto last = from + n;
  return tiny_stl::pair<RandomAccessIter, OutputIter>(last,
                                                      copy_n(from, last, to));
}

template <class InputIter, class Size, class OutputIter>
tiny_stl::pair<InputIter, OutputIter> copy_n(InputIter from, Size n,
                                             OutputIter to) {
  unchecked_copy_n(from, n, to, tiny_stl::iterator_category(from));
}

template <class InputIter, class OutputIter>
OutputIter unchecked_move_cat(InputIter first, InputIter last, OutputIter dest,
                              tiny_stl::input_iterator_tag) {
  for (; first != last; ++first, ++dest) {
    *dest = tiny_stl::move(*first);
  }
  return dest;
}

template <class RandomAccessIter, class OutputIter>
OutputIter unchecked_move_cat(RandomAccessIter first, RandomAccessIter last,
                              OutputIter dest,
                              tiny_stl::random_access_iterator_tag) {
  for (auto n = last - first; n > 0; --n) {
    *(dest++) = tiny_stl::move(*(first++));
  }
  return dest;
}

template <class InputIter, class OutputIer>
OutputIer unchecked_move(InputIter first, InputIter last, OutputIer dest) {
  return unchecked_move_cat(first, last, dest,
                            tiny_stl::iterator_category(first));
}

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

template <class InputIer, class OutputIer>
OutputIer move(InputIer first, InputIer last, OutputIer dest) {
  return unchecked_move(first, last, dest);
}

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

template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2 unchecked_move_backward(BidirectionalIter1 first,
                                           BidirectionalIter1 last,
                                           BidirectionalIter2 dest) {
  return unchecked_move_backward_cat(first, last, dest,
                                     tiny_stl::iterator_category(first));
}

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

template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2 move_backward(BidirectionalIter1 first,
                                 BidirectionalIter1 last,
                                 BidirectionalIter2 dest) {
  return unchecked_move_backward(first, last, dest);
}

template <class InputIter1, class InputIter2>
bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2) {
  for (; first1 != last1; ++first1, ++first2) {
    if (*first1 != *first2) {
      return false;
    }
  }

  return true;
}

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

template <class OutputIter, class Size, class T>
OutputIter unchecked_fill_n(OutputIter first, Size n, const T &value) {
  for (; n > 0; --n) {
    *(first++) = value;
  }

  return first;
}

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

template <class OutputIter, class Size, class T>
OutputIter fill_n(OutputIter first, Size n, const T &value) {
  return unchecked_fill_n(first, n, value);
}

template <class ForwardIter, class T>
void fill_cat(ForwardIter first, ForwardIter last, const T &value,
              tiny_stl::forward_iterator_tag) {
  for (; first != last; ++first) {
    *first = value;
  }
}

template <class RandomAccessIter, class T>
void fill_cat(RandomAccessIter first, RandomAccessIter last, const T &value,
              tiny_stl::random_access_iterator_tag) {
  fill_n(first, last - first, value);
}

template <class ForwardIter, class T>
void fill(ForwardIter first, ForwardIter last, const T &value) {
  fill_cat(first, last, value, tiny_stl::iterator_category(first));
}

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
