#ifndef INPUT_H__
#define INPUT_H__

#include <map>

namespace Ocho {
  //////////////////////////////////////////////////////////////////////////////
  // Class: Input
  //
  // Emulates Chip8 keyboard input
  class Input {
  public:
    Input()
      : lastKey_(NUM_KEYS)
    {
      memset(keys_, false, sizeof(bool) * NUM_KEYS);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: mapKey
    //
    // Maps the given keyboard key to the given Chip8 key
    void mapKey(const Byte& chipKey, const int& keyboardKey) {
      assert(chipKey < NUM_KEYS);
      keyMap_[chipKey] = keyboardKey;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: setKey
    //
    // Activates a key press for the given key
    void setKey(const int& key) {
      if (_isMapped(key)) {
        lastKey_ = _chipKey(key);
        keys_[lastKey_] = true;
      }
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: clearKey
    //
    // Deactivates a key press for the given key
    void clearKey(const int& key) {
      if (_isMapped(key)) {
        keys_[_chipKey(key)] = false;
      }
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: isPressed
    //
    // Indicates whether or not the given Chip8 key is pressed
    bool isPressed(const Byte& chipKey) {
      assert(chipKey < NUM_KEYS);
      return keys_[chipKey];
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: getLastKey
    //
    // Gets the key with highest priority in the queue
    Byte getLastKey() {
      Byte tmp = lastKey_;
      lastKey_ = NUM_KEYS;
      return tmp;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: hasKey
    //
    // Returns true if there is pending keyboard input, false otherwise
    bool hasKey() const {
      return (lastKey_ != NUM_KEYS);
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
    bool keys_[NUM_KEYS]; // Boolean map indicating which keys are pressed
    Byte lastKey_; // The most recent key pressed;
  };
}

#endif // INPUT_H__
