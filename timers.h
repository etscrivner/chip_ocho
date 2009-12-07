////////////////////////////////////////////////////////////////////////////////
// ChipOcho - A Simple Chip8 Emulator
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-06 15:39:54 by Eric Scrivner>
//
// Description:
//   Class which emulates the Chip8 timers
////////////////////////////////////////////////////////////////////////////////
#ifndef TIMERS_H__
#define TIMERS_H__

namespace Ocho {
  //////////////////////////////////////////////////////////////////////////////
  // Class: Timers
  //
  // Class which emulates the Chip8 delay and sound timers
  class Timers {
  public:
    Timers()
      : sound_(0), delay_(0)
    { }

    ////////////////////////////////////////////////////////////////////////////
    // Function: update
    //
    // Decrements any timer which is non-zero (should be called at around 60 Hz)
    void update() {
      if (sound_ > 0) { sound_--; }
      if (delay_ > 0) { delay_--; }
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: getSound
    //
    // Returns the current value of the sound timer
    Byte getSound() const { return sound_; }

    ////////////////////////////////////////////////////////////////////////////
    // Function: getDelay
    //
    // Returns the current value of the delay timer
    Byte getDelay() const { return delay_; }

    ////////////////////////////////////////////////////////////////////////////
    // Function: setSound
    //
    // Sets the sound timer to the given value
    void setSound(const Byte& sound) { sound_ = sound; }

    ////////////////////////////////////////////////////////////////////////////
    // Function: setDelay
    //
    // Sets the delay timer to the given value
    void setDelay(const Byte& delay) { delay_ = delay; }
  private:
    Byte sound_; // The sound timer
    Byte delay_; // The delay timer
  };
}

#endif // TIMERS_H__
