#pragma once

#include <iostream>
#include <vector>
/*
* http://analgorithmaday.blogspot.com/2011/05/randomized-selection-algorithm.html
*/
class RandomizedSelect
{
public:
	static int sort(std::vector<int>& values, unsigned int start, unsigned int end, unsigned int nSmallest, unsigned int seed = 0);
private:
	static int randomizedSelect(std::vector<int>& values, unsigned int start, unsigned int end, unsigned int nSmallest);
	static int randomizedPartition(std::vector<int>& values, unsigned int start, unsigned int end);
};

