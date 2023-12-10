/**
 * @file memory.hpp
 * @author Liu Yuan (2787141886@qq.com)
 * @brief This file is the header of `memory.cpp`, which contains some
 * helper functions for constructing and destroying objects.
 *
 * @details This file contains the following functions and classes:
 * - `address_of`: get the address of an object.
 * - `get_buffer_helper`: get a buffer with the given length.
 * - `get_temporary_buffer`: get a temporary buffer with the given length.
 * - `release_temporary_buffer`: release a temporary buffer.
 * - `temporary_buffer`: a class for temporary buffer.
 * - `auto_ptr`: a class for auto pointer.
 */
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

/**
 * @brief Get the address of an object.
 *
 * @tparam T The type of the object.
 * @param value The object.
 * @return constexpr T* The address of the object.
 */
template <class T> constexpr T *address_of(T &value) noexcept { return &value; }

/**
 * @brief Allocate a buffer with the given length, and return the buffer and its
 * length.
 *
 * @details This function will try to allocate a buffer with the given length,
 * which means it will try to allocate a buffer of size `sizeof(T) * len`. If
 * the allocation fails, it will try to allocate a buffer of size `sizeof(T) *
 * len / 2`, and so on. If the allocation succeeds, it will return the buffer
 * and its length. If the allocation fails, it will return a pair of `nullptr`
 * and `0`.
 *
 * @tparam T The type of the buffer.
 * @param len The length of the buffer.
 * @return pair<T*, ptrdiff_t> The buffer and its length.
 */
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

/**
 * @brief Get a buffer with the given length.
 * @warning `len` means the number of elements, **not** the number of bytes.
 *
 * @tparam T The type of the buffer.
 * @param len The length of the buffer.
 * @return pair<T*, ptrdiff_t> The buffer and its length.
 */
template <class T> pair<T *, ptrdiff_t> get_temporary_buffer(ptrdiff_t len) {
  return get_buffer_helper(len, static_cast<T *>(0));
}

/**
 * @brief Get a buffer with the given length.
 * @warning `len` means the number of elements, **not** the number of bytes.
 *
 * @tparam T The type of the buffer.
 * @param len The length of the buffer.
 * @return pair<T*, ptrdiff_t> The buffer and its length.
 */
template <class T>
pair<T *, ptrdiff_t> get_temporary_buffer(ptrdiff_t len, T *) {
  return get_buffer_helper(len, static_cast<T *>(0));
}

/**
 * @brief Release a temporary buffer.
 *
 * @tparam T The type of the buffer.
 * @param ptr The buffer.
 */
template <class T> void release_temporary_buffer(T *ptr) { free(ptr); }

/**
 * @brief A class for temporary buffer.
 *
 * @tparam ForwardIter The type of the iterator.
 * @tparam T The type of the buffer.
 */
template <class ForwardIter, class T> class temporary_buffer {
private:
  ptrdiff_t original_len; // The length used for requesting memory.
  ptrdiff_t len;          // The actual length of the buffer allocated.
  T *buffer;              // The buffer.

public:
  /**
   * @brief Construct a new temporary buffer object
   *
   * @details This function will try to allocate a buffer with the length as
   * the distance between `first` and `last`. The `original_len` will be set to
   * the length of the buffer requested. If the allocation fails, the function
   * will try to allocate a buffer with the length as the half of the length.
   * If the allocation fails again, the function will try to allocate a buffer
   * with the length as the half of the length, and so on. After the allocation,
   * `len` will be set to the actual length of the buffer allocated.
   *
   * @param first The beginning of the range.
   * @param last The end of the range.
   */
  temporary_buffer(ForwardIter first, ForwardIter last);

  /**
   * @brief Destroy the temporary buffer object
   *
   * @details This function will destroy all the objects in the buffer, and
   * release the buffer.
   */
  ~temporary_buffer() {
    tiny_stl::destroy(buffer, buffer + len);
    free(buffer);
  }

public:
  /**
   * @brief Get the length of the buffer.
   *
   * @return ptrdiff_t The length of the buffer.
   */
  ptrdiff_t size() const noexcept { return len; }
  /**
   * @brief Get the length of the buffer requested.
   *
   * @return ptrdiff_t The length of the buffer requested.
   */
  ptrdiff_t requested_size() const noexcept { return original_len; }
  /**
   * @brief Get the beginning of the buffer.
   *
   * @return T* The beginning of the buffer.
   */
  T *begin() noexcept { return buffer; }
  /**
   * @brief Get the end of the buffer.
   *
   * @return T* The end of the buffer.
   */
  T *end() noexcept { return buffer + len; }

private:
  /**
   * @brief Allocate a buffer.
   * @note The actual working function in ctor
   */
  void allocate_buffer();
  /**
   * @brief Initialize the buffer with the given value, which can
   * be trivially default constructed.
   */
  void initialize_buffer(const T &, std::true_type) {}
  /**
   * @brief Initialize the buffer with the given value, which can
   * not be trivially default constructed
   *
   * @param value The value to be assigned
   */
  void initialize_buffer(const T &value, std::false_type) {
    tiny_stl::uninitialized_fill_n(buffer, len, value);
  }

private:
  /**
   * @brief Construct a new temporary buffer object with anther
   * buffer object
   * @note deleted
   */
  temporary_buffer(const temporary_buffer &) = delete;
  /**
   * @brief Assign another object to this object
   * @note deleted
   */
  void operator=(const temporary_buffer &) = delete;
};

