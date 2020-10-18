#include <iostream>
#include <algorithm>
#include <time.h> 
#include <ctime>
#include <fstream>
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
	const unsigned int numberOfRandoms = 100001;
	const unsigned int randomIterations = 20;
	const unsigned int identicalIterations = 2;
	const unsigned int processSteps = 5;
	unsigned int totalIterations = randomIterations * identicalIterations;


	// Times
	std::chrono::microseconds quickSortTime = std::chrono::duration<long long, std::milli>();
	std::chrono::microseconds stdSortTime = std::chrono::duration<long long, std::milli>();
	std::chrono::microseconds randomSelectTime = std::chrono::duration<long long, std::milli>();
	std::chrono::microseconds medianMedianTime = std::chrono::duration<long long, std::milli>();
	std::chrono::microseconds nthElementTime = std::chrono::duration<long long, std::milli>();


	// Process prints
	std::cout << "Using " << randomIterations << " random iterations with " << identicalIterations << " identical iterations and " << numberOfRandoms << " elements:" << std::endl;
	for (unsigned int i = 0; i < processSteps; i++)
		std::cout << "_";
	std::cout << std::endl;

	// Log
	std::ofstream logFile;
	logFile.open("data.log", std::ios::out | std::ios::app);

	// Timestamp
	struct tm newtime;
	__time32_t aclock;
	char buffer[32];
	// Get time in seconds.
	_time32(&aclock);  
	// Convert time to struct tm form.
	_localtime32_s(&newtime, &aclock);   
	asctime_s(buffer, 32, &newtime);
	logFile << buffer << "\n";

	logFile << "Number of elements:\t\t" << numberOfRandoms << "\n";
	logFile << "Number of random iterations:\t" << randomIterations << "\n";
	logFile << "Number of identical iterations:\t" << identicalIterations << "\n\n";

	// Repeats with different data sets.
	for (unsigned int i = 0; i < randomIterations; i++)
	{
		std::srand(time(NULL));

		// Data
		std::vector<int>* values = new std::vector<int>();
		for (unsigned int i = 0; i < numberOfRandoms; i++)
			values->push_back(std::rand() + 1);

		// Repeats with same data set.
		for (unsigned int j = 0; j < identicalIterations; j++)
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
			median = MedianOfMedians::find_kth(medianMedianValues->data(), numberOfRandoms, (numberOfRandoms) / 2);
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

			if ((i * identicalIterations + j) % (totalIterations / processSteps) == 0)
				std::cout << "#";
		}

		delete(values);
	}
	std::cout << std::endl;

	logFile << "Quicksort time:\t\t" << quickSortTime.count() / totalIterations << std::endl;
	logFile << "std::sort time:\t\t" << stdSortTime.count() / totalIterations << std::endl;
	logFile << "RandomizedSelect time:\t" << randomSelectTime.count() / totalIterations << std::endl;
	logFile << "MedianOfMedians time:\t" << medianMedianTime.count() / totalIterations << std::endl;
	logFile << "nth_element time:\t" << nthElementTime.count() / totalIterations << std::endl;
	logFile << "\t\t\tMicroseconds" << std::endl;
	logFile << std::endl;

	logFile.close();
}
