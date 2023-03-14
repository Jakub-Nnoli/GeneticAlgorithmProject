#include "Exception.h"

InvalidItemValueInFileException::InvalidItemValueInFileException(int line)
{
	this->line = line;
}

std::string InvalidItemValueInFileException::what()
{
	return "Invalid item value in file, line: " + std::to_string(line);
}

InvalidItemCapacityInFileException::InvalidItemCapacityInFileException(int line)
{
	this->line = line;
}

std::string InvalidItemCapacityInFileException::what()
{
	return "Invalid item capacity in file, line: " + std::to_string(line);
}

InvalidItemValueException::InvalidItemValueException(int offset)
{
	this->offset = offset;
}

std::string InvalidItemValueException::what()
{
	return "Invalid item value in vector, item offset: " + std::to_string(offset);
}

InvalidItemCapacityException::InvalidItemCapacityException(int offset)
{
	this->offset = offset;
}

std::string InvalidItemCapacityException::what()
{
	return "Invalid item capacity in vector, item offset: " + std::to_string(offset);
}

std::string InvalidMaximumCapacityException::what()
{
	return "Maximum capacity of knapsack below or equal to 0, check input data";
}

std::string UnmatchingNumbersOfItemsException::what()
{
	return "Sizes of vectors describing item values and capacities do not match each other, check input data";
}

std::string FileReadingException::what()
{
	return "Could not read the file, check if file exists ad if the name is correct and if it includes file extension";
}

std::string InvalidPopulationSizeException::what()
{
	return "Population size below 2, check input data";
}

std::string InvalidCrossingProbabilityException::what()
{
	return "Crossing probability not between 0 and 1, check input data";
}

std::string InvalidMutationProbabilityException::what()
{
	return "Mutation probability not between 0 and 1, check input data";
}

std::string KnapsackProblemNotExistingException::what()
{
	return "Could not find knapsack problem, check if chosen problem exists";
}

InvalidNumberOfDataInLineException::InvalidNumberOfDataInLineException(int line)
{
	this->line = line;
}

std::string InvalidNumberOfDataInLineException::what()
{
	return "Invalid data in file, line: " + std::to_string(line);
}

std::string InvaliNumberOfAlgorithmIterationsException::what()
{
	return "Invalid number of algorithm iterations, check input data";
}
