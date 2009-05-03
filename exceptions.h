#ifndef EXCEPTIONS_H_D7S3DZIH
#define EXCEPTIONS_H_D7S3DZIH

#include <string>
#include <sstream>
#include <iomanip>

///////////////////////////////////////////////////////////////////////////////
// exception_t

class exception_t
{
public:
  // Function: exception_t
  //
  // Initializes the exception with an empty error message
  exception_t ()
    : message("")
    { }
	
  // Function: exception_t
  //
  // Parameters:
  //    msg - A short message describing the error
  //
  // Initializes the exception with the given error message
  exception_t (const std::string& msg)
    : message(msg)
  { }
	
  // Function: ~exception_t
  //
  // Deallocates any resources allocated by this exception
  virtual ~exception_t () {
    // do nothing
  }
	
  // Function: get_message
  //
  // Returns the message that generated the exception
  virtual const std::string get_message() const {
    return message;
  }
protected:
  std::string message; // A message describing the error
};

///////////////////////////////////////////////////////////////////////////////
// memory_exception_t

// Constant: memory_exception_class
//
// Classes of memory errors that can be generated
enum memory_error_type {
  OUT_OF_BOUNDS_READ,
  OUT_OF_BOUNDS_WRITE	
};

class memory_exception_t : public exception_t
{
public:
  // Function: memory_exception_t
  //
  // Parameters:
  //    error - The classification of the exception
  //    address - The address that triggered the error
  //
  // Initializes the exception with information about the address and
  // memory error type.
  memory_exception_t (const memory_error_type& error_type,
		      const unsigned int& address)
    {
      // Determine the type of error that occurred
      std::ostringstream msg_stream;
      
      switch(error_type) {
	// If the error is an out of bounds read
      case OUT_OF_BOUNDS_READ:
	{
	  msg_stream << "memory read failed at address 0x";
	}
	break;
	// If the error is an out of bounds write
      case OUT_OF_BOUNDS_WRITE:
	{
	  msg_stream << "memory write failed at address 0x";
	}
	break;
	// Otherwise
      default: break;
      }
      
      msg_stream << std::setw(4) << std::setfill('0') << std::hex << address;
      message = msg_stream.str();
    }
private:
  memory_error_type error_type; // The type of memory error
};

#endif /* end of include guard: EXCEPTIONS_H_D7S3DZIH */
