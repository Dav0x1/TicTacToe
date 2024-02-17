#include "GameState.h"

GameState::GameState(sf::RenderWindow& Window, sf::Event& Event, std::stack<state*>& States, int mode)
	:state(Window,Event,States) 
{
	this->Board = new board(this->window->getSize().x/2, this->window->getSize().y / 2,sf::Color(255,255,255),mode,this->font);
}

GameState::~GameState()
{
}

void GameState::render() 
{
	this->Board->render(*this->window);
	this->renderTopBar();
}
void GameState::update()
{
	this->Board->update(*this->window);
	this->updateTopBar();
}