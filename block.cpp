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
				 merkle + '\n';
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

void block::computeMerkle()
{
	std::vector<string> _merkle;

	for (auto it = transactionList.begin(); it != transactionList.end(); it++)
	{
		_merkle.push_back((*it).getID());
	}

	if (_merkle.size() == 0)
	{
		merkle = "00000000000000000000000000000000";
		return;
	}
	else if (_merkle.size() == 1)
	{
		merkle = _merkle[0];
		return;
	}
	//cout << "MERKLE\n";

	while (_merkle.size() > 1)
	{
		//cout << "\n\n";

		if (_merkle.size() % 2 != 0)
			_merkle.push_back(_merkle.back());

		std::vector<string> _newMerkle;

		for (auto it = _merkle.begin(); it != _merkle.end(); it += 2)
		{
			string concat = (*it) + (*(it + 1));
			string newHash = janHash(concat);
			_newMerkle.push_back(newHash);
			//cout << newHash << std::endl;
		}

		_merkle = _newMerkle;
	}
	merkle = _merkle[0];
	return;
}

string block::mineBlock()
{
	string diffString = "";

	for (int i = 0; i < difficulty; i++)
	{
		diffString += "0";
	}

	//compute merkle
	computeMerkle();

	auto start = high_resolution_clock::now();
	do
	{
		nonce++;
		blockHash = janHash(blockToString());
	} while (blockHash.substr(0, difficulty) != diffString);

	auto end = high_resolution_clock::now();
	duration<double> diff = end - start;
	timeStamp = time(0);
	cout << "Block " << blockIndex << " mined in: " << diff.count() << endl
		 << blockHash << endl
		 << endl;

	return blockHash;
}

void block::t_printBlock()
{
	if (nonce == -1)
	{
		timeStamp = 0;
	}
	std::cout << "BLOCK INDEX: " << blockIndex << std::endl
			  << "Version: " << version << std::endl
			  << "Previous block hash: " << prevHash << std::endl
			  << "Difficulty: " << difficulty << std::endl
			  << "Nonce: " << nonce << std::endl
			  << "Time stamp: " << std::to_string(timeStamp) << std::endl
			  << "Block Hash: " << blockHash << std::endl
			  << "Merkle root hash: " << merkle << std::endl
			  << "Data: \n";

	string a;
	/*
	for (int i = 0; i < transactionList.size(); i++)
	{
		cout << transactionList[i].toString();
	}
	cin >> a;
	*/
}