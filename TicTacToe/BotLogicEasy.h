#pragma once
#include "BotLogic.h"

class BotLogicEasy
	:public BotLogic
{
private:

public:
	BotLogicEasy(int* SquareState);
	int move();
};

