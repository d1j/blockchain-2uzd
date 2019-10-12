#pragma once

#include "includes.h"

struct transaction
{
	string sender;
	string receiver;
	double ammount;
	transaction(string _sender, string _receiver, double _ammount) : sender(_sender), receiver(_receiver), ammount(_ammount) {}
	string toString()
	{
		return sender + " " + receiver + " " + std::to_string(ammount) + '\n';
	}
};

class block
{
private:
	string prevHash;
	std::vector<transaction> transactionList;
	int difficulty;
	long long nonce;
	long long blockIndex;
	time_t timeStamp;
	string version;
	string blockHash;
	int numTransactions;
	int maxNumTransactions;

	string blockToString();

public:
	block(long long index, string _prevBlockHash, int _difficulty, string _version, int _maxNumTransactions);

	void addTransaction(transaction trans);
	string mineBlock();
	void t_printBlock();

	bool isBlockFull()
	{
		return (numTransactions >= maxNumTransactions);
	}
};
