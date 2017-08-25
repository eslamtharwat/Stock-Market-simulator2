#include "stateofaccount.h"

bool stateofaccount::create_state(int id, string note)
{
	ifstream file;
	ofstream temp;
	int file_id, not;
	string line;
	file.open("history.txt", ios::in);
	if (!file.is_open())
	{
		temp.open("history.txt", ios::out);
		temp.close();
		file.open("history.txt", ios::in);
	}
	temp.open("history.temp", ios::out);
	while (file >> file_id)
	{
		if (file_id == id)
		{
			file.ignore();
			temp << id << endl;
			file >> not;
			temp << not << endl;
			for (int i = 0; i < not; i++)
			{
				getline(file, line);
				temp << line << endl;
			}
			time(&t);
			localtime_s(now, &t);
			temp << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday << " " << now->tm_hour << ":" << now->tm_min << "  " << line;
			getline(file, line, '\0');
			temp << line;
			file.close();
			temp.close();
			remove("history.txt");
			rename("history.temp", "history.txt");
			return true;
		}
		else
		{
			getline(file, line, '*');
			file.ignore(100, '\n');
			temp << line << "******************************************" << endl;
		}
	}
	temp << id << endl << 1 << endl << "1 - " << note << endl << "******************************************";
	file.close();
	temp.close();
	remove("history.txt");
	rename("history.temp", "history.txt");
	return true;
}
vector<string> stateofaccount::read_state(int id)

{
	ifstream file;
	file.open("history.txt", ios::in);
	int file_id, not;
	string line;
	vector<string> linevec;
	if (!file.is_open())
	{
		throw"history file not found";
	}
	else
	{
		while (file >> file_id)
		{
			if (file_id == id)
			{
				file.ignore();
				file >> not;
				for (int i = 0; i < not; i++)
				{
					getline(file, line);
					linevec.push_back(line);
				}
				file.close();
				return linevec;
			}
			else
			{
				file.ignore(2000, '*');
				file.ignore(100, '\n');
			}
		}
		file.close();
		throw "id Not Found";
	}
}