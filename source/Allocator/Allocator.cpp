#include "Allocator/Allocator.hpp"
#include <cstdlib>
#include <new>
#include <stdexcept>
#include <format>

const int RAM_SIZE = 100;  // 100 bytes

Allocator::Allocator()
{
  mStart = static_cast<Block*>(std::malloc(RAM_SIZE));

  if (!mStart) throw std::bad_alloc();

  mStart->Size = RAM_SIZE - sizeof(Block);
  mStart->Next = nullptr;
}

void Allocator::alignBytes(size_t& bytes)
{
  /*
  EXAMPLE:
    bytes = 20
    bytes + 15 = 20 + 15 = 35
    35 = 00100011
    ~0x0F = 11110000;

    The bitwise AND does this:
    00100011 AND
    11110000 = 00100000 = 32. So 20 bytes can be contained in 32

    The bytes are aligned
  */
  bytes = (bytes + 15) & ~0x0F;
}

void* Allocator::allocate(size_t bytes)
{
  // 1. Align the bytes to allow the CPU to optimize the reads
  alignBytes(bytes);

  Block* current = mStart;
  while (current)
  {
    // Find the first block of memory starting from the first
    if (!current->Used && current->Size >= bytes)
    {
      if (current->Size >= sizeof(Block) + bytes)
      {
        // casting Block* to char* to work byte-by-byte
        Block* newBlock = reinterpret_cast<Block*>(reinterpret_cast<char*>(current) + sizeof(Block) + bytes);
        newBlock->Size = current->Size - bytes - sizeof(Block);
        newBlock->Used = false;
        newBlock->Next = current->Next;  // places the new block in the middle of current and current->Next

        current->Size = bytes;
        current->Next = newBlock;
      }

      current->Used = true;
      return reinterpret_cast<char*>(current) + sizeof(Block);
    }

    current = current->Next;
  }

  throw std::runtime_error("BAD ALLOC: out of memory");
}

// free the memory using coalescing
void Allocator::free(void* ptr)
{
  if (!ptr) return;

  Block* current = mStart;

  while (current)
  {
    void* dataAddr = reinterpret_cast<char*>(current) + sizeof(Block);

    if (ptr == dataAddr)
    {
      current->Used = false;

      // if the next block is free, unites the blocks to avoid memory fargmentation
      if (current->Next && !current->Next->Used)
      {
        current->Size += sizeof(Block) + current->Next->Size;
        current->Next = current->Next->Next;
      }

      // stops the cycle
      return;
    }

    current = current->Next;
  }
}

size_t Allocator::getFreeRAM() const
{
  size_t counter = 0;
  Block* current = mStart;
  while (current)
  {
    if (!current->Used) counter += current->Size;

    current = current->Next;
  }

  return counter;
}

int Allocator::getBlockNumber() const
{
  int counter = 0;
  Block* current = mStart;
  while (current)
  {
    counter++;

    current = current->Next;
  }

  return counter;
}