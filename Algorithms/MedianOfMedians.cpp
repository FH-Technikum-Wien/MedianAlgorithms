#include "MedianOfMedians.h"


int MedianOfMedians::sort(std::vector<int>& values, unsigned int size, unsigned int nthSmallest)
{
	if (size == 1 && nthSmallest == 0)
		return values[0];

	std::vector<int> medians;
	for (unsigned i = 0; i < size / 5; i++)
	{
		// Do quicksort for the first 2 indexes.
		for (unsigned int j = 0; j < 3; j++)
		{
			// Find smallest. Everything before j + 1 is sorted.
			unsigned int smallest = j;
			for (unsigned k = j + 1; k < 5; k++)
			{
				if (values[i * 5 + k] < values[i * 5 + smallest])
					smallest = k;
			}
			// Swap smallest with current position.
			std::swap(values[i * 5 + j], values[i * 5 + smallest]);
		}
		// Median is at index 2 of a sorted group of 5 elements.
		medians.push_back(values[(i * 5) + 2]);
	}

	// If not a factor of 5, take first element.
	unsigned int remain = size % 5;
	if (remain != 0) {
		medians.push_back(values[(size - remain)]);
	}

	int pivotValue = sort(medians, medians.size(), medians.size() / 2);

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

	// Put pivot in between lower and higher.
	std::swap(values[pivot], values[size - 1]);

	// If pivot is wanted number, return.
	if (pivot == nthSmallest)
		return pivotValue;

	// If pivot is bigger than wanted number, repeat with lower half.
	if (pivot > nthSmallest)
		return sort(values, pivot, nthSmallest);
	
	// If pivot is smaller than wanted number, repeat with higher half.
	std::vector<int> subValues(values.begin() + pivot + 1, values.end());
	return sort(subValues, size - pivot - 1, nthSmallest - pivot - 1);
}
