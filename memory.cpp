#include "memory.h"
#include "exceptions.h"

#include <fstream>
using namespace std;

Ocho::Memory::Memory() {
	// Clear memory to all zeros
	memset(memory_, 0, sizeof(Ocho::Byte) * Ocho::MEMORY_SIZE);
}

///////////////////////////////////////////////////////////////////////////////

const Ocho::Byte Ocho::Memory::read(const Ocho::Word& address) const {
	OCHO_ASSERT(address < Ocho::MEMORY_SIZE,
	            Ocho::MemoryException::bad_read(address));
	return memory_[address];
}

///////////////////////////////////////////////////////////////////////////////

const Ocho::Word Ocho::Memory::read_word(const Ocho::Word& address) const {
	OCHO_ASSERT(address < Ocho::MEMORY_SIZE - 1,
	            Ocho::MemoryException::bad_read(address));
	return SWAP_ENDIAN(*((Word*)&memory_[address]));
}

////////////////////////////////////////////////////////////////////////////////

Ocho::Byte* Ocho::Memory::read_ptr(const Ocho::Word& address) {
	OCHO_ASSERT(address < Ocho::MEMORY_SIZE,
	            Ocho::MemoryException::bad_read(address));
	return &memory_[address];
}

///////////////////////////////////////////////////////////////////////////////

void Ocho::Memory::write(const Ocho::Word& address, Ocho::Byte value) {
	OCHO_ASSERT(address < Ocho::MEMORY_SIZE,
	            Ocho::MemoryException::bad_write(address));
	memory_[address] = value;
}

///////////////////////////////////////////////////////////////////////////////

bool Ocho::Memory::load(const std::string& file_name) {
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
	streamsize amount_to_read = max(Ocho::MAX_PROGRAM_SIZE, rom_size);
	
	// Go to beginning of file and read the ROM data into the memory at CHIP_LOAD_OFFSET
	rom.seekg(0, ios_base::beg);
	rom.read((char*)&memory_[Ocho::LOAD_OFFSET], amount_to_read);
	rom.close();
	
	return true;
}
