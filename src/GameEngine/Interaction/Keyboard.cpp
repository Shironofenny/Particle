#include "Keyboard.h"
#include <iostream>

Keyboard::Keyboard()
{
	std::fill_n(m_KeyState, 256, false);
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
}

bool Keyboard::isKeyDown(unsigned char const & key) const
{
	return m_KeyState[key];
}

bool Keyboard::isKeyUp(unsigned char const & key) const
{
	return !m_KeyState[key];
}
