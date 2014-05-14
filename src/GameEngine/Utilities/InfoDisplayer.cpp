#include "InfoDisplayer.h"

InfoDisplayer::InfoDisplayer()
{

}

void InfoDisplayer::renderInfo(int _position, string const & _str)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0, 0.0, 0.9);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);

	{
		float positionX = -0.98;
		float positionY = 0.05 * (_position + 1) - 1; 

		glRasterPos2f(positionX, positionY);
		for(string::size_type i = 0; i < _str.size(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, _str[i]);
		}
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
