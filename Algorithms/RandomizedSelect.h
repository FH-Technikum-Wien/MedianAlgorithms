#pragma once

#include <iostream>
/*
* http://analgorithmaday.blogspot.com/2011/05/randomized-selection-algorithm.html
*/
class RandomizedSelect
{
public:
	static int sort(int* values, unsigned int start, unsigned int end, unsigned int nSmallest, unsigned int seed = 0);
private:
	static int randomizedSelect(int* values, unsigned int start, unsigned int end, unsigned int nSmallest);
	static int randomizedPartition(int* values, unsigned int start, unsigned int end);
};

