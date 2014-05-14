#ifndef __RANDOMGENERATOR_H__
#define __RANDOMGENERATOR_H__

#include "MathHeader.h"

class RandomGenerator
{
public:

	// Singeleton
	static RandomGenerator & getInstance()
	{
		static RandomGenerator instance;
		return instance;
	}

	// Return a random number
	double getRandom();
	
	// Return a random vector
	Vector getRandomVector();
	
	// Return a spherical random vector
	Vector getRandomUnitVector();

private:

	// Constructor
	RandomGenerator();

	// Prevent from external implementation
	RandomGenerator(RandomGenerator const &);
	void operator = (RandomGenerator const &);

	// The seed used to get number randomized
	int m_Seed;

};

#endif
