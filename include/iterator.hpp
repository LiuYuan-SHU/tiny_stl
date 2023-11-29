/**
 * @file iterator.hpp
 * @author Liu Yuan (2787141886@qq.com)
 * @brief This file contains some iterator related classes
 *
 * @details This file contains some iterator related classes, including:
 * - iterator tags
 *    - `input_iterator_tag`
 *    - `output_iterator_tag`
 *    - `forward_iterator_tag`
 *    - `bidirectional_iterator_tag`
 *    - `random_access_iterator_tag`
 * - iterator class implementation `iterator`
 * - iterator traits extraction mechanism
 *    - `has_iterator_cat`
 *    - `iterator_traits_impl`
 *    - `iterator_traits_helper`
 *    - `iterator_traits`
 *    - `has_iterator_cat_of`
 * - iterator category check
 *    - `is_input_iterator`
 *    - `is_output_iterator`
 *    - `is_forward_iterator`
 *    - `is_bidirectional_iterator`
 *    - `is_random_iterator`
 *    - `is_iterator`
 * - iterator traits helper functions
 *    - `iterator_category`
 *    - `distance_type`
 *    - `value_type`
 * - iterator operations
 *    - `distance_dispatch`
 *    - `distance`
 *    - `advance_dispatch`
 *    - `advance`
 * - reverse iterator
 *    - `reverse_iterator`
 * - reverse iterator operations
 */
#ifndef TINY_STL__INCLUDE__ITERATOR_HPP
#define TINY_STL__INCLUDE__ITERATOR_HPP

#include <cstddef>
#include <type_traits>

#include "type_traits.hpp"

