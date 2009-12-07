////////////////////////////////////////////////////////////////////////////////
// ChipOcho - A Simple Chip8 Emulator
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-06 16:15:34 by Eric Scrivner>
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
  class Timers;
  class Video;

  //////////////////////////////////////////////////////////////////////////////
  // Class: Cpu
  //
  // Emulates the Chip8 CPU by stepping through memory and executing the
  // instructions stored there.
  class Cpu {
  public:
    Cpu(Memory* memory, Video* video, Timers* timers)
      : pc_(LOAD_OFFSET), i_(0), opcode_(0), stack_ptr_(0),
        memory_(memory), video_(video), timers_(timers) {
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
    void cls(); // Clear the screen
    void ret(); // Return from subroutine
    void jp(); // Jump to an address
    void call(); // Call a subroutine
    void seri(); // Skip next instruction if VX == KK
    void sne();  // Skip next instruction if VX != KK
    void serr(); // Skip next instruction if VX == VY
    void ldri(); // VX = KK
    void addri(); // VX += KK
    void ldrr(); // VX = VY
    void orrr(); // VX = VX or VY
    void andrr(); // VX = VX and VY
    void xorrr(); // VX = VX xor VY
    void addrr(); // VX += VY, VF = carry
    void sub(); // VX -= VY, VF = not borrow
    void shr(); // VX >>= 1, VF = carry
    void subn(); // VX = VY - VX, VF = not borrow
    void shl(); // VX <<= 1, VF = carry
    void snerr(); // Skip next instruction if VX != VY
    void ldi(); // I = NNN
    void jpo(); // Jump to NNN + V0
    void rnd(); // VX = rand() & KK
    void drw(); // Draw sprite at (VX, VY) from Mem(I), VF = collision
                       // If N = 0 16x16 sprite else 8xN sprite
    void skp(); // Skip next instruction if key VX pressed
    void sknp(); // Skip next instruction key VX not pressed
    void ldrd(); // VX = Delay timer
    void ldrk(); // Waits for keypress and stores value in VX
    void lddr(); // Delay timer = VX
    void ldsr(); // Sound timer = VX
    void addi(); // I += VX
    void ldf(); // I = address of 4x5 sprite for character VX
    void bcd(); // BCD encode VX into Mem(I)..Mem(I + 2)
    void saveregs(); // Save V0..VX starting at Mem(I)
    void loadregs(); // Load V0..VX starting at Mem(I)

    Word pc_;                   // Program counter
    Word i_;                    // The address register
    Byte v_[NUM_REGS];          // The registers
    Word opcode_;               // The current opcode
    Word stack_[STACK_DEPTH];   // The call stack
    Word stack_ptr_;            // The current stack index
    
    Memory* memory_; // The memory object used by the CPU
    Video*  video_;  // The video object used by the CPU
    Timers* timers_; // The timers
  };
}

#endif // CPU_H__
