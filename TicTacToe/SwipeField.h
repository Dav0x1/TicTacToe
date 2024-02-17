#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class SwipeField
{
private:
	enum states { IDLE, HOVER, ACTIVE, PRESSED };

	sf::Text *text;
	sf::Color color;
	int amount;
	int activeText;

	int leftTextState;
	int middleTextState;
	int rightTextState;

	int textSpace;

	bool mousePressedOutLeft;
	bool mousePressedOutMiddle;
	bool mousePressedOutRight;

	void move(int direction);
public:
	//Constructors and destructors
	SwipeField(std::string Text[],int Amount,sf::Font &Font,int FontSize,sf::Color Color,int PosX,int PosY,int active);
	//Render and update state
	void render(sf::RenderTarget & Target);
	int update(sf::RenderWindow& Window);
};

