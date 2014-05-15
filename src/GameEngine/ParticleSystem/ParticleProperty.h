#ifndef __PARTICLECOLOR_H__
#define __PARTICLECOLOR_H__

#include <vector>
#include <iostream>


#include "../Utilities/MathHeader.h"
#include "../../GLHeader.h"

using namespace std;

class ParticleProperty
{
public:

	// Constructor
	ParticleProperty();

	// Destructor
	~ParticleProperty();

	// Get a color from time ratio
	void getProperty(float _timeRatio, GLfloat color[4], Vector & scale, float & pressure);

	// Add a key frame to the particle color class
	void addFrame(float _tr, float _r, float _g, float _b, float _a,\
			float _sx, float _sy, float _sz, float _p);

	// Initialize this particle color class
	void initialize();

protected:

	// Time ratio from start to end
	vector<float> m_TimeRatio;

	// RGB sequence
	vector<Vector> m_RGB;

	// Alpha sequence
	vector<float> m_Alpha;

	// The scale sequence of the particle
	vector<Vector> m_Scale;

	// The pressure sequence of the particle
	vector<float> m_Pressure;

};

#endif
