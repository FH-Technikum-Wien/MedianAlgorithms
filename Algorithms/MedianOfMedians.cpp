#include "MedianOfMedians.h"


int MedianOfMedians::sort(int* values, unsigned int size, unsigned int nthSmallest)
{
	if (size < 6) {
		std::sort(values, values + size);
		return values[nthSmallest];
	}

	std::vector<int> medians;
	for (unsigned i = 0; i < size / 5; i++)
	{
		// Sort in groups of five.
		std::sort(values + (i * 5), values + (i * 5) + 4);
		// Median is at index 2 of a sorted group of 5 elements.
		medians.push_back(values[(i * 5) + 2]);
	}

	unsigned int remain = size % 5;
	if (remain != 0) {
		std::sort(values + (size / 5), values + size);
		// Add median of remain.
		medians.push_back(values[(size - remain) / 2]);
	}

	int pivotValue = sort(&medians[0], medians.size(), medians.size() / 2);

	// Find pivotValue in array and put it at the end.
	for (unsigned int i = 0; i < size; i++) {
		if (values[i] == pivotValue) {
			std::swap(values[i], values[size - 1]);
			break;
		}
	}

	// Sort by pivotValue.
	int pivot = 0;
	for (unsigned int i = 0; i < size - 1; i++) {
		if (values[i] < pivotValue)
			std::swap(values[i], values[pivot++]);
	}

	// Put pivot inbetween lower and higher.
	std::swap(values[pivot], values[size - 1]);

	// If pivot is wanted number, return.
	if (pivot == nthSmallest)
		return pivotValue;

	// If pivot is bigger than wanted number, repeat with lower half.
	if (pivot > nthSmallest)
		return sort(values, pivot, nthSmallest);
	
	// If pivot is smaller than wanted number, repeat with higher half.
	return sort(values + pivot + 1, size - pivot - 1, nthSmallest - pivot - 1);
}