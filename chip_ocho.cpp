////////////////////////////////////////////////////////////////////////////////
// ChipOcho - A Simple Chip8 Emulator
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-06 17:59:05 by Eric Scrivner>
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

// OpenGL includes
#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif 

////////////////////////////////////////////////////////////////////////////////
// Constants
unsigned int kMultiplier   = 3;
unsigned int kWindowWidth  = Ocho::VIDEO_WIDTH * kMultiplier;
unsigned int kWindowHeight = Ocho::VIDEO_HEIGHT * kMultiplier;
const char*  kWindowTitle  = "ChipOcho";

int timerFreq  = 167; // 60 Hz
int cpuFreq    = 333; // 30 Hz
timeval lastCountDown, lastCycle;

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

	// Redraw the Chip8 display
	gVideo.redraw();

  // Swap the redraw buffer onto the screen
  glutSwapBuffers();
}

////////////////////////////////////////////////////////////////////////////////
// Function: Reshape
//
// Reshapes the viewport so that (0, 0, 0) is the center of the screen and the
// x-coordinates go from -(width/2) to width/2 while the y-coordinates go from
// -(height/2) to height/2.
void Reshape(int width, int height) {
  // Setup the viewport to map physical pixels to GL "logical" pixels
  glViewport(0, 0, (GLint)width, (GLint)height);

  // Adjust the region of 3D space projected onto the window
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
	gluOrtho2D(0, kWindowWidth, 0, kWindowHeight);

  glMatrixMode(GL_MODELVIEW);
}

////////////////////////////////////////////////////////////////////////////////
// Function: OnKeyPress
//
// Handles a key press from the user
void OnKeyPress(unsigned char key, int, int) {
  switch(key) {
  case 27: // Exit (ESC)
    exit(0);
    break;
  default: gInput.addKey(key); break;
  }

  glutPostRedisplay();
}

////////////////////////////////////////////////////////////////////////////////
// Function: UpdateCpu
//
// Executes the next CPU instruction
void UpdateCpu(int) {
	cout << "cpu" << endl;
	gCpu.runNext();
	//glutPostRedisplay();
}

////////////////////////////////////////////////////////////////////////////////
// Function: UpdateTimers
//
// Updates the Chip8 timers
void UpdateTimers(int) {
	cout << "timr" << endl;
	gTimers.update();
}

////////////////////////////////////////////////////////////////////////////////
// Function: InitGlut
//
// Initialize the GLUT
void InitGlut(int& argc, char* argv[]) {
  // Initialize GLUT
  glutInit(&argc, argv);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(kWindowWidth, kWindowHeight);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow(kWindowTitle);

  // Setup callbacks
  glutDisplayFunc(Redraw);
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(OnKeyPress);
	glutTimerFunc(0, UpdateTimers, 0);
	glutTimerFunc(0, UpdateCpu, 0);
}

int main (int argc, char* argv[]) {
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
	gInput.mapKey(0x1, 'q');
	gInput.mapKey(0x2, 'w');
	gInput.mapKey(0x3, 'e');
	gInput.mapKey(0xC, 'r');
	gInput.mapKey(0x4, 'a');
	gInput.mapKey(0x5, 's');
	gInput.mapKey(0x6, 'd');
	gInput.mapKey(0xD, 'f');
	gInput.mapKey(0x7, 'z');
	gInput.mapKey(0x8, 'x');
	gInput.mapKey(0x9, 'c');
	gInput.mapKey(0xA, '1');
	gInput.mapKey(0x0, '2');
	gInput.mapKey(0xB, '3');
	gInput.mapKey(0xF, '4');

	gettimeofday(&lastCountDown, 0);
	gettimeofday(&lastCycle, 0);

	InitGlut(argc, argv);
	glutMainLoop();
  return 0;
}
