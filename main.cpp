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
	// Don't use 101.
	const unsigned int numberOfRandoms = 100001;
	std::vector<int>* values = new std::vector<int>();
	std::srand(0);
	for (unsigned int i = 0; i < numberOfRandoms; i++)
		values->push_back(std::rand());

	//printArray(values, numberOfRandoms);

	std::vector<int>* quickSortValues = new std::vector<int>(*values);
	std::vector<int>* stdSortValues = new std::vector<int>(*values);
	std::vector<int>* randomSelectValues = new std::vector<int>(*values);
	std::vector<int>* medianMedianValues = new std::vector<int>(*values);
	std::vector<int>* nthElementValues = new std::vector<int>(*values);

	Quicksort::sort(*quickSortValues, 0, numberOfRandoms - 1);
	int median = quickSortValues->at(numberOfRandoms / 2);
	std::cout << "Quicksort - Median: " << median << std::endl;

	delete(quickSortValues);

	std::sort(stdSortValues->begin(), stdSortValues->end());
	median = stdSortValues->at(numberOfRandoms / 2);
	std::cout << "std::sort - Median: " << median << std::endl;

	delete(stdSortValues);

	median = RandomizedSelect::sort(*randomSelectValues, 0, numberOfRandoms - 1, (numberOfRandoms + 1) / 2);
	std::cout << "RandomSelect - Median: " << median << std::endl;

	delete(randomSelectValues);

	median = MedianOfMedians::sort(*medianMedianValues, numberOfRandoms, (numberOfRandoms) / 2);
	std::cout << "Median of medians - Median: " << median << std::endl;

	delete(medianMedianValues);

	std::nth_element(nthElementValues->begin(), nthElementValues->begin() + (numberOfRandoms / 2), nthElementValues->end());
	median = nthElementValues->at(numberOfRandoms / 2);
	std::cout << "STL-nth_element - Median: " << median << std::endl;

	delete(nthElementValues);
}
