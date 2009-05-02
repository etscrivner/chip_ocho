#ifndef MEMORY_H_KRVI8REV
#define MEMORY_H_KRVI8REV

#include <string>
#include "types.h"
#include "constants.h"

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
	const byte& read (const two_bytes& address) const;
	
	// Function: read_two_bytes
	//
	// Parameters:
	//    address - The byte address in memory
	//
	// Returns a two byte value whose uppermost byte is at
	// address at whose lower byte is at address + 1.
	const two_bytes& read_two_bytes(const two_bytes& address) const;
	
	// Function: write
	//
	// Parameters:
	//    address - The byte address in memory
	//    value - The value to be written
	//
	// Writes the given value at the given address in memory
	void write (const two_bytes& address, byte value);
	
	// Function: load
	//
	// Parameters:
	//    file_name - The name of the file to be loaded
	//
	// Loads the given file into memory at the offset CHIP_OCHO_LOAD_OFFSET.
	// Returns true if the file was loaded into memory, false otherwise.
	bool load (const std::string& file_name);
private:
	byte memory[CHIP_OCHO_MEMORY_SIZE]; // The memory
};

#endif /* end of include guard: MEMORY_H_KRVI8REV */
