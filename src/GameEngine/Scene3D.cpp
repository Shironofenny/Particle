#include "Scene3D.h"
#include "Utilities/ConstantHandler.h"

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
	m_ParticleSystem.parseXML(ConstantHandler::getInstance().particleSystemSource);
	m_PhysicsRegion.getLeftNearBottom() = Vector(-1., -1., -1.);
	m_PhysicsRegion.getRightFarTop() = Vector(1., 1., 1.);
	m_NavierStokes.initialize(Vector(10, 19, 10),\
		 m_ParticleSystem.getSource() +	Vector(0, 0.25, 0), 0.05);
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
		
NavierStokes & Scene3D::getNavierStokes()
{
	return m_NavierStokes;
}
	
NavierStokes const & Scene3D::getNavierStokes() const
{
	return m_NavierStokes;
}
