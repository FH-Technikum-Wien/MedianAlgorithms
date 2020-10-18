#include "MedianOfMedians.h"


int MedianOfMedians::sort(std::vector<int>& values, unsigned int size, unsigned int nthSmallest)
{
	if (size == 1 && nthSmallest == 0)
		return values[0];

	std::vector<int> medians;
	for (unsigned i = 0; i < size / 5; i++)
	{
		int* currentFive = &values[0] + i * 5;
		// Do insertion sort for the first 2 indices.
		for (unsigned int j = 0; j < 3; j++)
		{
			// Find smallest. Everything before j + 1 is sorted.
			unsigned int smallest = j;
			for (unsigned k = j + 1; k < 5; k++)
			{
				if (currentFive[k] < currentFive[smallest])
					smallest = k;
			}
			// Swap smallest with current position.
			std::swap(currentFive[j], currentFive[smallest]);
		}
		// Median is at index 2 of a sorted group of 5 elements.
		medians.push_back(currentFive[2]);
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

/*
* https://gist.github.com/andlima/1774060
*/
int MedianOfMedians::find_kth(int* v, int n, int k) {
	if (n == 1 && k == 0) return v[0];

	int m = (n + 4) / 5;
	int* medians = new int[m];
	for (int i = 0; i < m; i++) {
		if (5 * i + 4 < n) {
			int* w = v + 5 * i;
			for (int j0 = 0; j0 < 3; j0++) {
				int jmin = j0;
				for (int j = j0 + 1; j < 5; j++) {
					if (w[j] < w[jmin]) jmin = j;
				}
				std::swap(w[j0], w[jmin]);
			}
			medians[i] = w[2];
		}
		else {
			medians[i] = v[5 * i];
		}
	}

	int pivot = find_kth(medians, m, m / 2);
	delete[] medians;

	for (int i = 0; i < n; i++) {
		if (v[i] == pivot) {
			std::swap(v[i], v[n - 1]);
			break;
		}
	}

	int store = 0;
	for (int i = 0; i < n - 1; i++) {
		if (v[i] < pivot) {
			std::swap(v[i], v[store++]);
		}
	}
	std::swap(v[store], v[n - 1]);

	if (store == k) {
		return pivot;
	}
	else if (store > k) {
		return find_kth(v, store, k);
	}
	else {
		return find_kth(v + store + 1, n - store - 1, k - store - 1);
	}
}
