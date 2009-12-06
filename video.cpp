////////////////////////////////////////////////////////////////////////////////
// ChipOcho - A Simple Chip8 Emulator
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-06 12:09:21 by Eric Scrivner>
//
// Description:
//   Class emulating the Chip8 video system.
//////////////////////////////////////////////////////////////////////////////// 
#include "video.h"

#include <cstring>

////////////////////////////////////////////////////////////////////////////////
// Standard colors
const Ocho::Color Ocho::Color::Black = Color(0.0F, 0.0F, 0.0F);
const Ocho::Color Ocho::Color::Red   = Color(1.0F, 0.0F, 0.0F);
const Ocho::Color Ocho::Color::Green = Color(0.0F, 1.0F, 0.0F);
const Ocho::Color Ocho::Color::Blue  = Color(0.0F, 0.0F, 1.0F);
const Ocho::Color Ocho::Color::Grey  = Color(0.5F, 0.5F, 0.5F);
const Ocho::Color Ocho::Color::White = Color(1.0F, 1.0F, 1.0F);

////////////////////////////////////////////////////////////////////////////////

void Ocho::Video::clear_screen() {
	// Clear the chip8 memory
	memset(memory_, 0, sizeof(Byte) * Ocho::VIDEO_WIDTH * Ocho::VIDEO_HEIGHT);
}

////////////////////////////////////////////////////////////////////////////////
