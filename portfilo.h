#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "stocks.h"
using namespace std;

class Portfilo
{
private:
	string stock_name;
	int quantity;
	float stock_price;
public:
	float stock_total_cost();
	string getstock_name();
	int getquantity();
	int getquantity(int, string);
	float getstock_price();
	float getstock_price(string);

	void load_portfilo(ifstream*, string*, int*);
	bool save_portfilo(int, int, string);
	vector<Portfilo> search_portfilo(int);
};