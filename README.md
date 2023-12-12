# tiny_stl

> A subset of STL, implemented in C++17, CMake, XMake, GTest and Doxygen

XMake 生成项目:

<img src="README.assets/image-20231212130055137.png" alt="image-20231212130055137" style="zoom:50%;" />

运行测试:

<img src="README.assets/image-20231212130249544.png" alt="image-20231212130249544" style="zoom:50%;" />

生成文档:

<img src="README.assets/image-20231212130350849.png" alt="image-20231212130350849" style="zoom: 25%;" />

<img src="README.assets/image-20231212131007855.png" alt="image-20231212131007855" style="zoom:25%;" />

## Quick Start

### 安装C++环境

### 安装 XMake/CMake

> 更推荐 XMake

1. XMake: https://github.com/xmake-io/xmake
2. CMake: https://cmake.org/download/

### 安装 GTest

1. 使用 Xrepo
   ```shell
   xrepo install -m debug gtest
   ```
   如果使用 xrepo 安装,xmake 会自行进行调度. 不推荐使用 xrepo 与 cmake 混用, 配置上会带来一定的麻烦
2. 使用包管理器直接安装: 更推荐在 Linux 环境下进行这样的操作

### 安装 Doxygen(文档生成)

1. xrepo
2. 包管理器

### 运行

#### XMake

```shell
xmake
# 运行测试
xmake run test
# 生成文档
xmake run doc
```

#### CMake

```shell
cmake -B build && cd build
# test
make build && ./test/test   # 可执行文件位于: project_dir/build/test
# doc
make doc                    # 网页文件位于: project_dir/build/doc/html/index.html
```

## 项目结构

```
tiny_stl
├── CMakeLists.txt      # CMake 顶层文件
├── LICENSE             # MIT 许可
├── README.md           # 本文件
├── doc                 # 文档      
│   ├── CMakeLists.txt      # CMake 配置文件
│   ├── Doxyfile.in         # Doxygen 配置文件模板文件
│   └── xmake.lua           # XMake 配置文件
├── include             # 头文件
├── test                # 测试
│   ├── CMakeLists.txt      # CMake 配置文件
│   ├── algo.hpp            # 诸如此类的文件夹都是测试文件
│   ├── main.cpp            # 测试入口
│   └── xmake.lua           # XMake 配置文件
└── xmake.lua           # 顶层 XMake 配置文件
```

[TOC]

## 代码实现顺序 & 笔记

```mermaid
flowchart TD

subgraph v0.1.x
  iterator[iterator.hpp]
  type_traits[type_traits.hpp]
  utility[utility.hpp]
  functional[functional.hpp]
end

subgraph v0.2.x
  construct[construct.hpp]
  algobase[algobase.hpp]
  allocator[allocator.hpp]
  uninitialized[uninitialized.hpp]
  memory[memory.hpp]
  heap_algo[heap_algo.hpp]
end

subgraph v0.3.x
  algo[algo.hpp]
end

type_traits --> iterator
utility --> type_traits
construct --> iterator & type_traits
algobase --> utility & iterator
allocator --> construct & utility
uninitialized --> algobase & construct & iterator & utility
memory --> construct & iterator & uninitialized & utility
heap_algo --> iterator
algo --> algobase & functional & heap_algo & iterator & memory
```

### [`type_traits.hpp`](./include/type_traits.hpp)

使用`constexpr`实现编译期常量的使用d

### [`iterator.hpp`](./include/iterator.hpp)

1. 迭代器

    - 五种迭代器类型

    - 迭代器的特征(trait)有什么

2. 萃取器

    1. 调用顺序:

      ```mermaid
      flowchart TD
      iterator_traits --has iterator_category field--> 
      iterator_traits_helper --is derived class of input_iterator_tag or output_iterator_tag--> 
      iterator_traits_impl
      ```

      

    2. SFINAE(*Substitution Failure Is Not An Error*)

      > 如果在模板参数推断或函数重载解析中，替换（substitution）某个模板导致失败，编译器将不会报错，而是会尝试选择其他备选项

      ```cpp
      /**
       * 1. Function Template overload
       * 此处尝试在第二个模板参数的位置获取 T 实例的 some_member 成员, 如果成功, 那么模板匹配成功, 实例化模板, 否则匹配失败
       */
      template <typename T, typename = decltype(std::declval<T>().some_member)>
      void someFunction(T value) {
        // Implementation for types with 'some_member'
      }
      
      template <typename T>
      void someFunction(T value) {
        // Default implementation for types without 'some_member'
      }
      ```

      ```cpp
      /**
       * 2. Template specialization
       */
      template <typename T, typename Enable = void>
      struct MyClass {
        // Default implementation
      };
      
      /**
       * 此处测试 T 是不是可以当做整型值使用, 如果匹配成功, 则实例化模板, 否则匹配失败
       */
      template <typename T>
      struct MyClass<T, std::enable_if_t<std::is_integral<T>::value>> {
        // Specialization for integral types
      };
      ```
