#ifndef TINY_STL__INCLUDE__VECTOR_HPP
#define TINY_STL__INCLUDE__VECTOR_HPP

#include <cstddef>
#include <initializer_list>

#include "algo.hpp"
#include "algobase.hpp"
#include "allocator.hpp"
#include "exception.hpp"
#include "iterator.hpp"
#include "memory.hpp"
#include "uninitialized.hpp"
#include "utility.hpp"

namespace tiny_stl {

#ifdef max
#pragma message("#undefining macro max")
#undef max
#endif

#ifdef min
#pragma message("#undefining macro min")
#undef min
#endif

template <class T> class vector {
  static_assert(!std::is_same_v<bool, typename std::remove_const_t<T>>,
                "vector<bool> is not supported");

public:
  using allocator_type = tiny_stl::allocator<T>;
  using data_allocator = tiny_stl::allocator<T>;

  using value_type = typename allocator_type::value_type;
  using pointer = typename allocator_type::pointer;
  using const_pointer = typename allocator_type::const_pointer;
  using reference = typename allocator_type::reference;
  using const_reference = typename allocator_type::const_reference;
  using size_type = typename allocator_type::size_type;
  using difference_type = typename allocator_type::difference_type;

  using iterator = value_type *;
  using const_iterator = const value_type *;
  using reverse_iterator = tiny_stl::reverse_iterator<iterator>;
  using const_reverse_iterator = tiny_stl::reverse_iterator<const_iterator>;

private:
  iterator _begin;
  iterator _end;
  iterator _cap;

public:
  vector() noexcept { try_init(); }

  explicit vector(size_type n) { fill_init(n, value_type()); }

  vector(size_type n, const value_type &value) { fill_init(n, value); }

  template <class Iter,
            typename std::enable_if_t<tiny_stl::is_input_iterator<Iter>::value,
                                      int>::type = 0>
  vector(Iter first, Iter last) {
    TINY_STL__DEBUG(!(last < first));
    range_init(first, last);
  }

  vector(const vector &other) { range_init(other._begin, other._end); }

  vector(const vector &&other) noexcept
      : _begin(other._begin), _end(other._end), _cap(other._cap) {
    other._begin = nullptr;
    other._end = nullptr;
    other._cap = nullptr;
  }

  vector(std::initializer_list<value_type> ilist) {
    range_init(ilist.begin(), ilist.end());
  }

  vector &operator=(const vector &other);
  vector &operator=(vector &&other) noexcept;

  vector &operator=(std::initializer_list<value_type> ilist) {
    vector tmp(ilist.begin(), ilist.end());
    swap(tmp);
    return *this;
  }

  ~vector() {
    destroy_and_recover(_begin, _end, _cap - _begin);
    _begin = _end = _cap = nullptr;
  }

public:
  iterator begin() noexcept { return _begin; }
  const_iterator begin() const noexcept { return _begin; }
  iterator end() noexcept { return _end; }
  const_iterator end() const noexcept { return _end; }

  reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const noexcept {
    return reverse_iterator(end());
  }
  reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const noexcept {
    return reverse_iterator(begin());
  }

  const_iterator cbegin() const noexcept { return begin(); }
  const_iterator cend() const noexcept { return end(); }
  const_reverse_iterator crbegin() const noexcept { return rbegin(); }
  const_reverse_iterator crend() const noexcept { return rend(); }

  bool empty() const noexcept { return _end == _begin; }
  size_type size() const noexcept {
    return static_cast<size_type>(_end - _begin);
  }
  size_type max_size() const noexcept {
    return static_cast<size_type>(-1) / sizeof(T);
  }
  size_type capacity() const noexcept {
    return static_cast<size_type>(_cap - _begin);
  }
  void reserve(size_type n);
  void shrink_to_fit();

  reference operator[](size_type n) {
    TINY_STL__DEBUG(n < size());
    return *(_begin + n);
  }
  const_reference operator[](size_type n) const {
    TINY_STL__DEBUG(n < size());
    return *(_begin + n);
  }
  reference at(size_type n) {
    THROW_OUT_OF_RANGE_IF(!(n < size()),
                          "vector<T>::at() subcript out of range");
    return (*this)[n];
  }
  const_reference at(size_type n) const {
    THROW_OUT_OF_RANGE_IF(!(n < size()),
                          "vector<T>::at() subcript out of range");
    return (*this)[n];
  }
  reference front() {
    TINY_STL__DEBUG(!empty());
    return *_begin;
  }
  const_reference front() const {
    TINY_STL__DEBUG(!empty());
    return *_begin;
  }
  reference back() {
    TINY_STL__DEBUG(!empty());
    return *(_end - 1);
  }
  const_reference back() const {
    TINY_STL__DEBUG(!empty());
    return *(_end - 1);
  }

  pointer data() noexcept { return _begin; }
  const_pointer data() const noexcept { return _begin; }

  void assign(size_type n, const value_type &value) { fill_assign(n, value); }

  template <class Iter, typename std::enable_if_t<
                            tiny_stl::is_input_iterator<Iter>::value, int> = 0>
  void assign(Iter first, Iter last) {
    TINY_STL__DEBUG(!(last < first));
    copy_assign(first, last, iterator_category(first));
  }
  void assign(std::initializer_list<value_type> ilist) {
    copy_assign(ilist.begin(), ilist.end(), tiny_stl::forward_iterator_tag{});
  }

  template <class... Args> iterator emplace(const_iterator pos, Args &&...args);
  template <class... Args> void emplace_back(Args &&...args);

  void push_back(const value_type &value);
  void push_back(value_type &&value) { emplace_back(tiny_stl::move(value)); }

  void pop_back();

  iterator insert(const_iterator pos, const value_type &value);
  iterator insert(const_iterator pos, value_type &&value) {
    return emplace(pos, tiny_stl::move(value));
  }
  iterator insert(const_iterator pos, size_type n, const value_type &value) {
    TINY_STL__DEBUG(pos >= begin() && pos <= end());
    return fill_insert(const_cast<iterator>(pos), n, value);
  }
  template <class Iter, typename std::enable_if_t<
                            tiny_stl::is_input_iterator<Iter>::value, int> = 0>
  void insert(const_iterator pos, Iter first, Iter last) {
    TINY_STL__DEBUG(pos >= begin() && pos <= end() && !(last < first));
    copy_insert(const_cast<iterator>(pos), first, last);
  }

  iterator erase(const_iterator pos);
  iterator erase(const_iterator first, const_iterator last);
  void clear() { erase(begin(), end()); }

  void resize(size_type new_size) { return resize(new_size, value_type{}); }
  void resize(size_type new_size, const value_type &value);

  void reverse() { tiny_stl::reverse(begin(), end()); }

  void swap(vector &other) noexcept;

private:
  void try_init() noexcept;

  void init_space(size_type size, size_type cap);

  void fill_init(size_type n, const value_type &value);

  template <class Iter> void range_init(Iter first, Iter last);

  void destroy_and_recover(iterator first, iterator last, size_type n);

  size_type get_new_cap(size_type add_size);

  void fill_assign(size_type n, const value_type &value);

  template <class InputIter>
  void copy_assign(InputIter first, InputIter last, input_iterator_tag);

  template <class ForwardIter>
  void copy_assign(ForwardIter first, ForwardIter last, forward_iterator_tag);

  template <class... Args>
  void reallocate_emplace(iterator pos, Args &&...args);
  void reallocate_insert(iterator pos, const value_type &value);

  iterator fill_insert(iterator pos, size_type n, const value_type &value);
  template <class InputIter>
  void copy_insert(iterator pos, InputIter first, InputIter last);

  void reinsert(size_type size);
};

template <class T> vector<T> &vector<T>::operator=(const vector &other) {
  if (this != &other) {
    const auto len = other.size();
    if (len > capacity()) {
      vector tmp(other.begin(), other.end());
      swap(tmp);
    } else if (size() >= len) {
      auto iter = tiny_stl::copy(other.begin(), other.end(), begin());
      data_allocator::destroy(iter, _end);
      _end = _begin + len;
    } else {
      tiny_stl::copy(other.begin(), other.begin() + size(), _begin);
      tiny_stl::uninitialized_copy(other.begin() + size(), other.end(), _end);
      _cap = _end = _begin + len;
    }
  }
  return *this;
}

template <class T> vector<T> &vector<T>::operator=(vector &&other) noexcept {
  destroy_and_recover(_begin, _end, _cap - _begin);
  _begin = other._begin;
  _end = other._end;
  _cap = other._cap;
  other._begin = nullptr;
  other._end = nullptr;
  other._cap = nullptr;
}

template <class T> void vector<T>::reserve(size_type n) {
  if (capacity() < n) {
    THROW_LENGTH_ERROR_IF(
        n > max_size(),
        "n can not be greater than max_size() in vector<T>::reserve(n)");
    const auto old_size = size();
    auto tmp = data_allocator::allocate(n);
    tiny_stl::uninitialized_move(_begin, _end, tmp);
    data_allocator::deallocate(_begin, _cap - _begin);
    _begin = tmp;
    _end = tmp + old_size;
    _cap = _begin + n;
  }
}

template <class T> void vector<T>::shrink_to_fit() {
  if (_end < _cap) {
    reinseret(size());
  }
}

template <class T>
template <class... Args>
typename vector<T>::iterator vector<T>::emplace(const_iterator pos,
                                                Args &&...args) {
  TINY_STL__DEBUG(pos >= begin() && pos <= end());
  iterator xpos = const_cast<iterator>(pos);
  const size_type n = xpos - _begin;
  if (_end != _cap && xpos == _end) {
    data_allocator::construct(tiny_stl::address_of(*_end),
                              tiny_stl::forward<Args>(args)...);
    ++_end;
  } else if (_end != _cap) {
    auto new_end = _end;
    data_allocator::construct(tiny_stl::address_of(*_end), *(_end - 1));
    ++new_end;
    tiny_stl::copy_backward(xpos, _end - 1, _end);
    *xpos = value_type(tiny_stl::forward<Args>(args)...);
    _end = new_end;
  } else {
    reallocate_emplace(xpos, tiny_stl::forward<Args>(args)...);
  }
  return begin() + n;
}

template <class T>
template <class... Args>
void vector<T>::emplace_back(Args &&...args) {
  if (_end < _cap) {
    data_allocator::construct(
        tiny_stl::address_of(*_end, tiny_stl::forward<Args>(args)...));
    ++_end;
  } else {
    reallocate_emplace(_end, tiny_stl::forward<Args>(args)...);
  }
}

template <class T> void vector<T>::push_back(const value_type &value) {
  if (_end == _cap) {
    data_allocator::construct(tiny_stl::address_of(*_end), value);
    ++_end;
  } else {
    reallocate_insert(_end, value);
  }
}

template <class T> void vector<T>::pop_back() {
  TINY_STL__DEBUG(!empty());
  data_allocator::destroy(_end - 1);
  --_end;
}

template <class T>
typename vector<T>::iterator vector<T>::insert(const_iterator pos,
                                               const value_type &value) {
  TINY_STL__DEBUG(pos >= begin() && pos <= end());
  iterator xpos = const_cast<iterator>(pos);
  const size_type n = pos - _begin;
  if (_end != _cap && xpos == _end) {
    data_allocator::construct(tiny_stl::address_of(*_end), value);
    ++_end;
  } else if (_end != _cap) {
    auto new_end = _end;
    data_allocator::construct(tiny_stl::address_of(*_end), *(_end - 1));
    ++new_end;
    auto value_copy = value;
    tiny_stl::copy_backward(xpos, _end - 1, _end);
    *xpos = tiny_stl::move(value_copy);
    _end = new_end;
  } else {
    reallocate_insert(xpos, value);
  }
  return _begin + n;
}

template <class T>
typename vector<T>::iterator vector<T>::erase(const_iterator pos) {
  TINY_STL__DEBUG(pos >= begin() && pos < end());
  iterator xpos = _begin + (pos - begin());
  tiny_stl::move(xpos + 1, _end, xpos);
  data_allocator::destroy(_end - 1);
  --_end;
  return xpos;
}

template <class T>
typename vector<T>::iterator vector<T>::erase(const_iterator first,
                                              const_iterator last) {
  TINY_STL__DEBUG(first >= begin() && last <= end() && !(last < first));
  const auto n = first - begin();
  iterator erase_begin = _begin;
  tiny_stl::advance(erase_begin, tiny_stl::distance(_begin, first));
  data_allocator::destroy(
      tiny_stl::move(erase_begin + (last - first), _end, erase_begin), _end);
  _end = _end - (last - first);
  return _begin + n;
}

template <class T>
void vector<T>::resize(size_type new_size, const value_type &value) {
  if (new_size < size()) {
    erase(begin() + new_size, end());
  } else {
    insert(end(), new_size - size(), value);
  }
}

template <class T> void vector<T>::swap(vector &other) noexcept {
  if (this != &other) {
    tiny_stl::swap(_begin, other._begin);
    tiny_stl::swap(_end, other._end);
    tiny_stl::swap(_cap, other._cap);
  }
}

template <class T> void vector<T>::try_init() noexcept {
  try {
    _begin = data_allocator::allocate(16);
    _end = _begin;
    _cap = _begin + 16;
  } catch (...) {
    _begin = nullptr;
    _end = nullptr;
    _cap = nullptr;
  }
}

template <class T> void vector<T>::init_space(size_type size, size_type cap) {
  try {
    _begin = data_allocator::allocate(cap);
    _end = _begin + size;
    _cap = _begin + cap;
  } catch (...) {
    _begin = nullptr;
    _end = nullptr;
    _cap = nullptr;
    throw;
  }
}

template <class T>
void vector<T>::fill_init(size_type n, const value_type &value) {
  const size_type init_size = tiny_stl::max(static_cast<size_type>(16), n);
  init_space(n, init_size);
  tiny_stl::uninitialized_fill_n(_begin, n, value);
}

template <class T>
template <class Iter>
void vector<T>::range_init(Iter first, Iter last) {
  const size_type len = tiny_stl::distance(first, last);
  const size_type init_size = tiny_stl::max(len, static_cast<size_type>(16));
  init_space(len, init_size);
  tiny_stl::uninitialized_copy(first, last, _begin);
}

template <class T>
void vector<T>::destroy_and_recover(iterator first, iterator last,
                                    size_type n) {
  data_allocator::destroy(first, last);
  data_allocator::deallocate(first, n);
}

template <class T>
typename vector<T>::size_type vector<T>::get_new_cap(size_type add_size) {
  const auto old_size = capacity();
  THROW_LENGTH_ERROR_IF(old_size > max_size() - add_size,
                        "vector<T>'s size too big");
  if (old_size > max_size() - old_size / 2) {
    return old_size + add_size > max_size() - 16 ? old_size + add_size
                                                 : old_size + add_size + 16;
  }
  const size_type new_size =
      old_size == 0
          ? tiny_stl::max(add_size, static_cast<size_type>(16))
          : tiny_stl::max(old_size + old_size / 2, old_size + add_size);
  return new_size;
}

template <class T>
void vector<T>::fill_assign(size_type n, const value_type &value) {
  if (n > capacity()) {
    vector tmp(n, value);
    swap(tmp);
  } else if (n > size()) {
    tiny_stl::fill(begin(), end(), value);
    _end = tiny_stl::uninitialized_fill(_end, n - size(), value);
  } else {
    erase(tiny_stl::fill_n(_begin, n, value), _end);
  }
}

template <class T>
template <class InputIter>
void vector<T>::copy_assign(InputIter first, InputIter last,
                            input_iterator_tag) {
  auto cur = _begin;
  for (; first != last && cur != _end; ++first, ++cur) {
    *cur = *first;
  }
  if (first == last) {
    erase(cur, _end);
  } else {
    insert(_end, first, last);
  }
}

template <class T>
template <class ForwardIter>
void vector<T>::copy_assign(ForwardIter first, ForwardIter last,
                            forward_iterator_tag) {
  const size_type len = tiny_stl::distance(first, last);
  if (len > capacity()) {
    vector tmp(first, last);
    swap(tmp);
  } else if (size() >= len) {
    auto new_end = tiny_stl::copy(first, last, _begin);
    data_allocator::destroy(new_end, _end);
    _end = new_end;
  } else {
    auto mid = first;
    tiny_stl::advance(mid, size());
    tiny_stl::copy(first, mid, _begin);
    auto new_end = tiny_stl::uninitialized_copy(mid, last, _end);
    _end = new_end;
  }
}

template <class T>
template <class... Args>
void vector<T>::reallocate_emplace(iterator pos, Args &&...args) {
  const auto new_size = get_new_cap(1);
  auto new_begin = data_allocator::allocate(new_size);
  auto new_end = new_begin;
  try {
    new_end = tiny_stl::uninitialized_move(_begin, pos, new_begin);
    data_allocator::construct(tiny_stl::address_of(*new_end),
                              tiny_stl::forward<Args>(args)...);
    ++new_end;
    new_end = tiny_stl::uninitialized_move(pos, _end, new_end);
  } catch (...) {
    data_allocator::destroy(new_begin, new_size);
  }
  destroy_and_recover(_begin, _end, _cap - _begin);
  _begin = new_begin;
  _end = new_end;
  _cap = new_begin + new_size;
}

template <class T>
void vector<T>::reallocate_insert(iterator pos, const value_type &value) {
  const auto new_size = get_new_cap(1);
  auto new_begin = data_allocator::allocate(new_size);
  auto new_end = new_begin;
  const value_type &value_copy = value;
  try {
    new_end = tiny_stl::uninitialized_move(_begin, pos, new_begin);
    data_allocator::construct(tiny_stl::address_of(*new_end), value_copy);
    ++new_end;
    new_end = tiny_stl::uninitialized_move(pos, _end, new_end);
  } catch (...) {
    data_allocator::deallocate(new_begin, new_size);
    throw;
  }
  destroy_and_recover(_begin, _end, _cap - _begin);
  _begin = new_begin;
  _end = new_end;
  _cap = new_begin + new_size;
}

template <class T>
typename vector<T>::iterator vector<T>::fill_insert(iterator pos, size_type n,
                                                    const value_type &value) {
  if (n == 0) {
    return pos;
  }
  const size_type xpos = pos - _begin;
  const value_type value_copy = value;
  if (static_cast<size_type>(_cap - _end) >= n) {
    const size_type after_elems = _end - pos;
    auto old_end = _end;
    if (after_elems > n) {
      tiny_stl::uninitialized_copy(_end - n, _end, _end);
      _end += n;
      tiny_stl::move_backward(pos, old_end - n, old_end);
      tiny_stl::uninitialized_fill_n(pos, n, value_copy);
    } else {
      _end = tiny_stl::uninitialized_fill_n(_end, n - after_elems, value_copy);
      _end = tiny_stl::uninitialized_move(pos, old_end, _end);
      tiny_stl::uninitialized_fill_n(pos, after_elems, value_copy);
    }
  } else {
    const auto new_size = get_new_cap(n);
    auto new_begin = data_allocator::allocate(new_size);
    auto new_end = new_begin;
    try {
      new_end = tiny_stl::uninitialized_move(_begin, pos, new_begin);
      new_end = tiny_stl::uninitialized_fill_n(new_end, n, value);
      new_end = tiny_stl::uninitialized_move(pos, _end, new_end);
    } catch (...) {
      destroy_and_recover(new_begin, new_end, new_size);
      throw;
    }
    data_allocator::deallocate(_begin, _cap - _begin);
    _begin = new_begin;
    _end = new_end;
    _cap = _begin + new_size;
  }
  return _begin + xpos;
}

template <class T>
template <class IIter>
void vector<T>::copy_insert(iterator pos, IIter first, IIter last) {
  if (first == last) {
    return;
  }
  const auto n = tiny_stl::distance(first, last);
  if ((_cap - _end) >= n) {
    const auto after_elems = _end - pos;
    auto old_end = _end;
    if (after_elems > n) {
      _end = tiny_stl::uninitialized_copy(_end - n, _end, _end);
      tiny_stl::move_backward(pos, old_end - n, old_end);
      tiny_stl::uninitialized_copy(first, last, pos);
    } else {
      auto mid = first;
      tiny_stl::advance(mid, after_elems);
      _end = tiny_stl::uninitialized_copy(mid, last, _end);
      _end = tiny_stl::uninitialized_move(pos, old_end, _end);
      tiny_stl::uninitialized_copy(first, mid, pos);
    }
  } else {
    const auto new_size = get_new_cap(n);
    auto new_begin = data_allocator::allocate(new_size);
    auto new_end = new_begin;
    try {
      new_end = tiny_stl::uninitialized_move(_begin, pos, new_begin);
      new_end = tiny_stl::uninitialized_copy(first, last, new_end);
      new_end = tiny_stl::uninitialized_move(pos, _end, new_end);
    } catch (...) {
      destroy_and_recover(new_begin, new_end, new_size);
      throw;
    }
    data_allocator::deallocate(_begin, _cap - _begin);
    _begin = new_begin;
    _end = new_end;
    _cap = _begin + new_size;
  }
}

template <class T> void vector<T>::reinsert(size_type size) {
  auto new_begin = data_allocator::allocate(size);
  try {
    tiny_stl::uninitialized_move(_begin, _end, new_begin);
  } catch (...) {
    data_allocator::deallocate(new_begin, size);
    throw;
  }
  data_allocator::deallocate(_begin, _cap - _begin);
  _begin = new_begin;
  _end = _begin + size;
  _cap = _begin + size;
}

template <class T>
bool operator==(const vector<T> &left, const vector<T> &right) {
  return left.size() == right.size() &&
         tiny_stl::equal(left.begin(), left.end(), right.begin());
}

template <class T>
bool operator<(const vector<T> &left, const vector<T> &right) {
  return tiny_stl::lexicographical_compare(left.begin(), left.end(),
                                           right.begin(), right.end());
}

template <class T>
bool operator!=(const vector<T> &left, const vector<T> &right) {
  return !(left == right);
}

template <class T>
bool operator>(const vector<T> &left, const vector<T> &right) {
  return right < left;
}

template <class T>
bool operator<=(const vector<T> &left, const vector<T> &right) {
  return !(right < left);
}

template <class T>
bool operator>=(const vector<T> &left, const vector<T> &right) {
  return !(left < right);
}

template <class T> void swap(vector<T> &left, vector<T> &right) {
  left.swap(right);
}

} // namespace tiny_stl

#endif // !TINY_STL__INCLUDE__VECTOR_HPP
