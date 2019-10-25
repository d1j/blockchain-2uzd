#include "blockchain.h"

#include <fstream>

blockchain::blockchain(string fileName, int _difficulty, int _maxNumTransactions, string _version) : currentIndex(0),
																									 difficulty(_difficulty),
																									 version(_version),
																									 maxNumTransactions(_maxNumTransactions)
{
	distributor = janHash(std::to_string(-1));
	//Initialize blockchain with data from files.
	BC.emplace_back(currentIndex, "00000000000000000000000000000000", difficulty, version, maxNumTransactions);
	std::ifstream input(fileName);
	while (!input.eof())
	{
		string sender, receiver;
		double ammount;
		input >> sender >> receiver >> ammount;
		transaction trans(sender, receiver, ammount);
		addTransactionToQueue(trans);
	}
	while (!queue.empty())
	{
		addTransactionToBlockchain();
	}
}

void blockchain::addTransactionToQueue(transaction trans)
{
	queue.push_back(trans);
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

double blockchain::calculateBalance(string accountID)
{
	double sendersBalance = 0;
	for (int i = 0; i <= currentIndex; i++) //iterates through blocks
	{
		for (int j = 0; j < BC[i].getNumTransactions(); j++) //iterates through transactions
		{
			transaction pastTrans = BC[i].getTransaction(j);
			if (pastTrans.getSender() == accountID)
			{
				sendersBalance -= pastTrans.getAmmount();
			}
			if (pastTrans.getReceiver() == accountID)
			{
				sendersBalance += pastTrans.getAmmount();
			}
		}
	}
	return sendersBalance;
}

bool blockchain::isTransactionValid(transaction trans)
{
	if (trans.getSender() != distributor)
	{
		double sendersBalance = calculateBalance(trans.getSender());
		if (sendersBalance > trans.getAmmount())
		{
			//transaction is valid
			return true;
		}
		return false;
	}
	return true;
}

void blockchain::addTransactionToBlockchain()
{
	if (BC[currentIndex].isBlockFull())
	{
		//Block is full. Mine block. Create new block.
		string newBlockHash = BC[currentIndex++].mineBlock();
		BC.emplace_back(currentIndex, newBlockHash, difficulty, version, maxNumTransactions);
	}
	//Add a new transaction.
	if (!queue[0].isTransactionModified() && isTransactionValid(queue[0]))
	{
		/*
		cout << "Transaction added: \n"
			 << queue[0].toString() << endl;
		*/
		//Transaction is valid and not modified

		BC[currentIndex].addTransaction(queue[0]);
	}
	/*
	else
	{
		cout << "Transaction discarded: \n"
			 << queue[0].toString() << endl;
	}
	*/
	queue.pop_front();
}
