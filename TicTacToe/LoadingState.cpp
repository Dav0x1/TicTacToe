#include "LoadingState.h"
//Constructors and destructors
LoadingState::LoadingState(sf::RenderWindow& Window, sf::Event& Event,std::stack<state*> &States)
	:state(Window, Event, States)
{
	this->states = &States;
	
	this->TextStack.push(new DisappearingText("C++ & SFML", this->font, sf::Color(255,0,0),100,sf::Vector2i(this->window->getSize().x, this->window->getSize().y),1,1,4));
	this->TextStack.push(new DisappearingText("DaV", this->font, sf::Color(255,0,0),100,sf::Vector2i(this->window->getSize().x, this->window->getSize().y),1,1,4));
	this->TextStack.push(new DisappearingText("Created by", this->font, sf::Color(255,0,0),100,sf::Vector2i(this->window->getSize().x, this->window->getSize().y),1,1,3));
	this->TextStack.push(new DisappearingText("TicTacToe", this->font, sf::Color(255,0,0),100,sf::Vector2i(this->window->getSize().x, this->window->getSize().y),1,1,5));

}
LoadingState::~LoadingState()
{
	
}
//Render and update state
void LoadingState::render()
{
	if(!this->TextStack.empty())
		this->TextStack.top()->render(*this->window);
}
void LoadingState::update()
{
	//TEMPORARY
	this->states->push(new MainMenuState(*this->window, *this->event, *this->states));
	//---
	this->updateTextStack();  
}

void LoadingState::updateTextStack()
{
	if (!this->TextStack.empty()) {
		if (this->TextStack.top()->update()) {
			delete this->TextStack.top();
			this->TextStack.pop();
		}
	}
	else
	{
		this->states->push(new MainMenuState(*this->window,*this->event,*this->states));
	}
}
