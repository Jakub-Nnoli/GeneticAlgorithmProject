#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int popSize, double crossProb, double mutProb, KnapsackProblem& problem)
{
	//std::cout << "Parameter_GeneticAlgorithm_constructor\n";
	if (popSize <= 2)
		throw InvalidPopulationSizeException();
	if (crossProb <= 0 || crossProb > 1)
		throw InvalidCrossingProbabilityException();
	if (mutProb <= 0 || mutProb > 1)
		throw InvalidMutationProbabilityException();
	if (&problem == nullptr)
		throw KnapsackProblemNotExistingException();
	PopSize = popSize;
	CrossProb = crossProb;
	MutProb = mutProb;
	ourProblem = &problem;
	NumberOfItems = ourProblem->getNumberOfItems();
	currentPopulation.reserve(PopSize);
	nextPopulation.reserve(PopSize);
}

GeneticAlgorithm::GeneticAlgorithm(const GeneticAlgorithm& other)
{
	//std::cout << "Copying_GeneticAlgorithm_constructor\n";
	PopSize = other.PopSize;
	CrossProb = other.CrossProb;
	MutProb = other.MutProb;
	ourProblem = other.ourProblem;
	NumberOfItems = other.NumberOfItems;
	currentPopulation = other.currentPopulation;
	nextPopulation = other.nextPopulation;
}

GeneticAlgorithm::GeneticAlgorithm(GeneticAlgorithm&& other) noexcept
{
	//std::cout << "Moving_GeneticAlgorithm_constructor\n";
	PopSize = other.PopSize;
	CrossProb = other.CrossProb;
	MutProb = other.MutProb;
	ourProblem = other.ourProblem;
	NumberOfItems = other.NumberOfItems;
	currentPopulation = other.currentPopulation;
	nextPopulation = other.nextPopulation;

	other.PopSize = 0;
	other.CrossProb = 0;
	other.MutProb = 0;
	other.ourProblem = nullptr;
	other.NumberOfItems = 0;
	other.currentPopulation.clear();
	other.nextPopulation.clear();
}

GeneticAlgorithm::~GeneticAlgorithm()
{
	//std::cout << "Destructor_GeneticAlgorithm\n";
}

GeneticAlgorithm& GeneticAlgorithm::operator=(const GeneticAlgorithm& other)
{
	//std::cout << "Copy_GeneticAlgorithm_operator=\n";
	if (this != &other)
	{
		PopSize = other.PopSize;
		CrossProb = other.CrossProb;
		MutProb = other.MutProb;
		ourProblem = other.ourProblem;
		NumberOfItems = other.NumberOfItems;
		currentPopulation = other.currentPopulation;
		nextPopulation = other.nextPopulation;
	}
	return *this;
}

GeneticAlgorithm& GeneticAlgorithm::operator=(GeneticAlgorithm&& other) noexcept
{
	//std::cout << "Move_GeneticAlgorithm_operator=\n";
	if (this != &other)
	{
		PopSize = other.PopSize;
		CrossProb = other.CrossProb;
		MutProb = other.MutProb;
		ourProblem = other.ourProblem;
		NumberOfItems = other.NumberOfItems;
		currentPopulation = other.currentPopulation;
		nextPopulation = other.nextPopulation;

		other.PopSize = 0;
		other.CrossProb = 0;
		other.MutProb = 0;
		other.ourProblem = nullptr;
		other.NumberOfItems = 0;
		other.currentPopulation.clear();
		other.nextPopulation.clear();
	}
	return *this;
}

void GeneticAlgorithm::generateFirstPopulation()
{
	std::vector<bool> tab;
	tab.reserve(NumberOfItems);
	for (int i = 0; i < PopSize; i++)
	{
		for (int i = 0; i < NumberOfItems; i++)
			tab.push_back(rng.generateGenotypeElement());
		Individual individual(NumberOfItems,tab,*ourProblem);
		currentPopulation.push_back(individual);
		tab.clear();
	}
	evaluateIndividualsFitness();
}

void GeneticAlgorithm::printCurrentPopulation()
{
	for (int i = 0; i < PopSize; i++)
	{
		std::cout << "Individual nr ";
		std::cout << i;
		std::cout << ": ";
		currentPopulation.at(i).printIndividual();
	}
	std::cout << std::endl;
}

void GeneticAlgorithm::evaluateIndividualsFitness()
{
	for (int i = 0; i < PopSize; i++)
		currentPopulation.at(i).evaluateFitness();
}

std::pair<int, int> GeneticAlgorithm::drawParents()
{
	int first = chooseBetterParent(rng.generateIndividualOffset(PopSize), rng.generateIndividualOffset(PopSize));
	int second = chooseBetterParent(rng.generateIndividualOffset(PopSize), rng.generateIndividualOffset(PopSize));

	return std::pair<int, int>(first,second);
}

int GeneticAlgorithm::chooseBetterParent(int first, int second)
{
	if (currentPopulation.at(first).getFitness() < currentPopulation.at(second).getFitness())
		return second;
	return first;
}

void GeneticAlgorithm::crossParents()
{
	std::pair<int, int> parentOffsets = drawParents();

	Individual firstParent(currentPopulation.at(parentOffsets.first));
	Individual secondParent(currentPopulation.at(parentOffsets.second));

	if (rng.generateCrossingProb() > CrossProb)
	{
		nextPopulation.push_back(firstParent);
		nextPopulation.push_back(secondParent);
	}
	else
	{
		std::pair<Individual, Individual> children = firstParent.cross(secondParent);
		children.first.mutate(MutProb);
		children.second.mutate(MutProb);
		nextPopulation.push_back(children.first);
		nextPopulation.push_back(children.second);
	}
}

void GeneticAlgorithm::createNewPopulation()
{
	while (nextPopulation.size() < PopSize - 1)	//jezeli bedzie parzysta liczba osobnikow, to i tak petla za kazdym razem bedzie dodawala po dwa osobniki
		crossParents();							//wiec nawet zawsze w nastepnej generacji bdzie tyle samo osobnikow
	if (PopSize % 2 == 1)						//z kolei gdy bedzie nieparzysta to w nowej genereacji bedzie o jednego osobnika mniej
		nextPopulation.push_back(currentPopulation.at(rng.generateIndividualOffset(PopSize)));	//wiec go losujemy sposrod rodzicow

	currentPopulation.clear();
	currentPopulation = nextPopulation;
	nextPopulation.clear();
	evaluateIndividualsFitness();
	bestIndividual();
}

Individual& GeneticAlgorithm::bestIndividual()
{
	int best = 0;
	for (int i = 0; i < PopSize; i++)
	{
		if (currentPopulation.at(i).getFitness() > currentPopulation.at(best).getFitness())
			best = i;
	}
	if (currentPopulation.at(best).getFitness() > currentBest.getFitness())
		currentBest = currentPopulation.at(best);
	return currentBest;
}

void GeneticAlgorithm::runAlgorithm(int numberOfIterations)
{
	if (numberOfIterations < 1)
		throw InvaliNumberOfAlgorithmIterationsException();
	else
	{
		generateFirstPopulation();
		for (int i = 0; i < numberOfIterations; i++)
		{
			createNewPopulation();
			std::cout << "Iteraton number: ";
			std::cout << (i + 1);
			std::cout << std::endl;
			std::cout << "Current best individual: ";
			currentBest.printIndividual();
			std::cout << std::endl;
		}
		//printCurrentPopulation();
	}
}


