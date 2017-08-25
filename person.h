#pragma once
#include <string>
#include <fstream>
using namespace std;
class Person
{
protected:
	string gender;
	string NID;
	string name;
	string pass;
	string phone;
	string email;
	string type;

public:
	int  id;

	Person();

	void setgender(string);
	void setNID(string);
	void setname(string);
	void setpass(string);
	void setphone(string);
	void setemail(string);
	void settype(string);

	string getgender();
	string getNID();
	string getname();
	string getpass();
	string getphone();
	string getemail();
	string gettype();

	void create_person();
	void save_person();
	bool search_person(int);
	bool delete_person(int);
	bool update_person(int);
};