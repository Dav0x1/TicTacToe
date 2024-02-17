#include "BotLogicHard.h"

BotLogicHard::BotLogicHard(int* SquareState)
	:BotLogic(SquareState)
{

}

int BotLogicHard::move()
{
	//1 - player, 2 - bot , 0 - empty
	//Easy bot logic - Find random empty position
	
	//Check if board is empty (put in random place)
	bool empty = true;
	for (int i = 0;i<9;i++) {
		if (this->squareState[i] != 0) {
			empty = false;
			break;
		}
	}
	if (empty) {
		std::srand(time(NULL));
		int rand = std::rand() % 9;
		return rand;
	}
	//Check if bot isn't close to win (this mean that place have x2 "O" in row or col)
	if (this->squareState[0] == 2 && this->squareState[1] == 2 && this->squareState[2] == 0)
		return 2;
	else if (this->squareState[1] == 2 && this->squareState[2] == 2 && this->squareState[0] == 0)
		return 0;
	else if (this->squareState[3] == 2 && this->squareState[4] == 2 && this->squareState[5] == 0)
		return 5;
	else if (this->squareState[4] == 2 && this->squareState[5] == 2 && this->squareState[3] == 0)
		return 3;
	else if (this->squareState[6] == 2 && this->squareState[7] == 2 && this->squareState[8] == 0)
		return 8;
	else if (this->squareState[7] == 2 && this->squareState[8] == 2 && this->squareState[6] == 0)
		return 6;
	else if (this->squareState[0] == 2 && this->squareState[2] == 2 && this->squareState[1] == 0)
		return 1;
	else if (this->squareState[3] == 2 && this->squareState[5] == 2 && this->squareState[4] == 0)
		return 4;
	else if (this->squareState[6] == 2 && this->squareState[8] == 2 && this->squareState[7] == 0)
		return 7;

	else if (this->squareState[0] == 2 && this->squareState[3] == 2 && this->squareState[6] == 0)
		return 6;
	else if (this->squareState[3] == 2 && this->squareState[6] == 2 && this->squareState[0] == 0)
		return 0;
	else if (this->squareState[1] == 2 && this->squareState[4] == 2 && this->squareState[7] == 0)
		return 7;
	else if (this->squareState[4] == 2 && this->squareState[7] == 2 && this->squareState[1] == 0)
		return 1;
	else if (this->squareState[2] == 2 && this->squareState[5] == 2 && this->squareState[8] == 0)
		return 8;
	else if (this->squareState[5] == 2 && this->squareState[8] == 2 && this->squareState[2] == 0)
		return 2;
	else if (this->squareState[0] == 2 && this->squareState[6] == 2 && this->squareState[3] == 0)
		return 3;
	else if (this->squareState[1] == 2 && this->squareState[7] == 2 && this->squareState[4] == 0)
		return 4;
	else if (this->squareState[2] == 2 && this->squareState[8] == 2 && this->squareState[5] == 0)
		return 5;

	else if (this->squareState[0] == 2 && this->squareState[4] == 2 && this->squareState[8] == 0)
		return 8;
	else if (this->squareState[4] == 2 && this->squareState[8] == 2 && this->squareState[0] == 0)
		return 0;
	else if (this->squareState[2] == 2 && this->squareState[4] == 2 && this->squareState[6] == 0)
		return 6;
	else if (this->squareState[6] == 2 && this->squareState[4] == 2 && this->squareState[2] == 0)
		return 2;
	else if (this->squareState[0] == 2 && this->squareState[8] == 2 && this->squareState[4] == 0)
		return 4;
	else if (this->squareState[2] == 2 && this->squareState[6] == 2 && this->squareState[4] == 0)
		return 4;
	//Check if player isn't close to win (this mean that plce have x2 "X" in row or col)
	// 12 23 45 56 78 89
	// 14 47 25 58 36 69
	// 15 59 75 53
	if (this->squareState[0] == 1 && this->squareState[1] == 1 && this->squareState[2] == 0)
		return 2;
	else if (this->squareState[1] == 1 && this->squareState[2] == 1 && this->squareState[0] == 0)
		return 0;
	else if (this->squareState[3] == 1 && this->squareState[4] == 1 && this->squareState[5] == 0)
		return 5;
	else if (this->squareState[4] == 1 && this->squareState[5] == 1 && this->squareState[3] == 0)
		return 3;
	else if (this->squareState[6] == 1 && this->squareState[7] == 1 && this->squareState[8] == 0)
		return 8;
	else if (this->squareState[7] == 1 && this->squareState[8] == 1 && this->squareState[6] == 0)
		return 6;
	else if (this->squareState[0] == 1 && this->squareState[2] == 1 && this->squareState[1] == 0)
		return 1;
	else if (this->squareState[3] == 1 && this->squareState[5] == 1 && this->squareState[4] == 0)
		return 4;
	else if (this->squareState[6] == 1 && this->squareState[8] == 1 && this->squareState[7] == 0)
		return 7;

	else if (this->squareState[0] == 1 && this->squareState[3] == 1 && this->squareState[6] == 0)
		return 6;
	else if (this->squareState[3] == 1 && this->squareState[6] == 1 && this->squareState[0] == 0)
		return 0;
	else if (this->squareState[1] == 1 && this->squareState[4] == 1 && this->squareState[7] == 0)
		return 7;
	else if (this->squareState[4] == 1 && this->squareState[7] == 1 && this->squareState[1] == 0)
		return 1;
	else if (this->squareState[2] == 1 && this->squareState[5] == 1 && this->squareState[8] == 0)
		return 8;
	else if (this->squareState[5] == 1 && this->squareState[8] == 1 && this->squareState[2] == 0)
		return 2;
	else if (this->squareState[0] == 1 && this->squareState[6] == 1 && this->squareState[3] == 0)
		return 3;
	else if (this->squareState[1] == 1 && this->squareState[7] == 1 && this->squareState[4] == 0)
		return 4;
	else if (this->squareState[2] == 1 && this->squareState[8] == 1 && this->squareState[5] == 0)
		return 5;

	else if (this->squareState[0] == 1 && this->squareState[4] == 1 && this->squareState[8] == 0)
		return 8;
	else if (this->squareState[4] == 1 && this->squareState[8] == 1 && this->squareState[0] == 0)
		return 0;
	else if (this->squareState[2] == 1 && this->squareState[4] == 1 && this->squareState[6] == 0)
		return 6;
	else if (this->squareState[6] == 1 && this->squareState[4] == 1 && this->squareState[2] == 0)
		return 2;
	else if (this->squareState[0] == 1 && this->squareState[8] == 1 && this->squareState[4] == 0)
		return 4;
	else if (this->squareState[2] == 1 && this->squareState[6] == 1 && this->squareState[4] == 0)
		return 4;


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
