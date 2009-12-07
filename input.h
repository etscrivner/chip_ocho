#ifndef INPUT_H__
#define INPUT_H__

#include <map>

namespace Ocho {
  //////////////////////////////////////////////////////////////////////////////
  // Keyboard constants
  const unsigned int QUEUE_SIZE = 5;

  //////////////////////////////////////////////////////////////////////////////
  // Class: Input
  //
  // Emulates Chip8 keyboard input
  class Input {
  public:
    Input()
      : front_(-1), back_(-1)
    { }

    ////////////////////////////////////////////////////////////////////////////
    // Function: mapKey
    //
    // Maps the given keyboard key to the given Chip8 key
    void mapKey(const Byte& chipKey, const int& keyboardKey) {
      keyMap_[chipKey] = keyboardKey;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: addKey
    //
    // Adds the given key to the keypress queue if it is a mapped key
    void addKey(const int& key) {
      if (_isMapped(key)) {
        back_ = (back_ + 1) % QUEUE_SIZE;
        keyQueue_[back_] = _chipKey(key);
      }
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: getLastKey
    //
    // Gets the key with highest priority in the queue
    Byte getLastKey() {
      front_ = (front_ + 1) % QUEUE_SIZE;
      return keyQueue_[front_];
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: hasKey
    //
    // Returns true if there is pending keyboard input, false otherwise
    bool hasKey() const {
      return (front_ != back_);
    }
  private:
    ////////////////////////////////////////////////////////////////////////////
    // Function: _isMapped
    //
    // Returns true if the given key is mapped, false otherwise
    bool _isMapped(const int& key) {
      for (std::map<Byte, int>::iterator it = keyMap_.begin();
           it != keyMap_.end(); it++) {
        if (it->second == key) {
          return true;
        }
      }
      return false;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: _chipKey
    //
    // Returns the Chip8 key corresponding to the given keyboard key
    Byte _chipKey(const int& key) {
      for (std::map<Byte, int>::iterator it = keyMap_.begin();
           it != keyMap_.end(); it++) {
        if (it->second == key) {
          return it->first;
        }
      }
      return 0x10;
    }

    std::map<Byte, int> keyMap_; // Maps Chip8 keys to keyboard keys
    Byte keyQueue_[QUEUE_SIZE]; // Stores the 5 most recently pressed keys
    int front_; // The front queue index
    int back_; // The back queue index
  };
}

#endif // INPUT_H__
