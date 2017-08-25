#include "client.h"

/*void showalloffers(int, string, float, int)
{

}*/
bool setbuyoffer(trade r)
{
	ifstream file;
	ofstream temp;
	string line;
	int file_id;
	file.open("offers.csv", ios::in);
	if (!file.is_open())
	{
		temp.open("offers.csv", ios::out);
		temp.close();
		file.open("offers.csv", ios::in);
	}
	temp.open("offer_buy.temp", ios::out);
	while (file >> file_id)
	{
		if (file_id == r.id)
		{
			getline(file, line);
			temp << file_id << line << endl << r.id << ',' << "buy" << ',' << r.stock_id << ',' << r.price << ',' << r.quantity;
			getline(file, line, '\0');
			temp << line;
			file.close();
			temp.close();
			remove("offers.csv");
			rename("offers.temp", "offers.csv");
			return true;
		}
		getline(file, line);
		temp << file_id << line << endl;
	}
	temp << r.id << ',' << "buy" << ',' << r.stock_id << ',' << r.price << ',' << r.quantity;
	file.close();
	temp.close();
	remove("offers.csv");
	rename("offers.temp", "offers.csv");
	return true;
}
bool setselloffer(trade r)
{
	ifstream file;
	ofstream temp;
	string line;
	int file_id;
	file.open("offers.csv", ios::in);
	if (!file.is_open())
	{
		temp.open("offers.csv", ios::out);
		temp.close();
		file.open("offers.csv", ios::in);
	}
	temp.open("offers.temp", ios::out);
	while (file >> file_id)
	{
		if (file_id == r.id)
		{
			getline(file, line);
			temp << file_id << line << endl << r.id << ',' << "sell" << ',' << r.stock_id << ',' << r.price << ',' << r.quantity;
			getline(file, line, '\0');
			temp << line;
			file.close();
			temp.close();
			remove("offers.csv");
			rename("offers.temp", "offers.csv");
			return true;
		}
		getline(file, line);
		temp << file_id << line << endl;
	}
	temp << r.id << ',' << "sell" << ',' << r.stock_id << ',' << r.price << ',' << r.quantity;
	file.close();
	temp.close();
	remove("offers.csv");
	rename("offers.temp", "offers.csv");
	return true;
}
/*void approveoffer()
{

}*/