#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Exception.h"

class KnapsackProblem
{
public:
	KnapsackProblem(std::string& fileName);
	KnapsackProblem(int maxCap, std::vector<int>& itemVals, std::vector<int>& itemCaps);

	KnapsackProblem(const KnapsackProblem& other);
	KnapsackProblem(KnapsackProblem&& other) noexcept;

	~KnapsackProblem();

	KnapsackProblem& operator=(const KnapsackProblem& other);
	KnapsackProblem& operator=(KnapsackProblem&& other) noexcept;

	int getMaxCapacity();
	int getNumberOfItems();
	int getItemValue(int itemIndex);
	int getItemCapacity(int itemIndex);

	std::pair<int, int> evaluateIndividualFitnessAndCapacity(std::vector<bool>& genotype);

	void printProblemDetails();

private:
	//skladowe
	int maxCapacity;
	int numberOfItems;
	std::vector<int> itemValues;
	std::vector<int> itemCapacities;

};

