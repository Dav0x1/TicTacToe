#pragma once
#include <SFML/Graphics.hpp>
#include <stack>

#include "LoadingState.h"

class engine
{
private:
	//Variables
	sf::RenderWindow window;
	sf::Event event;

	sf::VideoMode vMode;
	char windowName[20];

	std::stack<state*> states;
public:
	//Constructors and destructors
	engine();

	//Initialization
	void initVariable();
	void initState();

	//Functions
	bool loop();
	void pollEvents();

};