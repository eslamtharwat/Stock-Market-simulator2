#include "bank.h"

bank::bank()
{
	balance = 0;
}

float bank::getbalance()
{
	return balance;
}
string bank::getbank_name()
{
	return bank_name;
}

void bank::setbank_name(string bank_name)
{
	this->bank_name = bank_name;
}
void bank::withdrow(float cash)
{
	balance -= cash;
}
void bank::deposit(float cash)
{
	balance += cash;
}
void bank::buy(float price, int quantity, float commision)
{
	balance -= (price + commision)*quantity;
}
void bank::sell(float price, int quantity, float commision)
{
	balance += (price - commision)*quantity;
}
bool bank::save_bank(int id)
{
	ifstream file;
	ofstream temp;
	int file_id;
	string line;
	file.open("bank.csv", ios::in);
	if (!file.is_open())
	{
		temp.open("bank.csv", fstream::out);
		temp.close();
		file.open("bank.csv", ios::in);
	}
	temp.open("bank.temp", ios::out);
	while (file >> file_id)
	{
		if (id == file_id)
		{
			temp << id << ',' << bank_name << ',' << balance << endl;
			getline(file, line, '\0');
			temp << line;
			file.close();
			temp.close();
			remove("bank.csv");
			rename("bank.temp", "bank.csv");
			return true;
		}
		else
		{
			getline(file, line);
			temp << file_id << line << endl;
		}
	}
	temp << id << ',' << bank_name << ',' << balance;
	file.close();
	temp.close();
	remove("bank.csv");
	rename("bank.temp", "bank.csv");
	return true;
}
bool bank::load_bank(int id)
{
	ifstream file;
	int file_id;
	string line;
	file.open("bank.csv", ios::in);
	if (!file.is_open())
	{
		throw "Bank File not found";
		return false;
	}
	while (file >> file_id)
	{
		if (id == file_id)
		{
			file.ignore();
			getline(file, bank_name, ',');
			file.ignore();
			file >> balance;
			file.close();
			return true;
		}
		else
			file.ignore(100,'\n');
	}
	throw "id not found";
	file.close();
	return false;
}