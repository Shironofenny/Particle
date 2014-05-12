#include "FPSCounter.h"

FPSCounter::FPSCounter()
{
	m_TotalElapsedTime = 0;
	m_FPSString = new char [7];
}

FPSCounter::~FPSCounter()
{
	delete[] m_FPSString;
}

void FPSCounter::update()
{
	m_PreviousElapsedTime = m_TotalElapsedTime;
	m_TotalElapsedTime = glutGet(GLUT_ELAPSED_TIME);
	m_TimeInterval = m_TotalElapsedTime - m_PreviousElapsedTime;
}

double FPSCounter::getTotalElapsedTime()
{
	return ((double)m_PreviousElapsedTime/1000);
}

double FPSCounter::getTimeInterval()
{
	return ((double)m_TimeInterval/1000);
}

double FPSCounter::getFPS()
{
	return (1000/(double)m_TimeInterval);
}

char const * FPSCounter::getFPSString()
{
	double fps = getFPS();
	
	// Check if bigger than maximum
	if (fps >= 999.99)
	{
		for (int i = 0; i <= 5; i++)
		{
			if (i == 3) m_FPSString[i] = '.';
			else m_FPSString[i] = '9';
		}
		m_FPSString[6] = '\0';
		return m_FPSString;
	}

	double denominator = 100;

	for(int i = 0; i <= 5; i++)
	{
		if (i == 3) m_FPSString[i] = '.';
		else
		{
			int digit = (int)(fps/denominator);
			*(m_FPSString + i) = digit + '0';
			fps -= digit * denominator;
			denominator = denominator/10;
		}
	}
	*(m_FPSString + 6) = '\0';
	return m_FPSString;
}

void FPSCounter::renderFPS()
{
	char const * fps = getFPSString();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	{
		glTranslatef(2, 2, 0);
		glColor3f(1.0, 1.0, 1.0);
		for (int i = 0; i <= 6; i++)
		{
			glutStrokeCharacter(GLUT_STROKE_ROMAN, fps[i]);
		}
	}
	glPopMatrix();
}
