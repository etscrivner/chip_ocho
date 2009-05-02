#ifndef CONSTANTS_H_Y1TH07GJ
#define CONSTANTS_H_Y1TH07GJ

#include <fstream>

// ChipOcho Memory Constants
const unsigned int CHIP_OCHO_MEMORY_SIZE = 0xFFF; // Size of memory in bytes
const unsigned int CHIP_LOAD_OFFSET = 0x200; 
	// The offset in bytes at which programs are loaded
const unsigned int MAX_CHIP_PROGRAM_SIZE = (CHIP_OCHO_MEMORY_SIZE - 
											CHIP_LOAD_OFFSET);
	// The maximum allowable size of a program

#endif /* end of include guard: CONSTANTS_H_Y1TH07GJ */
