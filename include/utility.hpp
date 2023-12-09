/**
 * @file utility.hpp
 * @author Liu Yuan (2787141886@qq.com)
 * @brief  This file contains some helper functions and `pair` class
 *
 * @details This file contains some helper functions and `pair` class,
 * including:
 * - `move`
 * - `forward`
 * - `swap`
 * - `swap_range`
 * - `pair`
 * - `make_pair`
 */
#ifndef TINY_STL__INCLUDE__UTILITY_HPP
#define TINY_STL__INCLUDE__UTIL_HPP

#include "type_traits.hpp"

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

/**
 * @brief `forward` mechanism.
 *
 * @details Remove the reference of the type while leaving `const` and
 * `volatile`(which is called CV limitation). Return `&&`.
 *
 * @tparam T The base type of the argument.
 * @param arg The argument.
 * @return T&& The rvalue reference of the argument.
 */
template <class T>
T &&forward(typename std::remove_reference_t<T> &arg) noexcept {
  return static_cast<T &&>(arg);
}

/**
 * @brief `forward` mechanism.
 *
 * @details Remove the reference of the type while leaving `const` and
 * `volatile`(which is called CV limitation). Return `&&`.
 *
 * @tparam T The base type of the argument.
 * @param arg The argument.
 * @return T&& The rvalue reference of the argument.
 */
template <class T>
T &&forward(typename std::remove_reference_t<T> &&arg) noexcept {
  static_assert(!std::is_lvalue_reference_v<T>, "bad forward");
  return static_cast<T &&>(arg);
}

/**
 * @brief Swap two objects by calling `swap` function.
 *
 * @tparam T The type of the objects.
 * @param left The left object.
 * @param right The right object.
 */
template <class T> void swap(T &left, T &right) {
  auto tmp(::tiny_stl::move(left));
  left = ::tiny_stl::move(right);
  right = ::tiny_stl::move(tmp);
}

/**
 * @brief Swap two range by calling `swap` function
 *
 * @details The first range is limited by `[first, last)`, while the second
 * range is started from `dest`
 * @warning Make sure the second range is as long as the first range, this
 * function doesn't provide error check
 *
 * @tparam ForwardIter1 The type of the iterator of the first range
 * @tparam ForwardIter2 The type of the iterator of the second range
 * @param first The start of the first range
 * @param last The end of the first range
 * @param dest The start of the second range
 * @return ForwardIter2 The end of the second range
 */
template <class ForwardIter1, class ForwardIter2>
ForwardIter2 swap_range(ForwardIter1 first, ForwardIter1 last,
                        ForwardIter2 dest) {
  for (; first != last; ++first, (void)++dest) {
    swap(*first, *dest);
  }
  return dest;
}

/**
 * @brief Swap two C-arrays by calling `swap` function
 *
 * @tparam T The type of the C-arrays
 * @tparam N The length of the C-arrays
 */
template <class T, size_t N> void swap(T (&a)[N], T (&b)[N]) {
  swap_range(a, a + N, b);
}

/**
 * @brief `pair` class, a simple implementation of `std::pair`
 *
 * @tparam T1 The type of the first element
 * @tparam T2 The type of the second element
 */
