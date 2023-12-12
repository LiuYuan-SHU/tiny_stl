/**
 * @file heap_algo.hpp
 * @author Liu Yuan (2787141886@qq.com)
 * @brief This file is the header of `heap_algo.cpp`, which contains some
 * helper functions for heap operations.
 *
 * @details This file contains the following functions:
 * - `push_heap_aux`: auxiliary function for `push_heap`.
 * - `push_heap_d`: auxiliary function for `push_heap`.
 * - `push_heap`: push an element into a heap.
 * - 'adjust_heap': adjust a heap.
 * - `pop_heap_aux`: auxiliary function for `pop_heap`.
 * - `pop_heap`: pop the top element of a heap.
 * - 'sort_heap': sort a heap into ascending order.
 * - 'make_heap': make a heap from an iterator range.
 */
#ifndef TINY_STL__INCLUDE__HEAP_ALGO_HPP
#define TINY_STL__INCLUDE__HEAP_ALGO_HPP

#include "iterator.hpp"

namespace tiny_stl {

/**
 * @brief Auxiliary function for `push_heap_d`.
 *
 * @details This function is used to push an element into a max heap.
 * The element to be pushed will be put at the end of the heap, and then
 * the heap will be adjusted to keep the heap property.
 *
 * @tparam RandomAccessIter The type of the iterator.
 * @tparam Distance The type of the distance.
 * @tparam T The type of the value.
 * @param first The start of the heap.
 * @param holeIndex The index of the hole, which is the position of the new
 * element.
 * @param topIndex The index of the top element.
 * @param value The value to be pushed.
 */
template <class RandomAccessIter, class Distance, class T>
void push_heap_aux(RandomAccessIter first, Distance holeIndex,
                   Distance topIndex, T value) {
  auto parent = (holeIndex - 1) / 2;
  while (holeIndex > topIndex && *(first + parent) < value) {
    *(first + holeIndex) = *(first + parent);
    holeIndex = parent;
    parent = (holeIndex - 1) / 2;
  }
  *(first + holeIndex) = value;
}

/**
 * @brief Auxiliary function for `push_heap`.
 *
 * @details The element to be pushed will be put at the end of the heap, and
 * then the heap will be adjusted to keep the heap property. Thus, the
 * `holeIndex` parameter of `push_heap_aux` is `last - first - 1`,  the
 * `topIndex` parameter is `0` and the `value` parameter is `*(last - 1)`.
 *
 * @tparam RandomAccessIter The type of the iterator.
 * @tparam Distance The type of the distance.
 * @param first The start of the heap.
 * @param last The end of the heap.
 */
template <class RandomAccessIter, class Distance>
void push_heap_d(RandomAccessIter first, RandomAccessIter last, Distance *) {
  tiny_stl::push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0),
                          *(last - 1));
}

/**
 * @brief Push an element into a max heap.
 * @warning The element to be pushed should be put at the end of the heap before
 * calling this function.
 *
 * @tparam RandomAccessIter The type of the iterator.
 * @param first The start of the heap.
 * @param last The end of the heap.
 */
template <class RandomAccessIter>
void push_heap(RandomAccessIter first, RandomAccessIter last) {
  tiny_stl::push_heap_d(first, last, tiny_stl::distance_type(first));
}

/**
 * @brief Auxiliary function for `push_heap_d`, with a compare function.
 *
 * @details This function is used to push an element into a max heap.
 * The element to be pushed will be put at the end of the heap, and then
 * the heap will be adjusted to keep the heap property.
 *
 * @tparam RandomAccessIter The type of the iterator.
 * @tparam Distance The type of the distance.
 * @tparam T The type of the value.
 * @tparam Compare The type of the compare function.
 * @param first The start of the heap.
 * @param holeIndex The index of the hole, which is the position of the new
 * element.
 * @param topIndex The index of the top element.
 * @param value The value to be pushed.
 * @param compare The compare function.
 */
