#pragma once
#include "SFML/Graphics.hpp"
#include "BotLogicEasy.h"
#include "BotLogicHard.h"
#include <vector>
#include <iostream>
#include <cmath>
class cross {
private:
	sf::RectangleShape line[2];
public:
	cross(int x, int y, sf::Color Color);

	void render(sf::RenderTarget& Target);
};

class board
{
private:
	//bg color 49, 153, 158
	enum states {IDLE,ACTIVE,PRESSED};
	sf::RectangleShape Lines[4];
	sf::RectangleShape* WinLine;
	sf::RectangleShape Squares[9];
	sf::RectangleShape Shadow;
	int SuqaresState[9]{};
	sf::Text EndInfo;
	sf::Text EndInfo1;

	std::vector<sf::CircleShape*> O;
	std::vector<cross*> X;
	int state[9];
	
	BotLogic* Bot;

	bool WhoseTurn;
	bool isWin;

	int isPressedOut;
public:
	board(int x,int y,sf::Color Color,int mode, sf::Font& Font);

	void render(sf::RenderTarget &Target);
	void update(sf::RenderWindow &Window);

	void updatePlayerMove(sf::RenderWindow& Window);

	void drawWinLine(int squareNum1, int SquareNum2, bool playerWon);
	bool insert(int pos, sf::Color Color);
	void checkWin();
};
