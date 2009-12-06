////////////////////////////////////////////////////////////////////////////////
// ChipOcho - A Simple Chip8 Emulator
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-06 12:14:46 by Eric Scrivner>
//
// Description:
//   Class which emulates the Chip8 CPU.
////////////////////////////////////////////////////////////////////////////////
#include "cpu.h"
#include "exceptions.h"
#include "memory.h"
#include "video.h"

#define VX (v_[((opcode_ >> 8) & 0xF)])
#define VY (v_[((opcode_ >> 4) & 0xF)])
#define KK (opcode_ & 0xFF)
#define NNN (opcode_ & 0xFFF)
 
////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::runNext() {
	// Fetch the next opcode from memory
	opcode_ = memory_->read_word(pc_);

	// Increment the program counter
	pc_ += 2;

	// Decode the opcode
	switch(opcode_ & 0xF000) {
	case 0x0000: {
		switch(opcode_ & 0x0FFF) {
		case 0x00E0: clrscr(); break;
		case 0x00EE: subret(); break;
		default: throw CpuException(opcode_, pc_);
		}
	}
	case 1000: jump(); break;
	case 2000: call(); break;
	case 3000: skipeqi(); break;
	case 4000: skipnei(); break;
	case 5000: skipeq(); break;
	break;
	default: throw CpuException(opcode_, pc_);
	}
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::clrscr() {
	video_->clear_screen();
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::subret() {
	pc_ = top();
	pop();
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::jump() {
	pc_ = NNN;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::call() {
	push(pc_);
	pc_ = NNN;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::skipeqi() {
	if (VX == KK) {
		pc_ += 2;
	}
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::skipnei() {
	if (VX != KK) {
		pc_ += 2;
	}
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::skipeq() {
	if (VX == VY) {
		pc_ += 2;
	}
}
