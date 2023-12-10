#ifndef TINY_STL__INCLUDE__HEAP_ALGO_HPP
#define TINY_STL__INCLUDE__HEAP_ALGO_HPP

#include "iterator.hpp"

namespace tiny_stl {

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

template <class RandomAccessIter, class Distance>
void push_heap_d(RandomAccessIter first, RandomAccessIter last, Distance *) {
  tiny_stl::push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0),
                          *(last - 1));
}

template <class RandomAccessIter>
void push_heap(RandomAccessIter first, RandomAccessIter last) {
  tiny_stl::push_heap_d(first, last, tiny_stl::distance_type(first));
}

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

template <class RandomAccessIter, class Compare, class Distance>
void push_heap_d(RandomAccessIter first, RandomAccessIter last, Distance *,
                 Compare compare) {
  push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0),
                *(last - 1), compare);
}

template <class RandomAccessIter, class Compare>
void push_heap(RandomAccessIter first, RandomAccessIter last, Compare compare) {
  tiny_stl::push_heap_d(first, last, tiny_stl::distance_type(first), compare);
}

template <class RandomAccessIter, class T, class Distance>
void adjust_heap(RandomAccessIter first, Distance holeIndex, Distance len,
                 T value) {
  auto topIndex = holeIndex;
  auto rchild = 2 * holeIndex + 2;
  while (rchild < len) {
    if (*(first + rchild) < *(first + rchild - 1)) {
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
  tiny_stl::push_heap_aux(first, holeIndex, topIndex, value);
}

template <class RandomAccessIter, class T, class Distance>
void pop_heap_aux(RandomAccessIter first, RandomAccessIter last,
                  RandomAccessIter dest, T value, Distance *) {
  *dest = *first;
  tiny_stl::adjust_heap(first, static_cast<Distance>(0), last - first, value);
}

template <class RandomAccessIter>
void pop_heap(RandomAccessIter first, RandomAccessIter last) {
  tiny_stl::pop_heap_aux(first, last - 1, last - 1, *(last - 1),
                         distance_type(first));
}

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

template <class RandomAccessIter, class T, class Distance, class Compare>
void pop_heap_aux(RandomAccessIter first, RandomAccessIter last,
                  RandomAccessIter dest, T value, Distance *, Compare compare) {
  *dest = *first;
  tiny_stl::adjust_heap(first, static_cast<Distance>(0), last - first, value,
                        compare);
}

template <class RandomAccessIter, class Compare>
void pop_heap(RandomAccessIter first, RandomAccessIter last, Compare compare) {
  tiny_stl::pop_heap_aux(first, last - 1, last - 1, *(last - 1),
                         distance_type(first), compare);
}

} // namespace tiny_stl

#endif // !TINY_STL__INCLUDE__HEAP_ALGO_HPP
