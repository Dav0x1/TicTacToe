#include "RectButton.h"
#include <iostream>

//Constructors and destructors
btn::RectButton::RectButton(unsigned short X, unsigned short Y, unsigned short Width, unsigned short Height, sf::Color Color) {
	this->isPressedOut = false;
	this->state = states::IDLE;
	this->style = styles::COLOR;

	this->clr = Color;
	this->btn.setFillColor(Color);
	this->btn.setPosition(X, Y);
	this->btn.setSize(sf::Vector2f(Width, Height));
}

btn::RectButton::RectButton(unsigned short X, unsigned short Y, unsigned short Width, unsigned short Height, sf::Texture& Texture)
{
	this->isPressedOut = false;
	this->state = states::IDLE;
	this->style = styles::TEXTURE;
	this->clr = sf::Color::White;	

	this->btn.setTexture(&Texture);
	this->btn.setPosition(X, Y);
	this->btn.setSize(sf::Vector2f(Width, Height));
}

btn::RectButton::~RectButton()
{

}

//Functions
void btn::RectButton::render(sf::RenderTarget& Target)
{
	Target.draw(this->btn);
}

bool btn::RectButton::update(sf::RenderWindow& Window)
{
	//Przycisk nie aktywowany
	if (this->state != states::PRESSED) {
		//Przycisk myszki aktywowany
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			//Aktywowany na przycisku
			if (this->btn.getGlobalBounds().contains(sf::Mouse::getPosition(Window).x, sf::Mouse::getPosition(Window).y)) {
				//Jezeli nie zostal nacisniety pierwszo poza przyciskiem
				if (!this->isPressedOut) {
					this->state = states::ACTIVE;
				}
			}
			//Aktywowany poza przyciskiem
			else this->isPressedOut = true;
		}
		//Przycisk myszki zwolniony
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->state == ACTIVE) {
			//Zwolniony na przycisku
			if (this->btn.getGlobalBounds().contains(sf::Mouse::getPosition(Window).x, sf::Mouse::getPosition(Window).y)) {
				if (!this->isPressedOut) this->state = states::PRESSED;
				else this->isPressedOut = false;

			}
			//Zwolniony poza przyciskiem
			else
			{
				this->isPressedOut = false;
				this->state = states::IDLE;
			}
		}
		//Przycisk nie aktywowany
		else {
			this->isPressedOut = false;
			//Kursor znajduje sie poza przyciskiem
			if (!this->btn.getGlobalBounds().contains(sf::Mouse::getPosition(Window).x, sf::Mouse::getPosition(Window).y)) {
				this->state = states::IDLE;
			}
			//Kursor na przycisku
			else {
				this->state = states::HOVER;
			}
		}
	}
	//Przycisk aktywowany
	else {
		this->state = states::IDLE;
		return true;
	}


	//IDLE
	if(this->state == states::IDLE) {
		if (this->style == styles::COLOR) {
			this->btn.setFillColor(this->clr);
		}
		else if (this->style == styles::TEXTURE) {
			this->btn.setFillColor(this->clr);
		}
	}
	//HOVER
	else if (this->state == states::HOVER) {
		if (this->style == styles::COLOR) {
			this->btn.setFillColor(this->clr);
		}
		else if (this->style == styles::TEXTURE) {
			this->btn.setFillColor(sf::Color(this->clr.r,this->clr.g,this->clr.b,200));
		}
	}
	//ACTIVE
	else{
		if (this->style == styles::COLOR) {
			this->btn.setFillColor(this->clr);
		}
		else if (this->style == styles::TEXTURE) {
			this->btn.setFillColor(sf::Color(this->clr.r, this->clr.g, this->clr.b, 100));
		}
	}

	return false;
}
