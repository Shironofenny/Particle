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

		// The information string
		string inverseInfo;
		string forwardInfo;
		string dragModeInfo;
		string selectModeInfo;
		string lockedInfo;

		// Root node name for XML file
		string xmlRootName;

		// Name of initial posing data
		string initXML;

		// The value of mouse scale along camera z direction in IK
		double mouseScale;

		// The value of delta in Inverse Kinematics
		double IKDelta;

		// The number of lights
		int numberOfLight;

		// The maximum number of lights
		int maximumNumberOfLight;

		// The vector stores all the informations of lights
		vector <Vector> positionOfLight;

	private:

		// Private constructor
		ConstantHandler();

		// Prevent from external implementation
		ConstantHandler(ConstantHandler const &);
		void operator = (ConstantHandler const &);

};

#endif
