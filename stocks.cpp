#include "stocks.h"

void Stocks::setprice(float price)
{
	this->price = price;
}
void Stocks::setclose_price(float close_price)
{
	this->close_price = close_price;
}

string Stocks::getcompany_name()
{
	return company_name;
}
float Stocks::getprice()
{
	return price;
}
float Stocks::getclose_price()
{
	return close_price;
}
string Stocks::getstock_id()
{
	return stock_id;
}
void Stocks::load_stock(ifstream* file)
{
	getline(*file, company_name, ',');
	getline(*file, stock_id, ',');
	*file >> price;
	file->ignore();
	*file >> close_price;
	file->ignore();
}
bool Stocks::search_stock(string stock_id)
{
	ifstream file;
	string name, id;
	file.open("Stocks.csv", ios::in);
	if (!file.is_open())
	{
		throw "Stock File Not Found";
		return false;
	}
	while (getline(file, name, ',') && getline(file, id, ',') && !file.eof())
	{
		if (id == stock_id)
		{
			company_name = name;
			this->stock_id = id;
			file >> price;
			file.ignore();
			file >> close_price;
			file.close();
			return true;
		}
		else
			file.ignore(200, '\n');
	}
	throw"Stock id not found";
	file.close();
	return false;
}
bool Stocks::save_price(string stock_id, float price)
{
	ifstream file;
	ofstream temp;
	string name, id, line;
	float close_price;
	file.open("Stocks.csv", ios::in);
	if (!file.is_open())
	{
		throw "Stock File Not Found";
		return false;
	}
	temp.open("Stocks.temp", ios::out);
	while (getline(file, name, ',') && getline(file, id, ',') && !file.eof())
	{
		temp << name << ',' << id << ',';
		if (id == stock_id)
		{
			file.ignore(100, ',');
			file >> close_price;
			file.ignore();
			temp << price << ',' << close_price << endl;
			getline(file, line, '\0');
			temp << line;
			file.close();
			temp.close();
			remove("stocks.txt");
			rename("stocks.temp", "stocks.txt");
			return true;
		}
		else
		{
			getline(file, line);
			temp << line << endl;
		}
	}
	throw"Stock id not found";
	file.close();
	temp.close();
	return false;

}
bool Stocks::save_close(string stock_id)
{
	ifstream file;
	ofstream temp;
	string name, id, line;
	float price;
	file.open("Stocks.csv", ios::in);
	if (!file.is_open())
	{
		throw "Stock File Not Found";
		return false;
	}
	temp.open("Stocks.temp", ios::out);
	while (getline(file, name, ',') && getline(file, id, ',') && !file.eof())
	{
		temp << name << ',' << id << ',';
		if (id == stock_id || stock_id == "all")
		{
			file >> price;
			file.ignore();
			file.ignore(100, '\n');
			temp << price << ',' << price << endl;
			getline(file, line, '\0');
			temp << line;
			if (stock_id != "all")
			{
				file.close();
				temp.close();
				return true;
			}
		}
		else
		{
			getline(file, line);
			temp << line << endl;
		}
	}
	file.close();
	temp.close();
	if (stock_id != "all")
	{
		throw"Stock id not found";
		return false;
	}
	else return true;
}