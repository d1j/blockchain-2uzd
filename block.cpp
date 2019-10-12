#include "block.h"
#include "janHash.h"

#include <ctime>
#include <chrono>

using namespace std::chrono;

block::block(long long _index, string _prevBlockHash, int _difficulty, string _version, int _maxNumTransactions) : version(_version),
																												   prevHash(_prevBlockHash),
																												   difficulty(_difficulty),
																												   nonce(-1),
																												   blockIndex(_index),
																												   transactionList(),
																												   numTransactions(0),
																												   maxNumTransactions(_maxNumTransactions)
{
}

string block::blockToString()
{
	string str = std::to_string(blockIndex) + '\n' +
				 version + '\n' +
				 prevHash + '\n' +
				 std::to_string(difficulty) + '\n' +
				 std::to_string(nonce) + '\n' +
				 std::to_string(timeStamp) + '\n';
	for (int i = 0; i < transactionList.size(); i++)
	{
		str += transactionList[i].toString();
	}
	return str;
}

void block::addTransaction(transaction trans)
{
	numTransactions++;
	transactionList.push_back(trans);
}

string block::mineBlock()
{
	string diffString = "";

	for (int i = 0; i < difficulty; i++)
	{
		diffString += "0";
	}

	auto start = high_resolution_clock::now();
	do
	{
		nonce++;
		timeStamp = time(0);
		blockHash = janHash(blockToString());
	} while (blockHash.substr(0, difficulty) != diffString);

	auto end = high_resolution_clock::now();
	duration<double> diff = end - start;
	cout << "Block " << blockIndex << " mined in: " << diff.count() << endl
		 << blockHash << endl
		 << endl;

	return blockHash;
}

void block::t_printBlock()
{
	std::cout << "BLOCK INDEX: " << blockIndex << std::endl
			  << "Version: " << version << std::endl
			  << "Previous block hash: " << prevHash << std::endl
			  << "Difficulty: " << difficulty << std::endl
			  << "Nonce: " << nonce << std::endl
			  << "Time stamp: " << std::to_string(timeStamp) << std::endl
			  << "Block Hash: " << blockHash << std::endl
			  << "Data: \n";
	/*for (int i = 0; i < transactionList.size(); i++) {
		cout << transactionList[i].toString();
	}*/
}