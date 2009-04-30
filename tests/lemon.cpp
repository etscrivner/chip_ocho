#include "lemon.h"
using namespace std;

lemon_t::lemon_t(unsigned int num_planned_tests)
: num_tests(num_planned_tests),
  test_number(0),
  num_skipped(0),
  num_failed(0)
{
	cout << "1.." << num_planned_tests << endl;
}

///////////////////////////////////////////////////////////////////////////////

void lemon_t::end() {
	// If any tests were skipped
	if (num_skipped > 0) {
		// Display information about the skipped tests
		cout << "# Looks like you planned " << num_tests;
		cout << " but only ran " << (num_tests - num_skipped) << ".\n";	
	}
	
	// If any tests were failed
	if (num_failed > 0) {
		// Display test failure statistics
		cout << "# Looks like you failed " << num_failed;
		cout << " of " << num_tests << " tests.\n";
	} else {
		// Otherwise tell you how well you did
		cout << "# Looks like you passed all " << num_tests << " tests.\n";
	}
}

///////////////////////////////////////////////////////////////////////////////

void lemon_t::diag(const std::string& message) {
	cout << "# " << message << "\n";
}

///////////////////////////////////////////////////////////////////////////////

bool lemon_t::ok(bool passed, const std::string& test_name) {
	// Increment the number of tests run
	num_tests++;
	
	// If this is a skip or todo message
	if (test_name[0] != '#') {
		// Append a dash to the front
		const_cast<string&>(test_name) = "- " + test_name;
		//test_name = "- " + test_name;
	}
	
	// If the test was passed
	if (passed) {
		// Inform you that the test passed
		cout << "ok " << num_tests << " " << test_name << "\n";
	} else {
		// Otherwise increment the number of failed tests
		num_failed++;
		
		// Inform you that the test failed
		cout << "not ok " << num_tests << " " << test_name << "\n";
		diag("  Test failed, expected <true> but was <false>");
	}
	
	return passed;
}

///////////////////////////////////////////////////////////////////////////////

template<typename type_t>
bool lemon_t::is(const type_t& this_one,
				 const type_t& that_one,
				 const std::string& test_name)
{
	bool passed = (this_one == that_one);
	
	ok(passed, test_name);
	
	if (!passed) {
		cout << "#         got: '" << this_one << "'\n";
		cout << "#    expected: '" << that_one << "'\n";
	}
	
	return passed;
}

///////////////////////////////////////////////////////////////////////////////

template<typename type_t>
bool lemon_t::isnt(const type_t& this_one,
				   const type_t& that_one,
				   const std::string& test_name)
{
	bool passed = (this_one != that_one);
	
	ok (passed, test_name);
	
	if (!passed) {
		cout << "#    '" << this_one << "'\n";
		cout << "#      !=\n";
		cout << "#    '" << that_one << "'\n";
	}
	
	return passed;
}

///////////////////////////////////////////////////////////////////////////////

bool lemon_t::pass(const std::string& test_name) {
	return ok(true, test_name);
}

///////////////////////////////////////////////////////////////////////////////

bool lemon_t::fail(const std::string& test_name) {
	return ok(false, test_name);
}

///////////////////////////////////////////////////////////////////////////////

void lemon_t::skip(const std::string& reason, unsigned int num_to_skip) {
	num_skipped += num_to_skip;
	
	for (unsigned int i = 0; i < num_to_skip; i++) {
		pass("# SKIP " + reason);
	}	
}

///////////////////////////////////////////////////////////////////////////////

void lemon_t::todo(const std::string& what) {
	num_skipped++;
	
	pass("# TODO " + what);
}