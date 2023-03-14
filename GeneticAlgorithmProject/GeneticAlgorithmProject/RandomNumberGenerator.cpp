#include "RandomNumberGenerator.h"

std::random_device dev;
std::mt19937 seed(dev());

bool RandomNumberGenerator::generateGenotypeElement()
{
	std::uniform_int_distribution<> distr(0, 1);
	return distr(seed);
}

int RandomNumberGenerator::generateIndividualOffset(int popSize)
{
	std::uniform_int_distribution<> distr(0, popSize - 1);
	return distr(seed);
}

double RandomNumberGenerator::generateCrossingProb()
{
	std::uniform_real_distribution<> distr(0, 1);
	return distr(seed);
}

double RandomNumberGenerator::generateMutationProb()
{
	std::uniform_real_distribution<> distr(0, 1);
	return distr(seed);
}

int RandomNumberGenerator::generateCuttingGenotypeOffset(int genSize)
{
	std::uniform_int_distribution<> distr(0, genSize - 2);
	return distr(seed);
}
