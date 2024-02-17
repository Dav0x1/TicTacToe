#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class DisappearingText
{
private:
	sf::Text text;
	sf::Color color;
	float alpha;
	float currentT,appearT,disappearT,totalT;

	std::clock_t loopTime;

	bool active = false;
public:
	//Constructors and destructors
	DisappearingText(std::string Text,sf::Font &Font,sf::Color Color,int FontSize,int PosX,int PosY,int AppperT, int DisappearT,int TotalT);
	DisappearingText(std::string Text,sf::Font &Font,sf::Color Color,int FontSize,sf::Vector2i ScreenSize,int AppperT, int DisappearT,int TotalT);
	~DisappearingText();
	//Render and update
	bool update();
	void render(sf::RenderTarget &Target);
	
	sf::FloatRect GetGlobalBounds();
};