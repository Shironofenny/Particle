#ifndef __PHYSICSENGINE_H__
#define __PHYSICSENGINE_H__

#include <Eigen/Core>
using namespace Eigen;

class PhysicsEngine
{
public:

	// Constructor
	PhysicsEngine ();

	// Destructor
	virtual ~PhysicsEngine ();

	// Main entrance of the whole engine, advance the system in time dt
	virtual void process(VectorXd & _force, VectorXd & _generalPos, VectorXd & _generalVel,\
		 	VectorXd & _generalIne, double dt);

};

#endif
