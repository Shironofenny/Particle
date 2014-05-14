#include "Keyboard.h"
#include <iostream>

Keyboard::Keyboard()
{
	std::fill_n(m_KeyState, 256, false);
	std::fill_n(m_KeyScreen, 256, false);
}

Keyboard::~Keyboard()
{

}

void Keyboard::updatePress(unsigned char const & key)
{
	m_KeyState[key] = true;
}

void Keyboard::updateRelease(unsigned char const & key)
{
	m_KeyState[key] = false;
	m_KeyScreen[key] = false;
}

bool Keyboard::isKeyDown(unsigned char const & key) const
{
	return m_KeyState[key];
}

bool Keyboard::isKeyTriggerDown(unsigned char const & key)
{
	if(m_KeyState[key])
	{
		if(!m_KeyScreen[key])
		{
			m_KeyScreen[key] = true;
			return true;
		}
	}
	return false;
}

bool Keyboard::isKeyUp(unsigned char const & key) const
{
	return !m_KeyState[key];
}
