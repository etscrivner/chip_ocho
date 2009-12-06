////////////////////////////////////////////////////////////////////////////////
// ChipOcho - A Simple Chip8 Emulator
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-06 12:44:49 by Eric Scrivner>
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
  class Video;

  //////////////////////////////////////////////////////////////////////////////
  // Class: Cpu
  //
  // Emulates the Chip8 CPU by stepping through memory and executing the
  // instructions stored there.
  class Cpu {
  public:
    Cpu(Memory* memory, Video* video)
      : pc_(LOAD_OFFSET), i_(0), opcode_(0), stack_ptr_(0),
        memory_(memory), video_(video) {
      memset(v_, 0, sizeof(Byte) * NUM_REGS);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: runNext
    //
    // Executes the next instruction in memory
    void runNext();
  private:
    ////////////////////////////////////////////////////////////////////////////
    // Function: push
    //
    // Pushes the given address onto the call stack
    void push(const Word& address) {
      assert(stack_ptr_ < STACK_DEPTH);
      stack_[stack_ptr_++] = address;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: top
    //
    // Returns the value at the top of the call stack
    Word top() { assert(stack_ptr_ > 0); return stack_[stack_ptr_ - 1]; }

    ////////////////////////////////////////////////////////////////////////////
    // Function: pop
    //
    // Pops the value off the top of the stack
    void pop() { assert(stack_ptr_ > 0); stack_ptr_--; }

    ////////////////////////////////////////////////////////////////////////////
    // Opcodes
    void clrscr(); // Clear the screen
    void subret(); // Return from subroutine
    void jump(); // Jump to an address
    void call(); // Call a subroutine
    void skipeqi(); // Skip next instruction if VX == KK
    void skipnei();  // Skip next instruction if VX != KK
    void skipeq(); // Skip next instruction if VX == VY
    void seti(); // VX = KK
    void addi(); // VX += KK
    void set(); // VX = VY
    void orr(); // VX = VX or VY
    void andr(); // VX = VX and VY
    void xorr(); // VX = VX xor VY
    void addc(); // VX += VY, VF = carry
    void subb(); // VX -= VY, VF = not borrow
    void shr(); // VX >>= 1, VF = carry
    void subf(); // VX = VY - VX, VF = not borrow
    void shl(); // VX <<= 1, VF = carry
    void skipne(); // Skip next instruction if VX != VY

    Word pc_; // Program counter
    Word i_; // The address register
    Byte v_[NUM_REGS]; // The registers
    Word opcode_; // The current opcode
    Word stack_[STACK_DEPTH]; // The call stack
    Word stack_ptr_; // The current stack index
    
    Memory* memory_; // The memory object used by the CPU
    Video*  video_; // The video object used by the CPU
  };
}

#endif // CPU_H__