namespace tiny_stl {

/**
 * @brief Input iterator tag
 *
 * @details An iterator with this tag can only be used for reading.
 */
struct input_iterator_tag {};

/**
 * @brief Output iterator tag
 *
 * @details An iterator with this tag can only be used for writing.
 */
struct output_iterator_tag {};

/**
 * @brief Forward iterator tag
 *
 * @details An iterator with this tag can be used for both reading and writing,
 * and it can iterate a range `[from, to)` from left to right.
 */
struct forward_iterator_tag : public input_iterator_tag {};

/**
 * @brief Bidirectional iterator tag
 *
 * @details An iterator with this tag can be used for both reading and writing,
 * and it can iterate a range `[from, to)` from both directions.
 */
struct bidirectional_iterator_tag : public forward_iterator_tag {};

/**
 * @brief Random access iterator tag
 *
 * @details An iterator with this tag can be used for both reading and writing,
 * and it can iterate a range `[from, to)` randomly.
 */
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T *, class Reference = T &>
struct iterator {
  using iterator_category = Category;
  using value_type = T;
  using pointer = Pointer;
  using reference = Reference;
  using difference_type = Distance;
};

/**
 * @brief Judge if `T` has iterator category
 *
 * @details The `test` functions in the class are not implemented, they are
 * declared to use SFINAE(*Substitution Failure Is Not An Error*) mechanism
 *  to check if type `T` has `iterator_category` filed. If `T` has the filed,
 *  `char test(typename U::iterator_category* = 0)` will be used during the
 *  compile time; otherwise, `static two test(...)` will be used. Thus, the
 *  value of `value` will be ensured.
 *
 * @tparam T The type to be judged.
 */
template <class T> struct has_iterator_cat {
private:
  /**
   * @brief Struct has different size with `char`
   *
   * @details Struct `two` has two `char` fields, which takes two bytes.
   * Thus, if the `two test(...)` is used, `sizeof(test<T>(0))` will be
   * `2`, which is different to `sizeof(char)`
   */
  struct two {
    char a;
    char b;
  };

  /**
   * @brief Default function to accept all kinds of parameter.
   *
   * @tparam U The template parameter different from `T`.
   * @param ... Whatever kinds of parameter.
   * @return two The struct has different size from `char`
   */
  template <class U> static two test(...);

  /**
   * @brief Overloaded function to accept `iterator` with `iterator_category`
   * field.
   *
   * @tparam U The template parameter different from `T`
   * @return char Just declared to execute `sizeof(test<T>(0))`
   */
  template <class U> static char test(typename U::iterator_category * = 0);

public:
  /**
   * @brief Represent if the template parameter `T` has field
   * `iterator_category`
   */
  static constexpr bool value = sizeof(test<T>(0)) == sizeof(char);
};

/**
 * @brief Iterator traits implementation.
 *
 * @details This is the class template which implements the mechanism to extract
 * iterator's traits
 *
 * @tparam Iterator The type of the extracted iterator
 * @tparam bool Additional template parameter for partial specialization
 */
template <class Iterator, bool> struct iterator_traits_impl {};

/**
 * @brief The partial specialization of struct `iterator_traits_impl`, which
 * truly extract the traits of the iterator.
 *
 * @tparam Iterator The type of the iterator
 */
template <class Iterator> struct iterator_traits_impl<Iterator, true> {
  using iterator_category = typename Iterator::iterator_category;
  using value_type = typename Iterator::value_type;
  using pointer = typename Iterator::pointer;
  using reference = typename Iterator::reference;
  using difference_type = typename Iterator::difference_type;
};

/**
 * @brief Iterator trait helper function.
 *
 * @details This is the class template which implements one more mechanism to
 * protect the program. By default, this layer does nothing and won't execute
 * the `iterator_traits_impl` part.
 *
 * @tparam Iterator The type of the iterator to be extracted
 * @tparam bool The template parameter for partial specialization
 */
template <class Iterator, bool> struct iterator_traits_helper {};

/**
 * @brief Partial specialized template function to add one more protection
 *
 * @details The partial specialization of struct `iterator_traits_helper`, which
 * adds one more protection and use `iterator_traits_impl` to extract the traits
 * of iterator of type `Iterator`. This layer checks if
 * `Iterator::iterator_category` is convertible to `input_iterator_tag` or
 * `output_iterator_tag`, which is an additional protection.
 *
 * @tparam Iterator The type of the iterator
 */
template <class Iterator>
struct iterator_traits_helper<Iterator, true>
    : public iterator_traits_impl<
          Iterator,
          std::is_convertible_v<typename Iterator::iterator_category,
                                input_iterator_tag> ||
              std::is_convertible_v<typename Iterator::iterator_category,
                                    output_iterator_tag>> {};

/**
 * @brief Top level of iterator trait extraction mechanism to extract the traits
 * of the type `Iterator`
 *
 * @details
 *    1. `has_iterator_cat` checks if type `Iterator` has `iterator_category`
 * filed \n
 *    2. `iterator_traits_helper` checks if type `Iterator::iterator_category`
 * can be converted into `input_iterator_tag` or `output_iterator_tag` \n
 *    3. Extract traits
 *
 * @tparam Iterator The type to be extracted
 */
template <class Iterator>
struct iterator_traits
    : public iterator_traits_helper<Iterator,
                                    has_iterator_cat<Iterator>::value> {};

/**
 * @brief The partial specialization edition for native pointer
 *
 * @tparam T The type pointed by the pointer
 */
template <class T> struct iterator_traits<T *> {
  using iterator_category = random_access_iterator_tag;
  using value_type = T;
  using pointer = T *;
  using reference = T &;
  using difference_type = ptrdiff_t;
};

/**
 * @brief The partial specialization edition for const native pointer
 * @attention Please check [this
 * question](https://stackoverflow.com/questions/12819405/why-is-stditerator-traitsvalue-type-non-const-even-for-a-const-iterator)
 * to check why `value_type` is `T` instead of `const T`
 * @tparam T The type pointed by the pointer
 */
template <class T> struct iterator_traits<const T *> {
  using iterator_category = random_access_iterator_tag;
  using value_type = T;
  using pointer = const T *;
  using reference = const T &;
  using difference_type = ptrdiff_t;
};

/**
 * @brief Check if iterator of type `T` can be converted into an iterator with
 * `iterator_category` of value `U`
 * @details This class is inherited from class `compile_time_constant_bool`,
 * which is the partial specialization of `integral_constant`, which means, you
 * can use `has_iterator_cat_of::value` to get a value of type `bool` to know
 * if iterator of type `T` can be converted into an iterator with
 * `iterator_category` of value `U` during compile time.
 *
 * @warning Please notice that, type `T` is an iterator type while type 'U' is
 * an iterator tag, which means, you should call this function like:
 * @code{.cpp}
 * tiny_stl::iterator<random_access_iterator_tag, int> ite1;
 * tiny_stl::iterator<bidirectional_iterator_tag, int> ite2;
 * tiny_stl::iterator<output_iterator_tag, int> ite3;
 * std::cout << tiny_stl::has_iterator_cat_of<
 *                  decltype(ite1), decltype(ite2)::iterator_category>::value
 *           << std::endl;
 * std::cout << tiny_stl::has_iterator_cat_of<
 *                  decltype(ite1), decltype(ite3)::iterator_category>::value
 *           << std::endl;
 * @endcode
 * Excepted output:
 * @code
 * 1
 * 0
 * @endcode
 *
 * @tparam T The iterator to be converted from
 * @tparam U The iterator tag to be converted to
 * @tparam bool If iterator of type `T` has field `iterator_category`
 */
template <class T, class U, bool = has_iterator_cat<iterator_traits<T>>::value>
struct has_iterator_cat_of
    : public compile_time_constant_bool<std::is_convertible_v<
          typename iterator_traits<T>::iterator_category, U>> {};

/**
 * @brief Partial specialization edition fo `has_iterator_cat_of` to handle
 * false condition
 *
 * @tparam T The type of iterator
 * @tparam U The category of iterator
 */
template <class T, class U>
struct has_iterator_cat_of<T, U, false> : public false_type {};

/**
 * @brief Check if `Iter` has category of `input_iterator_tag`
 *
 * @tparam Iter The type of iterator
 */
template <class Iter>
struct is_input_iterator
    : public has_iterator_cat_of<Iter, input_iterator_tag> {};

/**
 * @brief Check if `Iter` has category of `output_iterator_tag`
 *
 * @tparam Iter The type of iterator
 */
template <class Iter>
struct is_output_iterator
    : public has_iterator_cat_of<Iter, output_iterator_tag> {};

/**
 * @brief Check if `Iter` has category of `forward_iterator_tag`
 *
 * @tparam Iter The type of iterator
 */
template <class Iter>
struct is_forward_iterator
    : public has_iterator_cat_of<Iter, forward_iterator_tag> {};

/**
 * @brief Check if `Iter` has category of `bidirectional_iterator_tag`
 *
 * @tparam Iter The type of iterator
 */
template <class Iter>
struct is_bidirectional_iterator
    : public has_iterator_cat_of<Iter, bidirectional_iterator_tag> {};

/**
 * @brief Check if `Iter` has category of `random_access_iterator_tag`
 *
 * @tparam Iter The type of iterator
 */
template <class Iter>
struct is_random_iterator
    : public has_iterator_cat_of<Iter, random_access_iterator_tag> {};

/**
 * @brief Check if `Iter` is iterator
 * @details All categories of iterators can be converted into either
 * `input_iterator_tag` or `output_iterator_tag`
 *
 * @tparam Iter The type to be checked
 */
template <class Iter>
struct is_iterator
    : public compile_time_constant_bool<
          has_iterator_cat_of<Iter, input_iterator_tag>::value ||
          has_iterator_cat_of<Iter, output_iterator_tag>::value> {};

/**
 * @brief Get the `iterator_category` field of iterator of type `Iter`
 *
 * @tparam Iter The type of iterator
 * @return iterator_traits<Iter>::iterator_category The category of the iterator
 */
template <class Iter>
typename iterator_traits<Iter>::iterator_category
iterator_category(const Iter &) {
  using Category = typename iterator_traits<Iter>::iterator_category;
  return Category();
}

/**
 * @brief The `difference_type*` of the iterator of type `Iter`
 * @warning Return type is a pointer, which means usually `ptrdiff_t*` instead
 * of `ptrdiff_t`
 *
 * @tparam Iter The type of iterator
 * @return iterator_traits<Iter>::difference_type* The `difference_type*` of the
 * iterator
 */
template <class Iter>
typename iterator_traits<Iter>::difference_type *distance_type(const Iter &) {
  using Distance = typename iterator_traits<Iter>::distance_type *;
  return Distance(0);
}

/**
 * @brief The `value_type*` of the iterator of type `Iter`
 * @warning Return type is a pointer, instead of `value_type`
 *
 * @tparam Iter The type of iterator
 * @return iterator_traits<Iter>::value_type* The `value_type*` of the iterator
 */
template <class Iter>
typename iterator_traits<Iter>::value_type *value_type(const Iter &) {
  using Value = typename iterator_traits<Iter>::value_type *;
  return Value(0);
}

/**
 * @brief Get the distance between two input iterators
 *
 * @tparam InputIterator Iterator with `iterator_category` of
 * `input_iterator_tag`
 * @param first The left side of range `[first, last)`
 * @param last The right side of range `[first, last)`
 * @return iterator_traits<InputIterator>::difference_type The distance between
 * `first` and `last`
 * @
 */
template <class InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance_dispatch(InputIterator first, InputIterator last, input_iterator_tag) {
  typename iterator_traits<InputIterator>::difference_type n = 0;
  while (first != last) {
    ++first;
    ++n;
  }

  return n;
}

/**
 * @brief Get the distance between two random iterators
 *
 * @tparam RandomIterator Iterator with `iterator_category` of type
 * `random_access_iterator_tag`
 * @param first The left side of range `[first, last)`
 * @param last The right side of range `[first, last)`
 * @return iterator_traits<RandomIterator>::difference_type The distance between
 * `first` and `last`
 */
template <class RandomIterator>
typename iterator_traits<RandomIterator>::difference_type
distance_dispatch(RandomIterator first, RandomIterator last,
                  random_access_iterator_tag) {
  return last - first;
}

/**
 * @brief Get the distance between two input iterators, this is a general API,
 * handles all iterators of category inherited from `input_iterator_tag`
 *
 * @tparam InputIterator Iterator of category inherited from
 * `input_iterator_tag`
 * @param first The left side of range `[first, last)`
 * @param last The right side of range `[first, last)`
 * @return iterator_traits<InputIterator>::difference_type The distance between
 * `first` and `last`
 */
template <class InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last) {
  return distance_dispatch(first, last, iterator_category(first));
}

