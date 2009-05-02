#include "memory.h"
#include "exceptions.h"
#include <fstream>
using namespace std;

memory_t::memory_t () {
	memset(memory, 0, sizeof(byte) * CHIP_OCHO_MEMORY_SIZE);
}

///////////////////////////////////////////////////////////////////////////////

const byte& memory_t::read(const two_bytes& address) const {
	if(address >= CHIP_OCHO_MEMORY_SIZE) {
		throw memory_exception_t(OUT_OF_BOUNDS_READ, address);
	}
			
	return memory[address];
}

///////////////////////////////////////////////////////////////////////////////

const two_bytes& memory_t::read_two_bytes(const two_bytes& address) const {
	if (address >= (CHIP_OCHO_MEMORY_SIZE - 1)) {
		throw memory_exception_t(OUT_OF_BOUNDS_READ, address);
	}
	
	return *((two_bytes*)&memory[address]);
}

///////////////////////////////////////////////////////////////////////////////

void memory_t::write(const two_bytes& address, byte value) {
	if(address >= CHIP_OCHO_MEMORY_SIZE) {
		throw memory_exception_t(OUT_OF_BOUNDS_WRITE, address);
	}
		
	memory[address] = value;
}

///////////////////////////////////////////////////////////////////////////////

bool memory_t::load(const std::string& file_name) {
	// Attempt to open the ROM file
	ifstream rom(file_name.c_str());
	
	// If the ROM file could not be opened
	if(!rom.good() || rom.eof() || !rom.is_open()) {
		// Leave this method indicating an error ocurred
		return false;
	}
	
	// Determine the size of the file
	rom.seekg(0, ios_base::beg);
	ifstream::pos_type begin = rom.tellg();
	rom.seekg(0, ios_base::end);
	unsigned int rom_size = static_cast<unsigned int>(rom.tellg() - begin);
	
	// Use this to compute the number of bytes to be read
	streamsize amount_to_read = max(MAX_CHIP_PROGRAM_SIZE, rom_size);
	
	// Go to beginning of file and read the ROM data into the memory at CHIP_LOAD_OFFSET
	rom.seekg(0, ios_base::beg);
	rom.read((char*)&memory[CHIP_LOAD_OFFSET], amount_to_read);
	rom.close();
	
	return true;
}