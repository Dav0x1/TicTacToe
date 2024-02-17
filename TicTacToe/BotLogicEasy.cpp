#include "BotLogicEasy.h"

BotLogicEasy::BotLogicEasy(int* SquareState) 
	:BotLogic(SquareState){
	;
}

int BotLogicEasy::move()
{
	//1 - player, 2 - bot , 0 - empty
	//Easy bot logic - Find random empty position
	std::srand(time(NULL));

	std::vector<int> emptyPlaces;
	for (int i = 0; i < 9; i++) {
		if (this->squareState[i] == 0)	emptyPlaces.push_back(i);
	}

	if (emptyPlaces.size() > 0) {
		return emptyPlaces[rand() % emptyPlaces.size()];
	}

	return -1;
}
