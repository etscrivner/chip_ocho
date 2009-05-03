#ifndef TEST_MEMORY_H_KOSKNSB1
#define TEST_MEMORY_H_KOSKNSB1

#include "lemon.h"
#include "../memory.h"
#include "../exceptions.h"

void memory_test_suite() {
	// Test Suite
	lemon_t lemon(8);
	memory_t memory;
	
		// Test 1: Memory is initialized to all zeros
		bool is_zero = true;
		for (unsigned int i = 0; i < CHIP_OCHO_MEMORY_SIZE; i++) {
			if (memory.read(i) != 0) {
				is_zero = false;
			}
		}
		lemon.ok(is_zero, "Memory gets cleared initially to all zeros.");
	
		// Test 2: Memory can be written to and read from
		memory.write(0x100, 0xBE);
		lemon.is<unsigned char>(0xBE, memory.read(0x100),
					"You can read and write to memory.");
	
		// Test 3: Memory won't let you read out of bounds
		try {
			memory.read(0xFFF);
			lemon.fail("Memory won't let you read out of bounds.");
		} catch (memory_exception_t& e) {
			lemon.pass("Memory won't let you read out of bounds.");
		}
	
		// Test 4: Memory won't let you write out of bounds
		try {
			memory.write(0xFFF, 0xFF);
			lemon.fail("Memory won't let you write out bounds.");
		} catch(memory_exception_t& e) {
			lemon.pass("Memory won't let you write out bounds.");
		}
	
		// Test 5: Memory should fail to load non-existant files.
		lemon.not_ok(memory.load("rumble_ramble.txt"),
					"Memory fails to load non-existant files");
				
		// Test 6: Memory should succeed in loading existing file.
		lemon.ok(memory.load("tests/fixtures/memory_test_data"),
							"Memory succeeds in loading real files.");
						
		// Test 7: Memory loads data at the appropriate offset
		memory.load("tests/fixtures/memory_test_data");
		lemon.ok(std::string((char*)&memory.read(CHIP_LOAD_OFFSET)) == "TEST",
				"Memory loads data at the right offset.");
				
		// Test 8: You can read two bytes from memory at once
		memory.write(0x300, 0xEF); // My Intel is little-endian
		memory.write(0x301, 0xBE);
		lemon.is<two_bytes>(memory.read_two_bytes(0x300), 0xBEEF,
							"You can read two bytes from memory.");	
				
	// ~Test Suite
	lemon.end();
}

#endif /* end of include guard: TEST_MEMORY_H_KOSKNSB1 */
