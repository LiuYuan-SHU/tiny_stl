/**
 * @file construct.hpp
 * @author Liu Yuan (2787141886@qq.com)
 * @brief This file is the header of `construct.cpp`, which contains some
 * helper functions for constructing and destroying objects.
 *
 * @details This file contains the following functions:
 * - `construct`: construct an object at the given address.
 * - `destroy`: destroy an object at the given address.
 * - `destroy_cat`: destroy a range of objects.
 * - `destroy_one`: destroy an object.
 */
#ifndef TINY_STL__INCLUDE__CONSTRUCT_HPP
#define TINY_STL__INCLUDE__CONSTRUCT_HPP

#include <new>

#include "iterator.hpp"
#include "utility.hpp"

namespace tiny_stl {

/**
 * @brief Construct an object with default initialization at the given address.
 *
 * @tparam T The type of the object to be constructed.
 * @param ptr The address of the object to be constructed.
 */
template <class T> void construct(T *ptr) { ::new ((void *)ptr) T(); }

/**
 * @brief Construct an object with copy initialization at the given address.
 *
 * @tparam T The type of the object to be constructed.
 * @param ptr The address of the object to be constructed.
 * @param val The value to be copied.
 */
template <class T> void construct(T *ptr, const T &val) {
  ::new ((void *)ptr) T(val);
}

/**
 * @brief Construct an object with multiple parameters at the given address.
 *
 * @tparam T The type of the object to be constructed.
 * @tparam Args The types of the parameters.
 * @param ptr The address of the object to be constructed.
 * @param args The parameters to be passed to the constructor.
 */
template <class T, class... Args> void construct(T *ptr, Args... args) {
  ::new ((void *)ptr) T(tiny_stl::forward<Args>(args)...);
}

/**
 * @brief Destroy an object with trailing destructor at the given address.
 *
 * @tparam T The type of the object to be destroyed.
 */
template <class T> void destroy_one(T *, std::true_type) {}

/**
 * @brief Destroy an object with non-trailing destructor at the given address.
 *
 * @tparam T The type of the object to be destroyed.
 * @param ptr The address of the object to be destroyed.
 */
template <class T> void destroy_one(T *ptr, std::false_type) {
  if (ptr) {
    ptr->~T();
  }
}

/**
 * @brief Destroy a range of objects with trailing destructor.
 *
 * @tparam ForwardIter The type of the iterator.
 */
template <class ForwardIter>
void destroy_cat(ForwardIter, ForwardIter, std::true_type) {}

/**
 * @brief Destroy an object.
 * @note This function will call different functions according to whether
 * the object has a trailing destructor.
 *
 * @tparam T The type of the object to be destroyed.
 * @param ptr The address of the object to be destroyed.
 */
template <class T> void destroy(T *ptr) {
  destroy_one(ptr, std::is_trivially_destructible<T>{});
}

/**
 * @brief Destroy a range of objects with non-trailing destructor.
 *
 * @tparam ForwardIter The type of the iterator.
 * @param first The beginning of the range.
 * @param last The end of the range.
 */
template <class ForwardIter>
void destroy_cat(ForwardIter first, ForwardIter last, std::false_type) {
  for (; first != last; ++first) {
    destroy(&(*first));
  }
}

/**
 * @brief Destroy a range of objects.
 * @note This function will call different functions according to whether
 * the object has a trailing destructor.
 *
 * @tparam ForwardIter The type of the iterator.
 * @param first The beginning of the range.
 * @param last The end of the range.
 */
template <class ForwardIter> void destroy(ForwardIter first, ForwardIter last) {
  destroy_cat(
      first, last,
      std::is_trivially_destructible<
          typename tiny_stl::iterator_traits<ForwardIter>::value_type>{});
}

} // namespace tiny_stl

#endif // !TINY_STL__INCLUDE__CONSTRUCT_HPP
