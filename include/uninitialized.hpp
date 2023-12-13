/**
 * @file uninitialized.hpp
 * @author Liu Yuan (2787141886@qq.com)
 * @brief This file  is the header of `uninitialized.cpp`, which contains some
 * helper functions for constructing and destroying objects on raw memory.
 *
 * @details This file contains the following functions:
 * - `unchecked_uninit_copy`: copy a range of objects to a raw memory.
 * - `uninitialized_copy`: copy a range of objects to a raw memory.
 * - `unchecked_uninit_copy_n`: copy a range of objects to a raw memory.
 * - `uninitialized_copy_n`: copy a range of objects to a raw memory.
 * - `unchecked_uninit_fill`: fill a range of objects with a value.
 * - `uninitialized_fill`: fill a range of objects with a value.
 * - `unchecked_uninit_fill_n`: fill a range of objects with a value.
 * - `uninitialized_fill_n`: fill a range of objects with a value.
 * - `unchecked_uninit_move`: move a range of objects to a raw memory.
 * - `uninitialized_move`: move a range of objects to a raw memory.
 * - `unchecked_uninit_move_n`: move a range of objects to a raw memory.
 * - `uninitialized_move_n`: move a range of objects to a raw memory.
 */
#ifndef TINY_STL__INCLUDE__UNINITIALIZAED_HPP
#define TINY_STL__INCLUDE__UNINITIALIZAED_HPP

#include "algobase.hpp"
#include "construct.hpp"
#include "iterator.hpp"
#include "utility.hpp"

#include <type_traits>