/**
 * @brief `input_iterator_tag` edition for `advance` function
 * @warning `n >= 0` is required
 * @tparam InputIterator Iterator of category `input_iterator_tag`
 * @tparam Distance The distance to advance
 * @param iter The reference of iterator instance
 * @param n The steps to advance
 */
template <class InputIterator, class Distance>
void advance_dispatch(InputIterator &iter, Distance n, input_iterator_tag) {
  while (n--) {
    ++iter;
  }
}

/**
 * @brief `bidirectional_iterator_tag` edition for `advance` function
 *
 * @tparam BidirectionalIterator Iterator of category
 * `bidirectional_iterator_tag`
 * @tparam Distance The distance to advance
 * @param iter The reference of iterator instance
 * @param n The steps to advance
 */
template <class BidirectionalIterator, class Distance>
void advance_dispatch(BidirectionalIterator &iter, Distance n,
                      bidirectional_iterator_tag) {
  if (n >= 0)
    while (n--)
      ++iter;
  else
    while (n++)
      --iter;
}

/**
 * @brief `random_access_iterator_tag` edition for `advance` function
 *
 * @tparam RandomIterator Iterator of category `random_access_iterator_tag`
 * @tparam Distance The distance to advance
 * @param iter The reference of iterator instance
 * @param n The steps to advance
 */
