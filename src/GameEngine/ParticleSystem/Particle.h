#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "../Sprite.h"
#include "../Camera.h"

class Particle : public Sprite
{
public:

	// Constructor
	Particle(GLuint _texture, double _lifeTime);

	// Destructor
	~Particle();

	// Override function, should be called per frame to update the infomation (position, orientation)
	// of this particle
	void update(double dt);

	// Override function, called when you want to render this particle.
	void render(Camera & _camera);

	// Return life/totalLifeTime, used to judge color etc.
	double getLifeRatio();

	// Return if this particle is already dead.
	bool isDead();

	// Get a copy of orientation vector
	Vector & getOrientation();
	Vector const & getOrientation() const;

	// Get a copy of the mass of the particle
	double & getMass();
	double const & getMass() const;

	// Static part, which means this part is the same for all particles
	// Build particle ties a geometric coordinate to texture coordinate, and build this into a list
	static void buildParticle(double _scale);

protected:
	
	// The orientation of this particle
	Vector m_Orientation;

	// The current life of this particle
	double m_Life;

	// The total life time of this particle
	double m_LifeTime;

	// The mass of this particle
	double m_Mass;

	// The number of the loaded texture
	GLuint m_Texture;

	// Static part, which means this part is the same for all particles
	// The OpenGL call list number
	static GLuint ms_Shape;
};

#endif
