#pragma once
#include "person.h"
#include "trade.h"
#include <string>
#include <sstream>
class client:public Person
{
public:
	/*void showoallffers(int,string,float, int);*/
	bool setbuyoffer(trade r);
	bool setselloffer(trade r);
	/*void approveoffer();*/
};