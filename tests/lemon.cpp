////////////////////////////////////////////////////////////////////////////////
// Lemon Unit Test Framework
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-05 17:13:27 by Eric Scrivner>
//
// Description:
//   A very simple unit testing framework
////////////////////////////////////////////////////////////////////////////////
#include "lemon.h"
using namespace std;

Lemon::Lemon(unsigned int num_planned_tests)
  : num_tests(0),
    test_number(0),
    num_skipped(0),
    num_failed(0)
{
  cout << "1.." << num_planned_tests << endl;
}

///////////////////////////////////////////////////////////////////////////////

void Lemon::end() {
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

void Lemon::diag(const std::string& message) {
  cout << "# " << message << "\n";
}

///////////////////////////////////////////////////////////////////////////////

bool Lemon::ok(bool passed, const std::string& test_name) {
  // Increment the number of tests run
  num_tests++;
  
  // If this is a skip or todo message
  if (test_name[0] != '#') {
    // Append a dash to the front
    const_cast<string&>(test_name) = "- " + test_name;
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

bool Lemon::not_ok(bool failed, const std::string& test_name) {
  return ok(!failed, test_name);
}

///////////////////////////////////////////////////////////////////////////////

bool Lemon::pass(const std::string& test_name) {
  return ok(true, test_name);
}

///////////////////////////////////////////////////////////////////////////////

bool Lemon::fail(const std::string& test_name) {
  return ok(false, test_name);
}

///////////////////////////////////////////////////////////////////////////////

void Lemon::skip(const std::string& reason, unsigned int num_to_skip) {
  num_skipped += num_to_skip;
  
  for (unsigned int i = 0; i < num_to_skip; i++) {
    pass("# SKIP " + reason);
  }	
}

///////////////////////////////////////////////////////////////////////////////

void Lemon::todo(const std::string& what) {
  num_skipped++;
  
  pass("# TODO " + what);
}
