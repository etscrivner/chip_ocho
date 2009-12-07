////////////////////////////////////////////////////////////////////////////////
// ChipOcho - A Simple Chip8 Emulator
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-06 17:11:23 by Eric Scrivner>
//
// Description:
//   Class emulating the Chip8 video system.
//////////////////////////////////////////////////////////////////////////////// 
#include "video.h"

#include <cstring>

// OpenGL includes
#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif 

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
	for (size_t y = 0; y < Ocho::VIDEO_HEIGHT; y++) {
		for (size_t x = 0; x < Ocho::VIDEO_WIDTH; x++) {
			if (memory_[x][y] & 0x1) {
				glColor3f(1.0F, 1.0F, 1.0F);
			} else {
				glColor3f(0.0F, 0.0F, 0.0F);
			}
			glBegin(GL_QUADS);
			glVertex2f(x * pixelSize_, y * pixelSize_); // Top left
			glVertex2f((x + 1) * pixelSize_, y * pixelSize_); // Top right
			glVertex2f(x * pixelSize_, (y + 1) * pixelSize_); // Bottom left
			glVertex2f((x + 1) * pixelSize_, (y + 1) * pixelSize_); // Bottom right
			glEnd();
		}
	}
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
		if (memory_[realX + i][realY] != 0 &&
		    (memory_[realX + i][realY] ^ ((value >> i) & 1)) == 0) {
			// Set the collision variable
			wasCollision = true;
		}
		
		// Set the given pixel
		memory_[realX + i][realY] ^= ((value >> i) & 0x1);
	}

	return wasCollision;
}
