/**
 * @file functional.hpp
 * @author Liu Yuan (2787141886@qq.com)
 * @brief  This file contains some helper functions and classes for
 * `algorithm` and `container`.
 *
 * @details This file contains some helper functions and classes,
 * including:
 * - `unarg_function`: a helper class for unary function.
 * - `binary_function`: a helper class for binary function.
 * - `plus`: a helper class for `+` operation.
 * - `minus`: a helper class for binary `-` operation.
 * - `multiplies`: a helper class for `*` operation.
 * - `divides`: a helper class for `/` operation.
 * - `modulus`: a helper class for `%` operation.
 * - `negate`: a helper class for unary `-` operation.
 * - `identity_element`: a helper function for `identity_element`.
 * - `equal_to`: a helper class for `==` operation.
 * - `not_equal_to`: a helper class for `!=` operation.
 * - `greater`: a helper class for `>` operation.
 * - `less`: a helper class for `<` operation.
 * - `greater_equal`: a helper class for `>=` operation.
 * - `less_equal`: a helper class for `<=` operation.
 * - `logical_and`: a helper class for `&&` operation.
 * - `logical_or`: a helper class for `||` operation.
 * - `logical_not`: a helper class for `!` operation.
 * - `identity`: a helper class for `identity` operation.
 * - `select1st`: a helper class for selecting the first element of a pair.
 * - `select2nd`: a helper class for selecting the second element of a pair.
 * - `project1st`: a helper class for projecting the first parameter of a
 * function call
 * - `project2nd`: a helper class for projecting the second parameter of a
 * function call
 * - `hash`: a helper class for hash.
 */
#ifndef TINY_STL__INCLUDE__FUNCTIONAL_HPP
#define TINY_STL__INCLUDE__FUNCTIONAL_HPP

#include <cstddef>

