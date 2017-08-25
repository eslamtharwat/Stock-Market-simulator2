/*
#include "admin.h"
bool Person::delete_person(int id)
{
	ifstream file;
	ofstream temp;
	int file_id;
	string line;
	file.open("user.csv", ios::in);
	temp.open("user.temp", ios::out);
	while (file >> file_id)
	{
		if (id == file_id)
		{
			file.ignore(300, '\n');
			getline(file, line, '\0');
			temp << line;
			file.close();
			temp.close();
			return true;
		}
		else
		{
			getline(file, line);
			temp << file_id << line << endl;
		}
	}
	throw "User not found";
	file.close();
	temp.close();
	return false;
}
bool Person::update_person(int id)
{
	ifstream file;
	ofstream temp;
	int file_id;
	string line;
	file.open("user.csv", ios::in);
	temp.open("user.temp", ios::out);
	while (file >> file_id)
	{
		if (id == file_id)
		{
			file.ignore(300, '\n');
			temp << id << ',' << pass << ',' << type << ',' << name << ',' << NID << ',' << email << ',' << phone << ',' << gender << endl;
			getline(file, line, '\0');
			temp << line;
			file.close();
			temp.close();
			return true;
		}
		else
		{
			getline(file, line);
			temp << file_id << line << endl;
		}
	}
	throw "User not found";
	file.close();
	temp.close();
	return false;
}
*/