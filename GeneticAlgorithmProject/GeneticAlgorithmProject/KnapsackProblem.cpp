#include "KnapsackProblem.h"

KnapsackProblem::KnapsackProblem(std::string& fileName)
{
	//std::cout << "File_KnapsackProblem_constructor\n";
	std::ifstream inputFile(fileName);
	if (inputFile.is_open())
	{
		int lineIndex = 1;
		std::string readLine;
		std::istringstream readLineStream;

		std::getline(inputFile, readLine);
		readLineStream.str(readLine);

		readLineStream >> maxCapacity;
		if (maxCapacity <= 0)
			throw InvalidMaximumCapacityException();

		int itemVal = 0, itemCap = 0;
		while (!inputFile.eof())
		{
			lineIndex++;
			std::getline(inputFile, readLine);

			readLineStream.clear();
			readLineStream.str(readLine);

			readLineStream >> itemVal >> itemCap;

			if (itemVal <= 0)
				throw InvalidItemValueInFileException(lineIndex);
			if (itemCap <= 0)
				throw InvalidItemCapacityInFileException(lineIndex);

			itemValues.push_back(itemVal);
			itemCapacities.push_back(itemCap);
		}
		if (itemValues.size() != itemCapacities.size())
			throw UnmatchingNumbersOfItemsException();
		numberOfItems = itemValues.size();
		inputFile.close();
	}
	else
		throw FileReadingException();
}

KnapsackProblem::KnapsackProblem(int maxCap, std::vector<int>& itemVals, std::vector<int>& itemCaps)
{
	//std::cout << "Parameter_KnapsackProblem_constructor\n";
	if (maxCap <= 0)
		throw InvalidMaximumCapacityException();
	if (itemVals.size() != itemCaps.size())
		throw UnmatchingNumbersOfItemsException();
	for (int i = 0; i < itemVals.size(); i++)
	{
		if (itemVals.at(i) <= 0)
			throw InvalidItemValueException(i);
		if (itemCaps.at(i) <= 0)
			throw InvalidItemCapacityException(i);
	}
	maxCapacity = maxCap;
	numberOfItems = itemVals.size();
	itemValues = itemVals;
	itemCapacities = itemCaps;	
}

KnapsackProblem::KnapsackProblem(const KnapsackProblem& other)
{
	//std::cout << "Copying_KnapsackProblem_constructor\n";
	maxCapacity = other.maxCapacity;
	numberOfItems = other.numberOfItems;
	itemValues = other.itemValues;
	itemCapacities = other.itemCapacities;
}

KnapsackProblem::KnapsackProblem(KnapsackProblem&& other) noexcept
{
	//std::cout << "Moving_KnapsackProblem_constructor\n";
	maxCapacity = other.maxCapacity;
	numberOfItems = other.numberOfItems;
	itemValues = other.itemValues;
	itemCapacities = other.itemCapacities;

	other.maxCapacity = 0;
	other.numberOfItems = 0;
	other.itemValues.clear();
	other.itemCapacities.clear();
}

KnapsackProblem::~KnapsackProblem()
{
	//std::cout << "Destructor_KnapsackProblem\n";
}

KnapsackProblem& KnapsackProblem::operator=(const KnapsackProblem& other)
{
	//std::cout << "Copy_KnapsackProblem_operator=\n";
	if (this != &other)
	{
		maxCapacity = other.maxCapacity;
		numberOfItems = other.numberOfItems;
		itemValues = other.itemValues;
		itemCapacities = other.itemCapacities;
	}
	return *this;
}

KnapsackProblem& KnapsackProblem::operator=(KnapsackProblem&& other) noexcept
{
	//std::cout << "Move_KnapsackProblem_operator=\n";
	if (this != &other)
	{
		maxCapacity = other.maxCapacity;
		numberOfItems = other.numberOfItems;
		itemValues = other.itemValues;
		itemCapacities = other.itemCapacities;

		other.maxCapacity = 0;
		other.numberOfItems = 0;
		other.itemValues.clear();
		other.itemCapacities.clear();
	}
	return *this;
}

int KnapsackProblem::getMaxCapacity()
{
	return maxCapacity;
}

int KnapsackProblem::getNumberOfItems()
{
	return numberOfItems;
}

int KnapsackProblem::getItemValue(int itemIndex)
{
	return itemValues[itemIndex];
}

int KnapsackProblem::getItemCapacity(int itemIndex)
{
	return itemCapacities[itemIndex];
}

std::pair<int, int> KnapsackProblem::evaluateIndividualFitnessAndCapacity(std::vector<bool>& genotype)
{
	int value = 0;
	int capacity = 0;
	for (int i = 0; i < numberOfItems; i++)
	{
		if (genotype.at(i))
		{
			value += itemValues.at(i);
			capacity += itemCapacities.at(i);
		}
	}
	if (capacity <= maxCapacity)
		return std::pair<int,int>(value,capacity);
	return std::pair<int, int>(0, capacity);
}

void KnapsackProblem::printProblemDetails()
{
	std::cout << "Maximum knapsack capacity: "<<maxCapacity<<std::endl;
	std::cout << "Number of items: " << numberOfItems << std::endl;
	std::cout << "Item Values:  Item Capacities: " << std::endl;
	for (int i = 0; i < numberOfItems; i++)
		std::cout << itemValues.at(i) << " " << itemCapacities.at(i)<<std::endl;
}