template <class RandomAccessIter, class Distance, class T, class Compare>
void push_heap_aux(RandomAccessIter first, Distance holeIndex,
                   Distance topIndex, T value, Compare compare) {
  auto parent = (holeIndex - 1) / 2;
  while (holeIndex > topIndex && compare(*(first + parent), value)) {
    *(first + holeIndex) = *(first + parent);
    holeIndex = parent;
    parent = (parent - 1) / 2;
  }
  *(first + holeIndex) = value;
}

/**
 * @brief Auxiliary function for `push_heap`, with a compare function.
 *
 * @details The element to be pushed will be put at the end of the heap, and
 * then the heap will be adjusted to keep the heap property. Thus, the
 * `holeIndex` parameter of `push_heap_aux` is `last - first - 1`,  the
 * `topIndex` parameter is `0` and the `value` parameter is `*(last - 1)`.
 *
 * @tparam RandomAccessIter The type of the iterator.
 * @tparam Distance The type of the distance.
 * @tparam Compare The type of the compare function.
 * @param first The start of the heap.
 * @param last The end of the heap.
 * @param compare The compare function.
 */
template <class RandomAccessIter, class Compare, class Distance>
void push_heap_d(RandomAccessIter first, RandomAccessIter last, Distance *,
                 Compare compare) {
  push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0),
                *(last - 1), compare);
}

/**
 * @brief Push an element into a max heap.
 * @warning The element to be pushed should be put at the end of the heap before
 * calling this function.
 *
 * @tparam RandomAccessIter The type of the iterator.
 * @tparam Compare The type of the compare function.
 * @param first The start of the heap.
 * @param last The end of the heap.
 * @param compare The compare function.
 */
template <class RandomAccessIter, class Compare>
void push_heap(RandomAccessIter first, RandomAccessIter last, Compare compare) {
  tiny_stl::push_heap_d(first, last, tiny_stl::distance_type(first), compare);
}

/**
 * @brief Auxiliary function for `pop_heap`.
 *
 * @details This function is called in `pop_heap`, which is used to keep the
 * heap property after popping the top element of the heap. For example, a
 * max heap is given as follows:
 * @code{.cpp}
 * int example[] = {7, 3, 5, 1, 2, 4, 6};
 * @endcode
 * Now we want to pop the top element, which is `7`. We can swap `7` and `6`,
 * which will be like this:
 * @code
 * int example[] = {6, 3, 5, 1, 2, 4, 7};
 * @endcode
 * To keep the heap property, we need to first percolate down the element `2`,
 * and then percolate up the elements which are swapped when percolating down.
 * The percolating down process is like this:
 * @code{.cpp}
 * // At first, the hole is at index 0, `6` has children `3` and `5`.
 * int example[] = {6, 3, 5, 1, 2, 4, 7};
 * // `5` is greater than `3`, so assign `5` to the hole.
 * // Now hole is at index 2, has child `4`
 * int example[] = {5, 3, 5, 1, 2, 4, 7};
 * // Assign the only child to the hole. Now hole is at index 4, has no child.
 * int example[] = {5, 3, 4, 1, 2, 4, 7};
 * @endcode
 * After this, delete is finished. Now we need to re-push the element `6` into
 * the heap, which is the reason why we call `heap_push_aux`.
 *
 * @tparam RandomAccessIter The type of the iterator.
 * @tparam T The type of the value.
 * @tparam Distance The type of the distance.
 * @param first The start of the heap.
 * @param holeIndex The index of the hole, which is usually `0`, for the top
 * element is popped.
 * @param len The length of the heap.
 * @param value The value at the end of the heap, which will be re-pushed into
 * the heap.
 */
template <class RandomAccessIter, class T, class Distance>
void adjust_heap(RandomAccessIter first, Distance holeIndex, Distance len,
                 T value) {
  auto topIndex = holeIndex;
  auto rchild = 2 * holeIndex + 2;
  while (rchild < len) {
    if (*(first + rchild) <
        *(first + rchild - 1)) { // choose the greater elem in the children
      --rchild;
    }
    *(first + holeIndex) =
        *(first + rchild); // Assign the greater child to the hole.
    holeIndex = rchild;
    rchild = 2 * (rchild + 1);
  }
  if (rchild == len) {
    *(first + holeIndex) = *(first + (rchild - 1));
    holeIndex = rchild - 1;
  }
  tiny_stl::push_heap_aux(first, holeIndex, topIndex,
                          value); // Re-push the value.
}

