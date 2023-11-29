/**
 * @file type_traits.hpp
 * @author Liu Yuan (2787141886@qq.com)
 * @brief  This file contains some type traits
 *
 * @details This file contains some type traits, including:
 * - integral_constant
 * - compile_time_constant_bool
 * - true_type
 * - false_type
 * - is_pair
 */
#ifndef TINY_STL__INCLUDE__TYPE_TRAITS_HPP
#define TINY_STL__INCLUDE__TYPE_TRAITS_HPP

#include <type_traits>

namespace tiny_stl {

/**
 * @brief A helper class, representing compile-time constant.
 *
 * @tparam T The type of the constant
 * @tparam v The value of the constant
 */
template <class T, T v> struct integral_constant {
  static constexpr T value = v;
};

template <bool b> using compile_time_constant_bool = integral_constant<bool, b>;

/**
 * @brief  Compile-time true type
 */
using true_type = compile_time_constant_bool<true>;

/**
 * @brief Compile-time false type
 */
using false_type = compile_time_constant_bool<false>;

// -- Forward declaration begin
template <class T1, class T2> struct pair;
// -- Forward declaration end

/**
 * @brief Helper struct, judge if the given type is an instance of
 * `::tiny_stl::pair`. In such cases(template <class T>), it's `false`.

 * @tparam T The type to be judged
 */
template <class T> struct is_pair : ::tiny_stl::false_type {};

/**
 * @brief Helper struct, judge if the give type is an instance of
 * `::tiny_stl::pair`. If the template is specialized with
 * `::tiny_stl::pair<T1, T2>`, it's `true`.
 *
 * @tparam T1 The first template parameter.
 * @tparam T2 The second template parameter.
 */
template <class T1, class T2>
struct is_pair<::tiny_stl::pair<T1, T2>> : ::tiny_stl::true_type {};

} // namespace tiny_stl

#endif // !TINY_STL__INCLUDE__TYPE_TRAITS_HP