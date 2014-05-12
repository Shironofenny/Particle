#ifndef __SCENE3D_H__
#define __SCENE3D_H__

#include <vector>
#include <cmath>

#include "Scene.h"
#include "Camera.h"
#include "PhysicsEngine/NavierStokes.h"
#include "PhysicsEngine/Region.h"
#include "ParticleSystem/ParticleSystem.h"
#include "Utilities/TextureLoader.h"

using namespace std;

#define _USE_MATH_DEFINES

// Class name: Scene3D -- A collection of all stuff that a scene needs
// Description: This is in fact a transparent class, you could get all
// 		datas you need directly and modify them freely. However, the main
// 		reason for this class to exist is that it offers easy access for
// 		all datas to other blocks like (class) Updater and (class) Renderer.
class Scene3D : public Scene
{
	public:

		// Construction function
		Scene3D();

		// Destruction function
		~Scene3D();

		// Assign the dimension information.
		int getDimension() const { return 3; }

		// TBR
		// Initialize a scene.
		void createScene();

		// Get a copy of the current camera
		Camera & getCamera();
		Camera const & getCamera() const;

		// Return the position of the light source
		ParticleSystem & getParticleSystem();
		ParticleSystem const & getParticleSystem() const;

		Region m_PhysicsRegion;
	protected:
	
		// The main camera of this 3D scene
		Camera m_Camera;

		// The position of the light source
		ParticleSystem m_ParticleSystem;
};

#endif
