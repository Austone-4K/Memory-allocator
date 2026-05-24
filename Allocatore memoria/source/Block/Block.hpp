#pragma once

#include <cstdint>

struct alignas(16) Block  // alignas(16) allows the compiler to make the size of Block a multiple of 16. This alows the CPU
                          // to use the SIMD instructions
{
  bool Used = false;
  Block* Next = nullptr;
  size_t Size = 0;
};
