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
	m_ParticleSystem.parseXML(ConstantHandler::getInstance().particleSystemSource[0]);
	m_NavierStokes.parseXML(ConstantHandler::getInstance().navierStokesSource[0]);

	m_CurrentSystemNumber = 0;

	m_IsShowInfo = true;
	m_IsShowRegion = true;
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

bool & Scene3D::getIsShowInfo()
{
	return m_IsShowInfo;
}

bool const & Scene3D::getIsShowInfo() const
{
	return m_IsShowInfo;
}

bool & Scene3D::getIsShowRegion()
{
	return m_IsShowRegion;
}

bool const & Scene3D::getIsShowRegion() const
{
	return m_IsShowRegion;
}

int & Scene3D::getCurrentSystemNumber()
{
	return m_CurrentSystemNumber;
}

int const & Scene3D::getCurrentSystemNumber() const
{
	return m_CurrentSystemNumber;
}
