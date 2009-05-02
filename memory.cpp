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
	// Attempt to open the ROM file
	std::ifstream rom(file_name.c_str());
	
	// If the ROM file could not be opened
	if(!rom.good() || rom.eof() || !rom.is_open()) {
		// Leave this method indicating an error ocurred
		return false;
	}
	
	// Determine the size of the file
	rom.seekg(0, std::ios_base::beg);
	std::ifstream::pos_type begin = rom.tellg();
	rom.seekg(0, std::ios_base::end);
	std::streamsize rom_size = static_cast<std::streamsize>(rom.tellg() - begin);
	
	// Use this to compute the number of bytes to be read
	std::streamsize amount_to_read = std::max(MAX_CHIP_PROGRAM_SIZE, (unsigned int)rom_size);
	
	// Go to begining of file and read the ROM data into the memory at CHIP_LOAD_OFFSET
	rom.seekg(0, std::ios_base::beg);
	rom.read(&memory[CHIP_LOAD_OFFSET], amount_to_read);
	rom.close();
	
	return true;
}