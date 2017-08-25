#include "trade.h"

trade::trade()
{
	Commission = (float)0.05;
	broker_Commission = 0.25;
}

bool trade::load(ifstream *file)
{
	getline(*file, stock_id, ',');
	*file >> price;
	if (file->eof())
		return false;
	file->ignore();
	*file >> quantity;
	file->ignore();
	*file >> id;
	file->ignore();
	return true;
}
void trade::save(ofstream *file)
{
	*file << stock_id << ',' << price << ',' << quantity << ',' << id << endl;
}

void trade::setCommission(float Commission)
{
	this->Commission = Commission;
}
void trade::setbroker_Commission(float broker_Commission)
{
	this->broker_Commission = broker_Commission;
}

float trade::getCommission()
{
	return Commission;
}
float trade::getbroker_Commission()
{
	return broker_Commission;
}

bool trade::offer_buy()
{
	Portfilo p;
	bank b;
	Notification n;
	ostringstream note;
	if (p.getstock_price(stock_id) < price)
	{
		throw "Wrong price";
		return false;
	}
	b.load_bank(id);
	if (b.getbalance() < (price + Commission + broker_Commission)*quantity)
	{
		throw "no enough credit";
		return false;
	}
	note << "your broker offers buying " << quantity << " of your stock " << stock_id << " with " << (price + Commission + broker_Commission)*quantity << " $" << endl;
	n.create_Notification(id, note.str());
	return true;
}
bool trade::offer_sell()
{
	Portfilo p;
	Notification n;
	ostringstream note;
	p.search_portfilo(id);
	if (p.getquantity(id, stock_id) < quantity)
	{
		throw "Not much stock quantity";
		return false;
	}
	note << "your broker offers selling " << quantity << " of your stock " << stock_id << " with " << (price + Commission + broker_Commission)*quantity << " $" << endl;
	n.create_Notification(id, note.str());
	return true;
}

bool trade::buy()
{
	Portfilo p;
	bank b;
	if (p.getstock_price(stock_id) < price)
	{
		throw "Wrong price";
		return false;
	}
	b.load_bank(id);
	if (b.getbalance() < (price + Commission + broker_Commission)*quantity)
	{
		throw "no enough credit";
		return false;
	}
	b.buy(price, quantity, broker_Commission + Commission);
	b.save_bank(id);
	save_market_buy();
	return true;
}
bool trade::sell()
{
	Portfilo p;
	bank b;
	p.search_portfilo(id);
	b.load_bank(id);
	if (p.getquantity(id, stock_id) < quantity)
	{
		throw "Not much stock quantity";
		return false;
	}
	b.sell(price, quantity, broker_Commission + Commission);
	b.save_bank(id);
	save_market_sell();
	return true;
}

bool trade::save_market_buy()
{
	ifstream file;
	ofstream temp;
	string file_stock, line;
	float file_price;
	file.open("stock_market_buy.csv", ios::in);
	if (!file.is_open())
	{
		temp.open("stock_market_buy.csv", ios::out);
		temp.close();
		file.open("stock_market_buy.csv", ios::in);
	}
	temp.open("stock_market_buy.temp", ios::out);
	while (getline(file, file_stock, ',') && !file.eof())
	{
		while (file_stock == stock_id)
		{
			file >> file_price;
			if (file_price <= price)
			{
				getline(file, line);
				temp << file_stock << ',' << file_price << line << endl;
			}
			else if (file_price > price)
			{
				getline(file, line, '\0');
				temp << stock_id << ',' << price << ',' << quantity << ',' << id << endl << file_stock << ',' << file_price << line;
				file.close();
				temp.close();
				remove("stock_market_buy.csv");
				rename("stock_market_buy.temp", "stock_market_buy.csv");
				return true;
			}
			file_stock = "";
			getline(file, file_stock, ',');
			if (file_stock != stock_id)
			{
				getline(file, line, '\0');
				temp << stock_id << ',' << price << ',' << quantity << ',' << id << endl << file_stock << ',' << line;
				file.close();
				temp.close();
				remove("stock_market_buy.csv");
				rename("stock_market_buy.temp", "stock_market_buy.csv");
				return true;
			}
		}
		getline(file, line);
		temp << file_stock << ',' << line << endl;
	}
	temp << stock_id << ',' << price << ',' << quantity << ',' << id;
	file.close();
	temp.close();
	remove("stock_market_buy.csv");
	rename("stock_market_buy.temp", "stock_market_buy.csv");
	return true;
}
bool trade::save_market_sell()
{
	ifstream file;
	ofstream temp;
	string file_stock, line;
	float file_price;
	file.open("stock_market_sell.csv", ios::in);
	if (!file.is_open())
	{
		temp.open("stock_market_sell.csv", ios::out);
		temp.close();
		file.open("stock_market_sell.csv", ios::in);
	}
	temp.open("stock_market_sell.temp", ios::out);
	while (getline(file, file_stock, ',') && !file.eof())
	{
		while (file_stock == stock_id)
		{
			file >> file_price;
			if (file_price >= price)
			{
				getline(file, line);
				temp << file_stock << ',' << file_price << line << endl;
			}
			else if (file_price < price)
			{
				getline(file, line, '\0');
				temp << stock_id << ',' << price << ',' << quantity << ',' << id << endl << file_stock << ',' << file_price << line;
				file.close();
				temp.close();
				remove("stock_market_sell.csv");
				rename("stock_market_sell.temp", "stock_market_buy.csv");
				return true;
			}
			file_stock = "";
			getline(file, file_stock, ',');
			if (file_stock != stock_id)
			{
				getline(file, line, '\0');
				temp << stock_id << ',' << price << ',' << quantity << ',' << id << endl << file_stock << ',' << line;
				file.close();
				temp.close();
				remove("stock_market_buy.csv");
				rename("stock_market_buy.temp", "stock_market_buy.csv");
				return true;
			}
		}
		getline(file, line);
		temp << file_stock << ',' << line << endl;
	}
	temp << stock_id << ',' << price << ',' << quantity << ',' << id;
	file.close();
	temp.close();
	remove("stock_market_sell.csv");
	rename("stock_market_sell.temp", "stock_market_sell.csv");
	return true;
}

