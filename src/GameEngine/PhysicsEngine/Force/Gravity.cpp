#include "Gravity.h"

Gravity::Gravity(double const & _config) :
	Force(), 
	mGravityAcceleration(_config)
{

}

Gravity::~Gravity()
{

}

void Gravity::addToTotalForce(VectorXd & _force, VectorXd const & _generalPos,\
		 										      VectorXd const & _generalVel, VectorXd const & _generalIne) const
{
	for (int i = 0; i < _generalPos.size(); ++i)
	{
		if (i%2 == 1)
		{
			_force[i] -= _generalIne[i] * mGravityAcceleration;
		}
	}
}

void Gravity::addToTotalEnergy(VectorXd & _energy, VectorXd const & _generalPos, \
											  			 VectorXd const & _generalVel, VectorXd const & _generalIne) const
{
	
}