3. `template <class T> struct iterator_traits<const T *>`: [为何`value_type`是`T`](https://stackoverflow.com/questions/12819405/why-is-stditerator-traitsvalue-type-non-const-even-for-a-const-iterator)
4. `template<class Iterator >reference [tiny_stl::reverse_iterator](classtiny__stl_1_1reverse__iterator.html)< Iterator >::operator*()const`: 为何取值操作先自减, 再取值: https://stackoverflow.com/a/74161268/16941344

### `utility.hpp`

1. [C++ 通用引用](https://www.cnblogs.com/ljx-null/p/15940982.html)
2. [移动语义和完美转发浅析](https://www.cnblogs.com/ljx-null/p/16512384.html)

```c++
// SFINAE 的第一种形式: 如果匹配成功, 那么第三个模板参数会为 void  
template <class U1 = T1, class U2 = T2,
            typename = typename std::enable_if_t<
                std::is_default_constructible_v<U1> &&
                    std::is_default_constructible_v<U2>,
                void>>
  constexpr pair() : first(), second() {}
```

```c++
// SFINAE 的第二种形式: 如果匹配成功, 那么第三个模板参数会被自动赋值为 0
// 此处为 0 并没有特殊含义, 只是提供一个初始值
template <
      class U1 = T1, class U2 = T2,
      typename std::enable_if_t<std::is_copy_constructible_v<U1> &&
                                    std::is_copy_constructible_v<U2> &&
                                    std::is_convertible_v<const U1 &, T1> &&
                                    std::is_convertible_v<const U2 &, T2>,
                                int> = 0>
  constexpr pair(const T1 &a, const T2 &b) : first(a), second(b) {}
```

### `construct.hpp`

```mermaid
flowchart TD
destroy --> destroy_cat & destroy_one
```

> 根据一个变量是否有析构函数来决定调用的时候要不要调用析构函数: `std::is_trivially_destructible`

### `algobase.hpp`

> 函数命名中的`cat`的含义为`category`, 该函数命名意味着调用这个函数的通常是带着确定类型迭代器类型的迭代器

#### `copy`

```mermaid
flowchart TD;
copy --> unchecked_copy -->unchecked_copy_cat --> input_iterator_tag & random_access_iterator_tag
unchecked_copy --trivially_copy_constructible--> memmove
```

#### `copy_backward`

```mermaid
flowchart TD;
copy_backward --> unchecked_copy_backward --> unchecked_copy_backward_cat --> bidirectional_iterator_tag & random_access_iterator_tag
unchecked_copy_backward --trivially_copy_constructible--> memmove
```

#### `copy_n`

```mermaid
flowchart TD;
copy_n --> unchecked_copy_n --input_iterator_tag--> 常规实现
unchecked_copy_n --random_access_iterator_tag--> copy
copy --> unchecked_copy -->unchecked_copy_cat --> random_access_iterator_tag
```

#### `move`

```mermaid
flowchart TD;
move --> unchecked_move  --> unchecked_move_cat --> input_iterator_tag & random_access_iterator_tag
unchecked_move --trivially_move_assignable--> memmove
```

#### `move_backward`

```mermaid
flowchart TD;
move_backward --> unchecked_move_backward --> unchecked_move_backward_cat --> bidirectional_iterator_tag & random_access_iterator_tag
unchecked_move_backward --trivially_move_assignable--> memmove
```

#### `fill_n`

```mermaid
flowchart TD;
fill_n --> unchecked_fill_n --字面常量且大小为1--> memset
```

#### `fill`

```mermaid
flowchart TD;
fill --> fill_cat --random_access_iterator_tag--> fill_n 
fill_cat --forward_iterator_tag--> 常规实现 
```

### `uninitialized.hpp`

> 在未初始化的内存上操作数据

- 对于可以直接拷贝的数据(`std::is_trivially_copy_assignable`), 直接复制, 并且再根据迭代器的类型是`input_iterator_tag`还是`random_access_iterator_tag` 来决定调用的具体函数
- 对于不可以直接拷贝的数据, 则直接在对应的内存空间上调用`construct`来构造对象

```mermaid
flowchart TD;
uninitialized_copy --trivially_copy_constructible--> copy
uninitialized_copy --non_trivially_copy_constructible--> constrcut
```
### `functional.hpp`

1. 关于模板参数的讨论: https://github.com/Alinshans/MyTinySTL/issues/141
2. FNV-1a: https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1a_hash