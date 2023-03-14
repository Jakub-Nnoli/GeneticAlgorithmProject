#pragma once

#include <iostream>
#include <random>
#include <fstream>

class RandomNumberGenerator
{
public:
	bool generateGenotypeElement();
	int generateIndividualOffset(int popSize);
	double generateCrossingProb();
	double generateMutationProb();
	int generateCuttingGenotypeOffset(int genSize);
};

