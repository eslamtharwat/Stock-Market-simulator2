#include "password.h"
string getpassword()
{
	string result;

	char c;
	while ((c=getch()) && (c != '\r') && (c != '\n'))
	{
		if (c == '\b')
		{
			if (result.length())
			{
				cout <<"\b \b";
				result.erase(result.end() - 1);
			}
		}
		else
		{
			cout <<"*";
			result.push_back(c);
		}
	}
	return result;
}
string hidepassword(string password)
{
	ostringstream convert;
	int num;
	for (int i = 0; i < password.length(); ++i)
	{
		num = password[i];
		convert << num;
	}
	return convert.str();
}
string showpassword(string ascii)
{
	ostringstream convert;
	int num,c=0;
	string password;
	for (int i = 0; i < ascii.length();)
	{
		convert.str("");
		if (ascii.substr(i, 1) == "1")
		{
			convert << ascii.substr(i, 3);
			i += 3;
		}
		else
		{
			convert << ascii.substr(i, 2);
			i += 2;
		}
		istringstream convert_Text(convert.str());
		convert_Text >> num;
		password.push_back(num);
		c++;
	}
	return password;
}