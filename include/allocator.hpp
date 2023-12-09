/**
 * @file allocator.hpp
 * @author Liu Yuan (2787141886@qq.com)
 * @brief This file is the header of `allocator.cpp`, which contains the
 * allocator class.
 *
 * @details This file contains the following utilities:
 * - `allocator`: the allocator class.
 */
#ifndef TINY_STL__INCLUDE__ALLOCATOR_HPP
#define TINY_STL__INCLUDE__ALLOCATOR_HPP

#include "construct.hpp"
#include "utility.hpp"

namespace tiny_stl {

/**
 * @brief The allocator class, using very simple memory management.
 *
 * @tparam T The type of the object to be allocated.
 */
template <class T> class allocator {
public:
  using value_type = T;
  using pointer = T *;
  using const_pointer = const T *;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using difference_type = ptrdiff_t;

public:
  /**
   * @brief Allocate memory for an object of type T.
   *
   * @return T* The pointer to the allocated memory.
   */
  static T *allocate();
  /**
   * @brief Allocate memory for n objects of type T.
   *
   * @param n The number of objects to be allocated.
   * @return T* The pointer to the allocated memory.
   */
  static T *allocate(size_type n);

  /**
   * @brief Deallocate memory for an object of type T.
   *
   * @param ptr The pointer to the memory to be deallocated.
   */
  static void deallocate(T *ptr);
  /**
   * @brief Deallocate memory for n objects of type T.
   *
   * @param ptr The pointer to the memory to be deallocated.
   * @param n The number of objects to be deallocated.
   */
  static void deallocate(T *ptr, size_type n);

  /**
   * @brief Construct an object of type T.
   *
   * @param ptr The pointer to the memory to be constructed.
   */
  static void construct(T *ptr);
  /**
   * @brief Construct an object of type T with a value.
   *
   * @param ptr The pointer to the memory to be constructed.
   * @param value The value to be constructed.
   */
  static void construct(T *ptr, const T &value);
  /**
   * @brief Construct an object of type T with a value.
   *
   * @param ptr The pointer to the memory to be constructed.
   * @param value The value to be constructed.
   */
  static void construct(T *ptr, T &&value);

  /**
   * @brief Construct an object of type T with arguments.
   *
   * @tparam Args The types of the arguments.
   * @param ptr The pointer to the memory to be constructed.
   * @param args The arguments to be constructed.
   */
  template <class... Args> static void construct(T *ptr, Args &&...args);

  /**
   * @brief Destroy an object of type T.
   *
   * @param ptr The pointer to the memory to be destroyed.
   */
  static void destroy(T *ptr);
  /**
   * @brief Destroy objects of type T.
   *
   * @param first The pointer to the first memory to be destroyed.
   * @param last The pointer to the last memory to be destroyed.
   */
  static void destroy(T *first, T *last);
};

template <class T> T *allocator<T>::allocate() {
  return static_cast<T *>(::operator new(sizeof(T)));
}

template <class T> T *allocator<T>::allocate(size_type n) {
  if (n == 0)
    return nullptr;
  return static_cast<T *>(::operator new(n * sizeof(T)));
}

template <class T> void allocator<T>::deallocate(T *ptr) {
  if (ptr == nullptr)
    return;
  ::operator delete(ptr);
}

template <class T> void allocator<T>::deallocate(T *ptr, size_type /*size*/) {
  if (ptr == nullptr)
    return;
  ::operator delete(ptr);
}

template <class T> void allocator<T>::construct(T *ptr) { construct(ptr); }

template <class T> void allocator<T>::construct(T *ptr, const T &value) {
  ::tiny_stl::construct(ptr, value);
}

template <class T> void allocator<T>::construct(T *ptr, T &&value) {
  ::tiny_stl::construct(ptr, move(value));
}

template <class T>
template <class... Args>
void allocator<T>::construct(T *ptr, Args &&...args) {
  ::tiny_stl::construct(ptr, forward<Args>(args)...);
}

template <class T> void allocator<T>::destroy(T *ptr) { destroy(ptr); }

template <class T> void allocator<T>::destroy(T *first, T *last) {
  ::tiny_stl::destroy(first, last);
}

} // namespace tiny_stl

#endif // ! TINY_STL__INCLUDE__ALLOCATOR_HPP