////////////////////////////////////////////////////////////////////////////////
// ChipOcho - A Simple Chip8 Emulator
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-06 20:24:56 by Eric Scrivner>
//
// Description:
//   Application entry point.
////////////////////////////////////////////////////////////////////////////////
#include "cpu.h"
#include "input.h"
#include "memory.h"
#include "timers.h"
#include "video.h"

#include <sys/time.h>
#include <ctime>
#include <iostream>
using namespace std;

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

////////////////////////////////////////////////////////////////////////////////
// Constants
unsigned int kMultiplier   = 3;
unsigned int kWindowWidth  = Ocho::VIDEO_WIDTH * kMultiplier;
unsigned int kWindowHeight = Ocho::VIDEO_HEIGHT * kMultiplier;
const char*  kWindowTitle  = "ChipOcho";

SDL_Surface* gScreen = 0;
bool gQuit = false;

unsigned int kTimerFreq  = 20; // 60 Hz (in ms)
unsigned int kCpuFreq    = 5; // 60 Hz (in ms)
unsigned int gCpuUpdate = 0;
unsigned int gTimerUpdate = 0;

////////////////////////////////////////////////////////////////////////////////
// Components
Ocho::Memory gMemory;
Ocho::Input  gInput;
Ocho::Timers gTimers;
Ocho::Video  gVideo(kMultiplier);
Ocho::Cpu    gCpu(&gInput, &gMemory, &gVideo, &gTimers);

////////////////////////////////////////////////////////////////////////////////
// Function: Redraw
//
// Redraws the screen on an update
void Redraw() {
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	// Redraw the Chip8 display
	gVideo.redraw();

	// Swap buffers
	SDL_GL_SwapBuffers();
}

////////////////////////////////////////////////////////////////////////////////
// Function: Reshape
//
// Appropriately reshape the OpenGL coordinate system for the Chip8
void Reshape(int width, int height) {
  // Setup the viewport to map physical pixels to GL "logical" pixels
  glViewport(0, 0, (GLint)width, (GLint)height);

  // Adjust the region of 3D space projected onto the window
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

	gluOrtho2D(0, kWindowWidth, kWindowHeight, 0);

  glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

////////////////////////////////////////////////////////////////////////////////
// Function: PollInput
//
// Polls for user input and pushes into onto the input queue
void PollInput() {
	SDL_Event keyEvent;
	
	// Poll for new input
	while(SDL_PollEvent(&keyEvent)) {
		switch(keyEvent.type) {
		case SDL_KEYDOWN: // Key press event
			gInput.setKey(keyEvent.key.keysym.sym);
			break;
		case SDL_KEYUP:
			switch(keyEvent.key.keysym.sym) {
			case SDLK_ESCAPE: // Escape key
				gQuit = true;
				break;
			default: gInput.clearKey(keyEvent.key.keysym.sym); break;
			}
			break;
		case SDL_QUIT:
			gQuit = true;
			break;
		default: break;
		}
  }
}

////////////////////////////////////////////////////////////////////////////////
// Function: UpdateCpu
//
// Executes the next CPU instruction
void UpdateCpu() {
	if ((SDL_GetTicks() - gCpuUpdate) >= kCpuFreq) {
		gCpu.runNext();
		gCpuUpdate = SDL_GetTicks();
	}
}

////////////////////////////////////////////////////////////////////////////////
// Function: UpdateTimers
//
// Updates the Chip8 timers
void UpdateTimers() {
	if ((SDL_GetTicks() - gTimerUpdate) >= kTimerFreq) {
		gTimers.update();
		gTimerUpdate = SDL_GetTicks();
	}
}

////////////////////////////////////////////////////////////////////////////////
// Function: InitSdl
//
// Initializes the SDL system
bool InitSdl() {
	// If SDL could not be initialized
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
		// Print the error and abort
		cout << "Error, SDL_Init failed: " << SDL_GetError() << endl;
		return false;
	}

	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Initialize the screen
	gScreen = SDL_SetVideoMode(kWindowWidth, kWindowHeight,
	                           24, SDL_OPENGL);

	if (gScreen == NULL) {
		cout << "Error, could not set video mode: " << SDL_GetError() << endl;
		return false;
	}

	// Set the window title
	SDL_WM_SetCaption(kWindowTitle, 0);
	
	// Cleanup at the end
	atexit(SDL_Quit);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
// Function: main
//
// Application entry point
int main (int argc, char* argv[]) {
	// Ensure that we have enough command-line arguments
	if (argc < 2) {
		cout << "Usage: chip_ocho [rom]" << endl;
		return 1;
	}
	
	// Load a rom
	if (!gMemory.load(argv[1])) {
		cout << "Error, unable to load rom '" << argv[1] << "'\n";
		return 1;
	}

	// Map keybaord input
	gInput.mapKey(0x1, SDLK_q);
	gInput.mapKey(0x2, SDLK_w);
	gInput.mapKey(0x3, SDLK_e);
	gInput.mapKey(0xC, SDLK_r);
	gInput.mapKey(0x4, SDLK_a);
	gInput.mapKey(0x5, SDLK_s);
	gInput.mapKey(0x6, SDLK_d);
	gInput.mapKey(0xD, SDLK_f);
	gInput.mapKey(0x7, SDLK_z);
	gInput.mapKey(0x8, SDLK_x);
	gInput.mapKey(0x9, SDLK_c);
	gInput.mapKey(0xA, SDLK_1);
	gInput.mapKey(0x0, SDLK_2);
	gInput.mapKey(0xB, SDLK_3);
	gInput.mapKey(0xF, SDLK_4);

	// Attempt to initialize video
	if (!InitSdl()) {
		return 1;
	}

	// Setup the OpenGL coordinate system
	Reshape(kWindowWidth, kWindowHeight);

	// Setup the CPU and Timer callbacks
	gCpuUpdate = gTimerUpdate = SDL_GetTicks();

	// Enter the main loop
	while (!gQuit) {
		PollInput();

		UpdateCpu();
		UpdateTimers();

		Redraw();
	}

  return 0;
}