template <class ForwardIter, class T>
temporary_buffer<ForwardIter, T>::temporary_buffer(ForwardIter first,
                                                   ForwardIter last) {
  try {
    len = tiny_stl::distance(first, last);
    allocate_buffer();
    if (len > 0) {
      initialize_buffer(*first, std::is_trivially_default_constructible<T>{});
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

/**
 * @brief Auto pointer class, used for manage a pointer
 *
 * @tparam T The type of the value
 */
template <class T> class auto_ptr {
public:
  using ele_type = T;

private:
  T *m_ptr;

public:
  /**
   * @brief Construct a new auto ptr object with a raw pointer
   *
   * @param p The pointer
   */
  explicit auto_ptr(T *p = nullptr) : m_ptr(p) {}
  /**
   * @brief Construct a new auto ptr object from another object
   * @node By passing another object to the copy constructor, the object
   * passed will give up the ownership of the pointer.
   *
   * @param other The other object
   */
  auto_ptr(auto_ptr &other) : m_ptr(other.release()) {}
  /**
   * @brief Construct a new auto ptr object from another object
   * @node By passing another object to the copy constructor, the object
   * passed will give up the ownership of the pointer.
   *
   * @tparam U The type of the other object
   * @param other The other object
   */
  template <class U> auto_ptr(auto_ptr<U> &other) : m_ptr(other.release()) {}

  /**
   * @brief Assign another object to this object
   * @note The object passed will give up the ownership of the pointer.
   *
   * @param other The other object
   * @return auto_ptr& This object
   */
  auto_ptr &operator=(auto_ptr &other) {
    if (this != &other) {
      delete m_ptr;
      m_ptr = other.release();
    }
    return *this;
  }
  /**
   * @brief Assign another object to this object
   * @note The object passed will give up the ownership of the pointer.
   *
   * @tparam U The type of the other object
   * @param other The other object
   * @return auto_ptr& This object
   */
  template <class U> auto_ptr &operator=(auto_ptr<U> &other) {
    if (this->get() != other.get()) {
      delete m_ptr;
      m_ptr = other.release();
    }
    return *this;
  }

  /**
   * @brief Destroy the auto ptr object, and delete the pointer
   * @warning Do not manually delete the pointer, or the pointer will be
   * deleted twice.
   */
  ~auto_ptr() { delete m_ptr; }

public:
  /**
   * @brief Dereference the pointer
   *
   * @return T& The reference of the value
   */
  T &operator*() const { return *m_ptr; }
  /**
   * @brief Get the pointer
   *
   * @return T* The pointer
   */
  T *operator->() const { return m_ptr; }

  /**
   * @brief Get the pointer
   *
   * @return T* The pointer
   */
  T *get() const { return m_ptr; }

  /**
   * @brief Release the pointer
   * @note The caller will take the ownership of the pointer.
   * @warning This function will not delete the pointer, so the caller should
   * delete the pointer.
   *
   * @return T* The pointer
   */
  T *release() {
    T *tmp = m_ptr;
    m_ptr = nullptr;
    return tmp;
  }

  /**
   * @brief Reset the pointer
   * @note This function will delete the pointer.
   *
   * @param p The pointer
   */
  void reset(T *p = nullptr) {
    if (m_ptr != p) {
      delete m_ptr;
      m_ptr = p;
    }
  }
};

} // namespace tiny_stl

#endif // ! INY_STL__INCLUDE__MEMORY_HPP
