#ifndef TINY_STL__INCLUDE__CONSTRUCT_HPP
#define TINY_STL__INCLUDE__CONSTRUCT_HPP

#include <new>

#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

namespace TinySTL {

template <class T> void construct(T *ptr) { ::new ((void *)ptr) T(); }

template <class T> void construct(T *ptr, const T &val) {
  ::new ((void *)ptr) T(val);
}

template <class T, class... Args> void construct(T *ptr, Args... args) {
  ::new ((void *)ptr) T(tiny_stl::forward<Args>(args)...);
}

template <class T> void destroy_one(T *, std::true_type) {}

template <class T> void destroy_one(T *ptr, std::false_type) {
  if (ptr) {
    ptr->~T();
  }
}

template <class ForwardIter>
void destroy_cat(ForwardIter, ForwardIter, std::true_type) {}

template <class T> void destroy(T *ptr) {
  destroy_one(ptr, std::is_trivially_destructible<T>{});
}

template <class ForwardIter>
void destroy_cat(ForwardIter first, ForwardIter last, std::false_type) {
  for (; first != last; ++first) {
    destroy(&(*first));
  }
}

template <class ForwardIter> void destroy(ForwardIter first, ForwardIter last) {
  destroy_cat(
      first, last,
      std::is_trivially_destructible<
          typename tiny_stl::iterator_traits<ForwardIter>::value_type>{});
}

} // namespace TinySTL

#endif // !TINY_STL__INCLUDE__CONSTRUCT_HPP