bool trade::delete_market_buy(string stock, int count)
{
	ifstream file;
	ofstream temp;
	string file_stock, line;
	file.open("stock_market_buy.csv", ios::in);
	if (!file.is_open())
	{
		throw"market file not found";
		return false;
	}
	temp.open("stock_market_buy.temp", ios::out);
	while (getline(file, file_stock, ',') && !file.eof())
	{
		if (file_stock == stock)
		{
			for (int i = 0; i < count; i++)
				file.ignore(200, '\n');
			getline(file, line, '\0');
			temp << line;
			file.close();
			temp.close();
			remove("stock_market_buy.csv");
			rename("stock_market_buy.temp", "stock_market_buy.csv");
			return true;
		}
		getline(file, line);
		temp << file_stock << ',' << line << endl;
	}
	throw"stock not found";
	file.close();
	temp.close();
	remove("stock_market_sell.temp");
	return false;
}
bool trade::delete_market_sell(string stock, int count)
{
	ifstream file;
	ofstream temp;
	string file_stock, line;
	file.open("stock_market_sell.csv", ios::in);
	if (!file.is_open())
	{
		throw"market file not found";
		return false;
	}
	temp.open("stock_market_sell.temp", ios::out);
	while (getline(file, file_stock, ',') && !file.eof())
	{
		if (file_stock == stock)
		{
			for (int i = 0; i < count; i++)
				file.ignore(200, '\n');
			getline(file, line, '\0');
			temp << line;
			file.close();
			temp.close();
			remove("stock_market_sell.csv");
			rename("stock_market_sell.temp", "stock_market_sell.csv");
			return true;
		}
		getline(file, line);
		temp << file_stock << ',' << line << endl;
	}
	throw"stock not found";
	file.close();
	temp.close();
	remove("stock_market_sell.temp");
	return false;
}

bool trade::update_market_buy()
{
	ifstream file;
	ofstream temp;
	string stock_id, line;
	float price;
	int id, quantity;
	file.open("stock_market_buy.csv", ios::in);
	if (!file.is_open())
	{
		throw "market not found";
		return false;
	}
	temp.open("stock_market_buy.temp", ios::out);
	while (getline(file, stock_id, ',') && !file.eof())
	{
		while (this->stock_id == stock_id)
		{
			file >> price;
			file.ignore();
			file >> quantity;
			file.ignore();
			file >> id;
			file.ignore();
			if (this->price == price && this->id == id)
			{
				getline(file, line, '\0');
				temp << this->stock_id << ',' << this->price << ',' << this->quantity << ',' << id << line;
				file.close();
				temp.close();
				remove("stock_market_buy.csv");
				rename("stock_market_buy.temp", "stock_market_buy.csv");
				return true;
			}
			temp << stock_id << ',' << price << ',' << quantity << ',' << id << endl;
			getline(file, stock_id, ',');
			if (this->stock_id != stock_id)
			{
				file.close();
				temp.close();
				remove("stock_market_buy.temp");
				throw"order not found";
				return false;
			}
		}
		getline(file, line);
		temp << stock_id << ',' << line << endl;
	}
	file.close();
	temp.close();
	remove("stock_market_buy.temp");
	return false;
}
bool trade::update_market_sell()
{
	ifstream file;
	ofstream temp;
	string stock_id, line;
	float price;
	int id, quantity;
	file.open("stock_market_sell.csv", ios::in);
	if (!file.is_open())
	{
		throw "market not found";
		return false;
	}
	temp.open("stock_market_sell.temp", ios::out);
	while (getline(file, stock_id, ',') && !file.eof())
	{
		while (this->stock_id == stock_id)
		{
			file >> price;
			file.ignore();
			file >> quantity;
			file.ignore();
			file >> id;
			file.ignore();
			if (this->price == price && this->id == id)
			{
				getline(file, line, '\0');
				temp << stock_id << ',' << price << ',' << this->quantity << ',' << id << line;
				file.close();
				temp.close();
				remove("stock_market_sell.csv");
				rename("stock_market_sell.temp", "stock_market_sell.csv");
				return true;
			}
			temp << stock_id << ',' << price << ',' << quantity << ',' << id << endl;
			getline(file, stock_id, ',');
			if (this->stock_id != stock_id)
			{
				file.close();
				temp.close();
				remove("stock_market_sell.temp");
				throw"order not found";
				return false;
			}
		}
		getline(file, line);
		temp << stock_id << ',' << line << endl;
	}
	file.close();
	temp.close();
	remove("stock_market_sell.temp");
	return false;
}