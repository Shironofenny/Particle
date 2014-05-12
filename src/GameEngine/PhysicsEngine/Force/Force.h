#ifndef __FORCE_H__
#define __FORCE_H__

#include <Eigen/Core>
#include "../SceneUtilities.h"

using namespace Eigen;

// The virtual class of which all forces are oriented
// Remember to override following functions for each class derived:
class Force
{
public:

	// Construction function
	Force();

	// Destructor
	virtual ~Force();

	// Add to total forces that is used to update the physical system
	// Params:
	// <rw> _force: You need to add forces in to this vector. This vector
	// 							must share the same length as _general*
	// <r>  _generalPos: The generalized position of the system to be solved
	// <r>  _generalVec: The generalized velocity of the system to be solved
	// <r>  _generalIne: The generalized inertia of the system to be solved
	virtual void addToTotalForce(VectorXd & _force, VectorXd const & _generalPos,\
															 VectorXd const & _generalVel, VectorXd const & _generalIne) const;
	
	// Usually used in sanity checks
	// Params are the same as those in force term.
	virtual void addToTotalEnergy(VectorXd & _energy, VectorXd const & _generalPos, \
															VectorXd const & _generalVel, VectorXd const & _generalIne) const;
};

#endif