template <class RandomIterator, class Distance>
void advance_dispatch(RandomIterator &iter, Distance n,
                      random_access_iterator_tag) {
  iter += n;
}

/**
 * @brief The general `advance` function, calling different `advance_dispatch`
 * according to the category of `Iter`
 *
 * @tparam Iter The type of the iterator to advance
 * @tparam Distance The distance to advance
 * @param iter The reference of iterator instance
 * @param n The steps to advance
 */
template <class Iter, class Distance> void advance(Iter &iter, Distance n) {
  advance_dispatch(iter, n, iterator_category(iter));
}

/**
 * @brief Reverse iterator class
 * @details This class implements reverse iterator. It keeps an ordinary
 * iterator inside, and modify it along with different operations
 *
 * @tparam Iterator The type of the iterator to be reversed
 */
template <class Iterator> class reverse_iterator {
private:
  /**
   * @brief The instance of the iterator to be reversed
   */
  Iterator current;

public:
  using iterator_category =
      typename iterator_traits<Iterator>::iterator_category;
  using value_type = typename iterator_traits<Iterator>::value_type;
  using difference_type = typename iterator_traits<Iterator>::difference_type;
  using pointer = typename iterator_traits<Iterator>::pointer;
  using reference = typename iterator_traits<Iterator>::reference;
  using iterator_type = Iterator; // The type of the iterator to be reversed
  using self = reverse_iterator<Iterator>; // The type of the reverse iterator

public:
  /**
   * @brief Construct a new reverse iterator object
   */
  reverse_iterator() {}

  /**
   * @brief Construct a new reverse iterator object with an ordinary iterator
   *
   * @param iter The iterator to be reversed
   */
  explicit reverse_iterator(iterator_type iter) : current(iter) {}

  /**
   * @brief Construct a new reverse iterator object with another reverse
   * iterator
   *
   * @param rhs The reverse iterator to be copied
   */
  reverse_iterator(const self &rhs) : current(rhs.current) {}

public:
  /**
   * @brief Get the base iterator object
   *
   * @return iterator_type The type of base iterator
   */
  inline iterator_type base() const { return current; }

  /**
   * @brief Get the reference of the element pointed by the iterator
   * @note As for why `--tmp` is used before de-reference operation, please
   * check [this](https://stackoverflow.com/a/74161268/16941344)
   *
   * @return reference The reference of the element pointed by the iterator
   */
  inline reference operator*() const {
    auto tmp = current;
    return *--tmp;
  }

  /**
   * @brief Get the pointer of the element pointed by the iterator
   *
   * @return pointer The pointer of the element pointed by the iterator
   */
  inline pointer operator->() const { return &(operator*()); }

  /**
   * @brief Before-increment operator
   *
   * @return self& The iterator after increment
   */
  inline self &operator++() {
    --current;
    return *this;
  }

  /**
   * @brief After-increment operator
   *
   * @return self The iterator before increment
   */
  inline self operator++(int) {
    self tmp = *this;
    --current;
    return tmp;
  }

  /**
   * @brief Before-decrement operator
   *
   * @return self& The iterator after decrement
   */
  inline self &operator--() {
    ++current;
    return *this;
  }

  /**
   * @brief After-decrement operator
   *
   * @return self The iterator before decrement
   */
  inline self operator--(int) {
    self tmp = *this;
    ++current;
    return tmp;
  }

  /**
   * @brief Self-increment operator, make the iterator move forward `n` steps
   *
   * @param n The steps to move forward
   * @return self& The iterator after moving forward `n` steps
   */
  inline self &operator+=(difference_type n) {
    current -= n;
    return *this;
  }

  /**
   * @brief Increment operator, make the iterator move forward `n` steps, return
   * a new iterator
   *
   * @param n The steps to move forward
   * @return self The iterator before moving forward `n` steps
   */
  inline self operator+(difference_type n) const { return self(current - n); }

  /**
   * @brief Self-decrement operator, make the iterator move backward `n` steps
   *
   * @param n The steps to move backward
   * @return self& The iterator after moving backward `n` steps
   */
  inline self &operator-=(difference_type n) {
    current += n;
    return *this;
  }

  /**
   * @brief Decrement operator, make the iterator move backward `n` steps,
   * return
   *
   * @param n The steps to move backward
   * @return self The iterator before moving backward `n` steps
   */
  inline self operator-(difference_type n) const { return self(current + n); }

  /**
   * @brief Index operator, return the reference of the element pointed by the
   * iterator
   *
   * @param n The index of the element
   * @return reference The reference of the element
   */
  inline reference operator[](difference_type n) const { return *(*this + n); }
};

