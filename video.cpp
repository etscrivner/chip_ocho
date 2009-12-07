////////////////////////////////////////////////////////////////////////////////
// ChipOcho - A Simple Chip8 Emulator
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-06 19:50:53 by Eric Scrivner>
//
// Description:
//   Class emulating the Chip8 video system.
//////////////////////////////////////////////////////////////////////////////// 
#include "video.h"

#include <cstring>
#include <iostream>

#include <SDL/SDL_opengl.h>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Standard colors
const Ocho::Color Ocho::Color::Black = Color(0.0F, 0.0F, 0.0F);
const Ocho::Color Ocho::Color::Red   = Color(1.0F, 0.0F, 0.0F);
const Ocho::Color Ocho::Color::Green = Color(0.0F, 1.0F, 0.0F);
const Ocho::Color Ocho::Color::Blue  = Color(0.0F, 0.0F, 1.0F);
const Ocho::Color Ocho::Color::Grey  = Color(0.5F, 0.5F, 0.5F);
const Ocho::Color Ocho::Color::White = Color(1.0F, 1.0F, 1.0F);

////////////////////////////////////////////////////////////////////////////////

void Ocho::Video::redraw() {
	glBegin(GL_QUADS);
	for (size_t y = 0; y < Ocho::VIDEO_HEIGHT; y++) {
		for (size_t x = 0; x < Ocho::VIDEO_WIDTH; x++) {
			if (memory_[x][y] & 0x1) {
				glColor3f(1.0F, 1.0F, 1.0F);
			} else {
				glColor3f(0.0F, 0.0F, 0.0F);
			}
			_drawQuad(x * pixelSize_, y * pixelSize_,
			          (x + 1) * pixelSize_, (y + 1) * pixelSize_);
		}
	}
	glEnd();
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Video::clear_screen() {
	// Clear the chip8 memory
	memset(memory_, 0, sizeof(Byte) * Ocho::VIDEO_WIDTH * Ocho::VIDEO_HEIGHT);
}

////////////////////////////////////////////////////////////////////////////////

bool Ocho::Video::plot(const size_t& x, const size_t& y, const Byte& value) {
	bool wasCollision = false;

	size_t realX = x % Ocho::VIDEO_WIDTH;
	size_t realY = y % Ocho::VIDEO_HEIGHT;
	// Iterate through each bit in the sprite value
	for (size_t i = 0; i < 8; i++) {
		// If a pixel is erased
		if (memory_[realX + i][realY] != 0 && ((value >> (7 - i)) & 1) != 0) {
			// Set the collision variable
			wasCollision = true;
		}
		
		// Set the given pixel
		memory_[realX + i][realY] ^= ((value >> (7 - i)) & 1);
	}

	return wasCollision;
}

////////////////////////////////////////////////////////////////////////////////

void Ocho::Video::_drawQuad(int x1, int y1, int x2, int y2) {
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glVertex2d(x2, y2);
	glVertex2d(x1, y2);
}
