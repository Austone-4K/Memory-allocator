# Memory-allocator
A memory allocator, written in C++

# Functionalities
- Allocation and deallocation using memory coalescing.
- Functions to get the available RAM and the number of the existing blocks

# How to install it
  1. Clone the repository
  2. ```bash
     mkdir build && cd build
     cmake ..
     cmake --build .
     ```

Quick Start (How to Use) with CMakeLists.txt:
```cmake
  cmake_minimum_required(VERSION 3.25)

  project(Allocator)

  set(CMAKE_CXX_STANDARD 23)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

  add_library(Allocator
    source/Allocator/Allocator.cpp
  )

  target_include_directories(Allocator 
    PUBLIC 
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>
      $<INSTALL_INTERFACE:include>
  )
```

To try in your main.cpp:
```cpp
#include "include/Allocator.hpp"

int main()
{
  Allocator alloc;
  void* ptr = alloc.allocate(10);
  alloc.free(ptr);
}
```
