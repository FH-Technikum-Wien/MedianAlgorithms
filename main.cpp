#include <iostream>
#include <algorithm>
#include <time.h> 
#include "Algorithms/Quicksort.h"
#include "Algorithms/RandomizedSelect.h"
#include "Algorithms/MedianOfMedians.h"

#include <chrono>


void printArray(int values[], int arraySize) {
	for (int i = 0; i < arraySize; i++)
		std::cout << values[i] << " ";
	std::cout << std::endl;
}

int main()
{
	// Settings
	const unsigned int numberOfRandoms = 5001;
	const unsigned int randomIterations = 20;
	const unsigned int sameIterations = 10;
	const unsigned int processSteps = 20;
	unsigned int totalIterations = randomIterations * sameIterations;


	// Times
	std::chrono::microseconds quickSortTime = std::chrono::duration<long long, std::milli>();
	std::chrono::microseconds stdSortTime = std::chrono::duration<long long, std::milli>();
	std::chrono::microseconds randomSelectTime = std::chrono::duration<long long, std::milli>();
	std::chrono::microseconds medianMedianTime = std::chrono::duration<long long, std::milli>();
	std::chrono::microseconds nthElementTime = std::chrono::duration<long long, std::milli>();


	// Process prints
	std::cout << "Using " << randomIterations << " random iterations and " << sameIterations << "same iterations:"<< std::endl;
	for (unsigned int i = 0; i < processSteps; i++)
		std::cout << "_";
	std::cout << std::endl;

	// Repeats with different data sets.
	for (unsigned int i = 0; i < randomIterations; i++)
	{
		std::srand(time(NULL));

		// Data
		std::vector<int>* values = new std::vector<int>();
		for (unsigned int i = 0; i < numberOfRandoms; i++)
			values->push_back(std::rand());

		// Repeats with same data set.
		for (unsigned int j = 0; j < sameIterations; j++)
		{
			std::vector<int>* quickSortValues = new std::vector<int>(*values);
			std::vector<int>* stdSortValues = new std::vector<int>(*values);
			std::vector<int>* randomSelectValues = new std::vector<int>(*values);
			std::vector<int>* medianMedianValues = new std::vector<int>(*values);
			std::vector<int>* nthElementValues = new std::vector<int>(*values);

			// Quicksort
			auto start = std::chrono::high_resolution_clock::now();
			Quicksort::sort(*quickSortValues, 0, numberOfRandoms - 1);
			int median = quickSortValues->at(numberOfRandoms / 2);
			auto stop = std::chrono::high_resolution_clock::now();
			quickSortTime += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

			// std::sort
			start = std::chrono::high_resolution_clock::now();
			std::sort(stdSortValues->begin(), stdSortValues->end());
			median = stdSortValues->at(numberOfRandoms / 2);
			stop = std::chrono::high_resolution_clock::now();
			stdSortTime += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

			// RandomizedSelect
			start = std::chrono::high_resolution_clock::now();
			median = RandomizedSelect::sort(*randomSelectValues, 0, numberOfRandoms - 1, numberOfRandoms / 2);
			stop = std::chrono::high_resolution_clock::now();
			randomSelectTime += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

			// MedianOfMedians
			start = std::chrono::high_resolution_clock::now();
			median = MedianOfMedians::sort(*medianMedianValues, numberOfRandoms, (numberOfRandoms) / 2);
			stop = std::chrono::high_resolution_clock::now();
			medianMedianTime += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

			// nth_element
			start = std::chrono::high_resolution_clock::now();
			std::nth_element(nthElementValues->begin(), nthElementValues->begin() + (numberOfRandoms / 2), nthElementValues->end());
			median = nthElementValues->at(numberOfRandoms / 2);
			stop = std::chrono::high_resolution_clock::now();
			nthElementTime += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

			delete(quickSortValues);
			delete(stdSortValues);
			delete(randomSelectValues);
			delete(medianMedianValues);
			delete(nthElementValues);

			if ((i * sameIterations + j) % (totalIterations / processSteps) == 0)
				std::cout << "#";
		}

		delete(values);
	}
	std::cout << std::endl;

	std::cout << "Quicksort time:\t\t" << quickSortTime.count() / totalIterations << std::endl;
	std::cout << "std::sort time:\t\t" << stdSortTime.count() / totalIterations << std::endl;
	std::cout << "RandomizedSelect time:\t" << randomSelectTime.count() / totalIterations << std::endl;
	std::cout << "MedianOfMedians time:\t" << medianMedianTime.count() / totalIterations << std::endl;
	std::cout << "nth_element time:\t" << nthElementTime.count() / totalIterations << std::endl;
	std::cout << "\t\t\tMicroseconds" << std::endl;
}
