////////////////////////////////////////////////////////////////////////////////
// ChipOcho - A Simple Chip8 Emulator
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-05 17:07:14 by Eric Scrivner>
//
// Description:
//   Exceptions thrown by the emulator on error conditions
////////////////////////////////////////////////////////////////////////////////
#ifndef EXCEPTIONS_H_D7S3DZIH
#define EXCEPTIONS_H_D7S3DZIH

#include <string>
#include <sstream>
#include <iomanip>

#define OCHO_ASSERT(cond, exception) \
  if (!(cond)) { \
    throw (exception); \
  }

namespace Ocho {
  ///////////////////////////////////////////////////////////////////////////////
  // Class: Exception
  //
  // The base class for all exceptions thrown by the emulator
  class Exception {
  public:
    Exception()
    { }
	
    Exception(const std::string& msg)
      : message_(msg)
    { }
	
    virtual ~Exception()
    { }
    
    ////////////////////////////////////////////////////////////////////////////
    // Function: get_message
    //
    // Returns the message that generated the exception
    virtual const std::string get_message() const {
      return message_;
    }
  protected:
    std::string message_; // A message describing the error
  };

  ///////////////////////////////////////////////////////////////////////////////
  // Class: MemoryException
  //
  // An exception triggered because of an error condition in memory
  class MemoryException : public Exception {
  public:
    ////////////////////////////////////////////////////////////////////////////
    // Memory error types
    enum MemoryErrorT {
      OUT_OF_BOUNDS_READ,
      OUT_OF_BOUNDS_WRITE
    };

    ////////////////////////////////////////////////////////////////////////////
    // Function: MemoryException
    //
    // Parameters:
    //    error - The classification of the exception
    //    address - The address that triggered the error
    //
    // Initializes the exception with information about the address and
    // memory error type.
    MemoryException (const MemoryErrorT& error_type,
                     const Word& address)
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
      message_ = msg_stream.str();
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: bad_read
    //
    // Shortcut which returns a memory read exception at the given address.
    static MemoryException bad_read(const Word& address) {
      return MemoryException(OUT_OF_BOUNDS_READ, address);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: bad_write
    //
    // Shortcut which returns a memory write exception at the given address.
    static MemoryException bad_write(const Word& address) {
      return MemoryException(OUT_OF_BOUNDS_WRITE, address);
    }
  };
}
#endif /* end of include guard: EXCEPTIONS_H_D7S3DZIH */
