#ifndef __CONSTANTHANDLER_H__
#define __CONSTANTHANDLER_H__

#include <string>

#include "XMLParser.h"
#include "../Utilities/MathHeader.h"
#include "../../GLHeader.h"

using namespace std;

// Class to handle all constant definition
class ConstantHandler
{
	public:

		// Singleton
		static ConstantHandler & getInstance()
		{
			static ConstantHandler instance;
			return instance;
		}

		// Parse configuration from file
		void initialize();

		// Refresh the window size information
		void restoreWindowSize(int x, int y);

		// Switch to render movie out
		bool isMovieMade;

		// Camera configs
		double cameraSpeed;

		double cameraRotateZ;
		
		double virtualRotationRadius;

		// Window configs
		int windowSizeX;

		int windowSizeY;

		int mousePositionX;

		int mousePositionY;

		// The configuration file name of particle system
		vector<string> particleSystemSource;

		// The configuration file of Navier-Stokes simulation
		vector<string> navierStokesSource;

	private:

		// Private constructor
		ConstantHandler();

		// Prevent from external implementation
		ConstantHandler(ConstantHandler const &);
		void operator = (ConstantHandler const &);

};

#endif
