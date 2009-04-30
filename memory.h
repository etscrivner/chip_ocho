#ifndef MEMORY_H_KRVI8REV
#define MEMORY_H_KRVI8REV

#include "constants.h"
#include <string>

class memory_t
{
public:
	// Function: memory_t
	//
	// Clears the memory to all zeroes
	memory_t ();
	
	// Function: read
	//
	// Parameters:
	//    address - The byte address in memory
	//
	// Returns the value at the given address in memory
	const char& read(const unsigned int& address) const;
	
	// Function: write
	//
	// Parameters:
	//    address - The byte address in memory
	//    value - The value to be written
	//
	// Writes the given value at the given address in memory
	void write(const unsigned int& address, char value);
	
	// Function: load
	//
	// Parameters:
	//    file_name - The name of the file to be loaded
	//
	// Loads the given file into memory at the offset CHIP_OCHO_LOAD_OFFSET.
	// Returns true if the file was loaded into memory, false otherwise.
	bool load(const std::string& file_name);
private:
	char memory[CHIP_OCHO_MEMORY_SIZE]; // The memory
};

#endif /* end of include guard: MEMORY_H_KRVI8REV */
