#include "lemon.h"
#include "../memory.h"
using namespace std;

void memory_test_suite() {
	// Test Suite: Begin
	cout << "[Memory Test Suite]" << endl;
	lemon_t lemon(2);
	memory_t memory;
	
	// Test 1: Memory is initialized to all zeros
	bool is_zero = true;
	for (unsigned int i = 0; i < CHIP_OCHO_MEMORY_SIZE; i++) {
		if (memory.read(i) != 0) {
			is_zero = false;
		}
	}
	lemon.ok(is_zero, "Memory is initialized to all zeros.");
	
	// Test 2: Memory can be written to and read from
	memory.write(0x100, 0xBE);
	lemon.is<char>(0xBE, memory.read(0x100), "Memory can be written to.");
	
	// Test Suite: End
	lemon.end();
}

int main(int, const char**) {
	// Run all the available test suites
	memory_test_suite();
	
	return EXIT_SUCCESS;
}