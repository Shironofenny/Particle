#include "AirFriction.h"

AirFriction::AirFriction(double const & _config) :
	Force(), 
	mFrictionFactor(_config)
{

}

AirFriction::~AirFriction()
{

}

void AirFriction::addToTotalForce(VectorXd & _force, VectorXd const & _generalPos,\
							 										VectorXd const & _generalVel, VectorXd const & _generalIne) const
{
	_force -= mFrictionFactor * _generalVel;
}

void AirFriction::addToTotalEnergy(VectorXd & _energy, VectorXd const & _generalPos, \
															  VectorXd const & _generalVel, VectorXd const & _generalIne) const
{

}
