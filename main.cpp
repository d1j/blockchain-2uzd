#include <iostream>
#include <fstream>

#include "blockchain.h"
#include "generate.h"

int main()
{
	string transFileName = "transactions.txt", usersFileName = "users.txt";
	double maxBalanceSize = 10000;
	double maxTransSize = 10000;
	int maxNumTransactionsInABlock = 10;
	int difficulty = 2;
	int numUsers = 5;
	int numTransactions = 20;

	generateUsers(usersFileName, numUsers, maxBalanceSize);
	generateTransactions(usersFileName, transFileName, numTransactions, maxTransSize);

	blockchain BC(transFileName, difficulty, maxNumTransactionsInABlock);

	BC.t_printblockChain();
}