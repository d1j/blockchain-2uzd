#include "blockchain.h"

#include <fstream>

blockchain::blockchain(string fileName, int _difficulty, int _maxNumTransactions, string _version) : currentIndex(0),
																									 difficulty(_difficulty),
																									 version(_version),
																									 maxNumTransactions(_maxNumTransactions)
{
	//Initialize blockchain with data from files.
	BC.emplace_back(currentIndex, "00000000000000000000000000000000", difficulty, version, maxNumTransactions);
	std::ifstream input(fileName);
	while (!input.eof())
	{
		string sender, receiver;
		double ammount;
		input >> sender >> receiver >> ammount;
		transaction trans(sender, receiver, ammount);
		addTransaction(trans);
	}
}

void blockchain::t_printblockChain()
{
	//Print blokchain.
	for (int i = 0; i < BC.size(); i++)
	{
		BC[i].t_printBlock();
		std::cout << std::endl;
	}
}

void blockchain::addTransaction(transaction trans)
{
	if (BC[currentIndex].isBlockFull())
	{
		//Block is full. Mine block. Create new block.
		string newBlockHash = BC[currentIndex++].mineBlock();
		BC.emplace_back(currentIndex, newBlockHash, difficulty, version, maxNumTransactions);
	}
	//Add a new transaction.
	BC[currentIndex].addTransaction(trans);
}