namespace tiny_stl {

/**
 * @brief Copy a range of trivially copy assignable objects to a raw memory.
 *
 * @tparam InputIter The type of the iterators.
 * @tparam ForwardIter The type of the destination iterators.
 * @param first The begin iterator of the source range.
 * @param last The end iterator of the source range.
 * @param dest The begin iterator of the destination range.
 * @return InputIter The end iterator of the source range.
 */
template <class InputIter, class ForwardIter>
ForwardIter unchecked_uninit_copy(InputIter first, InputIter last,
                                  ForwardIter dest, std::true_type) {
  return tiny_stl::copy(first, last, dest);
}

/**
 * @brief Copy a range of non-trivially copy assignable objects to a raw memory.
 *
 * @tparam InputIter The type of the iterators.
 * @tparam ForwardIter The type of the destination iterators.
 * @param first The begin iterator of the source range.
 * @param last The end iterator of the source range.
 * @param dest The begin iterator of the destination range.
 * @return ForwardIter The end iterator of the destination range.
 */
template <class InputIter, class ForwardIter>
ForwardIter unchecked_uninit_copy(InputIter first, InputIter last,
                                  ForwardIter dest, std::false_type) {
  auto cur = dest;
  try {
    for (; first != last; ++first, ++cur) {
      tiny_stl::construct(&(*cur), *first);
    }
  } catch (...) {
    for (; cur != dest; --cur) {
      tiny_stl::destroy(&(*cur));
    }
  }
  return cur;
}

/**
 * @brief Copy a range of objects to a raw memory.
 *
 * @tparam InputIter The type of the iterators.
 * @tparam ForwardIter The type of the destination iterators.
 * @param first The begin iterator of the source range.
 * @param last The end iterator of the source range.
 * @param dest The begin iterator of the destination range.
 * @return ForwardIter The end iterator of the destination range.
 */
template <class InputIter, class ForwardIter>
ForwardIter uninitialized_copy(InputIter first, InputIter last,
                               ForwardIter dest) {
  return tiny_stl::unchecked_uninit_copy(
      first, last, dest,
      std::is_trivially_copy_assignable<
          typename tiny_stl::iterator_traits<InputIter>::value_type>{});
}

/**
 * @brief Copy a range of trivially copy assignable objects to a raw memory.
 *
 * @tparam InputIter The type of the iterators.
 * @tparam Size The type of the size.
 * @tparam FowardIter The type of the destination iterators.
 * @param first The begin iterator of the source range.
 * @param n The size of the source range.
 * @param dest The begin iterator of the destination range.
 * @return FowardIter The end iterator of the destination range.
 */
template <class InputIter, class Size, class FowardIter>
FowardIter unchecked_uninit_copy_n(InputIter first, Size n, FowardIter dest,
                                   std::true_type) {
  return tiny_stl::copy_n(first, n, dest).second;
}

/**
 * @brief Copy a range of non-trivially copy assignable objects to a raw memory.
 *
 * @tparam InputIter The type of the iterators.
 * @tparam Size The type of the size.
 * @tparam FowardIter The type of the destination iterators.
 * @param first The begin iterator of the source range.
 * @param n The size of the source range.
 * @param dest The begin iterator of the destination range.
 * @return FowardIter The end iterator of the destination range.
 */
template <class InputIter, class Size, class FowardIter>
FowardIter unchecked_uninit_copy_n(InputIter first, Size n, FowardIter dest,
                                   std::false_type) {
  auto cur = dest;
  try {
    for (; n > 0; --n, ++cur, ++first) {
      tiny_stl::construct(&(*cur), *first);
    }
  } catch (...) {
    for (; cur != dest; --cur) {
      tiny_stl::destroy(&(*cur));
    }
  }
  return cur;
}

/**
 * @brief Copy a range of objects to a raw memory.
 *
 * @tparam InputIter The type of the iterators.
 * @tparam Size The type of the size.
 * @tparam FowardIter The type of the destination iterators.
 * @param first The begin iterator of the source range.
 * @param n The size of the source range.
 * @param dest The begin iterator of the destination range.
 * @return FowardIter The end iterator of the destination range.
 */
template <class InputIter, class Size, class FowardIter>
FowardIter uninitialized_copy_n(InputIter first, Size n, FowardIter dest) {
  return tiny_stl::unchecked_uninit_copy_n(
      first, n, dest,
      std::is_trivially_copy_constructible_v<
          typename tiny_stl::iterator_traits<InputIter>::value_type>);
}

/**
 * @brief Fill a range of trivially copy assignable objects with a value.
 *
 * @tparam ForwardIter The type of the iterators.
 * @tparam T The type of the value.
 * @param first The begin iterator of the range.
 * @param last The end iterator of the range.
 * @param value The value to be filled.
 * @return ForwardIter The end iterator of the range.
 */
template <class ForwardIter, class T>
void unchecked_uninit_fill(ForwardIter first, ForwardIter last, const T &value,
                           std::true_type) {
  tiny_stl::fill(first, last, value);
}

/**
 * @brief Fill a range of non-trivially copy assignable objects with a value.
 *
 * @tparam ForwardIter The type of the iterators.
 * @tparam T The type of the value.
 * @param first The begin iterator of the range.
 * @param last The end iterator of the range.
 * @param value The value to be filled.
 * @return ForwardIter The end iterator of the range.
 */
template <class ForwardIter, class T>
void unchecked_uninit_fill(ForwardIter first, ForwardIter last, const T &value,
                           std::false_type) {
  auto cur = first;
  try {
    for (; cur != last; ++cur) {
      tiny_stl::construct(&*cur, value);
    }
  } catch (...) {
    for (; first != cur; ++first)
      tiny_stl::destroy(&*first);
  }
}

/**
 * @brief Fill a range of objects with a value.
 *
 * @tparam ForwardIter The type of the iterators.
 * @tparam T The type of the value.
 * @param first The begin iterator of the range.
 * @param last The end iterator of the range.
 * @param value The value to be filled.
 * @return ForwardIter The end iterator of the range.
 */
template <class ForwardIter, class T>
void uninitialized_fill(ForwardIter first, ForwardIter last, const T &value) {
  tiny_stl::unchecked_uninit_fill(
      first, last, value,
      std::is_trivially_copy_assignable_v<
          typename iterator_traits<ForwardIter>::value_type>);
}

/**
 * @brief Fill a range of trivially copy assignable objects with a value.
 *
 * @tparam ForwardIter The type of the iterators.
 * @tparam Size The type of the size.
 * @tparam T The type of the value.
 * @param first The begin iterator of the range.
 * @param n The size of the range.
 * @param value The value to be filled.
 * @return ForwardIter The end iterator of the range.
 */
template <class ForwardIter, class Size, class T>
ForwardIter unchecked_uninit_fill_n(ForwardIter first, Size n, const T &value,
                                    std::true_type) {
  return tiny_stl::fill_n(first, n, value);
}

/**
 * @brief Fill a range of non-trivially copy assignable objects with a value.
 *
 * @tparam ForwardIter The type of the iterators.
 * @tparam Size The type of the size.
 * @tparam T The type of the value.
 * @param first The begin iterator of the range.
 * @param n The size of the range.
 * @param value The value to be filled.
 * @return ForwardIter The end iterator of the range.
 */
template <class ForwardIter, class Size, class T>
ForwardIter unchecked_uninit_fill_n(ForwardIter first, Size n, const T &value,
                                    std::false_type) {
  auto cur = first;
  try {
    for (; n > 0; --n, ++cur) {
      tiny_stl::construct(&(*cur), value);
    }
  } catch (...) {
    for (; first != cur; ++first)
      tiny_stl::destroy(&(*first));
  }
  return cur;
}

/**
 * @brief Fill a range of objects with a value.
 *
 * @tparam ForwardIter The type of the iterators.
 * @tparam Size The type of the size.
 * @tparam T The type of the value.
 * @param first The begin iterator of the range.
 * @param n The size of the range.
 * @param value The value to be filled.
 * @return ForwardIter The end iterator of the range.
 */
template <class ForwardIter, class Size, class T>
ForwardIter uninitialized_fill_n(ForwardIter first, Size n, const T &value) {
  return tiny_stl::unchecked_uninit_fill_n(
      first, n, value,
      std::is_trivially_copy_assignable_v<
          typename iterator_traits<ForwardIter>::value_type>);
}

/**
 * @brief Move a range of trivially move assignable objects to a raw memory.
 *
 * @tparam InputIter The type of the iterators.
 * @tparam ForwardIter The type of the destination iterators.
 * @param first The begin iterator of the source range.
 * @param last The end iterator of the source range.
 * @param dest The begin iterator of the destination range.
 * @return InputIter The end iterator of the source range.
 */
template <class InputIter, class ForwardIter>
ForwardIter unchecked_uninit_move(InputIter first, InputIter last,
                                  ForwardIter dest, std::true_type) {
  return tiny_stl::move(first, last, dest);
}

/**
 * @brief Move a range of non-trivially move assignable objects to a raw memory.
 *
 * @tparam InputIter The type of the iterators.
 * @tparam ForwardIter The type of the destination iterators.
 * @param first The begin iterator of the source range.
 * @param last The end iterator of the source range.
 * @param dest The begin iterator of the destination range.
 * @return ForwardIter The end iterator of the destination range.
 */
template <class InputIter, class ForwardIter>
ForwardIter unchecked_uninit_move(InputIter first, InputIter last,
                                  ForwardIter dest, std::false_type) {
  ForwardIter cur = dest;
  try {
    for (; first != last; ++first, ++cur) {
      tiny_stl::construct(&*cur, tiny_stl::move(*first));
    }
  } catch (...) {
    tiny_stl::destroy(dest, cur);
  }
  return cur;
}

/**
 * @brief Move a range of objects to a raw memory.
 *
 * @tparam InputIter The type of the iterators.
 * @tparam ForwardIter The type of the destination iterators.
 * @param first The begin iterator of the source range.
 * @param last The end iterator of the source range.
 * @param dest The begin iterator of the destination range.
 * @return ForwardIter The end iterator of the destination range.
 */
template <class InputIter, class ForwardIter>
ForwardIter uninitialized_move(InputIter first, InputIter last,
                               ForwardIter dest) {
  return tiny_stl::unchecked_uninit_move(
      first, last, dest,
      std::is_trivially_move_assignable_v<
          typename iterator_traits<InputIter>::value_type>);
}

/**
 * @brief Move a range of trivially move assignable objects to a raw memory.
 *
 * @tparam InputIter The type of the iterators.
 * @tparam Size The type of the size.
 * @tparam ForwardIter The type of the destination iterators.
 * @param first The begin iterator of the source range.
 * @param n The size of the source range.
 * @param dest The begin iterator of the destination range.
 * @return InputIter The end iterator of the source range.
 */
template <class InputIter, class Size, class ForwardIter>
ForwardIter unchecked_uninit_move_n(InputIter first, Size n, ForwardIter dest,
                                    std::true_type) {
  return tiny_stl::move(first, first + n, dest);
}

/**
 * @brief Move a range of non-trivially move assignable objects to a raw memory.
 *
 * @tparam InputIter The type of the iterators.
 * @tparam Size The type of the size.
 * @tparam ForwardIter The type of the destination iterators.
 * @param first The begin iterator of the source range.
 * @param n The size of the source range.
 * @param dest The begin iterator of the destination range.
 * @return ForwardIter The end iterator of the destination range.
 */
template <class InputIter, class Size, class ForwardIter>
ForwardIter unchecked_uninit_move_n(InputIter first, Size n, ForwardIter dest,
                                    std::false_type) {
  auto cur = dest;
  try {
    for (; n > 0; --n, ++first, ++cur) {
      tiny_stl::construct(&*cur, tiny_stl::move(*first));
    }
  } catch (...) {
    for (; dest != cur; ++dest)
      tiny_stl::destroy(&*dest);
    throw;
  }
  return cur;
}

/**
 * @brief Move a range of objects to a raw memory.
 *
 * @tparam InputIter The type of the iterators.
 * @tparam Size The type of the size.
 * @tparam ForwardIter The type of the destination iterators.
 * @param first The begin iterator of the source range.
 * @param n The size of the source range.
 * @param dest The begin iterator of the destination range.
 * @return ForwardIter The end iterator of the destination range.
 */
template <class InputIter, class Size, class ForwardIter>
ForwardIter uninitialized_move_n(InputIter first, Size n, ForwardIter dest) {
  return tiny_stl::unchecked_uninit_move_n(
      first, n, dest,
      std::is_trivially_move_assignable_v<
          typename iterator_traits<InputIter>::value_type>);
}

} // namespace tiny_stl

#endif // ! TINY_STL__INCLUDE__UNINITIALIZAED_HPP
