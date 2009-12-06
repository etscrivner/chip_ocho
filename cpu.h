////////////////////////////////////////////////////////////////////////////////
// ChipOcho - A Simple Chip8 Emulator
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-05 18:43:51 by Eric Scrivner>
//
// Description:
//   Class which emulates the Chip8 CPU.
////////////////////////////////////////////////////////////////////////////////
#ifndef CPU_H__
#define CPU_H__

#include "constants.h"
#include "types.h"

namespace Ocho {
  //////////////////////////////////////////////////////////////////////////////
  // Forward definitions
  class Memory;

  //////////////////////////////////////////////////////////////////////////////
  // Class: Cpu
  //
  // Emulates the Chip8 CPU by stepping through memory and executing the
  // instructions stored there.
  class Cpu {
  public:
    Cpu(Memory* memory)
      : memory_(memory) {
      memset(v_, 0, sizeof(Byte) * NUM_REGS);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: runNext
    //
    // Executes the next instruction in memory
    void runNext();
  private:
    Word pc_; // Program counter
    Byte v_[NUM_REGS]; // The registers
    Memory* memory_; // The memory object used by the CPU
  };
}

#endif // CPU_H__