template <class T1, class T2> struct pair {
  using first_type = T1;
  using second_type = T2;

  first_type first;
  second_type second;

  /**
   * @brief Default constructor
   *
   * @details If `T1` and `T2` are both default constructible, then call their
   * default constructor, otherwise, this constructor is deleted.
   *
   * @tparam U1 The type of the first argument
   * @tparam U2 The type of the second argument
   * @tparam std::enable_if_t<
   * std::is_default_constructible_v<U1> &&
   * std::is_default_constructible_v<U2>,
   * void> A SFINAE parameter, if `T1` and `T2` are both default constructible,
   * then this parameter is `void`, otherwise, this constructor is deleted.
   */
  template <class U1 = T1, class U2 = T2,
            typename = typename std::enable_if_t<
                std::is_default_constructible_v<U1> &&
                    std::is_default_constructible_v<U2>,
                void>>
  constexpr pair() : first(), second() {}

  /**
   * @brief The implicit constructor with two arguments
   *
   * @details If `T1` and `T2` are both copy constructible and convertible from
   * `const U1&` and `const U2&`, then call their copy constructor, otherwise,
   * this constructor is deleted. The third parameter is used to avoid
   * instantiation when `T1` and `T2` are not copy constructible. If `T1` and
   * `T2` are both copy constructible and convertible from `const U1&` and
   * `const U2&`, then this parameter is `int` and set to `0` by default. `0`
   * has no special meaning, just a value to assign. Otherwise, this constructor
   * is deleted.
   *
   * @tparam U1 The type of the first argument
   * @tparam U2 The type of the second argument
   */
  template <
      class U1 = T1, class U2 = T2,
      typename std::enable_if_t<std::is_copy_constructible_v<U1> &&
                                    std::is_copy_constructible_v<U2> &&
                                    std::is_convertible_v<const U1 &, T1> &&
                                    std::is_convertible_v<const U2 &, T2>,
                                int> = 0>
  constexpr pair(const T1 &a, const T2 &b) : first(a), second(b) {}

  /**
   * @brief The explicit constructor with two arguments
   *
   * @details If `T1` and `T2` are both copy constructible and not convertible
   * from `const U1&` and `const U2&`, then call their copy constructor,
   * otherwise, this constructor is deleted. The third parameter is used to
   * avoid instantiation when `T1` and `T2` are not copy constructible. If `T1`
   * and `T2` are both copy constructible and not convertible from `const U1&`
   * and `const U2&`, then this parameter is `int`, `0` by default. `0` has no
   * special meaning, just a value to assign. Otherwise, this constructor is
   * deleted.
   *
   * @tparam U1 The type of the first argument
   * @tparam U2 The type of the second argument
   */
  template <
      class U1 = T1, class U2 = T2,
      typename std::enable_if_t<std::is_copy_constructible_v<U1> &&
                                    std::is_copy_constructible_v<U2> &&
                                    (!std::is_convertible_v<const U1 &, T1> ||
                                     !std::is_convertible_v<const U2 &, T2>),
                                int> = 0>
  explicit constexpr pair(const T1 &a, const T2 &b) : first(a), second(b) {}

  /**
   * @brief Construct a new pair object, this function is generated by compiler
   *
   * @param other A const reference of another `pair` object
   */
  pair(const pair &other) = default;

  /**
   * @brief Construct a new pair object, this function is generated by compiler
   *
   * @param other A rvalue of another `pair` object
   */
  pair(pair &&other) = default;

  /**
   * @brief  Move ctor.
   *
   * @details If `T1` and `T2` are both constructible and convertible from
   * `U1&&` and `U2&&`, then call their move constructor, otherwise, this
   * constructor is deleted. The third parameter is used to avoid instantiation
   * when `T1` and `T2` are not move constructible. If `T1` and `T2` are both
   * move constructible and convertible from `U1&&` and `U2&&`, then this
   * parameter is `int` and set to `0` by default. `0` has no special meaning,
   * just a value to assign. Otherwise, this constructor is deleted.
   *
   * @tparam U1 The type of the first argument
   * @tparam U2 The type of the second argument
   */
  template <
      class U1, class U2,
      typename std::enable_if_t<
          std::is_constructible_v<T1, U1> && std::is_constructible_v<T2, U2> &&
              std::is_convertible_v<U1, T1> && std::is_convertible_v<U2, T2>,
          int> = 0>
  constexpr pair(U1 &&a, U2 &&b)
      : first(forward<U1>(a)), second(forward<U2>(b)) {}

  /**
   * @brief Explicit move ctor.
   *
   * @details If `T1` and `T2` are both constructible and not convertible from
   * `U1&&` and `U2&&`, then call their move constructor, otherwise, this
   * constructor is deleted. The third parameter is used to avoid instantiation
   * when `T1` and `T2` are not move constructible. If `T1` and `T2` are both
   * move constructible and not convertible from `U1&&` and `U2&&`, then this
   * parameter is `int` and set to `0` by default. `0` has no special meaning,
   * just a value to assign. Otherwise, this constructor is deleted.
   *
   * @tparam U1 The type of the first argument
   * @tparam U2 The type of the second argument
   */
  template <class U1, class U2,
            typename std::enable_if_t<std::is_constructible_v<T1, U1> &&
                                          std::is_constructible_v<T2, U2> &&
                                          (!std::is_convertible_v<U1, T1> ||
                                           !std::is_convertible_v<U2, T2>),
                                      int> = 0>
  explicit constexpr pair(U1 &&a, U2 &&b)
      : first(forward<U1>(a)), second(forward<U2>(b)) {}

  /**
   * @brief Construct a new pair object from another pair object, whose template
   * parameters are different
   *
   * @details If `T1` and `T2` are both constructible and convertible from `U1`
   * and `U2`, then call their copy constructor, otherwise, this constructor is
   * deleted. The third parameter is used to avoid instantiation when `T1` and
   * `T2` are not copy constructible. If `T1` and `T2` are both copy
   * constructible and convertible from `U1` and `U2`, then this parameter is
   * `int` and set to `0` by default. `0` has no special meaning, just a value
   * to assign. Otherwise, this constructor is deleted.
   *
   * @tparam U1 The type of the first element of the other pair object
   * @tparam U2 The type of the second element of the other pair object
   */
  template <
      class U1, class U2,
      typename std::enable_if_t<
          std::is_constructible_v<T1, U1> && std::is_constructible_v<T2, U2> &&
              std::is_convertible_v<U1, T1> && std::is_convertible_v<U2, T2>,
          int> = 0>
  constexpr pair(const pair<U1, U2> &other)
      : first(other.first), second(other.second) {}

  /**
   * @brief Explicitly construct a new pair object from another pair object,
   * whose template parameters are different
   *
   * @details If `T1` and `T2` are both constructible and not convertible from
   * `U1` and `U2`, then call their copy constructor, otherwise, this
   * constructor is deleted. The third parameter is used to avoid instantiation
   * when `T1` and `T2` are not copy constructible. If `T1` and `T2` are both
   * copy constructible and not convertible from `U1` and `U2`, then this
   * parameter is `int` and set to `0` by default. `0` has no special meaning,
   * just a value to assign. Otherwise, this constructor is deleted.
   *
   * @tparam U1 The type of the first element of the other pair object
   * @tparam U2 The type of the second element of the other pair object
   */
  template <class U1, class U2,
            std::enable_if_t<std::is_constructible_v<T1, U1> &&
                                 std::is_constructible_v<T2, U2> &&
                                 (!std::is_convertible_v<U1, T1> ||
                                  !std::is_convertible_v<U2, T2>),
                             int> = 0>
  explicit constexpr pair(const pair<U1, U2> &other)
      : first(other.first), second(other.second) {}

  /**
   * @brief Move ctor.
   *
   * @details If `T1` and `T2` are both constructible and convertible from
   * `U1&&` and `U2&&`, then call their move constructor, otherwise, this
   * constructor is deleted. The third parameter is used to avoid instantiation
   * when `T1` and `T2` are not move constructible. If `T1` and `T2` are both
   * move constructible and convertible from `U1&&` and `U2&&`, then this
   * parameter is `int` and set to `0` by default. `0` has no special meaning,
   * just a value to assign. Otherwise, this constructor is deleted.
   *
   * @tparam U1 The type of the first element of the other pair object
   * @tparam U2 The type of the second element of the other pair object
   */
  template <
      class U1, class U2,
      std::enable_if_t<
          std::is_constructible_v<T1, U1> && std::is_constructible_v<T2, U2> &&
              std::is_convertible_v<U1, T1> && std::is_convertible_v<U2, T2>,
          int> = 0>
  constexpr pair(pair<U1, U2> &&other)
      : first(forward<U1>(other.first)), second(forward<U2>(other.second)) {}

  /**
   * @brief Explicit move ctor.
   *
   * @details If `T1` and `T2` are both constructible and not convertible from
   * `U1&&` and `U2&&`, then call their move constructor, otherwise, this
   * constructor is deleted. The third parameter is used to avoid instantiation
   * when `T1` and `T2` are not move constructible. If `T1` and `T2` are both
   * move constructible and not convertible from `U1&&` and `U2&&`, then this
   * parameter is `int` and set to `0` by default. `0` has no special meaning,
   * just a value to assign. Otherwise, this constructor is deleted.
   *
   * @tparam U1 The type of the first element of the other pair object
   * @tparam U2 The type of the second element of the other pair object
   */
  template <class U1, class U2,
            std::enable_if_t<std::is_constructible_v<T1, U1> &&
                                 std::is_constructible_v<T2, U2> &&
                                 (!std::is_convertible_v<U1, T1> ||
                                  !std::is_convertible_v<U2, T2>),
                             int> = 0>
  explicit constexpr pair(pair<U1, U2> &&other)
      : first(forward<U1>(other.first)), second(forward<U2>(other.second)) {}

  /**
   * @brief The copy assignment operator
   * @note This function does not support different template parameters
   *
   * @param other The other pair object
   * @return pair& The reference of this pair object
   */
  pair &operator=(const pair &other) {
    if (&other != this) {
      this->first = other.first;
      this->second = other.second;
    }
    return *this;
  }

  /**
   * @brief The move assignment operator
   * @note This function does not support different template parameters
   *
   * @param other The other pair object
   * @return pair& The reference of this pair object
   */
  pair &operator=(pair &&other) {
    if (&other != this) {
      this->first = move(other.first);
      this->second = move(other.second);
    }
    return *this;
  }

  /**
   * @brief The copy assignment operator
   * @note This function supports different template parameters
   *
   * @tparam U1 The type of the first element of the other pair object
   * @tparam U2 The type of the second element of the other pair object
   * @param other The other pair object
   * @return pair& The reference of this pair object
   */
  template <class U1, class U2> pair &operator=(const pair<U1, U2> &other) {
    this->first = other.first;
    this->second = other.second;
    return *this;
  }

  /**
   * @brief The move assignment operator
   * @note This function supports different template parameters
   *
   * @tparam U1 The type of the first element of the other pair object
   * @tparam U2 The type of the second element of the other pair object
   * @param other The other pair object
   * @return pair& The reference of this pair object
   */
  template <class U1, class U2> pair &operator=(pair<U1, U2> &&other) {
    this->first = move(other.first);
    this->second = move(other.second);
    return *this;
  }

  /**
   * @brief Destroy the pair object, this function is generated by compiler
   */
  ~pair() = default;

  /**
   * @brief Swap the content of this pair object and another pair object
   *
   * @param other The other pair object
   */
  void swap(pair &other) {
    using tiny_stl::swap;
    swap(this->first, other.first);
    swap(this->second, other.second);
  }
};

