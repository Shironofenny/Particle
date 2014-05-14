#include "Particle.h"

#include "../Interaction/Keyboard.h"
#include <iostream>
using namespace std;

// Private static member need to be declared
extern GLuint Particle::ms_Shape;

Particle::Particle(GLuint _texture, double _lifeTime) :
	m_LifeTime(_lifeTime), 
	m_Texture(_texture) 
{
	m_Life = 0.0;
}

Particle::~Particle()
{

}

void Particle::buildParticle(double _scale)
{
	Particle::ms_Shape = glGenLists(1);
	glNewList(Particle::ms_Shape, GL_COMPILE);
	{
		glBegin(GL_TRIANGLE_STRIP);
		{
			glTexCoord2f(1, 1);
			glVertex3f(_scale, _scale, 0.0);
			glTexCoord2f(0, 1);
			glVertex3f(-_scale, _scale, 0.0);
			glTexCoord2f(1, 0);
			glVertex3f(_scale, -_scale, 0.0);
			glTexCoord2f(0, 0);
			glVertex3f(-_scale, -_scale, 0.0);
		}
		glEnd();
	}
	glEndList();
}

double Particle::getLifeRatio()
{
	return m_Life / m_LifeTime;
}

bool Particle::isDead()
{
	return (m_Life > m_LifeTime);
}

void Particle::update(double dt)
{
	m_Position += m_Velocity * dt;
	m_Life += dt;
	m_Pressure += dt;
	m_Pressure = m_Pressure > 0 ? 0 : m_Pressure;
}

void Particle::render(Camera & _camera)
{
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, m_Texture);
		glTranslatev(m_Position);
		_camera.irrotate2D();
		glCallList(Particle::ms_Shape);
	}
	glPopMatrix();
}
	
Vector & Particle::getVelocity()
{
	return m_Velocity;
}
	
Vector const & Particle::getVelocity() const
{
	return m_Velocity;
}
	
double & Particle::getMass()
{
	return m_Mass;
}

double const & Particle::getMass() const
{
	return m_Mass;
}
	
double & Particle::getPressure()
{
	return m_Pressure;
}

double const & Particle::getPressure() const
{
	return m_Pressure;
}
