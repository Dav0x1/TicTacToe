#include "MainMenuState.h"
//Constructors and destructors
MainMenuState::MainMenuState(sf::RenderWindow& Window, sf::Event& Event, std::stack<state*>& States)
	:state(Window, Event, States)
{
	this->Text = new DisappearingText("Game mode",this->font,sf::Color(255,0,0),80,120,140,1,1,1000000);
	this->TextInfo = new DisappearingText("Press middle mode to start",this->font,sf::Color(255,0,0),20,200,370,1,1,1000000);

	std::string tab[] = {"Easy","Hard","Impossible","Learning" ,"5" };
	this->GameModes = new SwipeField(tab,4,this->font,40, sf::Color(135, 95, 95),this->window->getSize().x/2, this->window->getSize().y / 2,0);
}
MainMenuState::~MainMenuState()
{

}
//Render and update state
void MainMenuState::render()
{
	this->Text->render(*this->window);
	this->TextInfo->render(*this->window);
	this->GameModes->render(*this->window);
	this->renderTopBar();
}
void MainMenuState::update()
{
	this->Text->update();
	this->TextInfo->update();
	int mode = this->GameModes->update(*this->window);
	if (mode!=-1) {
		this->states->push(new GameState(*this->window,*this->event,*this->states,mode));
	}
	this->updateTopBar();
}
