////////////////////////////////////////////////////////////////////////////////
// ChipOcho - A Simple Chip8 Emulator
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-05 16:15:10 by Eric Scrivner>
//
// Description:
//   Constants which are referenced throughout the emulator.
////////////////////////////////////////////////////////////////////////////////
#ifndef CONSTANTS_H__
#define CONSTANTS_H__

namespace Ocho {
  //////////////////////////////////////////////////////////////////////////////
  // Memory constants
  const unsigned int MEMORY_SIZE = 0xFFF; // Size in bytes
  // The offset in memory in bytes at which programs are loaded
  const unsigned int LOAD_OFFSET = 0x200;
  // The maximum allowable size of a program in bytes
  const unsigned int MAX_PROGRAM_SIZE = (MEMORY_SIZE - LOAD_OFFSET);

  //////////////////////////////////////////////////////////////////////////////
  // CPU constants
  const unsigned int NUM_REGS   = 0x0F; // The number of CPU registers
  const unsigned int STACK_SIZE = 0x30; // Maximum call stack depth
}

#endif // CONSTANTS_H__
