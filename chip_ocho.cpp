////////////////////////////////////////////////////////////////////////////////
// ChipOcho - A Simple Chip8 Emulator
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-06 16:48:59 by Eric Scrivner>
//
// Description:
//   Application entry point.
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "cpu.h"
#include "memory.h"
#include "timers.h"
#include "video.h"
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

////////////////////////////////////////////////////////////////////////////////
// Components
Ocho::Memory gMemory;
Ocho::Timers gTimers;
Ocho::Video  gVideo(kMultiplier);
Ocho::Cpu    gCpu(&gMemory, &gVideo, &gTimers);

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
  default: break;
  }

  glutPostRedisplay();
}

////////////////////////////////////////////////////////////////////////////////
// Function: Update
//
// Handles the idle loop updating of the simulation components
void Update() {
	// Update the CPU and timers
	gCpu.runNext();
	gTimers.update();

	// Redraw the display
	glutPostRedisplay();
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
  glutIdleFunc(Update);
}

int main (int argc, char* argv[]) {
	gMemory.load("./roms/INVADERS");
	InitGlut(argc, argv);
	glutMainLoop();
  return 0;
}
