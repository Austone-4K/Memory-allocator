#pragma once

#include <cstdint>
#include "Block/Block.hpp"

class Allocator
{
 public:
  Allocator();

  void* allocate(size_t bytes);

  void free(void* ptr);

  size_t getFreeRAM() const;
  int getBlockNumber() const;

 private:
  Block* mStart;

  void alignBytes(size_t& bytes);
};