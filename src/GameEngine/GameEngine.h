#ifndef __ANIMATIONENGINE_H__
#define __ANIMATIONENGINE_H__

#include <vector>

#include <iostream>

#include "../GLHeader.h"
#include "Updater3D.h"
#include "Renderer3D.h"
#include "Utilities/FPSCounter.h"
#include "Utilities/OBJLoader.h"
#include "Utilities/TextureLoader.h"

using namespace std;

// This class is designed to handle the whole animation.
// It should be revised to the extend that simply calling (this.method) .Run()
// is enough for your (method) main function.
// 
// !! You should always starts from this class to modify any changes that
// 		you want to show in your animation clips.
class GameEngine
{
	public:
		
		// Construction function
		//
		// TODO Always modify it and add describing comments below this line.
		//
		// Usr comments starts from the following line:
		GameEngine();

		// Destruction function
		//
		// TODO Always remember to free any used pointers here to avoid memory leakage.
		//
		// Usr comments starts from the following line:
		~GameEngine();

		// Initialize the engine
		void initialize(std::string _runDir);

		// Only use this function as external call for the whole physics engine.
		// This function serves as the call back function for OpenGL
		void run();

	private:

		// Update function
		void updateGame();

		// Render function
		void renderGame();

		// System level codes ends here
		//
		// TODO Add any stuff you need to be private below this comment:
		//
		// Your code goes from here.

		// Initialize global light configuration
		void initializeLight();
		
		// The scene class for the 3D animation
		Scene3D * m_Scene;

		// The updater class for the 3D animation
		Updater3D * m_Updater;

		// The renderer of the 3D scene
		Renderer3D * m_Renderer;

		// Data used to initialize light <TBD>
		GLfloat ambient[4];
		GLfloat position[4];
		GLfloat mat_diffuse[4];
		GLfloat mat_specular[4];
		GLfloat mat_shininess[1];
	
};

#endif
