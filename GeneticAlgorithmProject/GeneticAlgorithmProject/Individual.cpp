#include "Individual.h"

Individual::Individual()
{
	genSize = 0;
	fitness = 0;
	capacity = 0;
	currentProblem = nullptr;
}

Individual::Individual(int size, std::vector<bool>& genotype, KnapsackProblem& problem)
{
	//std::cout << "Parameter_Individual_constructor\n";
	genSize = size;
	fitness = DEFAULT_FITNESS_VALUE;
	capacity = DEFAULT_CAPACITY_VALUE;
	gen = genotype;
	currentProblem = &problem;
}

Individual::Individual(const Individual& other)
{
	//std::cout << "Copying_Individual_constructor\n";
	genSize = other.genSize;
	fitness = other.fitness;
	capacity = other.capacity;
	gen = other.gen;
	currentProblem = other.currentProblem;
}

Individual::Individual(Individual&& other) noexcept
{
	//std::cout << "Moving_Individual_constructor\n";
	genSize = other.genSize;
	fitness = other.fitness;
	capacity = other.capacity;
	gen = other.gen;
	currentProblem = other.currentProblem;

	other.genSize = 0;
	other.fitness = 0;
	other.capacity = 0;
	other.gen.clear();
}

Individual::~Individual()
{
	//std::cout << "Destructor_Individual\n";
}

Individual& Individual::operator=(const Individual& other)
{
	//std::cout << "Copy_Individual_operator=\n";
	if (this != &other)
	{
		genSize = other.genSize;
		fitness = other.fitness;
		capacity = other.capacity;
		gen = other.gen;
		currentProblem = other.currentProblem;
	}
	return *this;
}

Individual& Individual::operator=(Individual&& other) noexcept
{
	//std::cout << "Move_Individual_operator=\n";
	if (this != &other)
	{
		genSize = other.genSize;
		fitness = other.fitness;
		capacity = other.capacity;
		gen = other.gen;
		currentProblem = other.currentProblem;

		other.genSize = 0;
		other.fitness = 0;
		other.capacity = 0;
		other.gen.clear();
	}
	return *this;
}

int Individual::getGenSize()
{
	return genSize;
}

int Individual::getFitness()
{
	return fitness;
}

int Individual::getCapacity()
{
	return capacity;
}

std::vector<bool>& Individual::getGen()
{
	return gen;
}

void Individual::printIndividual()
{
	for (int i = 0; i < genSize; i++)
	{
		std::cout << gen.at(i);
	}
	std::cout << "; fitness = ";
	std::cout << fitness;
	std::cout << "; capacity = ";
	std::cout << capacity;
	std::cout << std::endl;
}

void Individual::evaluateFitness()
{
	std::pair<int, int> data = currentProblem->evaluateIndividualFitnessAndCapacity(gen);
	if (fitness == (-1))
		fitness = data.first;
	capacity = data.second;
}

std::pair<Individual, Individual> Individual::cross(Individual& secondParent)
{
	int whereToCut = rng.generateCuttingGenotypeOffset(genSize);	//miejsca, gdzie moga nastapic przeciecia numerujemy od 0 do n-2 (0 - przecinamy miedzy elemntami o indeksach 0 i 1, 1 - miedzy 1 i 2 itd.) 

	std::vector<bool> firstChildGenotype;
	std::vector<bool> secondChildGenotype;

	firstChildGenotype.reserve(genSize);
	secondChildGenotype.reserve(genSize);

	for (int i = 0; i <= whereToCut; i++)
	{
		firstChildGenotype.push_back(gen.at(i));
		secondChildGenotype.push_back(secondParent.gen.at(i));
	}
	for (int i = whereToCut + 1; i < genSize; i++)
	{
		firstChildGenotype.push_back(secondParent.gen.at(i));
		secondChildGenotype.push_back(gen.at(i));
	}

	Individual firstChild(genSize, firstChildGenotype, *currentProblem);
	Individual secondChild(genSize, secondChildGenotype, *currentProblem);

	return std::pair<Individual, Individual>(firstChild,secondChild);
}

void Individual::mutate(double mutProb)
{
	double mutate;
	for (int i = 0; i < genSize; i++)
	{
		mutate = rng.generateMutationProb();
		if (mutate <= mutProb)
		{
			if (gen.at(i) == 0)
				gen.at(i) = 1;
			else
				gen.at(i) = 0;
		}
	}
}


