#include <iostream>
#include <algorithm>
#include "Algorithms/Quicksort.h"
#include "Algorithms/RandomizedSelect.h"
#include "Algorithms/MedianOfMedians.h"


void printArray(int values[], int arraySize) {
	for (int i = 0; i < arraySize; i++)
		std::cout << values[i] << " ";
	std::cout << std::endl;
}

int main()
{
	const unsigned int numberOfRandoms = 101;
	int values[numberOfRandoms];
	std::srand(0);
	for (unsigned int i = 0; i < numberOfRandoms; i++)
		values[i] = std::rand();

	//printArray(values, numberOfRandoms);

	int quickSortValues[numberOfRandoms];
	int stdSortValues[numberOfRandoms];
	int randomSelectValues[numberOfRandoms];
	int medianMedianValues[numberOfRandoms];
	int nthElementValues[numberOfRandoms];
	std::copy(std::begin(values), std::end(values), quickSortValues);
	std::copy(std::begin(values), std::end(values), stdSortValues);
	std::copy(std::begin(values), std::end(values), randomSelectValues);
	std::copy(std::begin(values), std::end(values), medianMedianValues);
	std::copy(std::begin(values), std::end(values), nthElementValues);

	Quicksort::sort(quickSortValues, 0, numberOfRandoms - 1);
	std::cout << "Quicksort - Median: " << quickSortValues[numberOfRandoms / 2] << std::endl;

	std::sort(stdSortValues, stdSortValues + numberOfRandoms);
	std::cout << "std::sort - Median: " << stdSortValues[numberOfRandoms / 2] << std::endl;

	int median = RandomizedSelect::sort(randomSelectValues, 0, numberOfRandoms - 1, (numberOfRandoms + 1) / 2);
	std::cout << "RandomSelect - Median: " << median << std::endl;

	median = MedianOfMedians::sort(medianMedianValues, numberOfRandoms, (numberOfRandoms) / 2);
	std::cout << "Median of medians - Median: " << median << std::endl;

	std::nth_element(nthElementValues, nthElementValues + (numberOfRandoms / 2), nthElementValues + numberOfRandoms);
	std::cout << "STL-nth_element - Median: " << nthElementValues[numberOfRandoms / 2] << std::endl;
}
