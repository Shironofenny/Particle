#include "GLUTConfig.h"
#include "./GameEngine/Camera.h"
#include "GLScreenCapturer.h"

extern char const * g_Name;
extern GameEngine g_Engine;

GLScreenCapturer capture("./bin/video/sccap-%d.ppm");

void GLUTConfig::g_InitializeEngine(int * _argcp, char ** _argv, int _wWidth, int _wHeight, int _wPosX, int _wPosY)
{
	// Init GLUT window.
	glutInit(_argcp, _argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(_wWidth, _wHeight);
	glutInitWindowPosition(_wPosX, _wPosY);

	// Name the animation window.
	glutCreateWindow(g_Name);

	//glEnable( GL_DEPTH_TEST );
	//glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	std::string runDir(*_argv);
	g_Engine.initialize(runDir);
}

bool GLUTConfig::g_CheckGLErrors()
{
	GLenum errCode;
	const GLubyte *errString;
			  
	if ((errCode = glGetError()) != GL_NO_ERROR) 
	{
	  errString = gluErrorString(errCode);
	  cerr << "OpenGL Error:" <<errString<<endl;
	  fprintf(stderr,  " %s\n",  errString);
	  return false; 
	}
	return true;
}    

void GLUTConfig::g_Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if(Keyboard::getInstance().isKeyDown('1'))
	{
		glutFullScreen();
		Mouse::getInstance().refresh();
	}
	if(Keyboard::getInstance().isKeyDown('2'))
	{
		glutReshapeWindow(960, 540);
		glutPositionWindow(150, 100);
		Mouse::getInstance().refresh();
	}
	if(Keyboard::getInstance().isKeyDown(27))
		exit(0);
	
	glPushMatrix();

		g_Engine.run();

	glPopMatrix();

	if(ConstantHandler::getInstance().isMovieMade)
	{
	 	capture.capture();
	}

	glFlush();
	glutSwapBuffers();
}

void GLUTConfig::g_Reshape(int w,  int h)
{
	glViewport(0, 0, w, h);

	ConstantHandler::getInstance().restoreWindowSize(w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the clipping volume
	gluPerspective(60.0f, (GLfloat)w / (GLfloat)h, 1.0f, 100.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLUTConfig::g_KeyboardPressed( unsigned char key, int x, int y )
{
	Keyboard::getInstance().updatePress(key);
}

void GLUTConfig::g_KeyboardReleased( unsigned char key, int x, int y )
{
	Keyboard::getInstance().updateRelease(key);
}

void GLUTConfig::g_Mouse(int button, int state, int x, int y)
{
	Mouse::getInstance().updateActive(button, state, x, y);
}

void GLUTConfig::g_MouseMove(int x, int y)
{
	Mouse::getInstance().updatePassive(x, y);
}

void GLUTConfig::g_MousePassive(int x, int y)
{
	Mouse::getInstance().updatePassive(x, y);
}

void GLUTConfig::g_Run()
{
	// Assign call back function
	glutDisplayFunc(g_Display);
	glutReshapeFunc(g_Reshape);
	glutIdleFunc(g_Display);
	glutKeyboardFunc(g_KeyboardPressed);
	glutKeyboardUpFunc(g_KeyboardReleased);

	glutMouseFunc(g_Mouse);
	glutMotionFunc(g_MouseMove);
	glutPassiveMotionFunc(g_MousePassive);

	glutWarpPointer(ConstantHandler::getInstance().mousePositionX, \
									ConstantHandler::getInstance().mousePositionY);

	glutMainLoop();
}