/**
 * @brief Auxiliary function for `pop_heap`
 *
 * @details This function move the first value to the end of the heap, decrease
 * the size of heap by `1` and call `adjust_heap` to re-push the last element to
 * keep the heap property.
 *
 * @tparam RandomAccessIter The type of the iterator.
 * @tparam T The type of the value.
 * @tparam Distance The type of the distance.
 * @param first The start of the heap.
 * @param last The end of the heap.
 * @param dest The destination of the last element.
 * @param value The value at the end of the heap, which will be re-pushed into
 * the heap.
 */
template <class RandomAccessIter, class T, class Distance>
void pop_heap_aux(RandomAccessIter first, RandomAccessIter last,
                  RandomAccessIter dest, T value, Distance *) {
  *dest = *first;
  tiny_stl::adjust_heap(first, static_cast<Distance>(0), last - first, value);
}

/**
 * @brief Move the first element in the heap to the end of the heap, and
 * re-push the last element to keep the heap property.
 *
 * @tparam RandomAccessIter The type of the iterator.
 * @param first The start of the heap.
 * @param last The end of the heap.
 */
template <class RandomAccessIter>
void pop_heap(RandomAccessIter first, RandomAccessIter last) {
  tiny_stl::pop_heap_aux(first, last - 1, last - 1, *(last - 1),
                         distance_type(first));
}

/**
 * @brief Auxiliary function with comparer for `pop_heap_d`.
 *
 * @tparam RandomAccessIter The type of the iterator.
 * @tparam T The type of the value.
 * @tparam Distance The type of the distance.
 * @tparam Compare The type of the comparer.
 * @param first The start of the heap.
 * @param holeIndex The index of the hole, which is `0`, for the top element is
 * popped.
 * @param len The length of the heap.
 * @param value The value at the end of the heap, which will be re-pushed into
 * @param compare The comparer.
 */
template <class RandomAccessIter, class T, class Distance, class Compare>
void adjust_heap(RandomAccessIter first, Distance holeIndex, Distance len,
                 T value, Compare compare) {
  auto topIndex = holeIndex;
  auto rchild = 2 * holeIndex + 2;
  while (rchild < len) {
    if (compare(*(first + rchild), *(first + rchild - 1))) {
      --rchild;
    }
    *(first + holeIndex) = *(first + rchild);
    holeIndex = rchild;
    rchild = 2 * (rchild + 1);
  }
  if (rchild == len) {
    *(first + holeIndex) = *(first + (rchild - 1));
    holeIndex = rchild - 1;
  }
  tiny_stl::push_heap_aux(first, holeIndex, topIndex, value, compare);
}

/**
 * @brief Auxiliary function for `pop_heap` with comparer.
 *
 * @details This function move the first value to the end of the heap, decrease
 * the size of heap by `1` and call `adjust_heap` to re-push the last element to
 * keep the heap property.
 *
 * @tparam RandomAccessIter The type of the iterator.
 * @tparam T The type of the value.
 * @tparam Distance The type of the distance.
 * @tparam Compare The type of the comparer.
 * @param first The start of the heap.
 * @param last The end of the heap.
 * @param dest The destination of the last element.
 * @param value The value at the end of the heap, which will be re-pushed into
 * the heap.
 * @param compare The comparer.
 */
template <class RandomAccessIter, class T, class Distance, class Compare>
void pop_heap_aux(RandomAccessIter first, RandomAccessIter last,
                  RandomAccessIter dest, T value, Distance *, Compare compare) {
  *dest = *first;
  tiny_stl::adjust_heap(first, static_cast<Distance>(0), last - first, value,
                        compare);
}

/**
 * @brief Move the first element in the heap to the end of the heap, and
 * re-push the last element to keep the heap property.
 *
 * @tparam RandomAccessIter The type of the iterator.
 * @tparam Compare The type of the comparer.
 * @param first The start of the heap.
 * @param last The end of the heap.
 * @param compare The comparer.
 */
