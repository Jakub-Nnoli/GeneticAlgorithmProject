#include <iostream>
#include <random>
#include "GeneticAlgorithm.h"
int main()
{
	try
	{	
		std::string fileName;
		int iterations=-1, popSize=-1;
		double crossProb=-1, mutProb=-1;

		std::cout << "Hello, please insert necessary data to run your algorithm" << std::endl;

		std::cout << "Just remember, the file name you give should have file extension" << std::endl;
		std::cout << "And data in this file should have one integer in the first line and two integers in all next lines!" << std::endl;
		std::cout << "Enter file name (string with file extension): ";
		std::cin >> fileName;
		KnapsackProblem problem(fileName);

		std::cout << "Enter number of algorithm iterations (integer greater than 0): ";
		std::cin >> iterations;
		
		std::cout << "Enter population size (integer greater than 2): ";
		std::cin >> popSize;

		std::cout << "Enter crossing probability (double between 0 and 1): ";
		std::cin >> crossProb;

		std::cout << "Enter mutatuion probability (double between 0 and 1): ";
		std::cin >> mutProb;

		GeneticAlgorithm ga(popSize, crossProb, mutProb, problem);
		ga.runAlgorithm(iterations);
	}
	catch (InvalidPopulationSizeException e)
	{
		std::cout << e.what();
	}
	catch (InvalidCrossingProbabilityException e)
	{
		std::cout << e.what();
	}
	catch (InvalidMutationProbabilityException e)
	{
		std::cout << e.what();
	}
	catch (KnapsackProblemNotExistingException e)
	{
		std::cout << e.what();
	}
	catch (InvalidMaximumCapacityException e)
	{
		std::cout << e.what();
	}
	catch (UnmatchingNumbersOfItemsException e)
	{
		std::cout << e.what();
	}
	catch (InvalidItemValueException e)
	{
		std::cout << e.what();
	}
	catch (InvalidItemCapacityException e)
	{
		std::cout << e.what();
	}
	catch (InvalidItemValueInFileException e)
	{
		std::cout << e.what();
	}
	catch (InvalidItemCapacityInFileException e)
	{
		std::cout << e.what();
	}
	catch (FileReadingException e)
	{
		std::cout << e.what();
	}
	catch (InvalidNumberOfDataInLineException e)
	{
		std::cout << e.what();
	}
	catch (InvaliNumberOfAlgorithmIterationsException e)
	{
		std::cout << e.what();
	}

	return 0;
}