namespace tiny_stl {

/**
 * @brief A helper class for unary function.
 *
 * @tparam Arg The type of the argument.
 * @tparam Result The type of the result.
 */
template <class Arg, class Result> struct unarg_function {
  using argument_type = Arg;
  using result_type = Result;
};

/**
 * @brief A helper class for binary function.
 *
 * @tparam Arg1 The type of the first argument.
 * @tparam Arg2 The type of the second argument.
 * @tparam Result The type of the result.
 */
template <class Arg1, class Arg2, class Result> struct binary_function {
  using first_argument_type = Arg1;
  using second_argument_type = Arg2;
  using result_type = Result;
};

/**
 * @brief The helper class for `+` operation.
 *
 * @tparam T The type of the argument.
 */
template <class T> struct plus : public binary_function<T, T, T> {
  T operator()(const T &x, const T &y) const { return x + y; }
};

/**
 * @brief The helper class for `-` operation.
 *
 * @tparam T The type of the argument.
 */
template <class T> struct minus : public binary_function<T, T, T> {
  T operator()(const T &x, const T &y) const { return x - y; }
};

/**
 * @brief The helper class for `*` operation.
 *
 * @tparam T The type of the argument.
 */
template <class T> struct multiplies : public binary_function<T, T, T> {
  T operator()(const T &x, const T &y) const { return x * y; }
};

/**
 * @brief The helper class for `/` operation.
 *
 * @tparam T The type of the argument.
 */
template <class T> struct divides : public binary_function<T, T, T> {
  T operator()(const T &x, const T &y) const { return x / y; }
};

/**
 * @brief The helper class for `%` operation.
 *
 * @tparam T The type of the argument.
 */
template <class T> struct modulus : public binary_function<T, T, T> {
  T operator()(const T &x, const T &y) const { return x % y; }
};

/**
 * @brief The helper class for unary `-` operation.
 *
 * @tparam T The type of the argument.
 */
template <class T> struct negate : public unarg_function<T, T> {
  T operator()(const T &x) const { return -x; }
};

/**
 * @brief The helper function for `identity_element`.
 *
 * @details An identity element is a special type of element of a set with
 * respect to a binary operation on that set, which leaves other elements
 * unchanged when combined with them.
 *
 * @tparam T The type of the argument.
 */
template <class T> T identity_element(plus<T>) { return T{0}; }

/**
 * @brief The helper function for `identity_element`.
 *
 * @details An identity element is a special type of element of a set with
 * respect to a binary operation on that set, which leaves other elements
 * unchanged when combined with them.
 *
 * @tparam T The type of the argument.
 */
template <class T> T identity_element(multiplies<T>) { return T{1}; }

/**
 * @brief The helper class for `==` operation.
 *
 * @tparam T The type of the argument.
 */
template <class T> struct equal_to : public binary_function<T, T, bool> {
  bool operator()(const T &x, const T &y) const { return x == y; }
};

/**
 * @brief The helper class for `!=` operation.
 *
 * @tparam T The type of the argument.
 */
template <class T> struct not_equal_to : public binary_function<T, T, bool> {
  bool operator()(const T &x, const T &y) const { return x != y; }
};

/**
 * @brief The helper class for `>` operation.
 *
 * @tparam T The type of the argument.
 */
template <class T> struct greater : public binary_function<T, T, bool> {
  bool operator()(const T &x, const T &y) const { return x > y; }
};

/**
 * @brief The helper class for `<` operation.
 *
 * @tparam T The type of the argument.
 */
template <class T> struct less : public binary_function<T, T, bool> {
  bool operator()(const T &x, const T &y) const { return x < y; }
};

/**
 * @brief The helper class for `>=` operation.
 *
 * @tparam T The type of the argument.
 */
template <class T> struct greater_equal : public binary_function<T, T, bool> {
  bool operator()(const T &x, const T &y) const { return x >= y; }
};

/**
 * @brief The helper class for `<=` operation.
 *
 * @tparam T The type of the argument.
 */
template <class T> struct less_equal : public binary_function<T, T, bool> {
  bool operator()(const T &x, const T &y) const { return x <= y; }
};

/**
 * @brief The helper class for `&&` operation.
 *
 * @tparam T The type of the argument.
 */
template <class T> struct logical_and : public binary_function<T, T, bool> {
  bool operator()(const T &x, const T &y) const { return x && y; }
};

/**
 * @brief The helper class for `||` operation.
 *
 * @tparam T The type of the argument.
 */
template <class T> struct logical_or : public binary_function<T, T, bool> {
  bool operator()(const T &x, const T &y) const { return x || y; }
};

/**
 * @brief The helper class for `!` operation.
 *
 * @tparam T The type of the argument.
 */
template <class T> struct logical_not : public unarg_function<T, bool> {
  bool operator()(const T &x) const { return !x; }
};

/**
 * @brief The helper class for `identity` operation.
 * @attention The second template parameter is `bool`, yet the return type is
 * `T`.
 *
 * @tparam T The type of the argument.
 */
template <class T> struct identity : public unarg_function<T, bool> {
  const T &operator()(const T &x) const { return x; }
};

/**
 * @brief The helper class for selecting the first element of a pair.
 *
 * @tparam Pair The type of the argument.
 */
template <class Pair>
struct select1st : public unarg_function<Pair, typename Pair::first_type> {
  const typename Pair::first_type &operator()(const Pair &x) const {
    return x.first;
  }
};

/**
 * @brief The helper class for selecting the second element of a pair.
 *
 * @tparam Pair The type of the argument.
 */
template <class Pair>
struct select2nd : public unarg_function<Pair, typename Pair::second_type> {
  const typename Pair::second_type &operator()(const Pair &x) const {
    return x.second;
  }
};

/**
 * @brief The helper class for projecting the first parameter of a function call
 *
 * @tparam Arg1 The type of the first argument.
 * @tparam Arg2 The type of the second argument.
 */
template <class Arg1, class Arg2>
struct project1st : public binary_function<Arg1, Arg2, Arg1> {
  Arg1 operator()(const Arg1 &x, const Arg2 &) const { return x; }
};

/**
 * @brief The helper class for projecting the second parameter of a function
 * call
 *
 * @tparam Arg1 The type of the first argument.
 * @tparam Arg2 The type of the second argument.
 */
template <class Arg1, class Arg2>
struct project2nd : public binary_function<Arg1, Arg2, Arg1> {
  Arg2 operator()(const Arg1 &, const Arg2 &y) const { return y; }
};

/**
 * @brief The helper class for hash.
 * @note For non-built-in types, no hash function is provided.
 *
 * @tparam Key The type of the argument.
 */
template <class Key> struct hash {};

/**
 * @brief The partial specialization of `hash` for pointers.
 * @note For pointers, the hash function return the address of the pointer.
 *
 * @tparam Ptr The pointer type
 */
template <class Ptr> struct hash<Ptr *> {
  size_t operator()(Ptr *ptr) const noexcept {
    return reinterpret_cast<size_t>(ptr);
  }
};

/*
 * The following code handles other built-in types, which just return the value
 * of the argument as the hash value.
 */
#define MYSTL_TRIVIAL_HASH_FCN(Type)                                           \
  template <> struct hash<Type> {                                              \
    size_t operator()(Type val) const noexcept {                               \
      return static_cast<size_t>(val);                                         \
    }                                                                          \
  };

MYSTL_TRIVIAL_HASH_FCN(bool)

MYSTL_TRIVIAL_HASH_FCN(char)

MYSTL_TRIVIAL_HASH_FCN(signed char)

MYSTL_TRIVIAL_HASH_FCN(unsigned char)

MYSTL_TRIVIAL_HASH_FCN(wchar_t)

MYSTL_TRIVIAL_HASH_FCN(char16_t)

MYSTL_TRIVIAL_HASH_FCN(char32_t)

MYSTL_TRIVIAL_HASH_FCN(short)

MYSTL_TRIVIAL_HASH_FCN(unsigned short)

MYSTL_TRIVIAL_HASH_FCN(int)

MYSTL_TRIVIAL_HASH_FCN(unsigned int)

MYSTL_TRIVIAL_HASH_FCN(long)

MYSTL_TRIVIAL_HASH_FCN(unsigned long)

MYSTL_TRIVIAL_HASH_FCN(long long)

MYSTL_TRIVIAL_HASH_FCN(unsigned long long)

#undef MYSTL_TRIVIAL_HASH_FCN

/**
 * @brief The helper function for hashing floating-point numbers.
 *
 * @details The following code is the implementation of the FNV-1a hash. The
 * pseudo-code is as follows:
 * @code {}
 * algorithm fnv-1a is
 *   hash := FNV_offset_basis
 *
 *   for each byte_of_data to be hashed do
 *          hash := hash XOR byte_of_data
 *          hash := hash × FNV_prime
 *
 *   return hash
 * @endcode
 * The mechanism of the FNV-1a hash is to XOR the current hash value with the
 * next byte of data, then multiply by a prime number. The FNV-1a hash is
 * designed to be fast while maintaining a low collision rate.
 *
 * @param first The pointer to the first byte of the data.
 * @param count The number of bytes to be hashed.
 * @return size_t The hash value.
 */
inline size_t bitwise_hash(const unsigned char *first, size_t count) {
#if (_MSC_VER && _WIN64) || ((__GNUC__ || __clang__) && __SIZEOF_POINTER__ == 8)
  const size_t fnv_offset = 14695981039346656037ull;
  const size_t fnv_prime = 1099511628211ull;
#else
  const size_t fnv_offset = 2166136261u;
  const size_t fnv_prime = 16777619u;
#endif
  size_t result = fnv_offset;
  for (size_t i = 0; i < count; ++i) {
    result ^= (size_t)first[i];
    result *= fnv_prime;
  }
  return result;
}

/**
 * @brief The partial specialization of `hash` for `float`
 * @note For floating-point numbers, the hash function is implemented by
 * bitwise hashing.
 *
 * @tparam T The type of the argument.
 */
template <> struct hash<float> {
  size_t operator()(const float &val) {
    return val == 0.0f
               ? 0
               : bitwise_hash((const unsigned char *)&val, sizeof(float));
  }
};

/**
 * @brief The partial specialization of `hash` for `double`
 * @note For floating-point numbers, the hash function is implemented by
 * bitwise hashing.
 *
 * @tparam T The type of the argument.
 */
template <> struct hash<double> {
  size_t operator()(const double &val) {
    return val == 0.0f
               ? 0
               : bitwise_hash((const unsigned char *)&val, sizeof(double));
  }
};

/**
 * @brief The partial specialization of `hash` for `long double`
 * @note For floating-point numbers, the hash function is implemented by
 * bitwise hashing.
 *
 * @tparam T The type of the argument.
 */
template <> struct hash<long double> {
  size_t operator()(const long double &val) {
    return val == 0.0f
               ? 0
               : bitwise_hash((const unsigned char *)&val, sizeof(long double));
  }
};

} // namespace tiny_stl

#endif // ! TINY_STL__INCLUDE__FUNCTIONAL_HPP
