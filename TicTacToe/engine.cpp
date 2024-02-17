#include "engine.h"

//Constructors and destructors
engine::engine() {
	this->initVariable();
	this->initState();
}

//Initialization
void engine::initVariable()
{
	this->vMode.width = 600;
	this->vMode.height = 600;

	sprintf_s(this->windowName,"Tic Tac Toe");

	this->window.create(this->vMode,this->windowName,sf::Style::None);
}

void engine::initState()
{
	this->states.push(new LoadingState(this->window, this->event,this->states));
}

//Functions
bool engine::loop() {
	while (this->window.isOpen() && !this->states.empty()) {
		this->window.clear(sf::Color(49, 153, 158));
		this->pollEvents();
		this->states.top()->update();
		this->states.top()->render();
		this->window.display();
	}
	return true;
}

void engine::pollEvents()
{
	while (this->window.pollEvent(this->event))
	{
		// "close requested" event: we close the window
		if (this->event.type == sf::Event::Closed)
			this->window.close();
	}
}
