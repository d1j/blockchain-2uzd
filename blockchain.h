#pragma once
#include "includes.h"
#include "block.h"

#include <vector>

class blockchain
{
private:
	std::vector<block> BC;
	std::vector<transaction> queue;
	int currentIndex;
	int difficulty;
	int maxNumTransactions;
	string version;

public:
	blockchain(string fileName, int _difficulty, int _maxNumTransactions, string _version = "v0.1");

	void addTransaction(transaction trans);

	void t_printblockChain();

	int getCurrentIndex()
	{
		return currentIndex;
	}
};
