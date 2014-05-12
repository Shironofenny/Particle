#ifndef __SCENEUTILITIES_H__
#define __SCENEUTILITIES_H__

#include <utility>
#include <tuple>
#include <vector>

using namespace std;

namespace sceneUtility
{
	// Line : <firstNode, secondNode>
	typedef pair <int, int> line;

	// Spring : see following 
	typedef tuple <line, double, double> spring;

	const int gSpringNodes = 0;
	const int gSpringLength = 1;
	const int gSpringK = 2;

	const double gKOfSpring = 100.0;
	const double gInitialLength = 2.0;

	// Gravity
	const double gGravityAcceleration = 9.81;

	// Torque :
	typedef tuple <int, int, int, double> torque;

	const int gTorqueNodeBefore = 0;
	const int gTorqueNodeCenter = 1;
	const int gTorqueNodeAfter = 2;

	const double gKOfTorque = 100.0;

	// Air friction. 
	// Assume air firction F_air = (g)AirFrictionFactor * v
	const double gAirFrictionFactor = 1.0;

	// Time step of the calculation
	const double gDt = 0.05;
}

#endif
