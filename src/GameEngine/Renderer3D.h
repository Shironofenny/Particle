#ifndef __RENDERER3D_H__
#define __RENDERER3D_H__

#include "Renderer.h"
#include "Scene3D.h"
#include "Utilities/InfoDisplayer.h"

class Renderer3D : public Renderer
{
	public:

		// Constructor
		Renderer3D(Scene3D & _scene);

		// Destructor
		~Renderer3D();

		// Assign the dimension information
		int getDimension() const { return 3; };

		// The main entrance of this class
		void Render();

	private:

		// A private copy of the scene information
		Scene3D & m_Scene;

		// Flag for showing all the info
		bool m_InfoFlag;
};

#endif
