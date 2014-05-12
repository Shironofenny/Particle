#include "ParticleSystem.h"
#include "../Utilities/TextureLoader.h"
#include "../Utilities/RandomGenerator.h"

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::parseXML(string const & _filename)
{
	int w, h;
	m_ParticleTexture = TextureLoader::getInstance().loadTexture("data/texture/particle.png", w, h);
	Particle::buildParticle( w * 0.002 );
	for(int i = 1; i < 100; i++)
	{
		Particle par(m_ParticleTexture, 1.0);
		par.getOrientation() += RandomGenerator::getInstance().getRandomVector();
		par.getMass() = 1.0;
		m_Particles.push_back(par);
	}
}
	
void ParticleSystem::update(double dt)
{
	for(vector<Particle>::iterator it = m_Particles.begin(); it < m_Particles.end(); it++)
	{
		it->update(dt);
		if (it->isDead())
		{
			m_Particles.erase(it);
			it -= 1;
		}
	}
	for(int i = 1; i < 10; i++)
	{
		Particle par(m_ParticleTexture, 1.0);
		par.getOrientation() += RandomGenerator::getInstance().getRandomVector();
		par.getMass() = 1.0;
		m_Particles.push_back(par);
	}
}

void ParticleSystem::render(Camera & _camera)
{
	for(vector<Particle>::size_type i = 0; i < m_Particles.size(); i++)
	{
		m_Particles[i].render(_camera);
	}
}

int ParticleSystem::getParticleNumber()
{
	return m_Particles.size();
}
	
vector<Particle> & ParticleSystem::getParticles()
{
	return m_Particles;
}
	
vector<Particle> const & ParticleSystem::getParticles() const
{
	return m_Particles;
}
