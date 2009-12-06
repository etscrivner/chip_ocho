////////////////////////////////////////////////////////////////////////////////
// ChipOcho - A Simple Chip8 Emulator
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-05 16:19:51 by Eric Scrivner>
//
// Description:
//   Class which emulates the Chip8 CPU.
////////////////////////////////////////////////////////////////////////////////
#ifndef CPU_H__
#define CPU_H__

#include "types.h"

namespace Ocho {
  /////////////////////////////////////////////////////////////////////////////
  // Class: Cpu
  //
  // Emulates the Chip8 CPU by stepping through memory and executing the
  // instructions stored there.
  class Cpu {
  public:
  private:
    Word pc_; // Program counter
  };
}

#endif // CPU_H__
