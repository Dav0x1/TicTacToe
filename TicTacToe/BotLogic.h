#pragma once
#include <ctime>
#include <cstdlib>
#include <vector>

class BotLogic
{
protected:
	//1 - player, 2 - bot , 0 - empty
	int* squareState;
public:
	BotLogic(int* SquareState);
	~BotLogic();
	virtual int move();
};