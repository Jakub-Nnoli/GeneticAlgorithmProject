#pragma once

#include <iostream>
#include <vector>
#include <random>
#include "Individual.h"
#include "RandomNumberGenerator.h"
#include "Exception.h"

class GeneticAlgorithm
{
public:
	GeneticAlgorithm(int popSize, double crossProb, double mutProb, KnapsackProblem& problem);

	GeneticAlgorithm(const GeneticAlgorithm& other);
	GeneticAlgorithm(GeneticAlgorithm&& other) noexcept;
	
	~GeneticAlgorithm();

	GeneticAlgorithm& operator=(const GeneticAlgorithm& other);
	GeneticAlgorithm& operator=(GeneticAlgorithm&& other) noexcept;

	void runAlgorithm(int numberOfIterations);

private:
	//skladowe
	int PopSize;
	double CrossProb;
	double MutProb;

	KnapsackProblem* ourProblem;

	int NumberOfItems; //rowniez reprezentuje dlugosc kazdego genotypu

	std::vector<Individual> currentPopulation;
	std::vector<Individual> nextPopulation;

	Individual currentBest;

	RandomNumberGenerator rng;

	//metody
	void generateFirstPopulation();
	void printCurrentPopulation();
	void evaluateIndividualsFitness();
	std::pair<int, int> drawParents();
	int chooseBetterParent(int first, int second);
	void crossParents();
	void createNewPopulation();
	Individual& bestIndividual();
};