template <class RandomAccessIter, class Compare>
void pop_heap(RandomAccessIter first, RandomAccessIter last, Compare compare) {
  tiny_stl::pop_heap_aux(first, last - 1, last - 1, *(last - 1),
                         distance_type(first), compare);
}

/**
 * @brief Sort a heap into ascending order.
 *
 * @tparam RandomAccessIter The type of the iterator.
 * @param first The start of the heap.
 * @param last The end of the heap.
 */
template <class RandomAccessIter>
void sort_heap(RandomAccessIter first, RandomAccessIter last) {
  while (last - first > 1) {
    tiny_stl::pop_heap(first, last--);
  }
}

/**
 * @brief Sort a heap into ascending order.
 *
 * @tparam RandomAccessIter The type of the iterator.
 * @tparam Compare The type of the comparer.
 * @param first The start of the heap.
 * @param last The end of the heap.
 * @param compare The comparer.
 */
template <class RandomAccessIter, class Compare>
void sort_heap(RandomAccessIter first, RandomAccessIter last, Compare compare) {
  while (last - first > 1) {
    tiny_stl::pop_heap(first, last--, compare);
  }
}

/**
 * @brief Auxiliary function for `make_heap`
 *
 * @details Start from the last parent node, adjust the heap from bottom to top.
 * The last parent node is the last subtree which has children at index `2 * i +
 * 1` and `2 * i + 2`, where `i` is the index of the last parent node.
 *
 * @tparam RandomAccessIter The type of the iterator.
 * @tparam Distance The type of the distance.
 * @param first The start of the heap.
 * @param last The end of the heap.
 */
template <class RandomAccessIter, class Distance>
void make_heap_aux(RandomAccessIter first, RandomAccessIter last, Distance *) {
  // If the size of the heap is less than 2, it is already a heap
  if (last - first < 2) {
    return;
  }

  auto len = last - first;
  auto holeIndex = (len - 2) / 2; // The last parent node index
  while (true) {
    tiny_stl::adjust_heap(first, holeIndex, len, *(first + holeIndex));
    if (holeIndex == 0) {
      return;
    }
    holeIndex--; // Adjust all parent node till the root
  }
}

/**
 * @brief Make a heap from an iterator range.
 *
 * @tparam RandomAccessIter The type of the iterator.
 * @param first The start of the heap.
 * @param last The end of the heap.
 */
template <class RandomAccessIter>
void make_heap(RandomAccessIter first, RandomAccessIter last) {
  tiny_stl::make_heap_aux(first, last, distance_type(first));
}

/**
 * @brief Auxiliary function for `make_heap` with comparer.
 *
 * @details Start from the last parent node, adjust the heap from bottom to top.
 * The last parent node is the last subtree which has children at index `2 * i +
 * 1` and `2 * i + 2`, where `i` is the index of the last parent node.
 *
 * @tparam RandomAccessIter The type of the iterator.
 * @tparam Distance The type of the distance.
 * @tparam Compare The type of the comparer.
 * @param first The start of the heap.
 * @param last The end of the heap.
 * @param compare The comparer.
 */
template <class RandomAccessIter, class Distance, class Compare>
void make_heap_aux(RandomAccessIter first, RandomAccessIter last, Distance *,
                   Compare compare) {
  if (last - first < 2) {
    return;
  }
  auto len = last - first;
  auto holeIndex = (len - 2) / 2;
  while (true) {
    tiny_stl::adjust_heap(first, holeIndex, len, *(first + holeIndex), compare);
    if (holeIndex == 0) {
      return;
    }
    holeIndex--;
  }
}

/**
 * @brief Make a heap from an iterator range.
 *
 * @tparam RandomAccessIter The type of the iterator.
 * @tparam Compare The type of the comparer.
 * @param first The start of the heap.
 * @param last The end of the heap.
 * @param compare The comparer.
 */
template <class RandomAccessIter, class Compare>
void make_heap(RandomAccessIter first, RandomAccessIter last, Compare compare) {
  tiny_stl::make_heap_aux(first, last, distance_type(first), compare);
}

} // namespace tiny_stl

#endif // !TINY_STL__INCLUDE__HEAP_ALGO_HPP
