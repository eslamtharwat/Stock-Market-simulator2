#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include "person.h"
#include "password.h"
#include "Notification.h"
#include "bank.h"
#include <cctype>
#include "portfilo.h"
#include "trade.h"
#include "stateofaccount.h"
using namespace std;
void credit()
{
	system("CLS");
	cout << "\t\t\tStock Market Simulator Project FCIH\n\n\t\t\t Many Thanks To Dr.Ayman Ezzat \n\n\n\t\t Team Leader :   Tarek El-Shahawy\n\n\t\t members     :   Nader Alaa El-Din\n\t\t\t\t Ahmed Ali\n\t\t\t\t Eslam Therwat\n\t\t\t\t Ahmed El Saeed\n\t\t\t\t Mohamed Tarek\n\t\t\t\t Osama Mersal\n\n\n\n";
	system("pause");
}
int main()
{
	int userid;
	string password;
	Person p;
	Notification N;
	stateofaccount u;
	bank b;
	Portfilo f;
	trade t;
	int num;
	float cash;
	string line, line2;
	char choice;
	///////////////////////////////////////////////////////////////////////////
first:
	system("CLS");
	cout << " _____________________________________________________________________________" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                 Welcome in Stock Market Simulator Project                   |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                                [C] credit                                   |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                                1 - Login                                    |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                                2 - Sign up                                  |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                                3 - Exit                                     |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|_____________________________________________________________________________|" << endl;
	choice = getch();
	choice = tolower(choice);
	switch (choice)
	{
	case '1':
	{
	login:
		system("CLS");
		cout << endl << endl << "                               ---login---      [0] to return\n";
		cout << "                       User ID : ";
		cin >> userid;
		cin.ignore();
		if (userid == 0)
			goto first;
		cout << "                       Password  : ";
		try
		{
			password = getpassword();
			p.search_person(userid);
			if (p.getpass() != password)
				throw"wrong password or ID";
		}
		catch (const char *error)
		{
			cout << endl << "                 \a!!ERROR!!" << endl << "                       " << error << endl;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
			}
			_sleep(2000);
			goto login;
		}
		break;
	}
		//////////////////////////////////////////////////////////////////////////////////////
	case '2':
	{
	registeration:
		system("CLS");
		cout << endl << endl << "                               ---sign up---      [0] to return\n";
		cout << "                       Full Name : ";
		getline(cin, line);
		if (line == "0")
		{
			goto first;
		}
		p.setname(line);
		cout << "                           Email : ";
		getline(cin, line);
		p.setemail(line);
	pas:
		cout << "                        Password : ";
		line = getpassword();
		cout << endl << "               Re Enter Password : ";
		line2 = getpassword();
		if (line == line2)
			p.setpass(line);
		else
		{
			cout << endl << "\a               Not Match" << endl;
			_sleep(2000);
			goto pas;
		}
	gender:
		cout << endl << "                          gender :  [1] Male   [2] Female";
		num = getch();
		if (num == '1')
			p.setgender("male");
		else if (num == '2')
			p.setgender("female");
		else
		{
			cout << endl << "\aWrong input" << endl;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
			}
			_sleep(2000);
			goto gender;
		}
		cout << endl << "                     National ID : ";
		getline(cin, line);
		p.setNID(line);
		cout << "                    Bank Company : ";
		getline(cin, line);
		b.setbank_name(line);
		cout << "                   Mobile Number : ";
		getline(cin, line);
		p.setphone(line);
		p.settype("Client");
		/////////////////////////////////////////////////////////////////
		system("CLS");
		cout << " _____________________________________________________________________________" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|    Name : " << left << setw(30) << p.getname() << "  Mobile : " << setw(25) << p.getphone() << "|" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|    Gender : " << setw(6) << p.getgender() << "                        National ID : " << setw(20) << p.getNID() << "|" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|    Bank Company : " << setw(4) << setw(24) << b.getbank_name() << "TYPE : " << setw(6) << p.gettype() << "                     |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|_____________________________________________________________________________|" << endl;
	confirm:
		cout << "                  1 - Confirm            2 - Decline                           " << endl;
		choice = getch();
		if (choice == '2')
			goto registeration;
		else if (choice == '1')
		{
			p.create_person();
			p.save_person();
			b.save_bank(p.id);
			cout << endl << "Welcome !! " << p.getname() << endl << "your ID = ( " << p.id << " ) please Save it :D ";
			system("pause");
		}
		else
		{
			cout << endl << "\awrong input";
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
			}
			goto confirm;
		}
		break;
	}
	case '3':
		return 0;
	case 'c':
		credit();
	default:
		cout << "\a Wrong input";
		goto first;
	}
