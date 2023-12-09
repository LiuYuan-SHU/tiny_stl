#ifndef TINY_STL__INCLUDE__ALLOCATOR_HPP
#define TINY_STL__INCLUDE__ALLOCATOR_HPP

#include "construct.hpp"
#include "utility.hpp"

namespace tiny_stl {

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
  static T *allocate();
  static T *allocate(size_type n);

  static void deallocate(T *ptr);
  static void deallocate(T *ptr, size_type n);

  static void construct(T *ptr);
  static void construct(T *ptr, const T &value);
  static void construct(T *ptr, T &&value);

  template <class... Args> static void construct(T *ptr, Args &&...args);

  static void destroy(T *ptr);
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
  construct(ptr, value);
}

template <class T> void allocator<T>::construct(T *ptr, T &&value) {
  construct(ptr, move(value));
}

template <class T>
template <class... Args>
void allocator<T>::construct(T *ptr, Args &&...args) {
  construct(ptr, forward<Args>(args)...);
}

template <class T> void allocator<T>::destroy(T *ptr) { destroy(ptr); }

template <class T> void allocator<T>::destroy(T *first, T *last) {
  destroy(first, last);
}

} // namespace tiny_stl

#endif // ! TINY_STL__INCLUDE__ALLOCATOR_HPP