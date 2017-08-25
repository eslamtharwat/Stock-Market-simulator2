#pragma once
#include <string>
#include <fstream>
using namespace std;
class Stocks
{
private:
	string company_name;
protected:
	string stock_id;
	float price;
	float close_price;
public:
	void setprice(float);
	void setclose_price(float);

	string getcompany_name();
	float getprice();
	float getclose_price();
	string getstock_id();
	void load_stock(ifstream*);

	bool search_stock(string);
	bool save_price(string,float);
	bool save_close(string);
};