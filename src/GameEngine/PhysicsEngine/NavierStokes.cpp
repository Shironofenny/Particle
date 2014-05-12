#include "NavierStokes.h"

NavierStokes::NavierStokes()
{
}

NavierStokes::~NavierStokes()
{
}
	
void NavierStokes::process(ParticleSystem & _system, double dt)
{
	// First compute all the physics quantities in grid
	vector <Particle> particles = _system.getParticles();
	addToDensity(particles);
}

void NavierStokes::addToDensity(vector<Particle> & _particles)
{
	for(vector<Particle>::size_type i = 0; i < _particles.size(); i++)
	{
		m_Density()
	}
}

int NavierStokes::getIndice(int x, int y, int z)
{
	return (m_FrameScale[0] * m_FrameScale[1] * z + m_FrameScale[0] * y + x);
}
	
int NavierStokes::getIndiceFromPosition(Vector & _position)
{
	int x = (_position[0] + 1) / 2 * m_FrameScale[0];
	int y = (_position[1] + 1) / 2 * m_FrameScale[1];
	int z = (_position[2] + 1) / 2 * m_FrameScale[2];
	return getIndice(x, y, z);
}