/**
 * @brief The equality operator
 * @note This function does not support different template parameters
 *
 * @details Compare `first` and `second` respectively
 *
 * @tparam T1 The type of the first element
 * @tparam T2 The type of the second element
 * @param left The left pair object
 * @param right The right pair object
 * @return true Both `first` and `second` are equal
 * @return false Not both `first` and `second` are equal
 */
template <class T1, class T2>
bool operator==(const pair<T1, T2> &left, const pair<T1, T2> &right) {
  return left.first == right.first && left.second == right.second;
}

/**
 * @brief The less than operator
 * @note This function does not support different template parameters
 *
 * @details Compare `first` first, if they are equal, then compare `second`
 *
 * @tparam T1 The type of the first element
 * @tparam T2 The type of the second element
 * @param left The left pair object
 * @param right The right pair object
 * @return true The left pair object is less than the right pair object
 * @return false The left pair object is not less than the right pair object
 */
template <class T1, class T2>
bool operator<(const pair<T1, T2> &left, const pair<T1, T2> &right) {
  return left.first < right.first ||
         (!(right.first < left.first) && left.second < right.second);
}

/**
 * @brief The inequality operator
 * @note This function does not support different template parameters
 * @note This function is a wrapper of `operator==`
 *
 * @tparam T1 The type of the first element
 * @tparam T2 The type of the second element
 * @param left The left pair object
 * @param right The right pair object
 * @return true The left pair object is not equal to the right pair object
 * @return false The left pair object is equal to the right pair object
 */
