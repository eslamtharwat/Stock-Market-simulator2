#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "portfilo.h"
#include <vector>
#include <iomanip>
int Portfilomain()
{
	int id;
	Portfilo p;
	cout << "Enter ID" << endl;
	cin >> id;
	try
	{
		vector<Portfilo> portfil = p.search_portfilo(id);

		cout << left <<setw(15) << "Stock Name" << setw(15) << "Quantity" << setw(15) << "price" << setw(15) << "total cost" << endl;
		cout << "------------------------------------------------------------------" << endl;
		for (unsigned int i = 0; i < portfil.size(); i++)
			cout << left <<"   "<<setw(15) << portfil[i].getstock_name() << setw(15) << portfil[i].getquantity() << setw(15) << portfil[i].getstock_price() << setw(15) << portfil[i].stock_total_cost() << endl;
	}
	catch (const char* error)
	{
		cout << error;
	}
	return 0;
}