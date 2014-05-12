#include "Scene3D.h"

Scene3D::Scene3D():
	Scene(), 
	m_Camera(Vector(0, 0, 2))
{
}

Scene3D::~Scene3D()
{
}

void Scene3D::createScene()
{
	m_ParticleSystem.parseXML("data/particles.xml");
	m_PhysicsRegion.getLeftNearBottom() = Vector(-1., -1., -1.);
	m_PhysicsRegion.getRightFarTop() = Vector(1., 1., 1.);
}

Camera & Scene3D::getCamera()
{
	return m_Camera;
}

Camera const & Scene3D::getCamera() const
{
	return m_Camera;
}

ParticleSystem & Scene3D::getParticleSystem()
{
	return m_ParticleSystem;
}

ParticleSystem const & Scene3D::getParticleSystem() const
{
	return m_ParticleSystem;
}