/**
 * @brief Operator'-' for reverse iterator
 *
 * @tparam Iterator The original iterator type
 * @param lhs The left side of the operator
 * @param rhs The right side of the operator
 * @return reverse_iterator<Iterator>::difference_type The distance between two
 * iterators
 */
template <class Iterator>
typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator> &lhs,
          const reverse_iterator<Iterator> &rhs) {
  return rhs.base() - lhs.base();
}

/**
 * @brief Compare operator for reverse iterator, return `true` if two iterators
 * are equal
 *
 * @tparam Iterator The original iterator type
 * @param lhs The left side of the operator
 * @param rhs The right side of the operator
 * @return true The two iterators are equal
 * @return false The two iterators are not equal
 */
template <class Iterator>
bool operator==(const reverse_iterator<Iterator> &lhs,
                const reverse_iterator<Iterator> &rhs) {
  return lhs.base() == rhs.base();
}

/**
 * @brief Compare operator for reverse iterator, return `true` if left iterator
 * is smaller than right iterator
 *
 * @tparam Iterator The original iterator type
 * @param lhs The left side of the operator
 * @param rhs The right side of the operator
 * @return true The left iterator is smaller than right iterator
 * @return false The left iterator is not smaller than right iterator
 */
template <class Iterator>
bool operator<(const reverse_iterator<Iterator> &lhs,
               const reverse_iterator<Iterator> &rhs) {
  return lhs.base() > rhs.base();
}