client_home:
	system("CLS");
	cout << " _____________________________________________________________________________" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                 Welcome ";
	if (p.getgender() == "male"){ cout << "MR. "; }
	else{ cout << "MISS. "; }
	cout << left << setw(48) << p.getname() << "|" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|     [L]  logout      [H]  Home      [T]  trade screen       [C] credit      |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                       1 - Notification[ " << setw(2) << N.Notification_Number(p.id) << "]                                 |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                       2 - Edit Your profile                                 |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                       3 - State of Account                                  |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                       4 - Portfilo                                          |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                       5 - Broker request                                    |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                       6 - Trade                                             |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                       7 - Bank Management                                   |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|_____________________________________________________________________________|" << endl;
	choice = getch();
	choice = tolower(choice);
	switch (choice)
	{
	case '1':
		try
		{
			system("CLS");
			vector<string> mynote;
			N.read_Notification(p.id);
			cout << endl << endl;
			for (int i = 0; i < mynote.size(); i++)
				cout << mynote[i] << endl;
			N.delete_Notification(p.id);
		}
		catch (const char* error)
		{
			cout << endl << "!!ERROR!!" << endl << error << endl;
		}
		system("pause");
		break;
		/********************************************************************************/
	case '2':
	Edit :
		b.load_bank(p.id);
		system("CLS");
		 cout << " _____________________________________________________________________________" << endl;
		 cout << "|                                                                             |" << endl;
		 cout << "|                 Welcome ";
		 if (p.getgender() == "male"){ cout << "MR. "; }
		 else{ cout << "MISS. "; }
		 cout << left << setw(48) << p.getname() << "|" << endl;
		 cout << "|                                                                             |" << endl;
		 cout << "|     [L]  logout      [H]  Home      [T]  trade screen       [C] credit      |" << endl;
		 cout << "|                                                                             |" << endl;
		 cout << "|                                                                             |" << endl;
		 cout << "|    Name : " << left << setw(30) << p.getname() << "  Mobile : " << setw(25) << p.getphone() << "|" << endl;
		 cout << "|                                                                             |" << endl;
		 cout << "|    Gender : " << setw(6) << p.getgender() << "                        National ID : " << setw(20) << p.getNID() << "|" << endl;
		 cout << "|                                                                             |" << endl;
		 cout << "|    Bank Company : " << setw(4) << setw(24) << b.getbank_name() << "TYPE : " << setw(6) << p.gettype() << "                     |" << endl;
		 cout << "|                                                                             |" << endl;
		 cout << "|_____________________________________________________________________________|" << endl;
		 cout << " Edit   1 - Name               2 - Email                   3 - Password        " << endl << endl;
		 cout << "        4 - National ID        5 - Bank Company            6 - Mobile          " << endl << endl;
		 choice = getch();
		 switch (choice)
		 {
		 case '1':
			 cout << "                 Enter your New Full Name : ";
			 getline(cin, line);
			 p.setname(line);
			 break;
			 /*--------------------------------------------------------*/
		 case  '2':
			 cout << "                 Enter your New Email : ";
			 getline(cin, line);
			 p.setemail(line);
			 break;
			 /*--------------------------------------------------------*/
		 case '3':
		 pass :
			 cout << "                  Enter your Old Password : ";
			  line = getpassword();
			  if (line != p.getpass())
			  {
				  cout << "\n\a                 Wrong Password";
				  goto pass;
			  }
		  rpas:
			  cout << endl << "                  Enter your New Password : ";
			  line = getpassword();
			  cout << endl << "               Re Enter your New Password : ";
			  line2 = getpassword();
			  if (line == line2)
				  p.setpass(line);
			  else
			  {
				  cout << endl << "\a               Not Match" << endl;
				  _sleep(2000);
				  goto rpas;
			  }
			  break;
			  /*--------------------------------------------------------*/
		 case '4':
			 cout << endl << "            Enter your New National ID : ";
			 getline(cin, line);
			 p.setNID(line);
			 break;
			 /*--------------------------------------------------------*/
		 case '5':
			 cout << "                Enter your New Bank Company : ";
			 getline(cin, line);
			 b.setbank_name(line);
			 b.save_bank(p.id);
			 break;
			 /*--------------------------------------------------------*/
		 case '6':
			 cout << "              Enter your New Mobile Number : ";
			 getline(cin, line);
			 p.setphone(line);
			 p.settype("Client");
			 break;
			 /*--------------------------------------------------------*/
		 case 'h':
			 goto client_home;
			 break;
		 case 'l':
			 goto first;
			 break;
		 case 't':
			 system("START Stocks_Screen");
			 break;
		 case 'c':
			 credit();
			 break;
			 /*--------------------------------------------------------*/
		 default:
			 cout << "\a                   wrong Input";
			 system("pause");
			 break;
		 }
		 p.update_person(p.id);
		 goto Edit;
		 /********************************************************************************/
	case '3':
		system("CLS");
		try
		{
			vector<string> state = u.read_state(p.id);
			for (unsigned int i = 0; i < state.size(); i++)
				cout << state[i] << endl;
		}
		catch (const char* error)
		{
			cout << error;
		}
		system("pause");
		break;
		/********************************************************************************/
	case '4':
		system("CLS");
		try
		{
			vector<Portfilo> portfil = f.search_portfilo(p.id);

			cout << left << setw(15) << "Stock Name" << setw(15) << "Quantity" << setw(15) << "price" << setw(15) << "total cost" << endl;
			cout << "------------------------------------------------------------------" << endl;
			for (unsigned int i = 0; i < portfil.size(); i++)
				cout << left << "   " << setw(15) << portfil[i].getstock_name() << setw(15) << portfil[i].getquantity() << setw(15) << portfil[i].getstock_price() << setw(15) << portfil[i].stock_total_cost() << endl;
		}
		catch (const char* error)
		{
			cout << error;
		}
		system("pause");
		break;
		/********************************************************************************/
	case '5':
		system("CLS");
		break;
		/********************************************************************************/
	case '6':
		trd:
		system("CLS");
		cout << " _____________________________________________________________________________" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                 Welcome ";
		if (p.getgender() == "male"){ cout << "MR. "; }
		else{ cout << "MISS. "; }
		cout << left << setw(48) << p.getname() << "|" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|     [L]  logout      [H]  Home      [T]  trade screen       [C] credit      |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                1 - buy                                      |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                2 - Sell                                     |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|_____________________________________________________________________________|" << endl;
		choice = getch();
		switch (choice)
		{
		case '1':
			system("CLS");
			try
			{
				cout << endl << endl << "                               ---buy---      [0] to return\n";
				cout << endl << "                  Commission = " << t.getCommission() << "     Broker Commission = " << t.getbroker_Commission() << endl << endl;
				cout << endl << "                Enter Stock ID : ";
				cin >> t.stock_id;
				if (t.stock_id == "0")
					goto trd;
				cout << endl << "                Enter Stock Price : ";
				cin >> t.price;
				cout << endl << "                Enter Stock Quantity : ";
				cin >> t.quantity;
				t.id = p.id;
				t.buy();
			}
			catch (const char* error)
			{
				cout <<endl<<"\a!!ERROR!!" <<endl<<error;
				system("pause");
				goto trd;
			}
		case '2':
			system("CLS");
			try
			{
				cout << endl << endl << "                               ---Sell---      [0] to return\n";
				cout << endl << "                  Commission = " << t.getCommission() << "     Broker Commission = " << t.getbroker_Commission() << endl << endl;
				cout << endl << "                Enter Stock ID : ";
				cin >> t.stock_id;
				if (t.stock_id == "0")
					goto trd;
				cout << endl << "                Enter Stock Price : ";
				cin >> t.price;
				cout << endl << "                Enter Stock Quantity : ";
				cin >> t.quantity;
				t.id = p.id;
				t.sell();
			}
			catch (const char* error)
			{
				cout << endl << "\a!!ERROR!!" << endl << error;
				system("pause");
				goto trd;
			}
		case 'h':
			goto client_home;
			break;
		case 'l':
			goto first;
			break;
		case 't':
			system("START Stocks_Screen");
			break;
		case 'c':
			credit();
			break;
		default:
			cout << "\a                   wrong Input";
			system("pause");
			break;
		}
		goto trd;
		break;
		/********************************************************************************/
	case '7':
	bnk :
		system("CLS");
		cout << " _____________________________________________________________________________" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                            "<<setw(50)<<left<<b.getbank_name()<<"|" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                 Welcome ";
		if (p.getgender() == "male"){ cout << "MR. "; }
		else{ cout << "MISS. "; }
		cout << left << setw(48) << p.getname() << "|" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|     [L]  logout      [H]  Home      [T]  trade screen       [C] credit      |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                 your balance = "<<left<<fixed<<setprecision(2)<<setw(10)<<b.getbalance()<<"                                   |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                1 - Deposit                                  |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                2 - Withdraw                                 |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|                                                                             |" << endl;
		cout << "|_____________________________________________________________________________|" << endl;
		choice = getch();
		switch (choice)
		{
		case '1':
			system("CLS");
			cout << endl << endl << "                             ---Deposit---      [0] to return\n";
			cout << endl << "                      Enter Cash : ";
			cin >> cash;
			try
			{
				b.deposit(cash);
				b.save_bank(p.id);
			}
			catch (const char* error)
			{
				cout << endl << "\a!!ERROR!!" << endl << error;
				system("pause");
				goto bnk;
			}
			break;
		case '2':
			system("CLS");
			cout << endl << endl << "                             ---Withdraw---      [0] to return\n";
			cout << endl << "                      Enter Cash : ";
			cin >> cash;
			try
			{
				b.deposit(cash);
				b.save_bank(p.id);
			}
			catch (const char* error)
			{
				cout << endl << "\a!!ERROR!!" << endl << error;
				system("pause");
				goto bnk;
			}
			break;
		case 'h':
			goto client_home;
			break;
		case 'l':
			goto first;
			break;
		case 't':
			system("START Stocks_Screen");
			break;
		case 'c':
			credit();
			break;
		default:
			cout << "\a                   wrong Input";
			system("pause");
			break;
		}
		break;
		/********************************************************************************/
	case 'h':
		goto client_home;
		break;
	case 'l':
		goto first;
		break;
	case 't':
		system("START Stocks_Screen");
		break;
	case 'c':
		credit();
		break;
		/********************************************************************************/
	default:
		cout << "\a                   wrong Input";
		system("pause");
		break;
	}
	goto client_home;
}
