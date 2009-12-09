////////////////////////////////////////////////////////////////////////////////
// ChipOcho - A Simple Chip8 Emulator
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-06 21:21:00 by Eric Scrivner>
//
// Description:
//   Class which emulates the Chip8 CPU.
////////////////////////////////////////////////////////////////////////////////
#include "cpu.h"
#include "exceptions.h"
#include "input.h"
#include "memory.h"
#include "timers.h"
#include "video.h"

#include <iostream>

////////////////////////////////////////////////////////////////////////////////

#define X ((opcode_ >> 8) & 0xF)
#define Y ((opcode_ >> 4) & 0xF)
#define VX (v_[X])
#define VY (v_[Y])
#define VF (v_[0xF])
#define N (opcode_ & 0xF)
#define KK (opcode_ & 0xFF)
#define NNN (opcode_ & 0xFFF)
#define I i_
 
////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::runNext() {
	// If we're waiting for a key press then
	if (waitingForKey_) {
		if (input_->hasKey()) {
			VX = input_->getLastKey();
			waitingForKey_ = false;
		} else {
			return;
		}
	}

	// Fetch the next opcode from memory
	opcode_ = memory_->read_word(pc_);

	// Increment the program counter
	pc_ += 2;

	// Decode the opcode
	switch(opcode_ & 0xF000) {
	case 0x0000: {
		switch(opcode_ & 0x0FFF) {
		case 0x00E0: cls(); break;
		case 0x00EE: ret(); break;
		default: break;
		}
	}
	break;
	case 0x1000: jp(); break;
	case 0x2000: call(); break;
	case 0x3000: seri(); break;
	case 0x4000: sne(); break;
	case 0x5000: serr(); break;
	case 0x6000: ldri(); break;
	case 0x7000: addri(); break;
	case 0x8000: {
		switch(opcode_ & 0xF) {
		case 0x0: ldrr(); break;
		case 0x1: orrr(); break;
		case 0x2: andrr(); break;
		case 0x3: xorrr(); break;
		case 0x4: addrr(); break;
		case 0x5: sub(); break;
		case 0x6: shr(); break;
		case 0x7: subn(); break;
		case 0xE: shl(); break;
		default: throw CpuException(opcode_, pc_);
		}
	}
	break;
	case 0x9000: snerr(); break;
	case 0xA000: ldi(); break;
	case 0xB000: jpo(); break;
	case 0xC000: rnd(); break;
	case 0xD000: drw(); break;
	case 0xE000: {
		switch(opcode_ & 0xFF) {
		case 0x9E: skp(); break;
		case 0xA1: sknp(); break;
		default: throw CpuException(opcode_, pc_);
		}
	}
	break;
	case 0xF000: {
		switch(opcode_ & 0xFF) {
		case 0x07: ldrd(); break;
		case 0x0A: ldrk(); break;
		case 0x15: lddr(); break;
		case 0x18: ldsr(); break;
		case 0x1E: addi(); break;
		case 0x29: ldf(); break;
		case 0x33: bcd(); break;
		case 0x55: saveregs(); break;
		case 0x65: loadregs(); break;
		default: throw CpuException(opcode_, pc_);
		}
	}
	break;
	default: throw CpuException(opcode_, pc_);
	}
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::cls() {
	video_->clear_screen();
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::ret() {
	pc_ = top();
	pop();
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::jp() {
	pc_ = NNN;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::call() {
	push(pc_);
	pc_ = NNN;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::seri() {
	if (VX == KK) {
		pc_ += 2;
	}
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::sne() {
	if (VX != KK) {
		pc_ += 2;
	}
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::serr() {
	if (VX == VY) {
		pc_ += 2;
	}
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::ldri() {
	VX = KK;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::addri() {
	VX += KK;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::ldrr() {
	VX = VY;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::orrr() {
	VX |= VY;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::andrr() {
	VX &= VY;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::xorrr() {
	VX ^= VY;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::addrr() {
	VF = ((Word)VX + (Word)VY) >> 8;
	VX += VY;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::sub() {
	if (VY >= VX) {
		VF = 1;
	} else {
		VF = 0;
	}

	VX -= VY;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::shr() {
	VF = VX & 0x01;
	VX >>= 1;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::subn() {
	if (VY >= VX) {
		VF = 1;
	} else {
		VF = 0;
	}

	VX = VY - VX;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::shl() {
	VF = VX & 0x80;
	VF <<= 1;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::snerr() {
	if (VX != VY) {
		pc_ += 2;
	}
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::ldi() {
	I = NNN;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::jpo() {
	pc_ = NNN + v_[0];
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::rnd() {
	VX = rand() & KK;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::drw() {
	// Determine the size of the sprite
	size_t width  = 1;
	size_t height = N;
	if (N == 0) {
		width = 2;
		height = 16;
	}

	bool wasCollision = false;
	
	// Iterate through each vertical pixel...
	for (size_t y = 0; y < height; y++) {
		// and each horizontal pixel..
		for (size_t x = 0; x < width; x++) {
			// Plot the next chunk of 8 horizontal pixels
			if (video_->plot(VX, VY + y, memory_->read(I + y))) {
				wasCollision = true;
			}
		}
	}

	// Set the collision register
	VF = (wasCollision) ? 1 : 0;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::skp() {
	if (input_->isPressed(VX)) {
		pc_ += 2;
	}
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::sknp() {
	if (input_->isPressed(VX)) {
		pc_ += 2;
	}
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::ldrd() {
	VX = timers_->getDelay();
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::ldrk() {
	waitingForKey_ = true;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::lddr() {
	timers_->setDelay(VX);
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::ldsr() {
	timers_->setSound(VX);
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::addi() {
	I += VX;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::ldf() {
	I = ((Word)VX * 5);
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::bcd() {
	memory_->write(I + 2, VX % 10);
	memory_->write(I + 1, (VX / 100) % 10);
	memory_->write(I, VX / 100);
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::saveregs() {
	for (size_t i = 0; i < NUM_REGS; i++) {
		memory_->write(I + i, v_[i]);
	}
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Cpu::loadregs() {
	for (size_t i = 0; i < NUM_REGS; i++) {
		v_[i] = memory_->read(I + i);
	}
}