template <class T1, class T2>
bool operator!=(const pair<T1, T2> &left, const pair<T1, T2> &right) {
  return !(left == right);
}

/**
 * @brief The greater than operator
 * @note This function does not support different template parameters
 * @note This function is a wrapper of `operator<`
 *
 * @tparam T1 The type of the first element
 * @tparam T2 The type of the second element
 * @param left The left pair object
 * @param right The right pair object
 * @return true The left pair object is greater than the right pair object
 * @return false The left pair object is not greater than the right pair object
 */
template <class T1, class T2>
bool operator>(const pair<T1, T2> &left, const pair<T1, T2> &right) {
  return right < left;
}

/**
 * @brief The less than or equal to operator
 * @note This function does not support different template parameters
 * @note This function is a wrapper of `operator<`
 *
 * @tparam T1 The type of the first element
 * @tparam T2 The type of the second element
 * @param left The left pair object
 * @param right The right pair object
 * @return true The left pair object is less than or equal to the right pair
 * object
 * @return false The left pair object is not less than or equal to the right
 * pair object
 */
template <class T1, class T2>
bool operator<=(const pair<T1, T2> &left, const pair<T1, T2> &right) {
  return !(right < left);
}

/**
 * @brief The greater than or equal to operator
 * @note This function does not support different template parameters
 * @note This function is a wrapper of `operator<`
 *
 * @tparam T1 The type of the first element
 * @tparam T2 The type of the second element
 * @param left The left pair object
 * @param right The right pair object
 * @return true The left pair object is greater than or equal to the right pair
 * @return false The left pair object is not greater than or equal to the right
 */
template <class T1, class T2>
bool operator>=(const pair<T1, T2> &left, const pair<T1, T2> &right) {
  return !(left < right);
}

/**
 * @brief The equality operator
 * @note This function does not support different template parameters
 *
 * @tparam T1 The type of the first element
 * @tparam T2 The type of the second element
 * @param left The left pair object
 * @param right The right pair object
 */
template <class T1, class T2>
void swap(pair<T1, T2> &left, pair<T1, T2> &right) {
  left.swap(right);
}

/**
 * @brief Make a pair object with two arguments, the type of the arguments are
 * deduced automatically
 *
 * @tparam T1 The type of the first element
 * @tparam T2 The type of the second element
 * @param left The left pair object
 * @param right The right pair object
 * @return pair<T1, T2> The pair object
 */
template <class T1, class T2> pair<T1, T2> make_pair(T1 &&first, T2 &&second) {
  return pair<T1, T2>(forward<T1>(first), forward<T2>(second));
}

} // namespace tiny_stl

#endif // !TINY_STL__INCLUDE__UTIL_HPP