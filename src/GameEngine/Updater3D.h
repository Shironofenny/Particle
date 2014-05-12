#ifndef __UPDATER3D_H__
#define __UPDATER3D_H__

#include "Updater.h"
#include "Scene3D.h"
#include <vector>

class Updater3D : public Updater
{
	public:

		// Construction function
		Updater3D(Scene3D & _scene);

		// Destroyer
		~Updater3D() {}
		
		// Main function, ie. the entrance of the class.
		void Update(double dt);

	protected:
		
		// A private copy of the scene. As it is a reference, 
		// it will always trace and report any modifications
		// made to the original scene.
		Scene3D & m_Scene;
		
		// Process mouse selection using current mouse position.
		// It returns the number which is the number specified by glLoadName(int) of object 
		// hit by the mouse
		// If returns -1, then no object is hit.
		// See TODO tag inside to make it function well
		int processSelection();
};

#endif
