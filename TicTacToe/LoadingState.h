#pragma once
#include <stack>
#include <ctime>

#include "state.h"
#include "MainMenuState.h"
#include "DisappearingText.h"

class LoadingState :public state
{
protected:
	std::stack<state*>* states;

	std::stack<DisappearingText*>  TextStack;
public:
	//Constructors and destructors
	LoadingState(sf::RenderWindow &Window, sf::Event&Event, std::stack<state*> &States);
	~LoadingState();
	//Render and update state
	void render();
	void update();
	//Updating diffrent objects
	void updateTextStack();
};