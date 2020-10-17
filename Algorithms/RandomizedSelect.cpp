#include "RandomizedSelect.h"

int RandomizedSelect::sort(std::vector<int>& values, unsigned int start, unsigned int end, unsigned int nSmallest, unsigned int seed)
{
	// Set seed.
	std::srand(seed);
	return randomizedSelect(values, start, end, nSmallest);
}

int RandomizedSelect::randomizedSelect(std::vector<int>& values, unsigned int start, unsigned int end, unsigned int nSmallest)
{
	// Reached wanted nth-smallest number.
	if (start == end)
		return values[start];

	// Gets random pivot position.
	unsigned int rPivot = randomizedPartition(values, start, end);
	// Number of elements in partition p to rPivot.
	unsigned int elementCount = rPivot - start + 1;
	// Does pivot equal nth-smallest number?
	if (nSmallest == elementCount)
		return values[rPivot];

	if (nSmallest < elementCount)
		return sort(values, start, rPivot - 1, nSmallest);
	else
		return sort(values, rPivot + 1, end, nSmallest - elementCount);
}

int RandomizedSelect::randomizedPartition(std::vector<int>& values, unsigned int start, unsigned int end)
{
	// Get random pivot. Wrap around (+1 to include 'end').
	unsigned int pivot = start + std::rand() % (end - start + 1);
	int pivotValue = values[pivot];
	// Put pivot to end (start would also be fine).
	std::swap(values[pivot], values[end]);
	pivot = end;

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
