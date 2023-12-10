#ifndef INY_STL__INCLUDE__MEMORY_HPP
#define INY_STL__INCLUDE__MEMORY_HPP

#include "construct.hpp"
#include "iterator.hpp"
#include "uninitialized.hpp"
#include "utility.hpp"

#include <climits>
#include <cstddef>
#include <cstdlib>
#include <type_traits>

namespace tiny_stl {

template <class T> constexpr T *address_of(T &value) noexcept { return &value; }

template <class T> pair<T *, ptrdiff_t> get_buffer_helper(ptrdiff_t len, T *) {
  if (len > static_cast<ptrdiff_t>(INT_MAX / sizeof(T))) {
    len = static_cast<ptrdiff_t>(INT_MAX / sizeof(T));
  }

  while (len > 0) {
    T *tmp = static_cast<T *>(malloc(static_cast<size_t>(len) * sizeof(T)));
    if (tmp) {
      return pair<T *, ptrdiff_t>(tmp, len);
    } else {
      len /= 2;
    }
  }
  return pair<T *, ptrdiff_t>(nullptr, 0);
}

template <class T> pair<T *, ptrdiff_t> get_temporary_buffer(ptrdiff_t len) {
  return get_buffer_helper(len, static_cast<T *>(0));
}

template <class T>
pair<T *, ptrdiff_t> get_temporary_buffer(ptrdiff_t len, T *) {
  return get_buffer_helper(len, static_cast<T *>(0));
}

template <class T> void release_temporary_buffer(T *ptr) { free(ptr); }

template <class ForwardIter, class T> class temporary_buffer {
private:
  ptrdiff_t original_len;
  ptrdiff_t len;
  T *buffer;

public:
  temporary_buffer(ForwardIter first, ForwardIter last);

  ~temporary_buffer() {
    tiny_stl::destroy(buffer, buffer + len);
    free(buffer);
  }

public:
  ptrdiff_t size() const noexcept { return len; }
  ptrdiff_t requested_size() const noexcept { return original_len; }
  T *begin() noexcept { return buffer; }
  T *end() noexcept { return buffer + len; }

private:
  void allocate_buffer();
  void initialize_buffer(const T &, std::true_type);
  void initialize_buffer(const T &value, std::false_type) {
    tiny_stl::uninitialized_fill_n(buffer, len, value);
  }

private:
  temporary_buffer(const temporary_buffer &) = delete;
  void operator=(const temporary_buffer &) = delete;
};

template <class ForwardIter, class T>
temporary_buffer<ForwardIter, T>::temporary_buffer(ForwardIter first,
                                                   ForwardIter last) {
  try {
    len = tiny_stl::distance(first, last);
    allocate_buffer();
    if (len > 0) {
      initialize_buffer(*first, std::is_trivially_default_constructible_v<T>);
    }
  } catch (...) {
    free(buffer);
    buffer = nullptr;
    len = 0;
  }
}

template <class ForwardIter, class T>
void temporary_buffer<ForwardIter, T>::allocate_buffer() {
  original_len = len;
  if (len > static_cast<ptrdiff_t>(INT_MAX / sizeof(T))) {
    len = INT_MAX / sizeof(T);
  }
  while (len > 0) {
    buffer = static_cast<T *>(malloc(len * sizeof(T)));
    if (buffer) {
      break;
    } else {
      len /= 2;
    }
  }
}

template <class T> class auto_ptr {
public:
  using ele_type = T;

private:
  T *m_ptr;

public:
  explicit auto_ptr(T *p = nullptr) : m_ptr(p) {}
  auto_ptr(auto_ptr &other) : m_ptr(other.release()) {}
  template <class U> auto_ptr(auto_ptr<U> &other) : m_ptr(other.release()) {}

  auto_ptr &operator=(auto_ptr &other) {
    if (this != &other) {
      delete m_ptr;
      m_ptr = other.release();
    }
    return *this;
  }
  template <class U> auto_ptr &operator=(auto_ptr<U> &other) {
    if (this->get() != other.get()) {
      delete m_ptr;
      m_ptr = other.release();
    }
    return *this;
  }

  ~auto_ptr() { delete m_ptr; }

public:
  T &operator*() const { return *m_ptr; }
  T *operator->() const { return m_ptr; }

  T *get() const { return m_ptr; }

  T *release() {
    T *tmp = m_ptr;
    m_ptr = nullptr;
    return tmp;
  }

  void reset(T *p = nullptr) {
    if (m_ptr != p) {
      delete m_ptr;
      m_ptr = p;
    }
  }
};

} // namespace tiny_stl

#endif // ! INY_STL__INCLUDE__MEMORY_HPP
