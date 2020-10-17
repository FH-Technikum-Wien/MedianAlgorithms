#pragma once
#include <vector>
#include <stdexcept>
class LFGenerator
{
public:
	std::vector<unsigned int> seed{
		969861836,	779147150,	777653285,	158916089,	10865413,	603734547,	307912741,	215707035,	453268328,
		680915890,	861995934,	62657686,	766867134,	602853321,	292998651,	241909299,	411142524,	442694584,
		142542994,	292424026,	148636607,	159539163,	434258625,	105156655,	646156376,	768739706,	619144501,
		763349544,	796214269,	486238972,	165994625,	757035337,	464723123,	464011209,	184885318,	847812740,
		428315416,	459262655,	410398151,	22838314,	684290490,	972039257,	16925287,	269135801,	425976668,
		911606108,	384449829,	810739371,	224520191,	54314221,	143817267,	474255865
	};
	// 
	unsigned int j = 24;
	unsigned int k = 52;
	unsigned int m = 4294967295;

	LFGenerator() = default;

	LFGenerator(std::vector<unsigned int> seed, unsigned int j, unsigned int k, unsigned int m) : j(j), k(k), m(m) {
		if (j >= k)
			throw std::invalid_argument("The parameter 'j' must be smaller than 'k'!");
		else if (j >= seed.size())
			throw std::invalid_argument("The parameter 'j' must be smaller than the seed size!");
		else if (k > seed.size())
			throw std::invalid_argument("The parameter 'j' must be smaller or equal to the seed size!");
	};

	unsigned int next() {
		// Generate random number.
		unsigned int r = (seed[j - 1] + seed[k - 1]) % m;
		// Shift array
		for (unsigned int i = 0; i < seed.size() - 1; i++) {
			seed[i] = seed[i + 1];
		}
		// Add random number to seed.
		seed[seed.size() - 1] = r;

		return r;
	}

	/*
	* Returns a value between 0 and 1.
	*/
	float nextFloat() {
		return next() / m;
	}
};

