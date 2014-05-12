#ifndef __GRAVITY_H__
#define __GRAVITY_H__

#include "Force.h"

class Gravity : public Force
{
	public:
		
		// Constructor
		// <r> _config: Extra configuration that is required for the force
		// 							Spring force needs to know which two types are tighted
		// 							together with how big k is.
		Gravity(double const & _config);

		// Destructor
		~Gravity();

		// Override total force function
		void addToTotalForce(VectorXd & _force, VectorXd const & _generalPos,\
		 										VectorXd const & _generalVel, VectorXd const & _generalIne) const override;

		// Override total energy function
		void addToTotalEnergy(VectorXd & _energy, VectorXd const & _generalPos, \
											  VectorXd const & _generalVel, VectorXd const & _generalIne) const override;
		
	private:

		// The gravity acceleration
		double mGravityAcceleration;
};

#endif
