#ifndef TINY_STL__TEST__TEST_ALGO_HELPER_HPP
#define TINY_STL__TEST__TEST_ALGO_HELPER_HPP

#include <gtest/gtest.h>

class TestAlgo : public ::testing::Test {
public:
  class vector {
  private:
    int *_data;
    size_t _size;
    size_t _capacity;

  public:
    vector() : _data(nullptr), _size(0), _capacity(0) {}
    vector(size_t n) : _data(new int[n]), _size(n), _capacity(n) {}
    vector(size_t n, int val) : _data(new int[n]), _size(n), _capacity(n) {
      for (size_t i = 0; i < _size; ++i) {
        _data[i] = val;
      }
    }
    vector(const std::initializer_list<int> &il)
        : _data(new int[il.size()]), _size(il.size()), _capacity(il.size()) {
      size_t i = 0;
      for (auto &val : il) {
        _data[i++] = val;
      }
    }
    vector(const vector &other)
        : _data(new int[other._size]), _size(other._size),
          _capacity(other._capacity) {
      for (size_t i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
      }
    }
    vector(vector &&other)
        : _data(other._data), _size(other._size), _capacity(other._capacity) {
      other._data = nullptr;
      other._size = 0;
      other._capacity = 0;
    }
    ~vector() { delete[] _data; }
    vector &operator=(const vector &other) {
      if (this != &other) {
        delete[] _data;
        _data = new int[other._size];
        _size = other._size;
        _capacity = other._capacity;
        for (size_t i = 0; i < _size; ++i) {
          _data[i] = other._data[i];
        }
      }
      return *this;
    }
    vector &operator=(vector &&other) {
      if (this != &other) {
        delete[] _data;
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
      }
      return *this;
    }
    int &operator[](size_t pos) { return _data[pos]; }
    const int &operator[](size_t pos) const { return _data[pos]; }
    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }
    void resize(size_t n) {
      if (n > _capacity) {
        reserve(n);
      }
      _size = n;
    }
    void reserve(size_t n) {
      if (n > _capacity) {
        int *new_data = new int[n];
        for (size_t i = 0; i < _size; ++i) {
          new_data[i] = _data[i];
        }
        delete[] _data;
        _data = new_data;
        _capacity = n;
      }
    }
    void push_back(int val) {
      if (_size == _capacity) {
        reserve(_capacity == 0 ? 1 : _capacity * 2);
      }
      _data[_size++] = val;
    }
    void pop_back() { --_size; }
    int *begin() { return _data; }
    int *end() { return _data + _size; }
    const int *begin() const { return _data; }
    const int *end() const { return _data + _size; }
    bool operator==(const vector &other) const {
      if (_size != other._size) {
        return false;
      }
      for (size_t i = 0; i < _size; ++i) {
        if (_data[i] != other._data[i]) {
          return false;
        }
      }
      return true;
    }
    bool operator!=(const vector &other) const { return !(*this == other); }
  };
  class list {
  private:
    struct node {
      int val;
      node *prev;
      node *next;
      node(int val = 0, node *prev = nullptr, node *next = nullptr)
          : val(val), prev(prev), next(next) {}
      bool operator==(const node &other) const { return val == other.val; }
    };
    node *_head;
    node *_tail;
    size_t _size;

  public:
    list() : _head(new node()), _tail(new node()), _size(0) {
      _head->next = _tail;
      _tail->prev = _head;
    }
    list(size_t n, int val) : _head(new node()), _tail(new node()), _size(0) {
      _head->next = _tail;
      _tail->prev = _head;
      for (size_t i = 0; i < n; ++i) {
        push_back(val);
      }
    }
    list(const std::initializer_list<int> &il)
        : _head(new node()), _tail(new node()), _size(0) {
      _head->next = _tail;
      _tail->prev = _head;
      for (auto &val : il) {
        push_back(val);
      }
    }
    list(const list &other)
        : _head(new node()), _tail(new node()), _size(other._size) {
      _head->next = _tail;
      _tail->prev = _head;
      for (node *p = other._head->next; p != other._tail; p = p->next) {
        push_back(p->val);
      }
    }
    list(list &&other)
        : _head(other._head), _tail(other._tail), _size(other._size) {
      other._head = nullptr;
      other._tail = nullptr;
      other._size = 0;
    }
    ~list() {
      while (_head != nullptr) {
        node *p = _head;
        _head = _head->next;
        delete p;
      }
    }
    list &operator=(const list &other) {
      if (this != &other) {
        while (_head->next != _tail) {
          node *p = _head->next;
          _head->next = p->next;
          delete p;
        }
        _size = other._size;
        for (node *p = other._head->next; p != other._tail; p = p->next) {
          push_back(p->val);
        }
      }
      return *this;
    }
    list &operator=(list &&other) {
      if (this != &other) {
        while (_head->next != _tail) {
          node *p = _head->next;
          _head->next = p->next;
          delete p;
        }
        _head = other._head;
        _tail = other._tail;
        _size = other._size;
        other._head = nullptr;
        other._tail = nullptr;
        other._size = 0;
      }
      return *this;
    };
    size_t size() const { return _size; }
    void push_back(int val) {
      node *p = new node(val, _tail->prev, _tail);
      _tail->prev->next = p;
      _tail->prev = p;
      ++_size;
    }
    void pop_back() {
      node *p = _tail->prev;
      p->prev->next = _tail;
      _tail->prev = p->prev;
      delete p;
      --_size;
    }
    int &back() { return _tail->prev->val; }
    const int &back() const { return _tail->prev->val; }
    int &front() { return _head->next->val; }
    const int &front() const { return _head->next->val; }
    void clear() {
      while (_head->next != _tail) {
        node *p = _head->next;
        _head->next = p->next;
        delete p;
      }
      _size = 0;
    }
    node *begin() { return _head->next; }
    node *end() { return _tail; }
    const node *begin() const { return _head->next; }
    const node *end() const { return _tail; }
  };
};

#endif // !TINY_STL__TEST__TEST_ALGO_HELPER_HPP