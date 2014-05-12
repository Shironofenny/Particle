#include "RandomGenerator.h"
#include <cstdlib>
#include <ctime>

RandomGenerator::RandomGenerator()
{
	srand(time(NULL));
	m_Seed = rand();
}

double RandomGenerator::getRandom()
{
	srand(m_Seed);
	m_Seed = rand();
	return ( ((double)rand()) / RAND_MAX );
}

Vector RandomGenerator::getRandomVector()
{
	srand(m_Seed);
	m_Seed = rand();
	return Vector( (getRandom() * 2 - 1), (getRandom() * 2 - 1), (getRandom() * 2 - 1));
}
