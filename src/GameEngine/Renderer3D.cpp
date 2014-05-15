#include "Renderer3D.h"

#include <iostream>
using namespace std;

Renderer3D::Renderer3D(Scene3D & _scene) :
	Renderer(), 
	m_Scene(_scene)
{
	assert( _scene.getDimension() == 3 );
	assert( _scene.getDimension() == this->getDimension() );

	m_InfoFlag = true;
}

Renderer3D::~Renderer3D()
{
}

void Renderer3D::Render()
{
	Camera & camera = m_Scene.getCamera();

	glColor4f(1.0, 1.0, 1.0, 0.8);
	if(m_Scene.getIsShowInfo())
	{
		InfoDisplayer::getInstance().renderInfo(4, "R : Hide/Show simulation region");
		InfoDisplayer::getInstance().renderInfo(3, "H : Hide/Show information");
		InfoDisplayer::getInstance().renderInfo(1, "Use U I O J K L to move the source around");
		InfoDisplayer::getInstance().renderInfo(0, "L : +x | J : -x | I : +y | K : -y | O : +z | U : -z");
	}

	camera.setup();
	
	if(m_Scene.getIsShowRegion())
	{
		m_Scene.getNavierStokes().renderRegion();
	}
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_2D,  GL_TEXTURE_ENV_MODE,  GL_MODULATE);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA,  GL_ONE_MINUS_SRC_ALPHA);
	
	m_Scene.getParticleSystem().render(camera);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
