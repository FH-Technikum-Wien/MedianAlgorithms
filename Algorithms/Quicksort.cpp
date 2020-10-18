#include "Quicksort.h"

void Quicksort::sort(std::vector<int>& values, unsigned int start, unsigned int end)
{
	unsigned int pivot;
	if (start < end) {
		pivot = partition(values, start, end);
		// Prevents negative pivot.
		if (pivot == 0)
			return;
		// Sort left side.
		sort(values, start, pivot - 1);
		// Sort right side.
		sort(values, pivot + 1, end);
	}
}

unsigned int Quicksort::partition(std::vector<int>& values, unsigned int start, unsigned int end)
{
	int pivotValue = values[end];
	unsigned int i = start;

	for (unsigned int j = start; j < end; j++)
	{
		// Current values smaller/equal to pivot -> Swap.
		if (values[j] <= pivotValue) {

			if(i != j)
				std::swap(values[i], values[j]);
			i++;
		}
	}
	// Set pivot to correct spot.
	if(i != end)
		std::swap(values[i], values[end]);
	return i;
}


