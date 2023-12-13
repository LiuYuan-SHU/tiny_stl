#ifndef TINY_STL__INCLUDE__EXCEPTION_HPP
#define TINY_STL__INCLUDE__EXCEPTION_HPP

#include <stdexcept>

#include <cassert>

namespace tiny_stl {

// #TODO: disable this in release mode
#define TINY_STL__DEBUG(expr) assert(expr)

#define THROW_LENGTH_ERROR_IF(expr, what)                                      \
  if ((expr))                                                                  \
  throw std::length_error(what)

#define THROW_OUT_OF_RANGE_IF(expr, what)                                      \
  if ((expr))                                                                  \
  throw std::out_of_range(what)

#define THROW_RUNTIME_ERROR_IF(expr, what)                                     \
  if ((expr))                                                                  \
  throw std::runtime_error(what)

} // namespace tiny_stl

#endif // !TINY_STL__INCLUDE__EXCEPTION_HPP
