#pragma once
#include "state.h"
#include "board.h"

class GameState
	:public state
{
private:
	board *Board;
public:
	GameState(sf::RenderWindow& Window, sf::Event& Event, std::stack<state*>& States,int mode);
	~GameState();

	void render();
	void update();
};