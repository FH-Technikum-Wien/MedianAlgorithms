#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

/*
* https://gist.github.com/andlima/1774060
*/
class MedianOfMedians
{
public:
	static int sort(std::vector<int>& values, unsigned int size, unsigned int nthSmallest);
	static int find_kth(int* v, int n, int k);

};

