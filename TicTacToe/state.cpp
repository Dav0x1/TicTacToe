#include "state.h"

//Constructors and destructors
state::state(sf::RenderWindow& Window, sf::Event& Event, std::stack<state*> &States)
{
	this->initTextures();

	this->window = &Window;
	this->event = &Event;
	this->states = &States;
	this->font.loadFromFile("ZenTokyo.ttf");
	//Top Bar
	this->topBarRect.setSize(sf::Vector2f(this->window->getSize().x,30));
	this->topBarRect.setFillColor(sf::Color(0,0,0,100));

	this->gameName.setFillColor(sf::Color::White);
	this->gameName.setFont(this->font);
	this->gameName.setCharacterSize(25);
	this->gameName.setString("TicTacToe");
	this->gameName.setPosition(this->window->getSize().x/2-this->gameName.getGlobalBounds().width/2,0);

	this->exitButton = new btn::RectButton(this->window->getSize().x-26,4,22,22,this->textures["CLOSE"]);
	this->minimizeButton = new btn::RectButton(this->window->getSize().x-60,4,22,22,this->textures["MINIMIZE"]);
	this->returnButton = new btn::RectButton(this->window->getSize().x-94,4,22,22,this->textures["RETURN"]);
}
state::~state()
{
}
//Initializations
void state::initTextures()
{
	if (!this->textures["MINIMIZE"].loadFromFile("Resources/minimize.png"))
		std::cout << "STATE::LOAD::TEXTUR::MINIMIZE::ERROR";
	if (!this->textures["CLOSE"].loadFromFile("Resources/close.png"))
		std::cout << "STATE::LOAD::TEXTUR::CLOSE::ERROR";
	if (!this->textures["RETURN"].loadFromFile("Resources/return.png"))
		std::cout << "STATE::LOAD::TEXTUR::RETURN::ERROR";
		
}
//Render and update state
void state::render()
{
}
void state::update()
{
}

void state::renderTopBar()
{
	this->window->draw(this->topBarRect);
	this->window->draw(this->gameName);
	this->exitButton->render(*this->window);
	this->minimizeButton->render(*this->window);
	this->returnButton->render(*this->window);
}

void state::updateTopBar()
{
	if (this->exitButton->update(*this->window)) {
		this->window->close();
	}
	if (this->minimizeButton->update(*this->window)) {
		sf::WindowHandle WindowHandle = this->window->getSystemHandle();
		ShowWindow(WindowHandle, SW_MINIMIZE);
	}
	if (this->returnButton->update(*this->window)) {
		this->states->pop();
	}
}
