#include "generate.h"
#include "janHash.h"

#include <stdlib.h>
#include <fstream>

struct user
{
	string key;
	double ammount;
	user(string _key, double _ammount) : key(_key), ammount(_ammount) {}
};

void generateUsers(string outputFileName, int numUsers)
{
	std::ofstream output(outputFileName);
	for (int i = 0; i < numUsers; i++)
	{
		if (i == numUsers - 1)
		{
			output << janHash(std::to_string(i)) << " " << gen_reiksm(100, 1000000);
		}
		else
		{
			output << janHash(std::to_string(i)) << " " << gen_reiksm(100, 1000000) << std::endl;
		}
	}
	output.close();
}

void generateTransactions(string inputFileName, string outputFileName, int numTransactions)
{
	std::ifstream input(inputFileName);
	std::vector<user> users;
	while (!input.eof())
	{
		string key;
		double ammount;
		input >> key >> ammount;
		users.emplace_back(key, ammount);
	}
	users.pop_back();
	input.close();
	string distributor = janHash(std::to_string(-1));
	std::ofstream output(outputFileName);
	for (int i = 0; i < users.size(); i++)
	{
		output << distributor << " " << users[i].key << " " << users[i].ammount << endl;
	}
	for (int i = 0; i < numTransactions; i++)
	{
		string sender = users[gen_reiksm(0, users.size() - 1)].key;
		string receiver = users[gen_reiksm(0, users.size() - 1)].key;
		while (sender == receiver)
		{
			receiver = users[gen_reiksm(0, users.size() - 1)].key;
		}
		if (i == numTransactions - 1)
		{
			output << sender << " " << receiver << " " << gen_reiksm(1, 10000);
		}
		else
		{
			output << sender << " " << receiver << " " << gen_reiksm(1, 10000) << endl;
		}
	}
	output.close();
}