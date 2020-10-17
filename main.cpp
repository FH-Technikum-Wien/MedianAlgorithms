#include <iostream>
#include <algorithm>
#include "Quicksort.h"
#include "RandomizedSelect.h"
#include "MedianOfMedians.h"


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

	int* quickSortValues = new int[numberOfRandoms];
	int* stdSortValues = new int[numberOfRandoms];
	int* randomSelectValues = new int[numberOfRandoms];
	int* medianMedianValues = new int[numberOfRandoms];
	int* nthElementValues = new int[numberOfRandoms];
	std::copy(std::begin(values), std::end(values), quickSortValues);
	std::copy(std::begin(values), std::end(values), stdSortValues);
	std::copy(std::begin(values), std::end(values), randomSelectValues);
	std::copy(std::begin(values), std::end(values), medianMedianValues);
	std::copy(std::begin(values), std::end(values), nthElementValues);

	Quicksort::sort(quickSortValues, 0, numberOfRandoms - 1);
	std::cout << "Quicksort - Median: " << quickSortValues[numberOfRandoms / 2] << std::endl;

	delete[] quickSortValues;

	std::sort(stdSortValues, stdSortValues + numberOfRandoms);
	std::cout << "std::sort - Median: " << stdSortValues[numberOfRandoms / 2] << std::endl;

	delete[] stdSortValues;

	int median = RandomizedSelect::sort(randomSelectValues, 0, numberOfRandoms - 1, (numberOfRandoms + 1) / 2);
	std::cout << "RandomSelect - Median: " << median << std::endl;

	delete[] randomSelectValues;

	median = MedianOfMedians::sort(medianMedianValues, numberOfRandoms, (numberOfRandoms) / 2);
	std::cout << "Median of medians - Median: " << median << std::endl;

	delete[] medianMedianValues;

	std::nth_element(nthElementValues, nthElementValues + (numberOfRandoms / 2), nthElementValues + numberOfRandoms);
	std::cout << "STL-nth_element - Median: " << nthElementValues[numberOfRandoms / 2] << std::endl;

	delete[] nthElementValues;
}
