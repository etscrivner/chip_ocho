////////////////////////////////////////////////////////////////////////////////
// ChipOcho - A Simple Chip8 Emulator
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-06 15:14:10 by Eric Scrivner>
//
// Description:
//   Class emulating the Chip8 video system.
//////////////////////////////////////////////////////////////////////////////// 
#ifndef VIDEO_H__
#define VIDEO_H__

#include "constants.h"
#include "types.h"

namespace Ocho {
  //////////////////////////////////////////////////////////////////////////////
  // Class: Color
  //
  // Represents a color as a combination of red, green and blue component
  // values.
  class Color {
  public:
    float r, g, b;
  public:
    ////////////////////////////////////////////////////////////////////////////
    // Standard colors
    static const Color Black;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Grey;
    static const Color White;

    Color()
    : r(0.0F), g(0.0F), b(0.0F)
    { }

    Color(const float& red, const float& green, const float& blue)
    : r(red), g(green), b(blue)
    { }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Class: Video
  //
  // Implements Chip8 graphics using OpenGL.
  class Video {
  public:
    ////////////////////////////////////////////////////////////////////////////
    // Function: Video
    //
    // Parameters:
    //   pixelSize  - The size of a single Chip8 pixel in screen pixels
    //   background - The background color (black by default)
    //   foreground - The color used to render pixels (white by default)
    //
    // Initializes the video device and plot a single pixelSize by pixelSize
    // square for each pixels.
    Video(const unsigned int& pixelSize,
          const Color& background = Color::Black,
          const Color& foreground = Color::White)
      : pixelSize_(pixelSize),
        background_(background),
        foreground_(foreground)
    {
      clear_screen();
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: redraw
    //
    // Draws the current video memory onto the screen
    void redraw();

    ////////////////////////////////////////////////////////////////////////////
    // Function: clear_screen
    //
    // Clears the screen to the color black
    void clear_screen();

    ////////////////////////////////////////////////////////////////////////////
    // Function: plot
    //
    // Parameters:
    //   x - The x coordinate to be plotted
    //   y - The y coordinate to be plotted
    //   value - The pixel value to plot at that point
    //
    // Plots the given value at the given point and returns true if there was
    // a collision, false otherwise.
    bool plot(const size_t& x, const size_t& y, const Byte& value);
  private:
    unsigned int pixelSize_; // The size of a single pixel
    Color background_; // The background color
    Color foreground_; // The pixel color
    Byte  memory_[VIDEO_WIDTH][VIDEO_HEIGHT]; // The video memory
  };
}

#endif // VIDEO_H__
