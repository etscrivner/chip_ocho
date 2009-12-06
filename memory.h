////////////////////////////////////////////////////////////////////////////////
// ChipOcho - A Simple Chip8 Emulator
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-05 16:53:12 by Eric Scrivner>
//
// Description:
//   Class emulating Chip8 memory
////////////////////////////////////////////////////////////////////////////////
#ifndef MEMORY_H_
#define MEMORY_H_

#include <string>
#include "types.h"
#include "constants.h"

#ifdef LITTLE_ENDIAN
#define SWAP_ENDIAN(x) ((((x) >> 8) & 0xFF) | (((x) & 0xFF) << 8))
#else
#define SWAP_ENDIAN(x) (x)
#endif

namespace Ocho {
  //////////////////////////////////////////////////////////////////////////////
  // Class: Memory
  //
  // Class which emulates Chip8 memory.
  class Memory
  {
  public:
    Memory();

    ////////////////////////////////////////////////////////////////////////////
    // Function: read
    //
    // Parameters:
    //    address - The byte address in memory
    //
    // Returns the value at the given address in memory
    const Byte read(const Word& address) const;
  
    ////////////////////////////////////////////////////////////////////////////
    // Function: read_word
    //
    // Parameters:
    //    address - The byte address in memory
    //
    // Returns a word read from the given address
    const Word read_word(const Word& address) const;

    ////////////////////////////////////////////////////////////////////////////
    // Function: read_ptr
    //
    // Returns a pointer starting at the given address
    Byte* read_ptr(const Word& address);

    ////////////////////////////////////////////////////////////////////////////
    // Function: write
    //
    // Parameters:
    //    address - The byte address in memory
    //    value - The value to be written
    //
    // Writes the given value at the given address in memory
    void write(const Word& address, Byte value);
  
    ////////////////////////////////////////////////////////////////////////////
    // Function: load
    //
    // Parameters:
    //    file_name - The name of the file to be loaded
    //
    // Loads the given file into memory at the offset CHIP_OCHO_LOAD_OFFSET.
    // Returns true if the file was loaded into memory, false otherwise.
    bool load(const std::string& file_name);
  private:
    Byte memory_[MEMORY_SIZE]; // The memory
  };
}

#endif // MEMORY_H__
