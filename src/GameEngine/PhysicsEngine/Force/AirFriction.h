#ifndef __AIRFRICTION_H__
#define __AIRFRICTION_H__

#include "Force.h"

class AirFriction : public Force
{
	public:

		// Constructor
		AirFriction(double const &);

		// Destructor
		~AirFriction();

		// Override total force function
		void addToTotalForce(VectorXd & _force, VectorXd const & _generalPos,\
		 										VectorXd const & _generalVel, VectorXd const & _generalIne) const override;

		// Override total energy function
		void addToTotalEnergy(VectorXd & _energy, VectorXd const & _generalPos, \
											  VectorXd const & _generalVel, VectorXd const & _generalIne) const override;

	protected:

		double mFrictionFactor;
};

#endif
