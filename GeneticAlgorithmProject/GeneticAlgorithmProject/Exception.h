#pragma once
#include <iostream>
#include <string>
class Exception:public std::exception
{
};

class InvalidItemValueInFileException :public std::exception
{
public:
	InvalidItemValueInFileException(int line);
	std::string what();
private:
	int line;
};

class InvalidItemCapacityInFileException :public std::exception
{
public:
	InvalidItemCapacityInFileException(int line);
	std::string what();
private:
	int line;
};

class InvalidItemValueException :public std::exception
{
public:
	InvalidItemValueException(int offset);
	std::string what();
private:
	int offset;
};

class InvalidItemCapacityException :public std::exception
{
public:
	InvalidItemCapacityException(int offset);
	std::string what();
private:
	int offset;
};

class InvalidMaximumCapacityException :public std::exception
{
public:
	std::string what();
};

class UnmatchingNumbersOfItemsException :public std::exception
{
public:
	std::string what();
};

class FileReadingException :public std::exception
{
public:
	std::string what();
};

class InvalidPopulationSizeException :public std::exception
{
public:
	std::string what();
};

class InvalidCrossingProbabilityException :public std::exception
{
public:
	std::string what();
};

class InvalidMutationProbabilityException :public std::exception
{
public:
	std::string what();
};

class KnapsackProblemNotExistingException :public std::exception
{
public:
	std::string what();
};

class InvalidNumberOfDataInLineException :public std::exception
{
public:
	InvalidNumberOfDataInLineException(int line);
	std::string what();
private:
	int line;
};

class InvaliNumberOfAlgorithmIterationsException :public std::exception 
{
public:
	std::string what();
};