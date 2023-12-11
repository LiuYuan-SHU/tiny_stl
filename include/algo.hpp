#ifndef TINY_STL__INCLUDE__ALGO_HPP
#define TINY_STL__INCLUDE__ALGO_HPP

#include <cstddef>
#include <ctime>

#include "algobase.hpp"
#include "functional.hpp"
#include "heap_algo.hpp"
#include "iterator.hpp"
#include "memory.hpp"

namespace tiny_stl {

template <class InputIter, class UnaryPredict>
bool all_of(InputIter first, InputIter last, UnaryPredict unary_predict) {
  for (; first != last; ++first) {
    if (!unary_predict(*first)) {
      return false;
    }
  }
  return true;
}

template <class InputIter, class UnaryPredict>
bool any_of(InputIter first, InputIter last, UnaryPredict unary_predict) {
  for (; first != last; ++first) {
    if (unary_predict(*first)) {
      return true;
    }
  }
  return false;
}

template <class InputIter, class UnaryPredict>
bool none_of(InputIter first, InputIter last, UnaryPredict unary_predict) {
  for (; first != last; ++first) {
    if (unary_predict(*first)) {
      return false;
    }
  }
  return true;
}

template <class InputIter, class T>
size_t count(InputIter first, InputIter last, const T &value) {
  size_t result = 0;
  for (; first != last; ++first) {
    if (*first == value) {
      ++result;
    }
  }
  return result;
}

template <class InputIter, class UnaryPredict>
size_t count_if(InputIter first, InputIter last, UnaryPredict unary_predict) {
  size_t result = 0;
  for (; first != last; ++first) {
    if (unary_predict(*first)) {
      ++result;
    }
  }
  return result;
}

template <class InputIter, class T>
InputIter find(InputIter first, InputIter last, const T &value) {
  while (first != last && (*first) != value) {
    ++first;
  }
  return first;
}

template <class InputIter, class UnaryPredict>
InputIter find_if(InputIter first, InputIter last, UnaryPredict unary_predict) {
  while (first != last && !unary_predict(*first)) {
    ++first;
  }
  return first;
}

template <class InputIter, class UnaryPredict>
InputIter find_if_not(InputIter first, InputIter last,
                      UnaryPredict unary_predict) {
  while (first != last && unary_predict(*first)) {
    ++first;
  }
  return first;
}

template <class ForwardIter1, class ForwardIter2>
ForwardIter1 search(ForwardIter1 first1, ForwardIter1 last1,
                    ForwardIter2 first2, ForwardIter2 last2) {
  auto d1 = distance(first1, last1);
  auto d2 = distance(first2, last2);
  if (d1 < d2) {
    return last1;
  }

  auto current1 = first1;
  auto current2 = first2;
  while (current2 != last2) {
    if (*current1 == *current2) {
      ++current1;
      ++current2;
    } else {
      if (d1 == d2) {
        return last1;
      } else {
        current1 = ++first1;
        current2 = first2;
        --d1;
      }
    }
  }
  return first1;
}

template <class ForwardIter1, class ForwardIter2, class Compare>
ForwardIter1 search(ForwardIter1 first1, ForwardIter1 last1,
                    ForwardIter2 first2, ForwardIter2 last2, Compare compare) {
  auto d1 = distance(first1, last1);
  auto d2 = distance(first2, last2);
  if (d1 < d2) {
    return last1;
  }

  auto current1 = first1;
  auto current2 = first2;
  while (current2 != last2) {
    if (compare(*current1, *current2)) {
      ++current1;
      ++current2;
    } else {
      if (d1 == d2) {
        return last1;
      } else {
        current1 = ++first1;
        current2 = first2;
        --d1;
      }
    }
  }
  return first1;
}

template <class ForwardIter, class Size, class T>
ForwardIter search_n(ForwardIter first, ForwardIter last, Size n,
                     const T &value) {
  if (n <= 0) {
    return first;
  } else {
    first = find(first, last, value);
    while (first != last) {
      auto counter = n - 1;
      auto iter = first;
      ++iter;
      while (iter != last && counter != 0 && *iter == value) {
        ++iter;
        --counter;
      }
      if (counter == 0) {
        return first;
      } else {
        first = find(iter, last, value);
      }
    }
  }
  return last;
}

template <class ForwardIter, class Size, class T, class Compare>
ForwardIter search_n(ForwardIter first, ForwardIter last, Size n,
                     const T &value, Compare compare) {
  if (n <= 0) {
    return first;
  } else {
    while (first != last) {
      if (compare(*first, value)) {
        break;
      }
      ++first;
    }
    while (first != last) {
      auto counter = n - 1;
      auto iter = first;
      ++iter;
      while (iter != last && counter != 0 && compare(*iter, value)) {
        ++iter;
        --counter;
      }
      if (counter == 0) {
        return first;
      } else {
        while (iter != last) {
          if (compare(*iter, value)) {
            break;
          }
          ++iter;
        }
        first = iter;
      }
    }
  }
  return last;
}

template <class ForwardIter1, class ForwardIter2>
ForwardIter1 find_end_dispatch(ForwardIter1 first1, ForwardIter1 last1,
                               ForwardIter2 first2, ForwardIter2 last2,
                               forward_iterator_tag, forward_iterator_tag) {
  if (first2 == last2) {
    return last1;
  } else {
    auto result = last1;
    while (true) {
      auto new_result = search(first1, last1, first2, last2);
      if (new_result == last1) {
        return result;
      } else {
        result = new_result;
        first1 = new_result;
        ++first1;
      }
    }
  }
}

template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter1
find_end_dispatch(BidirectionalIter1 first1, BidirectionalIter1 last1,
                  BidirectionalIter2 first2, BidirectionalIter2 last2,
                  bidirectional_iterator_tag, bidirectional_iterator_tag) {
  using riter1 = reverse_iterator<BidirectionalIter1>;
  using riter2 = reverse_iterator<BidirectionalIter2>;

  riter1 rend1(first1);
  riter2 rend2(first2);
  riter1 rresult = search(riter1(last1), rend1, riter2(last2), rend2);
  if (rresult == rend1) {
    return last1;
  } else {
    auto result = rresult.base();
    advance(result, -distance(first2, last2));
    return result;
  }
}

template <class ForwardIter1, class ForwardIter2>
ForwardIter1 find_end(ForwardIter1 first1, ForwardIter1 last1,
                      ForwardIter2 first2, ForwardIter2 last2) {
  using Category1 = typename iterator_traits<ForwardIter1>::iterator_category;
  using Category2 = typename iterator_traits<ForwardIter2>::iterator_category;
  return find_end_dispatch(first1, last1, first2, last2, Category1(),
                           Category2());
}

template <class ForwardIter1, class ForwardIter2, class Compare>
ForwardIter1 find_end_dispatch(ForwardIter1 first1, ForwardIter1 last1,
                               ForwardIter2 first2, ForwardIter2 last2,
                               forward_iterator_tag, forward_iterator_tag,
                               Compare compare) {
  if (first2 == last2) {
    return last1;
  } else {
    auto result = last1;
    while (true) {
      auto new_result = tiny_stl::search(first1, last1, first2, last2, compare);
      if (new_result == last1) {
        return result;
      } else {
        result = new_result;
        first1 = new_result;
        ++first1;
      }
    }
  }
}

template <class BidirectionalIter1, class BidirectionalIter2, class Compare>
BidirectionalIter1
find_end_dispatch(BidirectionalIter1 first1, BidirectionalIter1 last1,
                  BidirectionalIter2 first2, BidirectionalIter2 last2,
                  bidirectional_iterator_tag, bidirectional_iterator_tag,
                  Compare compare) {
  using riter1 = reverse_iterator<BidirectionalIter1>;
  using riter2 = reverse_iterator<BidirectionalIter2>;
  riter1 rend1(first1);
  riter2 rend2(first2);
  riter1 rresult =
      tiny_stl::search(riter1(last1), rend1, riter2(last2), rend2, compare);
  if (rresult == rend1) {
    return last1;
  } else {
    auto result = rresult.base();
    tiny_stl::advance(result, -tiny_stl::distance(first2, last2));
    return result;
  }
}

template <class ForwardIter1, class ForwardIter2, class Compare>
ForwardIter1 find_end(ForwardIter1 first1, ForwardIter1 last1,
                      ForwardIter2 first2, ForwardIter2 last2,
                      Compare compare) {
  typedef typename iterator_traits<ForwardIter1>::iterator_category Category1;
  typedef typename iterator_traits<ForwardIter2>::iterator_category Category2;
  return tiny_stl::find_end_dispatch(first1, last1, first2, last2, Category1(),
                                     Category2(), compare);
}

template <class InputIter, class ForwardIter>
InputIter find_first_of(InputIter first1, InputIter last1, ForwardIter first2,
                        ForwardIter last2) {
  for (; first1 != last1; ++first1) {
    for (auto iter = first2; iter != last2; ++iter) {
      if (*first1 == *iter) {
        return iter;
      }
    }
  }
  return last1;
}

template <class InputIter, class ForwardIter, class Compare>
InputIter find_first_of(InputIter first1, InputIter last1, ForwardIter first2,
                        ForwardIter last2, Compare compare) {
  for (; first1 != last1; ++first1) {
    for (auto iter = first2; iter != last2; ++iter) {
      if (compare(*first1, *iter))
        return first1;
    }
  }
  return last1;
}

template <class InputIter, class Function>
Function for_each(InputIter first, InputIter last, Function func) {
  for (; first != last; ++first) {
    func(*first);
  }
  return func;
}

template <class ForwardIter>
ForwardIter adjacent_find(ForwardIter first, ForwardIter last) {
  if (first == last) {
    return last;
  }
  auto next = first;
  while (++next != last) {
    if (*first == *next) {
      return first;
    }
    first = next;
  }
  return last;
}

template <class ForwardIter, class Compare>
ForwardIter adjacent_find(ForwardIter first, ForwardIter last,
                          Compare compare) {
  if (first == last) {
    return last;
  }
  auto next = first;
  while (++next != last) {
    if (compare(*first, *next)) {
      return first;
    }
    first = next;
  }
  return last;
}

template <class ForwardIter, class T>
ForwardIter lbound_dispatch(ForwardIter first, ForwardIter last, const T &value,
                            forward_iterator_tag) {
  auto len = tiny_stl::distance(first, last);
  auto half = len;
  ForwardIter middle;
  while (len > 0) {
    half = len >> 1;
    middle = first;
    advance(middle, half);
    if (*middle < value) {
      first = middle;
      ++first;
      len = len - half - 1;
    } else {
      len = half;
    }
  }
  return first;
}

template <class RandomAccessIter, class T>
RandomAccessIter lbound_dispatch(RandomAccessIter first, RandomAccessIter last,
                                 const T &value, random_access_iterator_tag) {
  auto len = last - first;
  auto half = len;
  RandomAccessIter middle;
  while (len > 0) {
    half = len >> 1;
    middle = first + half;
    if (*middle < value) {
      first = middle + 1;
      len = len - half - 1;
    } else {
      len = half;
    }
  }
}

template <class ForwardIter, class T>
ForwardIter lower_bound(ForwardIter first, ForwardIter last, const T &value) {
  return lbound_dispatch(first, last, value, iterator_category(first));
}

template <class ForwardIter, class T, class Compare>
ForwardIter lbound_dispatch(ForwardIter first, ForwardIter last, const T &value,
                            forward_iterator_tag, Compare compare) {
  auto len = tiny_stl::distance(first, last);
  auto half = len;
  ForwardIter middle;
  while (len > 0) {
    half = len >> 1;
    middle = first;
    tiny_stl::advance(middle, half);
    if (compare(*middle, value)) {
      first = middle;
      ++first;
      len = len - half - 1;
    } else {
      len = half;
    }
  }
  return first;
}

template <class RandomIter, class T, class Compare>
RandomIter lbound_dispatch(RandomIter first, RandomIter last, const T &value,
                           random_access_iterator_tag, Compare compare) {
  auto len = last - first;
  auto half = len;
  RandomIter middle;
  while (len > 0) {
    half = len >> 1;
    middle = first + half;
    if (compare(*middle, value)) {
      first = middle + 1;
      len = len - half - 1;
    } else {
      len = half;
    }
  }
  return first;
}

template <class ForwardIter, class T, class Compare>
ForwardIter lower_bound(ForwardIter first, ForwardIter last, const T &value,
                        Compare compare) {
  return tiny_stl::lbound_dispatch(first, last, value, iterator_category(first),
                                   compare);
}

template <class ForwardIter, class T>
ForwardIter ubound_dispatch(ForwardIter first, ForwardIter last, const T &value,
                            forward_iterator_tag) {
  auto len = tiny_stl::distance(first, last);
  auto half = len;
  ForwardIter middle;
  while (len > 0) {
    half = len >> 1;
    middle = first;
    tiny_stl::advance(middle, half);
    if (value < *middle) {
      len = half;
    } else {
      first = middle;
      ++first;
      len = len - half - 1;
    }
  }
  return first;
}

template <class RandomIter, class T>
RandomIter ubound_dispatch(RandomIter first, RandomIter last, const T &value,
                           random_access_iterator_tag) {
  auto len = last - first;
  auto half = len;
  RandomIter middle;
  while (len > 0) {
    half = len >> 1;
    middle = first + half;
    if (value < *middle) {
      len = half;
    } else {
      first = middle + 1;
      len = len - half - 1;
    }
  }
  return first;
}

template <class ForwardIter, class T>
ForwardIter upper_bound(ForwardIter first, ForwardIter last, const T &value) {
  return tiny_stl::ubound_dispatch(first, last, value,
                                   iterator_category(first));
}

template <class ForwardIter, class T, class Compared>
ForwardIter ubound_dispatch(ForwardIter first, ForwardIter last, const T &value,
                            forward_iterator_tag, Compared comp) {
  auto len = tiny_stl::distance(first, last);
  auto half = len;
  ForwardIter middle;
  while (len > 0) {
    half = len >> 1;
    middle = first;
    tiny_stl::advance(middle, half);
    if (comp(value, *middle)) {
      len = half;
    } else {
      first = middle;
      ++first;
      len = len - half - 1;
    }
  }
  return first;
}

template <class RandomIter, class T, class Compare>
RandomIter ubound_dispatch(RandomIter first, RandomIter last, const T &value,
                           random_access_iterator_tag, Compare compare) {
  auto len = last - first;
  auto half = len;
  RandomIter middle;
  while (len > 0) {
    half = len >> 1;
    middle = first + half;
    if (compare(value, *middle)) {
      len = half;
    } else {
      first = middle + 1;
      len = len - half - 1;
    }
  }
  return first;
}

template <class ForwardIter, class T, class Compare>
ForwardIter upper_bound(ForwardIter first, ForwardIter last, const T &value,
                        Compare compare) {
  return tiny_stl::ubound_dispatch(first, last, value, iterator_category(first),
                                   compare);
}

template <class ForwardIter, class T>
bool binary_search(ForwardIter first, ForwardIter last, const T &value) {
  auto iter = tiny_stl::lower_bound(first, last, value);
  return iter != last && !(value < *iter);
}

template <class ForwardIter, class T, class Compare>
bool binary_search(ForwardIter first, ForwardIter last, const T &value,
                   Compare compare) {
  auto iter = tiny_stl::lower_bound(first, last, value);
  return iter != last && !compare(value, *iter);
}

// ?
template <class ForwardIter, class T>
tiny_stl::pair<ForwardIter, ForwardIter>
erange_dispatch(ForwardIter first, ForwardIter last, const T &value,
                forward_iterator_tag) {
  auto len = tiny_stl::distance(first, last);
  auto half = len;
  ForwardIter middle, left, right;
  while (len > 0) {
    half = len >> 1;
    middle = first;
    tiny_stl::advance(middle, half);
    if (*middle < value) {
      first = middle;
      ++first;
      len = len - half - 1;
    } else if (value < *middle) {
      len = half;
    } else {
      left = tiny_stl::lower_bound(first, last, value);
      tiny_stl::advance(first, len);
      right = tiny_stl::upper_bound(++middle, first, value);
      return tiny_stl::pair<ForwardIter, ForwardIter>(left, right);
    }
  }
  return tiny_stl::pair<ForwardIter, ForwardIter>(last, last);
}

// ?
template <class RandomIter, class T>
tiny_stl::pair<RandomIter, RandomIter>
erange_dispatch(RandomIter first, RandomIter last, const T &value,
                random_access_iterator_tag) {
  auto len = last - first;
  auto half = len;
  RandomIter middle, left, right;
  while (len > 0) {
    half = len >> 1;
    middle = first + half;
    if (*middle < value) {
      first = middle + 1;
      len = len - half - 1;
    } else if (value < *middle) {
      len = half;
    } else {
      left = tiny_stl::lower_bound(first, middle, value);
      right = tiny_stl::upper_bound(++middle, first + len, value);
      return tiny_stl::pair<RandomIter, RandomIter>(left, right);
    }
  }
  return tiny_stl::pair<RandomIter, RandomIter>(last, last);
}

// ?
template <class ForwardIter, class T>
tiny_stl::pair<ForwardIter, ForwardIter>
equal_range(ForwardIter first, ForwardIter last, const T &value) {
  return tiny_stl::erange_dispatch(first, last, value,
                                   iterator_category(first));
}

template <class ForwardIter, class T, class Compare>
tiny_stl::pair<ForwardIter, ForwardIter>
erange_dispatch(ForwardIter first, ForwardIter last, const T &value,
                forward_iterator_tag, Compare compare) {
  auto len = tiny_stl::distance(first, last);
  auto half = len;
  ForwardIter middle, left, right;
  while (len > 0) {
    half = len >> 1;
    middle = first;
    tiny_stl::advance(middle, half);
    if (compare(*middle, value)) {
      first = middle;
      ++first;
      len = len - half - 1;
    } else if (compare(value, *middle)) {
      len = half;
    } else {
      left = tiny_stl::lower_bound(first, last, value, compare);
      tiny_stl::advance(first, len);
      right = tiny_stl::upper_bound(++middle, first, value, compare);
      return tiny_stl::pair<ForwardIter, ForwardIter>(left, right);
    }
  }
  return tiny_stl::pair<ForwardIter, ForwardIter>(last, last);
}

template <class RandomIter, class T, class Compare>
tiny_stl::pair<RandomIter, RandomIter>
erange_dispatch(RandomIter first, RandomIter last, const T &value,
                random_access_iterator_tag, Compare compare) {
  auto len = last - first;
  auto half = len;
  RandomIter middle, left, right;
  while (len > 0) {
    half = len >> 1;
    middle = first + half;
    if (compare(*middle, value)) {
      first = middle + 1;
      len = len - half - 1;
    } else if (compare(value, *middle)) {
      len = half;
    } else {
      left = tiny_stl::lower_bound(first, middle, value, compare);
      right = tiny_stl::upper_bound(++middle, first + len, value, compare);
      return tiny_stl::pair<RandomIter, RandomIter>(left, right);
    }
  }
  return tiny_stl::pair<RandomIter, RandomIter>(last, last);
}

template <class ForwardIter, class T, class Compare>
tiny_stl::pair<ForwardIter, ForwardIter>
equal_range(ForwardIter first, ForwardIter last, const T &value,
            Compare compare) {
  return tiny_stl::erange_dispatch(first, last, value, iterator_category(first),
                                   compare);
}

template <class ForwardIter, class Generator>
void generate(ForwardIter first, ForwardIter last, Generator generator) {
  for (; first != last; ++first) {
    *first = generator();
  }
}

template <class ForwardIter, class Size, class Generator>
void generate_n(ForwardIter first, Size n, Generator generator) {
  for (; n > 0; --n, ++first) {
    *first = generator();
  }
}

template <class InputIter1, class InputIter2>
bool includes(InputIter1 first1, InputIter1 last1, InputIter2 first2,
              InputIter2 last2) {
  while (first1 != last1 && first2 != last2) {
    if (*first2 < *first1) {
      return false;
    } else if (*first1 < *first2) {
      ++first1;
    } else {
      ++first1, ++first2;
    }
  }
  return first2 == last2;
}

template <class InputIter1, class InputIter2, class Compare>
bool includes(InputIter1 first1, InputIter1 last1, InputIter2 first2,
              InputIter2 last2, Compare compare) {
  while (first1 != last1 && first2 != last2) {
    if (compare(*first2, *first1)) {
      return false;
    } else if (compare(*first1, *first2)) {
      ++first1;
    } else {
      ++first1, ++first2;
    }
  }
  return first2 == last2;
}

template <class RandomIter> bool is_heap(RandomIter first, RandomIter last) {
  auto n = tiny_stl::distance(first, last);
  auto parent = 0;
  for (auto child = 1; child < n; ++child) {
    if (first[parent] < first[child])
      return false;
    if ((child & 1) == 0)
      ++parent;
  }
  return true;
}

template <class RandomIter, class Compared>
bool is_heap(RandomIter first, RandomIter last, Compared comp) {
  auto n = tiny_stl::distance(first, last);
  auto parent = 0;
  for (auto child = 1; child < n; ++child) {
    if (comp(first[parent], first[child]))
      return false;
    if ((child & 1) == 0)
      ++parent;
  }
  return true;
}

template <class ForwardIter>
bool is_sorted(ForwardIter first, ForwardIter last) {
  if (first == last)
    return true;
  auto next = first;
  ++next;
  for (; next != last; first = next, ++next) {
    if (*next < *first)
      return false;
  }
  return true;
}

template <class ForwardIter, class Compare>
bool is_sorted(ForwardIter first, ForwardIter last, Compare compare) {
  if (first == last)
    return true;
  auto next = first;
  ++next;
  for (; next != last; first = next, ++next) {
    if (compare(*next, *first))
      return false;
  }
  return true;
}

template <class T>
const T &median(const T &left, const T &mid, const T &right) {
  if (left < mid)
    if (mid < right) // left < mid < right
      return mid;
    else if (left < right) // left < right <= mid
      return right;
    else // right <= left < mid
      return left;
  else if (left < right) // mid <= left < right
    return left;
  else if (mid < right) // mid < right <= left
    return right;
  else // right <= mid <= left
    return mid;
}

template <class T, class Compare>
const T &median(const T &left, const T &mid, const T &right, Compare compare) {
  if (compare(left, mid))
    if (compare(mid, right))
      return mid;
    else if (compare(left, right))
      return right;
    else
      return left;
  else if (compare(left, right))
    return left;
  else if (compare(mid, right))
    return right;
  else
    return mid;
}

template <class ForwardIter>
ForwardIter max_element(ForwardIter first, ForwardIter last) {
  if (first == last)
    return first;
  auto result = first;
  while (++first != last) {
    if (*result < *first)
      result = first;
  }
  return result;
}

template <class ForwardIter, class Compared>
ForwardIter max_element(ForwardIter first, ForwardIter last, Compared comp) {
  if (first == last)
    return first;
  auto result = first;
  while (++first != last) {
    if (comp(*result, *first))
      result = first;
  }
  return result;
}

template <class ForwardIter>
ForwardIter min_elememt(ForwardIter first, ForwardIter last) {
  if (first == last)
    return first;
  auto result = first;
  while (++first != last) {
    if (*first < *result)
      result = first;
  }
  return result;
}

template <class ForwardIter, class Compare>
ForwardIter min_elememt(ForwardIter first, ForwardIter last, Compare compare) {
  if (first == last)
    return first;
  auto result = first;
  while (++first != last) {
    if (compare(*first, *result))
      result = first;
  }
  return result;
}

template <class ForwardIter1, class ForwardIter2>
ForwardIter2 swap_ranges(ForwardIter1 first1, ForwardIter1 last1,
                         ForwardIter2 first2) {
  for (; first1 != last1; ++first1, ++first2) {
    tiny_stl::iter_swap(first1, first2);
  }
  return first2;
}

template <class InputIter, class OutputIter, class UnaryOperation>
OutputIter transform(InputIter first, InputIter last, OutputIter result,
                     UnaryOperation unary_op) {
  for (; first != last; ++first, ++result) {
    *result = unary_op(*first);
  }
  return result;
}

template <class InputIter1, class InputIter2, class OutputIter,
          class BinaryOperation>
OutputIter transform(InputIter1 first1, InputIter1 last1, InputIter2 first2,
                     OutputIter result, BinaryOperation binary_op) {
  for (; first1 != last1; ++first1, ++first2, ++result) {
    *result = binary_op(*first1, *first2);
  }
  return result;
}

template <class InputIter, class OutputIter, class T>
OutputIter remove_copy(InputIter first, InputIter last, OutputIter result,
                       const T &value) {
  for (; first != last; ++first) {
    if (*first != value) {
      *result++ = *first;
    }
  }
  return result;
}

template <class ForwardIter, class T>
ForwardIter remove(ForwardIter first, ForwardIter last, const T &value) {
  first = tiny_stl::find(first, last, value);
  auto next = first;
  return first == last ? first
                       : tiny_stl::remove_copy(++next, last, first, value);
}

template <class InputIter, class OutputIter, class UnaryPredicate>
OutputIter remove_copy_if(InputIter first, InputIter last, OutputIter result,
                          UnaryPredicate unary_pred) {
  for (; first != last; ++first) {
    if (!unary_pred(*first)) {
      *result = *first;
      ++result;
    }
  }
  return result;
}

template <class ForwardIter, class UnaryPredicate>
ForwardIter remove_if(ForwardIter first, ForwardIter last,
                      UnaryPredicate unary_pred) {
  first = tiny_stl::find_if(first, last, unary_pred);
  auto next = first;
  return first == last
             ? first
             : tiny_stl::remove_copy_if(++next, last, first, unary_pred);
}

template <class ForwardIter, class T>
void replace(ForwardIter first, ForwardIter last, const T &old_value,
             const T &new_value) {
  for (; first != last; ++first) {
    if (*first == old_value)
      *first = new_value;
  }
}

template <class InputIter, class OutputIter, class T>
OutputIter replace_copy(InputIter first, InputIter last, OutputIter result,
                        const T &old_value, const T &new_value) {
  for (; first != last; ++first, ++result) {
    *result = *first == old_value ? new_value : *first;
  }
  return result;
}

template <class InputIter, class OutputIter, class UnaryPredicate, class T>
OutputIter replace_copy_if(InputIter first, InputIter last, OutputIter result,
                           UnaryPredicate unary_pred, const T &new_value) {
  for (; first != last; ++first, ++result) {
    *result = unary_pred(*first) ? new_value : *first;
  }
  return result;
}

template <class ForwardIter, class UnaryPredicate, class T>
void replace_if(ForwardIter first, ForwardIter last, UnaryPredicate unary_pred,
                const T &new_value) {
  for (; first != last; ++first) {
    if (unary_pred(*first))
      *first = new_value;
  }
}

template <class BidirectionalIter>
void reverse_dispatch(BidirectionalIter first, BidirectionalIter last,
                      bidirectional_iterator_tag) {
  while (true) {
    if (first == last || first == --last)
      return;
    tiny_stl::iter_swap(first++, last);
  }
}

template <class RandomIter>
void reverse_dispatch(RandomIter first, RandomIter last,
                      random_access_iterator_tag) {
  while (first < last)
    tiny_stl::iter_swap(first++, --last);
}

template <class BidirectionalIter>
void reverse(BidirectionalIter first, BidirectionalIter last) {
  tiny_stl::reverse_dispatch(first, last, iterator_category(first));
}

template <class BidirectionalIter, class OutputIter>
OutputIter reverse_copy(BidirectionalIter first, BidirectionalIter last,
                        OutputIter result) {
  while (first != last) {
    --last;
    *result = *last;
    ++result;
  }
  return result;
}

template <class RandomIter>
void random_shuffle(RandomIter first, RandomIter last) {
  if (first == last)
    return;
  srand((unsigned)time(0));
  for (auto i = first + 1; i != last; ++i) {
    tiny_stl::iter_swap(i, first + (rand() % (i - first + 1)));
  }
}

template <class RandomIter, class RandomNumberGenerator>
void random_shuffle(RandomIter first, RandomIter last,
                    RandomNumberGenerator &rand) {
  if (first == last)
    return;
  auto len = tiny_stl::distance(first, last);
  for (auto i = first + 1; i != last; ++i) {
    tiny_stl::iter_swap(i, first + (rand(i - first + 1) % len));
  }
}

template <class ForwardIter>
ForwardIter rotate_dispatch(ForwardIter first, ForwardIter middle,
                            ForwardIter last, forward_iterator_tag) {
  auto first2 = middle;
  do {
    tiny_stl::swap(*first++, *first2++);
    if (first == middle)
      middle = first2;
  } while (first2 != last);

  auto new_middle = first;
  first2 = middle;
  while (first2 != last) {
    tiny_stl::swap(*first++, *first2++);
    if (first == middle) {
      middle = first2;
    } else if (first2 == last) {
      first2 = middle;
    }
  }
  return new_middle;
}

template <class BidirectionalIter>
BidirectionalIter
rotate_dispatch(BidirectionalIter first, BidirectionalIter middle,
                BidirectionalIter last, bidirectional_iterator_tag) {
  tiny_stl::reverse_dispatch(first, middle, bidirectional_iterator_tag());
  tiny_stl::reverse_dispatch(middle, last, bidirectional_iterator_tag());
  while (first != middle && middle != last)
    tiny_stl::swap(*first++, *--last);
  if (first == middle) {
    tiny_stl::reverse_dispatch(middle, last, bidirectional_iterator_tag());
    return last;
  } else {
    tiny_stl::reverse_dispatch(first, middle, bidirectional_iterator_tag());
    return first;
  }
}

template <class EuclideanRingElement>
EuclideanRingElement rgcd(EuclideanRingElement m, EuclideanRingElement n) {
  while (n != 0) {
    auto t = m % n;
    m = n;
    n = t;
  }
  return m;
}

template <class RandomIter>
RandomIter rotate_dispatch(RandomIter first, RandomIter middle, RandomIter last,
                           random_access_iterator_tag) {
  auto n = last - first;
  auto l = middle - first;
  auto r = n - l;
  auto result = first + (last - middle);
  if (l == r) {
    tiny_stl::swap_ranges(first, middle, middle);
    return result;
  }
  auto cycle_times = rgcd(n, l);
  for (auto i = 0; i < cycle_times; ++i) {
    auto tmp = *first;
    auto p = first;
    if (l < r) {
      for (auto j = 0; j < r / cycle_times; ++j) {
        if (p > first + r) {
          *p = *(p - r);
          p -= r;
        }
        *p = *(p + l);
        p += l;
      }
    } else {
      for (auto j = 0; j < l / cycle_times - 1; ++j) {
        if (p < last - l) {
          *p = *(p + l);
          p += l;
        }
        *p = *(p - r);
        p -= r;
      }
    }
    *p = tmp;
    ++first;
  }
  return result;
}

template <class ForwardIter>
ForwardIter rotate(ForwardIter first, ForwardIter middle, ForwardIter last) {
  if (first == middle)
    return last;
  if (middle == last)
    return first;
  return tiny_stl::rotate_dispatch(first, middle, last,
                                   iterator_category(first));
}

template <class ForwardIter, class OutputIter>
ForwardIter rotate_copy(ForwardIter first, ForwardIter middle, ForwardIter last,
                        OutputIter result) {
  return tiny_stl::copy(first, middle, tiny_stl::copy(middle, last, result));
}

template <class ForwardIter1, class ForwardIter2, class BinaryPred>
bool is_permutation_aux(ForwardIter1 first1, ForwardIter1 last1,
                        ForwardIter2 first2, ForwardIter2 last2,
                        BinaryPred pred) {
  constexpr bool is_ra_it = tiny_stl::is_random_iterator<ForwardIter1>::value &&
                            tiny_stl::is_random_iterator<ForwardIter2>::value;
  if (is_ra_it) {
    auto len1 = last1 - first1;
    auto len2 = last2 - first2;
    if (len1 != len2)
      return false;
  }

  for (; first1 != last1 && first2 != last2; ++first1, (void)++first2) {
    if (!pred(*first1, *first2))
      break;
  }
  if (is_ra_it) {
    if (first1 == last1)
      return true;
  } else {
    auto len1 = tiny_stl::distance(first1, last1);
    auto len2 = tiny_stl::distance(first2, last2);
    if (len1 == 0 && len2 == 0)
      return true;
    if (len1 != len2)
      return false;
  }

  for (auto i = first1; i != last1; ++i) {
    bool is_repeated = false;
    for (auto j = first1; j != i; ++j) {
      if (pred(*j, *i)) {
        is_repeated = true;
        break;
      }
    }

    if (!is_repeated) {
      auto c2 = 0;
      for (auto j = first2; j != last2; ++j) {
        if (pred(*i, *j))
          ++c2;
      }
      if (c2 == 0)
        return false;

      auto c1 = 1;
      auto j = i;
      for (++j; j != last1; ++j) {
        if (pred(*i, *j))
          ++c1;
      }
      if (c1 != c2)
        return false;
    }
  }
  return true;
}

template <class ForwardIter1, class ForwardIter2, class BinaryPred>
bool is_permutation(ForwardIter1 first1, ForwardIter1 last1,
                    ForwardIter2 first2, ForwardIter2 last2, BinaryPred pred) {
  return is_permutation_aux(first1, last1, first2, last2, pred);
}

template <class ForwardIter1, class ForwardIter2>
bool is_permutation(ForwardIter1 first1, ForwardIter1 last1,
                    ForwardIter2 first2, ForwardIter2 last2) {
  typedef typename iterator_traits<ForwardIter1>::value_type v1;
  typedef typename iterator_traits<ForwardIter2>::value_type v2;
  static_assert(std::is_same<v1, v2>::value,
                "the type should be same in tiny_stl::is_permutation");
  return is_permutation_aux(first1, last1, first2, last2,
                            tiny_stl::equal_to<v1>());
}

template <class BidirectionalIter>
bool next_permutation(BidirectionalIter first, BidirectionalIter last) {
  auto i = last;
  if (first == last || first == --i)
    return false;
  for (;;) {
    auto ii = i;
    if (*--i < *ii) {
      auto j = last;
      while (!(*i < *--j)) {
      }
      tiny_stl::iter_swap(i, j);
      tiny_stl::reverse(ii, last);
      return true;
    }
    if (i == first) {
      tiny_stl::reverse(first, last);
      return false;
    }
  }
}

template <class BidirectionalIter, class Compared>
bool next_permutation(BidirectionalIter first, BidirectionalIter last,
                      Compared comp) {
  auto i = last;
  if (first == last || first == --i)
    return false;
  for (;;) {
    auto ii = i;
    if (comp(*--i, *ii)) {
      auto j = last;
      while (!comp(*i, *--j)) {
      }
      tiny_stl::iter_swap(i, j);
      tiny_stl::reverse(ii, last);
      return true;
    }
    if (i == first) {
      tiny_stl::reverse(first, last);
      return false;
    }
  }
}

template <class BidirectionalIter>
bool prev_permutation(BidirectionalIter first, BidirectionalIter last) {
  auto i = last;
  if (first == last || first == --i)
    return false;
  for (;;) {
    auto ii = i;
    if (*ii < *--i) {
      auto j = last;
      while (!(*--j < *i)) {
      }
      tiny_stl::iter_swap(i, j);
      tiny_stl::reverse(ii, last);
      return true;
    }
    if (i == first) {
      tiny_stl::reverse(first, last);
      return false;
    }
  }
}

template <class BidirectionalIter, class Compared>
bool prev_permutation(BidirectionalIter first, BidirectionalIter last,
                      Compared comp) {
  auto i = last;
  if (first == last || first == --i)
    return false;
  for (;;) {
    auto ii = i;
    if (comp(*ii, *--i)) {
      auto j = last;
      while (!comp(*--j, *i)) {
      }
      tiny_stl::iter_swap(i, j);
      tiny_stl::reverse(ii, last);
      return true;
    }
    if (i == first) {
      tiny_stl::reverse(first, last);
      return false;
    }
  }
}

template <class InputIter1, class InputIter2, class OutputIter>
OutputIter merge(InputIter1 first1, InputIter1 last1, InputIter2 first2,
                 InputIter2 last2, OutputIter result) {
  while (first1 != last1 && first2 != last2) {
    if (*first2 < *first1) {
      *result = *first2;
      ++first2;
    } else {
      *result = *first1;
      ++first1;
    }
    ++result;
  }
  return tiny_stl::copy(first2, last2, tiny_stl::copy(first1, last1, result));
}

template <class InputIter1, class InputIter2, class OutputIter, class Compared>
OutputIter merge(InputIter1 first1, InputIter1 last1, InputIter2 first2,
                 InputIter2 last2, OutputIter result, Compared comp) {
  while (first1 != last1 && first2 != last2) {
    if (comp(*first2, *first1)) {
      *result = *first2;
      ++first2;
    } else {
      *result = *first1;
      ++first1;
    }
    ++result;
  }
  return tiny_stl::copy(first2, last2, tiny_stl::copy(first1, last1, result));
}

template <class BidirectionalIter, class Distance>
void merge_without_buffer(BidirectionalIter first, BidirectionalIter middle,
                          BidirectionalIter last, Distance len1,
                          Distance len2) {
  if (len1 == 0 || len2 == 0)
    return;
  if (len1 + len2 == 2) {
    if (*middle < *first)
      tiny_stl::iter_swap(first, middle);
    return;
  }
  auto first_cut = first;
  auto second_cut = middle;
  Distance len11 = 0;
  Distance len22 = 0;
  if (len1 > len2) {
    len11 = len1 >> 1;
    tiny_stl::advance(first_cut, len11);
    second_cut = tiny_stl::lower_bound(middle, last, *first_cut);
    len22 = tiny_stl::distance(middle, second_cut);
  } else {
    len22 = len2 >> 1;
    tiny_stl::advance(second_cut, len22);
    first_cut = tiny_stl::upper_bound(first, middle, *second_cut);
    len11 = tiny_stl::distance(first, first_cut);
  }
  auto new_middle = tiny_stl::rotate(first_cut, middle, second_cut);
  tiny_stl::merge_without_buffer(first, first_cut, new_middle, len11, len22);
  tiny_stl::merge_without_buffer(new_middle, second_cut, last, len1 - len11,
                                 len2 - len22);
}

template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter1
merge_backward(BidirectionalIter1 first1, BidirectionalIter1 last1,
               BidirectionalIter2 first2, BidirectionalIter2 last2,
               BidirectionalIter1 result) {
  if (first1 == last1)
    return tiny_stl::copy_backward(first2, last2, result);
  if (first2 == last2)
    return tiny_stl::copy_backward(first1, last1, result);
  --last1;
  --last2;
  while (true) {
    if (*last2 < *last1) {
      *--result = *last1;
      if (first1 == last1)
        return tiny_stl::copy_backward(first2, ++last2, result);
      --last1;
    } else {
      *--result = *last2;
      if (first2 == last2)
        return tiny_stl::copy_backward(first1, ++last1, result);
      --last2;
    }
  }
}

template <class BidirectionalIter1, class BidirectionalIter2, class Distance>
BidirectionalIter1
rotate_adaptive(BidirectionalIter1 first, BidirectionalIter1 middle,
                BidirectionalIter1 last, Distance len1, Distance len2,
                BidirectionalIter2 buffer, Distance buffer_size) {
  BidirectionalIter2 buffer_end;
  if (len1 > len2 && len2 <= buffer_size) {
    buffer_end = tiny_stl::copy(middle, last, buffer);
    tiny_stl::copy_backward(first, middle, last);
    return tiny_stl::copy(buffer, buffer_end, first);
  } else if (len1 <= buffer_size) {
    buffer_end = tiny_stl::copy(first, middle, buffer);
    tiny_stl::copy(middle, last, first);
    return tiny_stl::copy_backward(buffer, buffer_end, last);
  } else {
    return tiny_stl::rotate(first, middle, last);
  }
}

template <class BidirectionalIter, class Distance, class Pointer>
void merge_adaptive(BidirectionalIter first, BidirectionalIter middle,
                    BidirectionalIter last, Distance len1, Distance len2,
                    Pointer buffer, Distance buffer_size) {
  if (len1 <= len2 && len1 <= buffer_size) {
    Pointer buffer_end = tiny_stl::copy(first, middle, buffer);
    tiny_stl::merge(buffer, buffer_end, middle, last, first);
  } else if (len2 <= buffer_size) {
    Pointer buffer_end = tiny_stl::copy(middle, last, buffer);
    tiny_stl::merge_backward(first, middle, buffer, buffer_end, last);
  } else {
    auto first_cut = first;
    auto second_cut = middle;
    Distance len11 = 0;
    Distance len22 = 0;
    if (len1 > len2) {
      len11 = len1 >> 1;
      tiny_stl::advance(first_cut, len11);
      second_cut = tiny_stl::lower_bound(middle, last, *first_cut);
      len22 = tiny_stl::distance(middle, second_cut);
    } else {
      len22 = len2 >> 1;
      tiny_stl::advance(second_cut, len22);
      first_cut = tiny_stl::upper_bound(first, middle, *second_cut);
      len11 = tiny_stl::distance(first, first_cut);
    }
    auto new_middle =
        tiny_stl::rotate_adaptive(first_cut, middle, second_cut, len1 - len11,
                                  len22, buffer, buffer_size);
    tiny_stl::merge_adaptive(first, first_cut, new_middle, len11, len22, buffer,
                             buffer_size);
    tiny_stl::merge_adaptive(new_middle, second_cut, last, len1 - len11,
                             len2 - len22, buffer, buffer_size);
  }
}

template <class BidirectionalIter, class T>
void inplace_merge_aux(BidirectionalIter first, BidirectionalIter middle,
                       BidirectionalIter last, T *) {
  auto len1 = tiny_stl::distance(first, middle);
  auto len2 = tiny_stl::distance(middle, last);
  temporary_buffer<BidirectionalIter, T> buf(first, last);
  if (!buf.begin()) {
    tiny_stl::merge_without_buffer(first, middle, last, len1, len2);
  } else {
    tiny_stl::merge_adaptive(first, middle, last, len1, len2, buf.begin(),
                             buf.size());
  }
}

template <class BidirectionalIter>
void inplace_merge(BidirectionalIter first, BidirectionalIter middle,
                   BidirectionalIter last) {
  if (first == middle || middle == last)
    return;
  tiny_stl::inplace_merge_aux(first, middle, last, value_type(first));
}

template <class BidirectionalIter, class Distance, class Compared>
void merge_without_buffer(BidirectionalIter first, BidirectionalIter middle,
                          BidirectionalIter last, Distance len1, Distance len2,
                          Compared comp) {
  if (len1 == 0 || len2 == 0)
    return;
  if (len1 + len2 == 2) {
    if (comp(*middle, *first))
      tiny_stl::iter_swap(first, middle);
    return;
  }
  auto first_cut = first;
  auto second_cut = middle;
  Distance len11 = 0;
  Distance len22 = 0;
  if (len1 > len2) {
    len11 = len1 >> 1;
    tiny_stl::advance(first_cut, len11);
    second_cut = tiny_stl::lower_bound(middle, last, *first_cut, comp);
    len22 = tiny_stl::distance(middle, second_cut);
  } else {
    len22 = len2 >> 1;
    tiny_stl::advance(second_cut, len22);
    first_cut = tiny_stl::upper_bound(first, middle, *second_cut, comp);
    len11 = tiny_stl::distance(first, first_cut);
  }
  auto new_middle = tiny_stl::rotate(first_cut, middle, second_cut);
  tiny_stl::merge_without_buffer(first, first_cut, new_middle, len11, len22,
                                 comp);
  tiny_stl::merge_without_buffer(new_middle, second_cut, last, len1 - len11,
                                 len2 - len22, comp);
}

template <class BidirectionalIter1, class BidirectionalIter2, class Compared>
BidirectionalIter1
merge_backward(BidirectionalIter1 first1, BidirectionalIter1 last1,
               BidirectionalIter2 first2, BidirectionalIter2 last2,
               BidirectionalIter1 result, Compared comp) {
  if (first1 == last1)
    return tiny_stl::copy_backward(first2, last2, result);
  if (first2 == last2)
    return tiny_stl::copy_backward(first1, last1, result);
  --last1;
  --last2;
  while (true) {
    if (comp(*last2, *last1)) {
      *--result = *last1;
      if (first1 == last1)
        return tiny_stl::copy_backward(first2, ++last2, result);
      --last1;
    } else {
      *--result = *last2;
      if (first2 == last2)
        return tiny_stl::copy_backward(first1, ++last1, result);
      --last2;
    }
  }
}

template <class BidirectionalIter, class Distance, class Pointer,
          class Compared>
void merge_adaptive(BidirectionalIter first, BidirectionalIter middle,
                    BidirectionalIter last, Distance len1, Distance len2,
                    Pointer buffer, Distance buffer_size, Compared comp) {
  if (len1 <= len2 && len1 <= buffer_size) {
    Pointer buffer_end = tiny_stl::copy(first, middle, buffer);
    tiny_stl::merge(buffer, buffer_end, middle, last, first, comp);
  } else if (len2 <= buffer_size) {
    Pointer buffer_end = tiny_stl::copy(middle, last, buffer);
    tiny_stl::merge_backward(first, middle, buffer, buffer_end, last, comp);
  } else {
    auto first_cut = first;
    auto second_cut = middle;
    Distance len11 = 0;
    Distance len22 = 0;
    if (len1 > len2) {
      len11 = len1 >> 1;
      tiny_stl::advance(first_cut, len11);
      second_cut = tiny_stl::lower_bound(middle, last, *first_cut, comp);
      len22 = tiny_stl::distance(middle, second_cut);
    } else {
      len22 = len2 >> 1;
      tiny_stl::advance(second_cut, len22);
      first_cut = tiny_stl::upper_bound(first, middle, *second_cut, comp);
      len11 = tiny_stl::distance(first, first_cut);
    }
    auto new_middle =
        tiny_stl::rotate_adaptive(first_cut, middle, second_cut, len1 - len11,
                                  len22, buffer, buffer_size);
    tiny_stl::merge_adaptive(first, first_cut, new_middle, len11, len22, buffer,
                             buffer_size, comp);
    tiny_stl::merge_adaptive(new_middle, second_cut, last, len1 - len11,
                             len2 - len22, buffer, buffer_size, comp);
  }
}

template <class BidirectionalIter, class T, class Compared>
void inplace_merge_aux(BidirectionalIter first, BidirectionalIter middle,
                       BidirectionalIter last, T *, Compared comp) {
  auto len1 = tiny_stl::distance(first, middle);
  auto len2 = tiny_stl::distance(middle, last);
  temporary_buffer<BidirectionalIter, T> buf(first, last);
  if (!buf.begin()) {
    tiny_stl::merge_without_buffer(first, middle, last, len1, len2, comp);
  } else {
    tiny_stl::merge_adaptive(first, middle, last, len1, len2, buf.begin(),
                             buf.size(), comp);
  }
}

template <class BidirectionalIter, class Compared>
void inplace_merge(BidirectionalIter first, BidirectionalIter middle,
                   BidirectionalIter last, Compared comp) {
  if (first == middle || middle == last)
    return;
  tiny_stl::inplace_merge_aux(first, middle, last, value_type(first), comp);
}

template <class RandomIter>
void partial_sort(RandomIter first, RandomIter middle, RandomIter last) {
  tiny_stl::make_heap(first, middle);
  for (auto i = middle; i < last; ++i) {
    if (*i < *first) {
      tiny_stl::pop_heap_aux(first, middle, i, *i, distance_type(first));
    }
  }
  tiny_stl::sort_heap(first, middle);
}

template <class RandomIter, class Compared>
void partial_sort(RandomIter first, RandomIter middle, RandomIter last,
                  Compared comp) {
  tiny_stl::make_heap(first, middle, comp);
  for (auto i = middle; i < last; ++i) {
    if (comp(*i, *first)) {
      tiny_stl::pop_heap_aux(first, middle, i, *i, distance_type(first), comp);
    }
  }
  tiny_stl::sort_heap(first, middle, comp);
}

template <class InputIter, class RandomIter, class Distance>
RandomIter psort_copy_aux(InputIter first, InputIter last,
                          RandomIter result_first, RandomIter result_last,
                          Distance *) {
  if (result_first == result_last)
    return result_last;
  auto result_iter = result_first;
  while (first != last && result_iter != result_last) {
    *result_iter = *first;
    ++result_iter;
    ++first;
  }
  tiny_stl::make_heap(result_first, result_iter);
  while (first != last) {
    if (*first < *result_first) {
      tiny_stl::adjust_heap(result_first, static_cast<Distance>(0),
                            result_iter - result_first, *first);
    }
    ++first;
  }
  tiny_stl::sort_heap(result_first, result_iter);
  return result_iter;
}

template <class InputIter, class RandomIter>
RandomIter partial_sort_copy(InputIter first, InputIter last,
                             RandomIter result_first, RandomIter result_last) {
  return tiny_stl::psort_copy_aux(first, last, result_first, result_last,
                                  distance_type(result_first));
}

template <class InputIter, class RandomIter, class Distance, class Compared>
RandomIter psort_copy_aux(InputIter first, InputIter last,
                          RandomIter result_first, RandomIter result_last,
                          Distance *, Compared comp) {
  if (result_first == result_last)
    return result_last;
  auto result_iter = result_first;
  while (first != last && result_iter != result_last) {
    *result_iter = *first;
    ++result_iter;
    ++first;
  }
  tiny_stl::make_heap(result_first, result_iter, comp);
  while (first != last) {
    if (comp(*first, *result_first)) {
      tiny_stl::adjust_heap(result_first, static_cast<Distance>(0),
                            result_iter - result_first, *first, comp);
    }
    ++first;
  }
  tiny_stl::sort_heap(result_first, result_iter, comp);
  return result_iter;
}

template <class InputIter, class RandomIter, class Compared>
RandomIter partial_sort_copy(InputIter first, InputIter last,
                             RandomIter result_first, RandomIter result_last,
                             Compared comp) {
  return tiny_stl::psort_copy_aux(first, last, result_first, result_last,
                                  distance_type(result_first), comp);
}

template <class BidirectionalIter, class UnaryPredicate>
BidirectionalIter partition(BidirectionalIter first, BidirectionalIter last,
                            UnaryPredicate unary_pred) {
  while (true) {
    while (first != last && unary_pred(*first)) {
      ++first;
    }
    if (first == last)
      break;
    --last;
    while (first != last && !unary_pred(*last)) {
      --last;
    }
    if (first == last)
      break;
    tiny_stl::iter_swap(first, last);
    ++first;
  }
  return first;
}

template <class InputIter, class OutputIter1, class OutputIter2,
          class UnaryPredicate>
tiny_stl::pair<OutputIter1, OutputIter2>
partition_copy(InputIter first, InputIter last, OutputIter1 result_true,
               OutputIter2 result_false, UnaryPredicate unary_pred) {
  for (; first != last; ++first) {
    if (unary_pred(*first)) {
      *result_true++ = *first;
    } else {
      *result_false++ = *first;
    }
  }
  return tiny_stl::pair<OutputIter1, OutputIter2>(result_true, result_false);
}

constexpr static size_t kSmallSectionSize = 128;

template <class Size> Size slg2(Size n) {
  Size k = 0;
  for (; n > 1; n >>= 1)
    ++k;
  return k;
}

template <class RandomIter, class T>
RandomIter unchecked_partition(RandomIter first, RandomIter last,
                               const T &pivot) {
  while (true) {
    while (*first < pivot)
      ++first;
    --last;
    while (pivot < *last)
      --last;
    if (!(first < last))
      return first;
    tiny_stl::iter_swap(first, last);
    ++first;
  }
}

template <class RandomIter, class Size>
void intro_sort(RandomIter first, RandomIter last, Size depth_limit) {
  while (static_cast<size_t>(last - first) > kSmallSectionSize) {
    if (depth_limit == 0) {
      tiny_stl::partial_sort(first, last, last);
      return;
    }
    --depth_limit;
    auto mid =
        tiny_stl::median(*(first), *(first + (last - first) / 2), *(last - 1));
    auto cut = tiny_stl::unchecked_partition(first, last, mid);
    tiny_stl::intro_sort(cut, last, depth_limit);
    last = cut;
  }
}

template <class RandomIter, class T>
void unchecked_linear_insert(RandomIter last, const T &value) {
  auto next = last;
  --next;
  while (value < *next) {
    *last = *next;
    last = next;
    --next;
  }
  *last = value;
}

template <class RandomIter>
void unchecked_insertion_sort(RandomIter first, RandomIter last) {
  for (auto i = first; i != last; ++i) {
    tiny_stl::unchecked_linear_insert(i, *i);
  }
}

template <class RandomIter>
void insertion_sort(RandomIter first, RandomIter last) {
  if (first == last)
    return;
  for (auto i = first + 1; i != last; ++i) {
    auto value = *i;
    if (value < *first) {
      tiny_stl::copy_backward(first, i, i + 1);
      *first = value;
    } else {
      tiny_stl::unchecked_linear_insert(i, value);
    }
  }
}

template <class RandomIter>
void final_insertion_sort(RandomIter first, RandomIter last) {
  if (static_cast<size_t>(last - first) > kSmallSectionSize) {
    tiny_stl::insertion_sort(first, first + kSmallSectionSize);
    tiny_stl::unchecked_insertion_sort(first + kSmallSectionSize, last);
  } else {
    tiny_stl::insertion_sort(first, last);
  }
}

template <class RandomIter> void sort(RandomIter first, RandomIter last) {
  if (first != last) {
    tiny_stl::intro_sort(first, last, slg2(last - first) * 2);
    tiny_stl::final_insertion_sort(first, last);
  }
}

template <class RandomIter, class T, class Compared>
RandomIter unchecked_partition(RandomIter first, RandomIter last,
                               const T &pivot, Compared comp) {
  while (true) {
    while (comp(*first, pivot))
      ++first;
    --last;
    while (comp(pivot, *last))
      --last;
    if (!(first < last))
      return first;
    tiny_stl::iter_swap(first, last);
    ++first;
  }
}

template <class RandomIter, class Size, class Compared>
void intro_sort(RandomIter first, RandomIter last, Size depth_limit,
                Compared comp) {
  while (static_cast<size_t>(last - first) > kSmallSectionSize) {
    if (depth_limit == 0) {
      tiny_stl::partial_sort(first, last, last, comp);
      return;
    }
    --depth_limit;
    auto mid =
        tiny_stl::median(*(first), *(first + (last - first) / 2), *(last - 1));
    auto cut = tiny_stl::unchecked_partition(first, last, mid, comp);
    tiny_stl::intro_sort(cut, last, depth_limit, comp);
    last = cut;
  }
}

template <class RandomIter, class T, class Compared>
void unchecked_linear_insert(RandomIter last, const T &value, Compared comp) {
  auto next = last;
  --next;
  while (comp(value, *next)) {
    *last = *next;
    last = next;
    --next;
  }
  *last = value;
}

template <class RandomIter, class Compared>
void unchecked_insertion_sort(RandomIter first, RandomIter last,
                              Compared comp) {
  for (auto i = first; i != last; ++i) {
    tiny_stl::unchecked_linear_insert(i, *i, comp);
  }
}

template <class RandomIter, class Compared>
void insertion_sort(RandomIter first, RandomIter last, Compared comp) {
  if (first == last)
    return;
  for (auto i = first + 1; i != last; ++i) {
    auto value = *i;
    if (comp(value, *first)) {
      tiny_stl::copy_backward(first, i, i + 1);
      *first = value;
    } else {
      tiny_stl::unchecked_linear_insert(i, value, comp);
    }
  }
}

template <class RandomIter, class Compared>
void final_insertion_sort(RandomIter first, RandomIter last, Compared comp) {
  if (static_cast<size_t>(last - first) > kSmallSectionSize) {
    tiny_stl::insertion_sort(first, first + kSmallSectionSize, comp);
    tiny_stl::unchecked_insertion_sort(first + kSmallSectionSize, last, comp);
  } else {
    tiny_stl::insertion_sort(first, last, comp);
  }
}

template <class RandomIter, class Compared>
void sort(RandomIter first, RandomIter last, Compared comp) {
  if (first != last) {
    tiny_stl::intro_sort(first, last, slg2(last - first) * 2, comp);
    tiny_stl::final_insertion_sort(first, last, comp);
  }
}

template <class RandomIter>
void nth_element(RandomIter first, RandomIter nth, RandomIter last) {
  if (nth == last)
    return;
  while (last - first > 3) {
    auto cut = tiny_stl::unchecked_partition(
        first, last,
        tiny_stl::median(*first, *(first + (last - first) / 2), *(last - 1)));
    if (cut <= nth)
      first = cut;
    else
      last = cut;
  }
  tiny_stl::insertion_sort(first, last);
}

template <class RandomIter, class Compared>
void nth_element(RandomIter first, RandomIter nth, RandomIter last,
                 Compared comp) {
  if (nth == last)
    return;
  while (last - first > 3) {
    auto cut = tiny_stl::unchecked_partition(
        first, last,
        tiny_stl::median(*first, *(first + (last - first) / 2), *(last - 1)),
        comp);
    if (cut <= nth)
      first = cut;
    else
      last = cut;
  }
  tiny_stl::insertion_sort(first, last, comp);
}

template <class InputIter, class ForwardIter>
ForwardIter unique_copy_dispatch(InputIter first, InputIter last,
                                 ForwardIter result, forward_iterator_tag) {
  *result = *first;
  while (++first != last) {
    if (*result != *first)
      *++result = *first;
  }
  return ++result;
}

template <class InputIter, class OutputIter>
OutputIter unique_copy_dispatch(InputIter first, InputIter last,
                                OutputIter result, output_iterator_tag) {
  auto value = *first;
  *result = value;
  while (++first != last) {
    if (value != *first) {
      value = *first;
      *++result = value;
    }
  }
  return ++result;
}

template <class InputIter, class OutputIter>
OutputIter unique_copy(InputIter first, InputIter last, OutputIter result) {
  if (first == last)
    return result;
  return tiny_stl::unique_copy_dispatch(first, last, result,
                                        iterator_category(result));
}

template <class InputIter, class ForwardIter, class Compared>
ForwardIter unique_copy_dispatch(InputIter first, InputIter last,
                                 ForwardIter result, forward_iterator_tag,
                                 Compared comp) {
  *result = *first;
  while (++first != last) {
    if (!comp(*result, *first))
      *++result = *first;
  }
  return ++result;
}

template <class InputIter, class OutputIter, class Compared>
OutputIter unique_copy_dispatch(InputIter first, InputIter last,
                                OutputIter result, output_iterator_tag,
                                Compared comp) {
  auto value = *first;
  *result = value;
  while (++first != last) {
    if (!comp(value, *first)) {
      value = *first;
      *++result = value;
    }
  }
  return ++result;
}

template <class InputIter, class OutputIter, class Compared>
OutputIter unique_copy(InputIter first, InputIter last, OutputIter result,
                       Compared comp) {
  if (first == last)
    return result;
  return tiny_stl::unique_copy_dispatch(first, last, result,
                                        iterator_category(result), comp);
}

template <class ForwardIter>
ForwardIter unique(ForwardIter first, ForwardIter last) {
  first = tiny_stl::adjacent_find(first, last);
  return tiny_stl::unique_copy(first, last, first);
}

template <class ForwardIter, class Compared>
ForwardIter unique(ForwardIter first, ForwardIter last, Compared comp) {
  first = tiny_stl::adjacent_find(first, last, comp);
  return tiny_stl::unique_copy(first, last, first, comp);
}

} // namespace tiny_stl

#endif // TINY_STL__INCLUDE__ALGO_HPP
