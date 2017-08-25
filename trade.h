#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include "portfilo.h"
#include "bank.h"
#include "Notification.h"
using namespace std;
class trade
{
private:
	float Commission;
	float broker_Commission;
public:
	
	string stock_id;
	float price;
	int quantity;
	int id;

	trade();

	bool load(ifstream*);
	void save(ofstream*);

	void setCommission(float);
	void setbroker_Commission(float);
	
	float getCommission();
	float getbroker_Commission();

	bool offer_buy();
	bool offer_sell();

	bool buy();
	bool sell();

	bool save_market_buy();
	bool save_market_sell();
	
	bool delete_market_buy(string, int);
	bool delete_market_sell(string, int);
	
	bool update_market_buy();
	bool update_market_sell();
};