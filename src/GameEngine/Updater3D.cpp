#include "Updater3D.h"

Updater3D::Updater3D(Scene3D & _scene) :
	Updater(), 
	m_Scene(_scene)
{
}

void Updater3D::Update(double dt)
{
	Camera & camera = m_Scene.getCamera();
	
	camera.update(dt);

	m_Scene.getParticleSystem().update(dt);
}

int Updater3D::processSelection()
{
	// TODO Make a copy of all the objects that collision may happen.
	// NOTE All objects in detection must be rendered after glLoadName(int).
	// This int shall be the returning number to indicate which object is in collision

	// Camera needed to adjust viewing angle
	Camera & camera = m_Scene.getCamera();
	
	// The number of hit object
	int hitObject = -1;

	GLfloat fAspect;

	// Space for selection buffer
	GLuint selectBuff[256];

	// Hit counter and viewport storage
	GLint hits, viewport[4];

	// Setup selection buffer
	glSelectBuffer(256, selectBuff);

	// Get the viewport
	glGetIntegerv(GL_VIEWPORT, viewport);

	// Switch to projection and save the matrix
	glMatrixMode(GL_PROJECTION);

	glPushMatrix();
	{
		// Change render mode
		glRenderMode(GL_SELECT);

		// Establish new clipping volume to be unit cube around
		// mouse cursor point (xPos,  yPos) and extending two pixels
		// in the vertical and horizontal direction
		glLoadIdentity();
		gluPickMatrix(Mouse::getInstance().getPositionX(),\
			 	viewport[3] - Mouse::getInstance().getPositionY() + viewport[1], 0.1, 0.1, viewport);

		// Apply perspective matrix 
		fAspect = (float)viewport[2] / (float)viewport[3];

		gluPerspective(60.0f,  fAspect,  1.0,  1000.0);

		// Render only those needed for selection
		glPushMatrix();    
		{
			camera.setup();

			// TODO Render the exact objects, that you want to detect collision among.
		}
		glPopMatrix();
		glFlush();

		// Collect the hits
		hits = glRenderMode(GL_RENDER);

		// If hit(s) occurred,  display the info.
		if(hits != 0)
		{
			// Save current picked object.
			// Take only the nearest selection
			GLuint minZ = 0xffffffff;
			GLuint * ptr = (GLuint *) selectBuff;
			GLuint names;

			for (int i = 0; i < hits; i++)
			{
				names = *ptr;
				ptr++;
				if (*ptr < minZ)
				{
					minZ = *ptr;
					hitObject = *(ptr+2);
				}
				ptr += names + 2;
			}
		}
		
		// Restore the projection matrix
		glMatrixMode(GL_PROJECTION);
	}
	glPopMatrix();

	// Go back to modelview for normal rendering
	glMatrixMode(GL_MODELVIEW);

	return hitObject;
}
