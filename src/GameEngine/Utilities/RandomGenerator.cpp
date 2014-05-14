#include "RandomGenerator.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

#define _USE_MATH_DEFINES

RandomGenerator::RandomGenerator()
{
	srand(time(NULL));
	m_Seed = rand();
}

double RandomGenerator::getRandom()
{
	srand(m_Seed);
	m_Seed = rand();
	return ( ((float)rand()) / RAND_MAX );
}

Vector RandomGenerator::getRandomVector()
{
	return Vector( (getRandom() * 2 - 1), (getRandom() * 2 - 1), (getRandom() * 2 - 1));
}

Vector RandomGenerator::getRandomUnitVector()
{
	float phi = getRandom() * 2 * M_PI - M_PI / 12;
	float theta = acos(2 * getRandom() - 1);
	return Vector(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
}
