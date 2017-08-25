#include "portfilo.h"

float Portfilo::stock_total_cost()
{
	return quantity*stock_price;
}
string Portfilo::getstock_name()
{
	return stock_name;
}
int Portfilo::getquantity()
{
	return quantity;
}
int Portfilo::getquantity(int id, string stock_name)
{
	ifstream file;
	string line;
	int check_id, num;
	file.open("portfilo.txt", ios::in);
	if (!file.is_open())
		throw "File not found";
	while (file >> check_id)
	{
		file.ignore();
		if (check_id == id)
		{
			file >> num;
			file.ignore();
			for (int i = 1; i <= num; i++)
			{
				getline(file, this->stock_name, ',');
				if (this->stock_name == stock_name)
				{
					file >> quantity;
					file.close();
					return quantity;
				}
				file.close();
				throw "stock Not found";
			}
		}
		else
		{
			getline(file, line, '*');
			file.ignore(100, '\n');
		}
	}
	file.close();
	throw "id Not found";
}
float Portfilo::getstock_price()
{
	return stock_price;
}
float Portfilo::getstock_price(string stock_name)
{
	Stocks stocks;
	stocks.search_stock(stock_name);
	stock_price = stocks.getprice();
	return stock_price;
}
void Portfilo::load_portfilo(ifstream *file, string *stock_name, int *quantity)
{
	if (!file->is_open())
		throw "File Not open for load !!";
	getline(*file, *stock_name, ',');
	*file >> *quantity;
	file->ignore();
}
bool Portfilo::save_portfilo(int id, int quantity, string stock_name)
{
	int check_id, num;
	string line, check_stock;
	ifstream file;
	ofstream temp;
	file.open("portfilo.txt", ios::in);
	if (!file.is_open())
	{
		temp.open("portfilo.txt", ios::out);
		temp.close();
		file.open("portfilo.txt", ios::in);
	}
	temp.open("portfilo.temp", ios::in);
	while (file >> check_id)
	{
		file.ignore();
		temp << check_id << endl;
		if (check_id == id)
		{
			file >> num;
			file.ignore();
			temp << num + 1 << endl;
			for (int i = 1; i <= num; i++)
			{
				getline(file, check_stock, ',');
				if (check_stock == stock_name)
				{
					if (quantity != 0)
						temp << stock_name << ',' << quantity << endl;
					getline(file, line, '\0');
					temp << line;
					file.close();
					temp.close();
					remove("portfilo.txt");
					rename("portfilo.temp", "portfilo.txt");
					return true;
				}
				else
				{
					getline(file, line);
					temp << check_stock << ',' << line << endl;
				}
			}
			temp << stock_name << ',' << quantity << endl << "********************";
			file.close();
			temp.close();
			remove("portfilo.txt");
			rename("portfilo.temp", "portfilo.txt");
			return true;
		}
		else
		{
			getline(file, line, '*');
			file.ignore(100, '\n');
			temp << line << endl << "********************";
		}
	}
	temp << id << endl << 1 << endl << stock_name << ',' << quantity << endl << "********************";
	file.close();
	temp.close();
	remove("portfilo.txt");
	rename("portfilo.temp", "portfilo.txt");
	return true;
}
vector<Portfilo> Portfilo::search_portfilo(int id)
{
	ifstream file;
	vector<Portfilo> portfil;
	Portfilo p;
	string line;
	int check_id, num;
	file.open("portfilo.txt", ios::in);
	if (!file.is_open())
		throw "File not found";
	while (file >> check_id)
	{
		file.ignore();
		if (check_id == id)
		{
			file >> num;
			file.ignore();
			for (int i = 1; i <= num; i++)
			{
				load_portfilo(&file, &p.stock_name, &p.quantity);
				p.stock_price = getstock_price(p.stock_name);
				portfil.push_back(p);
			}
			file.close();
			return portfil;
		}
		else
		{
			getline(file, line, '*');
			file.ignore(100, '\n');
		}
	}
	file.close();
	throw "id Not found";
}