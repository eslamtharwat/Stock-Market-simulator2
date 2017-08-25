#pragma once
#include <string>
#include <fstream>
using namespace std;

class bank
{
private:
	float balance;
	string bank_name;

public:

	bank();

	float getbalance();
	string getbank_name();

	void setbank_name(string);

	void withdrow(float);
	void deposit(float);
	void buy(float, int, float);
	void sell(float, int, float);

	bool save_bank(int);
	bool load_bank(int);
};