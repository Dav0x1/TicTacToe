#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <stack>
#include <iostream>
#include <windows.h>
#include "RectButton.h"

class state
{
protected:
	sf::RenderWindow* window;
	sf::Event* event;

	sf::Font font;
	
	std::stack<state*> *states;

	//Top bar
	sf::RectangleShape topBarRect;
	sf::Text gameName;
	btn::RectButton *exitButton;
	btn::RectButton *minimizeButton;
	btn::RectButton *returnButton;
	//--
	std::map<std::string, sf::Texture> textures;
public:
	//Constructors and destructors
	state(sf::RenderWindow& Window, sf::Event& Event, std::stack<state*> &States);
	~state();
	//Initializations
	void initTextures();
	//Render and update state
	virtual void render();
	virtual void update();

	void renderTopBar();
	void updateTopBar();
};