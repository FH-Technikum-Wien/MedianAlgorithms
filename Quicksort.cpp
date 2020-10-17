#include "Quicksort.h"

void Quicksort::sort(int * values, unsigned int start, unsigned int end)
{
	unsigned int pivot;
	if (start < end) {
		pivot = partition(values, start, end);
		// Sort left side.
		sort(values, start, pivot - 1);
		// Sort right side.
		sort(values, pivot + 1, end);
	}
}

unsigned int Quicksort::partition(int* values, unsigned int start, unsigned int end)
{
	int pivotValue = values[end];
	unsigned int i = start;

	// Skip pivot.
	for (unsigned int j = start; j < end; j++)
	{
		// Current values smaller/equal to pivot -> Swap.
		if (values[j] <= pivotValue) {
			std::swap(values[i], values[j]);
			i++;
		}
	}
	// Set pivot to correct spot.
	std::swap(values[i], values[end]);
	return i;
}


