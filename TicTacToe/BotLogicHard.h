#pragma once
#include "BotLogic.h"
class BotLogicHard :
    public BotLogic
{
private:

public:
	BotLogicHard(int* SquareState);
	int move();
};

