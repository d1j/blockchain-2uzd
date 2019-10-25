#pragma once

#include "includes.h"

#include "janHash.h"

class transaction
{
private:
	string id;
	string sender;
	string receiver;
	double ammount;

public:
	transaction(string _sender, string _receiver, double _ammount) : sender(_sender), receiver(_receiver), ammount(_ammount)
	{
		string data = _sender + _receiver + std::to_string(_ammount);
		id = janHash(data);
	}
	string toString()
	{
		return id + " " + sender + " " + receiver + " " + std::to_string(ammount) + '\n';
	}
	bool isTransactionModified()
	{
		string data = sender + receiver + std::to_string(ammount);
		if (id == janHash(data))
		{
			return false;
		}
		return true;
	}
	string getSender()
	{
		return sender;
	}

	string getReceiver()
	{
		return receiver;
	}

	double getAmmount()
	{
		return ammount;
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

	int getNumTransactions()
	{
		return numTransactions;
	}

	transaction getTransaction(int index)
	{
		return transactionList[index];
	}
};
