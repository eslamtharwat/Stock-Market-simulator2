#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "trade.h"
#include "bank.h"
#include "portfilo.h"
#include "stocks.h"
#include "Notification.h"
#include "stateofaccount.h"
using namespace std;
void update_buying(trade t)
{
	try
	{
		Portfilo p;
		bank k;
		ostringstream note;
		Notification n;
		stateofaccount s;
		k.load_bank(t.id);
		p.save_portfilo(t.id, t.quantity, t.stock_id);
		k.buy(t.price, t.quantity, t.getCommission() + t.getbroker_Commission());
		note << "your bought " << t.quantity << " stock of " << t.stock_id << " with " << (t.price + t.getCommission() + t.getbroker_Commission())*t.quantity << " $ your balance = " << k.getbalance() << " $.";
		k.save_bank(t.id);
		s.create_state(t.id, note.str());
		n.create_Notification(t.id, note.str());
	}
	catch (const char *error)
	{
		cerr << "\a!!ERROR!!" << endl << error << endl;
	}
}
void update_selling(trade t)
{
	try
	{
		Portfilo p;
		bank k;
		ostringstream note;
		Notification n;
		stateofaccount s;
		k.load_bank(t.id);
		p.save_portfilo(t.id, t.quantity, t.stock_id);
		k.sell(t.price, t.quantity, t.getCommission() + t.getbroker_Commission());
		note << "your sold " << t.quantity << " stock of " << t.stock_id << " for " << (t.price - t.getCommission() - t.getbroker_Commission())*t.quantity << " $ your balance = " << k.getbalance() << " $.";
		k.save_bank(t.id);
		s.create_state(t.id, note.str());
		n.create_Notification(t.id, note.str());
	}
	catch (const char *error)
	{
		cerr << "\a!!ERROR!!" << endl << error << endl;
	}
}
int marketmain()
{
	trade b,s;
	Stocks sto;
	string stock_id, line_stocks, line_buy, line_sell;
	int buy_count, sell_count;
	ifstream file_sell, file_buy, file_stocks;
	file_stocks.open("stocks.csv", ios::in);
	while (!file_stocks.eof())
	{
	change:
		file_buy.close();
		file_sell.close();
		file_sell.open("stock_market_sell.csv", ios::in);
		file_buy.open("stock_market_buy.csv", ios::in);
		file_stocks.ignore(100,',');
		getline(file_stocks, stock_id, ',');
		file_stocks.ignore(100, '\n');
		while (b.load(&file_buy))
		{
			if (b.stock_id == stock_id)
			{
				while (s.load(&file_sell))
				{
					if (s.stock_id == stock_id)
					{
						if (b.price == s.price)
						{
							sto.save_price(s.stock_id, s.price);
						match:
							if (b.quantity > s.quantity)
							{
								b.quantity -= s.quantity;
								sell_count++;
								update_selling(s);
								s.load(&file_sell);
								if (s.stock_id == stock_id && b.price == s.price)
									goto match;
								else
								{
									update_buying(b);
									b.update_market_buy();
								}
							}
							else if (b.quantity < s.quantity)
							{
								s.quantity -= b.quantity;
								buy_count++;
								update_buying(b);
								s.load(&file_sell);
								if (b.stock_id == stock_id && b.price == s.price)
									goto match;
								else
								{
									update_selling(s);
									s.update_market_sell();
								}
							}
							else
							{
								sell_count++;
								buy_count++;
								update_buying(b);
								update_selling(s);
								s.load(&file_sell);
								b.load(&file_buy);
								if (b.stock_id == stock_id && s.stock_id == stock_id && b.price == s.price)
									goto match;
							}
							b.delete_market_buy(b.stock_id,buy_count);
							s.delete_market_sell(s.stock_id, sell_count);
						}
						goto change;
					}
				}
				goto change;
			}
		}
		goto change;
	}
	return 0;
}