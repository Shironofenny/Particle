#ifndef __PHYSICSENGINE_H__
#define __PHYSICSENGINE_H__

#include <Eigen/Core>

class PhysicsEngine
{
public:

	// Constructor
	PhysicsEngine ();

	// Destructor
	virtual ~PhysicsEngine ();

	// Main entrance of the whole engine, advance the system in time dt
	virtual void process(Eigen::VectorXd & _force, Eigen::VectorXd & _generalPos,\
		 	Eigen::VectorXd & _generalVel, Eigen::VectorXd & _generalIne, double dt);

	EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
};

#endif
