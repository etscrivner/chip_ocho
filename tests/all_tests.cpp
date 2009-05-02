#include <iostream>
#include "test_memory.h"
using namespace std;

int main(int, const char**) {
	// Run all the available test suites
	cout << "[Memory Test Suite]" << endl;
	memory_test_suite();
	
	cout << endl;
	
	return EXIT_SUCCESS;
}