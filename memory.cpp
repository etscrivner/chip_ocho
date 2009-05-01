#include "memory.h"
#include "exceptions.h"
#include <fstream>

memory_t::memory_t () {
	memset(memory, 0, sizeof(memory[0]) * CHIP_OCHO_MEMORY_SIZE);
}

///////////////////////////////////////////////////////////////////////////////

const char& memory_t::read(const unsigned int& address) const {
	if(address >= CHIP_OCHO_MEMORY_SIZE) {
		throw memory_exception_t(OUT_OF_BOUNDS_READ, address);
	}
			
	return memory[address];
}

///////////////////////////////////////////////////////////////////////////////

void memory_t::write(const unsigned int& address, char value) {
	if(address >= CHIP_OCHO_MEMORY_SIZE) {
		throw memory_exception_t(OUT_OF_BOUNDS_WRITE, address);
	}
		
	memory[address] = value;
}

///////////////////////////////////////////////////////////////////////////////

bool memory_t::load(const std::string& file_name) {
	std::ifstream rom(file_name.c_str());
	
	if(!rom.is_open())
		return false;
		
	rom.read(&memory[CHIP_LOAD_OFFSET],
			sizeof(memory[0]) * (CHIP_OCHO_MEMORY_SIZE - CHIP_LOAD_OFFSET));
	return true;
}