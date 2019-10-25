#pragma once
#include "includes.h"
#include "block.h"

#include <deque>

class blockchain
{
private:
	std::deque<block> BC;
	std::deque<transaction> queue;
	int currentIndex;
	int difficulty;
	int maxNumTransactions;
	string version;
	string distributor;

public:
	blockchain(string fileName, int _difficulty, int _maxNumTransactions, string _version = "v0.1");

	void addTransactionToBlockchain();

	void addTransactionToQueue(transaction trans);

	void t_printblockChain();

	bool isTransactionValid(transaction trans);

	double calculateBalance(string accountID);

	int getCurrentIndex()
	{
		return currentIndex;
	}
};
