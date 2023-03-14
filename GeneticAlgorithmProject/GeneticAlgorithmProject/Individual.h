#pragma once

#include <iostream>
#include <random>
#include "KnapsackProblem.h"
#include "RandomNumberGenerator.h"

#define DEFAULT_FITNESS_VALUE -1
#define DEFAULT_CAPACITY_VALUE -1

class Individual
{
public:
	Individual();
	Individual(int size, std::vector<bool>& genotype, KnapsackProblem& problem);
	
	Individual(const Individual& other);
	Individual(Individual&& other) noexcept;
	
	~Individual();

	Individual& operator=(const Individual& other);
	Individual& operator=(Individual&& other) noexcept;

	int getGenSize();
	int getFitness();
	int getCapacity();
	std::vector<bool>& getGen();

	void evaluateFitness();
	std::pair<Individual, Individual> cross(Individual& secondParent);
	void mutate(double mutProb);

	void printIndividual();

private:
	//skladowe
	int genSize;
	int fitness;
	int capacity;
	std::vector<bool> gen;
	KnapsackProblem* currentProblem;
	RandomNumberGenerator rng;
};