/**
 * @brief Compare operator for reverse iterator, return `true` if two iterators
 * are not equal
 *
 * @tparam Iterator The original iterator type
 * @param lhs The left side of the operator
 * @param rhs The right side of the operator
 * @return true The two iterators are not equal
 * @return false The two iterators are equal
 */
template <class Iterator>
bool operator!=(const reverse_iterator<Iterator> &lhs,
                const reverse_iterator<Iterator> &rhs) {
  return !(lhs == rhs);
}

/**
 * @brief Compare operator for reverse iterator, return `true` if left iterator
 * is greater than right iterator
 *
 * @tparam Iterator The original iterator type
 * @param lhs The left side of the operator
 * @param rhs The right side of the operator
 * @return true The left iterator is greater than right iterator
 * @return false The left iterator is not greater than right iterator
 */
template <class Iterator>
bool operator>(const reverse_iterator<Iterator> &lhs,
               const reverse_iterator<Iterator> &rhs) {
  return lhs.base() < rhs.base();
}

/**
 * @brief Compare operator for reverse iterator, return `true` if left iterator
 * is smaller than or equal to right iterator
 *
 * @tparam Iterator The original iterator type
 * @param lhs The left side of the operator
 * @param rhs The right side of the operator
 * @return true The left iterator is smaller than or equal to right iterator
 * @return false The left iterator is not smaller than or equal to right
 * iterator
 */
template <class Iterator>
bool operator<=(const reverse_iterator<Iterator> &lhs,
                const reverse_iterator<Iterator> &rhs) {
  return !(lhs > rhs);
}

/**
 * @brief Compare operator for reverse iterator, return `true` if left iterator
 * is greater than or equal to right iterator
 *
 * @tparam Iterator The original iterator type
 * @param lhs The left side of the operator
 * @param rhs The right side of the operator
 * @return true The left iterator is greater than or equal to right iterator
 * @return false The left iterator is not greater than or equal to right
 * iterator
 */
template <class Iterator>
bool operator>=(const reverse_iterator<Iterator> &lhs,
                const reverse_iterator<Iterator> &rhs) {
  return !(lhs < rhs);
}

} // namespace tiny_stl

#endif // !TINY_STL__INCLUDE__ITERATOR_HPP