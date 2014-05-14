#ifndef __NAVIERSTOKES_H__
#define __NAVIERSTOKES_H__

#include "PhysicsEngine.h"
#include "Region.h"
#include "../Utilities/MathHeader.h"
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

	// Initialize the physics engine
	void initialize(Vector _frameScale, Vector _deviation, float _spacing);
	
	// Main entrance of the whole engine, advance the system in time dt
	// For fluid equation, this function will first process in Eulerian scheme, then translate
	// the grids into Lagrangian scheme, i.e., assign each particle with a corresponding velocity
	// and corresponding position.
	void process(vector<Particle> & _particles, Vector & _source, double dt);

	// Render the region that this navier stokes has its effect
	void renderRegion();

protected:
	
	// Get the linear indice from a 3D grid point
	int getIndice(int x, int y, int z);

	// Return the size of the simulation system
	int getSize();

	// Get the indice of a real position to the gird
	void getIndiceFromPosition(Vector & _position, int & x, int & y, int & z, bool & isOut);

	// Add the data to the total density
	void setPressure(vector<Particle> & _particles);
	
	// Set the velocity field of this physics engine
	void setVelocity(Vector & _source);

	// Assign the velocity back to particles
	void assignVelocity(vector<Particle> & _particles);

	// Diffuse one step dt from _oldValue to new one
	void diffuse(Eigen::VectorXf & _oldValue, Eigen::VectorXf & _newValue, float _coeff,\
		 	int _type, double dt);

	// Advect one step dt from _oldValue to new one
	void advect(Eigen::VectorXf & _oldValue, Eigen::VectorXf & _newValue, Eigen::VectorXf & _vx,\
		Eigen::VectorXf & _vy, Eigen::VectorXf & _xz,	int _type, double dt);

	// Add pressure force to the velocity field
	void addPressure(double dt);

	// Remove the curl from the vector field, such that it is mass conserving
	void removeCurl(Eigen::VectorXf & _vx, Eigen::VectorXf & _vy, Eigen::VectorXf & _vz);

	// Set the boundary value
	void setBoundary(Eigen::VectorXf & _value, int type);

	// The region that Navier-Stokes is applied
	Region m_Region;

	// The deviation of the region from centering the source
	Vector m_Deviation;

	// The diffusivity of the fluid flow
	float m_Diffusivity;

	// The viscousity of the fluid flow
	float m_Viscousity;

	// The bouyancy force of the flow
	float m_Bouyancy;

	// The flag for initializing velocity field
	bool m_IsVelocityInitialized;

	// The vector stores the scale of the simulation scheme
	Vector m_FrameScale;

	// The space between grid points
	float m_Spacing;
	float m_OneOverSpacing;

	// The iteration time for computing diffusion and advection
	int m_IterationTime;

	// The storage of properties on grids
	// Whether this is a boundary
	Eigen::VectorXf m_IsBoundary;

	// Pressure at each grid point
	Eigen::VectorXf m_Pressure;

	// The divergence of V
	Eigen::VectorXf m_VDiv;

	// Velocity at each grid point
	Eigen::VectorXf m_VelocityX; 
	Eigen::VectorXf m_VelocityY; 
	Eigen::VectorXf m_VelocityZ; 
	Eigen::VectorXf m_VelocityX0; 
	Eigen::VectorXf m_VelocityY0; 
	Eigen::VectorXf m_VelocityZ0; 

};

#endif
