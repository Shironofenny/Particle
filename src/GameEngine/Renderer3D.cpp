#include "Renderer3D.h"

#include <iostream>
using namespace std;

Renderer3D::Renderer3D(Scene3D & _scene) :
	Renderer(), 
	m_Scene(_scene)
{
	assert( _scene.getDimension() == 3 );
	assert( _scene.getDimension() == this->getDimension() );
}

Renderer3D::~Renderer3D()
{
}

void Renderer3D::Render()
{
	Camera & camera = m_Scene.getCamera();

	camera.setup();
	
	m_Scene.getNavierStokes().renderRegion();

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_2D,  GL_TEXTURE_ENV_MODE,  GL_MODULATE);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA,  GL_ONE_MINUS_SRC_ALPHA);
	
	m_Scene.getParticleSystem().render(camera);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
