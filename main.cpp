#include <iostream>
#include <fstream>

#include "blockchain.h"
#include "generate.h"

int main()
{
	string transFileName = "transactions.txt", usersFileName = "users.txt";
	int maxNumTransactionsInABlock = 100;
	int difficulty = 2;
	int numUsers = 1000;
	int numTransactions = 10000;

	generateUsers(usersFileName, numUsers);
	generateTransactions(usersFileName, transFileName, numTransactions);

	blockchain BC(transFileName, difficulty, maxNumTransactionsInABlock);

	//BC.t_printblockChain();
}