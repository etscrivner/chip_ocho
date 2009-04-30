#include "memory.h"
#include <fstream>

// Function: memory::memory_t
//
// Clears the memory to all zeroes
memory_t::memory_t () {
	memset(memory, 0, sizeof(memory[0]) * CHIP_OCHO_MEMORY_SIZE);
}

// Function: memory::read
//
// Parameters:
//    address - The byte address in memory
//
// Returns the value at the given address in memory
const char& memory_t::read(const unsigned int& address) const {
	if(address >= CHIP_OCHO_MEMORY_SIZE)
		return memory[0];
			
	return memory[address];
}

// Function: memory::write
//
// Parameters:
//    address - The byte address in memory
//    value - The value to be written
//
// Writes the given value at the given address in memory
void memory_t::write(const unsigned int& address, char value) {
	if(address >= CHIP_OCHO_MEMORY_SIZE)
		return;
		
	memory[address] = value;
}

// Function: memory::load
//
// Parameters:
//    file_name - The name of the file to be loaded
//
// Loads the given file into memory at the offset CHIP_OCHO_LOAD_OFFSET.
// Returns true if the file was loaded into memory, false otherwise.
bool memory_t::load(const std::string& file_name) {
	std::ifstream rom(file_name.c_str());
	
	if(!rom.is_open())
		return false;
		
	rom.read(memory, sizeof(memory[0]) * CHIP_OCHO_MEMORY_SIZE);
	return true;
}