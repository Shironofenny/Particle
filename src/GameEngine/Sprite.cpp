#include "Sprite.h"

Sprite::Sprite():
	m_Position()
{

}

Sprite::Sprite(Vector const & _position):
	m_Position(_position)
{

}

Sprite::~Sprite()
{

}

void Sprite::update(double dt)
{

}

void Sprite::render()
{

}

Vector & Sprite::getPosition()
{
	return m_Position;
}

Vector const & Sprite::getPosition() const
{
	return m_Position;
}
