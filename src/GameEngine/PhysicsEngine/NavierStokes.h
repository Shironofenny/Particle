#ifndef __NAVIERSTOKES_H__
#define __NAVIERSTOKES_H__

#include "../Utilities/MathHeader.h"
#include "PhysicsEngine.h"
#include "../ParticleSystem/ParticleSystem.h"

// This class solves Navier Stokes equation in a Eulerian 3D grid
// and copy the result back to particles.
class NavierStokes : public PhysicsEngine
{
public:

	// Constructor
	NavierStokes();

	// Destructor
	~NavierStokes();
	
	// Main entrance of the whole engine, advance the system in time dt
	// For fluid equation, this function will first process in Eulerian scheme, then translate
	// the grids into Lagrangian scheme, i.e., assign each particle with a corresponding velocity
	// and corresponding position.
	void process(ParticleSystem & _system, double dt);

protected:
	
	// Get the linear indice from a 3D grid point
	int getIndice(int x, int y, int z);

	// Get the indice of a real position to the gird
	int getIndiceFromPosition(Vector & _position);

	// Add the data to the total density
	void addToDensity(vector<Particle> & _particles);

	// The vector stores the scale of the simulation scheme
	Vector m_FrameScale;

	// The storage of properties on grids
	// Whether this is a boundary
	VectorXd m_IsBoundary;

	// Mass at each grid point
	VectorXd m_Density;

	// Velocity at each grid point
	VectorXd m_VelocityX; 
	VectorXd m_VelocityY; 
	VectorXd m_VelocityZ; 

};

#endif
