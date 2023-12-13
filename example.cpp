#include <iostream>

#include <algorithm.hpp>
#include <vector.hpp>

int main() {
  tiny_stl::vector<int> vec{1, 2, 3, 4, 5};
  tiny_stl::for_each(vec.begin(), vec.end(), [](int &i) -> void { i *= i; });
  tiny_stl::copy(vec.begin(), vec.end(),
                 std::ostream_iterator<int>(std::cout, " "));
}
