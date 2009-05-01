#include "test_memory.h"
#include <iostream>
using namespace std;

int main(int, const char**) {
	// Run all the available test suites
	cout << "[Memory Test Suite]" << endl;
	memory_test_suite();
	
	return EXIT_SUCCESS;
}