#include "includes.h"

#include <random>

int gen_reiksm(int intPrad, int intPab)
{
	static std::random_device rd;
	static std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(intPrad, intPab);
	return dist(mt);
}