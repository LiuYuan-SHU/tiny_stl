#ifndef TINY_STL__INCLUDE__UNINITIALIZAED_HPP
#define TINY_STL__INCLUDE__UNINITIALIZAED_HPP

#include "algobase.hpp"
#include "construct.hpp"
#include "iterator.hpp"
#include "utility.hpp"

#include <type_traits>

namespace tiny_stl {

template <class InputIter, class ForwardIter>
InputIter unchecked_uninit_copy(InputIter first, InputIter last,
                                ForwardIter dest, std::true_type) {
  return tiny_stl::copy(first, last, dest);
}

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

template <class InputIter, class ForwardIter>
ForwardIter uninitialized_copy(InputIter first, InputIter last,
                               ForwardIter dest) {
  return tiny_stl::unchecked_uninit_copy(
      first, last, dest,
      std::is_trivially_copy_assignable_v<
          typename tiny_stl::iterator_traits<InputIter>::value_type>);
}

template <class InputIter, class Size, class FowardIter>
FowardIter unchecked_uninit_copy_n(InputIter first, Size n, FowardIter dest,
                                   std::true_type) {
  return tiny_stl::copy_n(first, n, dest).second;
}

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

template <class InputIter, class Size, class FowardIter>
FowardIter uninitialized_copy_n(InputIter first, Size n, FowardIter dest) {
  return tiny_stl::unchecked_uninit_copy_n(
      first, n, dest,
      std::is_trivially_copy_constructible_v<
          typename tiny_stl::iterator_traits<InputIter>::value_type>);
}

template <class ForwardIter, class T>
void unchecked_uninit_fill(ForwardIter first, ForwardIter last, const T &value,
                           std::true_type) {
  tiny_stl::fill(first, last, value);
}

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

template <class ForwardIter, class T>
void uninitialized_fill(ForwardIter first, ForwardIter last, const T &value) {
  tiny_stl::unchecked_uninit_fill(
      first, last, value,
      std::is_trivially_copy_assignable_v<
          typename iterator_traits<ForwardIter>::value_type>);
}

template <class ForwardIter, class Size, class T>
ForwardIter unchecked_uninit_fill_n(ForwardIter first, Size n, const T &value,
                                    std::true_type) {
  return tiny_stl::fill_n(first, n, value);
}

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

template <class ForwardIter, class Size, class T>
ForwardIter uninitialized_fill_n(ForwardIter first, Size n, const T &value) {
  return tiny_stl::unchecked_uninit_fill_n(
      first, n, value,
      std::is_trivially_copy_assignable_v<
          typename iterator_traits<ForwardIter>::value_type>);
}

template <class InputIter, class ForwardIter>
ForwardIter unchecked_uninit_move(InputIter first, InputIter last,
                                  ForwardIter dest, std::true_type) {
  return tiny_stl::move(first, last, dest);
}

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

template <class InputIter, class ForwardIter>
ForwardIter uninitialized_move(InputIter first, InputIter last,
                               ForwardIter dest) {
  return tiny_stl::unchecked_uninit_move(
      first, last, dest,
      std::is_trivially_move_assignable_v<
          typename iterator_traits<InputIter>::value_type>);
}

template <class InputIter, class Size, class ForwardIter>
ForwardIter unchecked_uninit_move_n(InputIter first, Size n, ForwardIter dest,
                                    std::true_type) {
  return tiny_stl::move(first, first + n, dest);
}

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

template <class InputIter, class Size, class ForwardIter>
ForwardIter uninitialized_move_n(InputIter first, Size n, ForwardIter dest) {
  return tiny_stl::unchecked_uninit_move_n(
      first, n, dest,
      std::is_trivially_move_assignable_v<
          typename iterator_traits<InputIter>::value_type>);
}

} // namespace tiny_stl

#endif // ! TINY_STL__INCLUDE__UNINITIALIZAED_HPP
