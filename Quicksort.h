#pragma once

#include <iostream>
#include <vector>


/*
* https://stackoverflow.com/questions/22504837/how-to-implement-quick-sort-algorithm-in-c
*/
class Quicksort
{
public:
	static void sort(int* values, unsigned int start, unsigned int end);

private:
	static unsigned int partition(int* values, unsigned int start, unsigned int end);
};

