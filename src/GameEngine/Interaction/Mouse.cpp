#include "Mouse.h"
#include <iostream>

Mouse::Mouse()
{
	refresh();
}

Mouse::~Mouse()
{

}

void Mouse::updateActive(int _button, int _state, int _x, int _y)
{
	switch(_button)
	{
	case GLUT_LEFT_BUTTON:
		m_State[0] = _state == GLUT_DOWN ? 1 : 0;
		break;
	case GLUT_MIDDLE_BUTTON:
		m_State[1] = _state == GLUT_DOWN ? 1 : 0;
		break;
	case GLUT_RIGHT_BUTTON:
		m_State[2] = _state == GLUT_DOWN ? 1 : 0;
		break;
	default:
		break;
	}

}

void Mouse::updatePassive(int _x, int _y)
{
	if(m_IsFirstUpdate)
	{
		m_IsFirstUpdate = false;
		m_XNow = _x;
		m_YNow = _y;
	}
	m_XLast = m_XNow;
	m_YLast = m_YNow;
	m_XNow = _x;
	m_YNow = _y;
}

bool Mouse::isOnBoundary()
{
	int xBoundary = ConstantHandler::getInstance().windowSizeX / 3;
	int yBoundary = ConstantHandler::getInstance().windowSizeY / 3;
	return (m_XNow <= xBoundary ||\
					m_XNow >= ConstantHandler::getInstance().windowSizeX - xBoundary ||\
		 			m_YNow <= yBoundary ||\
					m_YNow >= ConstantHandler::getInstance().windowSizeY - yBoundary);
}

int Mouse::getPositionX() const
{
	return m_XNow;
}

int Mouse::getPositionY() const
{
	return m_YNow;
}

int Mouse::getDifferenceX()
{
	int diff = m_XNow - m_XLast;
	m_XLast = m_XNow;
	return diff;
}

int Mouse::getDifferenceY()
{
	int diff = m_YNow - m_YLast;
	m_YLast = m_YNow;
	return diff;
}

int Mouse::getDeviationX() const
{
	return m_XNow - ConstantHandler::getInstance().mousePositionX;
}

int Mouse::getDeviationY() const
{
	return m_YNow - ConstantHandler::getInstance().mousePositionY;
}

void Mouse::refresh()
{
	refreshPositionInfo();

	for (int i = 0; i <=4; i++)
		m_State[i] = false;
}

void Mouse::refreshPositionInfo()
{
	m_IsFirstUpdate = true;
	m_XNow = 0;
	m_YNow = 0;
	m_XLast = 0;
	m_YLast = 0;
}

bool Mouse::isMouseLeftDown()
{
	return m_State[0];
}

bool Mouse::isMouseRightDown()
{
	return m_State[2];
}
