#ifndef TINY_STL__INCLUDE__UTILITY_HPP
#define TINY_STL__INCLUDE__UTILITY_HPP

#include "type_traits.hpp"

#include <cstddef>
#include <type_traits>

namespace tiny_stl {

/**
 * @brief `move` mechanism.
 *
 * @details Remove the reference of the type while leaving `const` and
 * `volatile`. Return `&&`.
 * @warning This function does not guarantee the return value is an rvalue.
 * If the argument is `const` or the argument does not provide a move
 * constructor, a copy constructor will be called.
 *
 * @tparam T The type of the argument.
 * @param arg The argument.
 * @return std::remove_reference_t<T>&& The rvalue reference of the argument.
 */
template <class T>
typename std::remove_reference_t<T> &&move(T &&arg) noexcept {
  return static_cast<typename std::remove_reference_t<T> &&>(arg);
}

template <class T>
T &&forward(typename std::remove_reference_t<T> &arg) noexcept {
  return static_cast<T &&>(arg);
}

template <class T>
T &&forward(typename std::remove_reference_t<T> &&arg) noexcept {
  static_assert(!std::is_lvalue_reference_v<T>, "bad forward");
  return static_cast<T &&>(arg);
}

template <class T> void swap(T &left, T &right) {
  auto tmp(move(left));
  left = move(right);
  right = move(tmp);
}

template <class ForwardIter1, class ForwardIter2>
ForwardIter2 swap_range(ForwardIter1 first, ForwardIter1 last,
                        ForwardIter2 dest) {
  for (; first != last; ++first, (void)++dest) {
    swap(*first, *dest);
  }
  return dest;
}

template <class T, size_t N> void swap(T (&a)[N], T (&b)[N]) {
  swap_range(a, a + N, b);
}

template <class T1, class T2> struct pair {
  using first_type = T1;
  using second_type = T2;

  first_type first;
  second_type second;

  template <class U1 = T1, class U2 = T2,
            typename = typename std::enable_if_t<
                std::is_default_constructible_v<U1> &&
                    std::is_default_constructible_v<U2>,
                void>>
  constexpr pair() : first(), second() {}

  template <
      class U1 = T1, class U2 = T2,
      typename std::enable_if_t<std::is_copy_constructible_v<U1> &&
                                    std::is_copy_constructible_v<U2> &&
                                    std::is_convertible_v<const U1 &, T1> &&
                                    std::is_convertible_v<const U2 &, T2>,
                                int> = 0>
  constexpr pair(const T1 &a, const T2 &b) : first(a), second(b) {}

  template <
      class U1 = T1, class U2 = T2,
      typename std::enable_if_t<std::is_copy_constructible_v<U1> &&
                                    std::is_copy_constructible_v<U2> &&
                                    (!std::is_convertible_v<const U1 &, T1> ||
                                     !std::is_convertible_v<const U2 &, T2>),
                                int> = 0>
  explicit constexpr pair(const T1 &a, const T2 &b) : first(a), second(b) {}

  pair(const pair &other) = default;
  pair(pair &&other) = default;

  template <
      class U1, class U2,
      typename std::enable_if_t<
          std::is_constructible_v<T1, U1> && std::is_constructible_v<T2, U2> &&
              std::is_convertible_v<U1, T1> && std::is_convertible_v<U2, T2>,
          int> = 0>
  constexpr pair(U1 &&a, U2 &&b)
      : first(forward<U1>(a)), second(forward<U2>(b)) {}

  template <class U1, class U2,
            typename std::enable_if_t<std::is_constructible_v<T1, U1> &&
                                          std::is_constructible_v<T2, U2> &&
                                          (!std::is_convertible_v<U1, T1> ||
                                           !std::is_convertible_v<U2, T2>),
                                      int> = 0>
  explicit constexpr pair(U1 &&a, U2 &&b)
      : first(forward<U1>(a)), second(forward<U2>(b)) {}

  template <
      class U1, class U2,
      typename std::enable_if_t<
          std::is_constructible_v<T1, U1> && std::is_constructible_v<T2, U2> &&
              std::is_convertible_v<U1, T1> && std::is_convertible_v<U2, T2>,
          int> = 0>
  constexpr pair(const pair<U1, U2> &other)
      : first(other.first), second(other.second) {}

  template <class U1, class U2,
            std::enable_if_t<std::is_constructible_v<T1, U1> &&
                                 std::is_constructible_v<T2, U2> &&
                                 (!std::is_convertible_v<U1, T1> ||
                                  !std::is_convertible_v<U2, T2>),
                             int> = 0>
  explicit constexpr pair(const pair<U1, U2> &other)
      : first(other.first), second(other.second) {}

  template <
      class U1, class U2,
      std::enable_if_t<
          std::is_constructible_v<T1, U1> && std::is_constructible_v<T2, U2> &&
              std::is_convertible_v<U1, T1> && std::is_convertible_v<U2, T2>,
          int> = 0>
  constexpr pair(pair<U1, U2> &&other)
      : first(forward<U1>(other.first)), second(forward<U2>(other.second)) {}

  template <class U1, class U2,
            std::enable_if_t<std::is_constructible_v<T1, U1> &&
                                 std::is_constructible_v<T2, U2> &&
                                 (!std::is_convertible_v<U1, T1> ||
                                  !std::is_convertible_v<U2, T2>),
                             int> = 0>
  explicit constexpr pair(pair<U1, U2> &&other)
      : first(forward<U1>(other.first)), second(forward<U2>(other.second)) {}

  pair &operator=(const pair &other) {
    if (&other != this) {
      this->first = other.first;
      this->second = other.second;
    }
    return *this;
  }

  pair &operator=(pair &&other) {
    if (&other != this) {
      this->first = move(other.first);
      this->second = move(other.second);
    }
    return *this;
  }

  template <class U1, class U2> pair &operator=(const pair<U1, U2> &other) {
    this->first = other.first;
    this->second = other.second;
    return *this;
  }

  template <class U1, class U2> pair &operator=(pair<U1, U2> &&other) {
    this->first = move(other.first);
    this->second = move(other.second);
    return *this;
  }

  ~pair() = default;

  void swap(pair &other) {
    using tiny_stl::swap;
    swap(this->first, other.first);
    swap(this->second, other.second);
  }
};

template <class T1, class T2>
bool operator==(const pair<T1, T2> &left, const pair<T1, T2> &right) {
  return left.first == right.first && left.second == right.second;
}

template <class T1, class T2>
bool operator<(const pair<T1, T2> &left, const pair<T1, T2> &right) {
  return left.first < right.first ||
         (!(right.first < left.first) && left.second < right.second);
}

template <class T1, class T2>
bool operator!=(const pair<T1, T2> &left, const pair<T1, T2> &right) {
  return !(left == right);
}

template <class T1, class T2>
bool operator>(const pair<T1, T2> &left, const pair<T1, T2> &right) {
  return right < left;
}

template <class T1, class T2>
bool operator<=(const pair<T1, T2> &left, const pair<T1, T2> &right) {
  return !(right < left);
}

template <class T1, class T2>
bool operator>=(const pair<T1, T2> &left, const pair<T1, T2> &right) {
  return !(left < right);
}

template <class T1, class T2>
void swap(pair<T1, T2> &left, pair<T1, T2> &right) {
  left.swap(right);
}

template <class T1, class T2> pair<T1, T2> make_pair(T1 &&first, T2 &&second) {
  return pair<T1, T2>(forward<T1>(first), forward<T2>(second));
}

} // namespace tiny_stl

#endif // !TINY_STL__INCLUDE__UTILITY_HPP