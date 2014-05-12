#ifndef __GLUTCONFIG_H__
#define __GLUTCONFIG_H__

#include "GLHeader.h"
#include "GLScreenCapturer.h"
#include "GameEngine/GameEngine.h"
#include "GameEngine/Interaction/Keyboard.h"
#include "GameEngine/Interaction/Mouse.h"
#include "GameEngine/Utilities/ConstantHandler.h"

#include <iostream>
using namespace std;

#define BUFFER_LENGTH 64
// Full Static class
// I HATE THIS PIECE OF CODE
namespace GLUTConfig
{
	// The initialization function.
	void g_InitializeEngine(int * _argcp, char ** _argv, int _wWidth, int _wHeight, int _wPosX, int _wPosY);

	// The call back display function for glut (used in idle)
	void g_Display();

	// The reshape call back function for glut
	void g_Reshape(int w, int h);

	// The run function
	void g_Run();

	// The error checking function
	bool g_CheckGLErrors();

	// Keyboard pressing function
	void g_KeyboardPressed( unsigned char key, int x, int y );
	
	// Keyboard releasing function
	void g_KeyboardReleased( unsigned char key, int x, int y );

	// Mouse click function
	void g_Mouse(int button, int state, int x, int y);

	// Mouse click and move callback function
	void g_MouseMove(int x, int y);

	// Mouse passive callback function
	void g_MousePassive(int x, int y);
}

#endif
