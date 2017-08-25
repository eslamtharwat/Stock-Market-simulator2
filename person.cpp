#include "person.h"
Person::Person()
{
	id = 20130000;
}

void Person::setgender(string gender)
{
	this->gender = gender;
}
void Person::setNID(string NID)
{
	this->NID = NID;
}
void Person::setname(string name)
{
	this->name = name;
}
void Person::setpass(string pass)
{
	this->pass = pass;
}
void Person::setphone(string phone)
{
	this->phone = phone;
}
void Person::setemail(string email)
{
	this->email = email;
}
void Person::settype(string type)
{
	this->type = type;
}

string Person::getgender()
{
	return gender;
}
string Person::getNID()
{
	return NID;
}
string Person::getname()
{
	return name;
}
string Person::getpass()
{
	return pass;
}
string Person::getphone()
{
	return phone;
}
string Person::getemail()
{
	return email;
}
string Person::gettype()
{
	return type;
}

void Person::create_person(){
	ifstream file;
	int id;
	file.open("user.csv", ios::in);
	if (!file.is_open())
	{
		id = this->id;
		throw "user File not Found";
	}
	else while (file >> id)
		file.ignore(200, '\n');
	file.close();
	this->id = id + 1;
}
void Person::save_person()
{
	ofstream file;
	file.open("user.csv", ios::out | ios::app);
	if (!file.is_open())
		throw "User File not Found";
	file <<endl<< id << ',' << pass << ',' << type << ',' << name << ',' << NID << ',' << email << ',' << phone << ',' << gender;
	file.close();
}
bool Person::search_person(int id)
{
	ifstream file;
	int file_id;
	file.open("user.csv", ios::in);
	if (!file.is_open())
	{
		throw "user file not found";
		return false;
	}
	while (file >> file_id)
	{
		if (id == file_id)
		{
			this->id = id;
			file.ignore();
			getline(file, pass, ',');
			getline(file, type, ',');
			getline(file, name, ',');
			getline(file, NID, ',');
			getline(file, email, ',');
			getline(file, phone, ',');
			getline(file, gender);
			file.close();
			return true;
		}
		else
			file.ignore(300, '\n');
	}
	throw "User not found";
	file.close();
	return false;
}
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
			remove("user.csv");
			rename("user.temp", "user.csv");
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
	remove("user.temp");
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
			remove("user.csv");
			rename("user.temp", "user.csv");
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
	remove("user.temp");
	return false;
}