#include "DisappearingText.h"

//Constructors and destructors
DisappearingText::DisappearingText(std::string Text, sf::Font & Font, sf::Color Color, int FontSize, int PosX, int PosY, int AppperT, int DisappearT, int TotalT)
{
	this->text.setCharacterSize(FontSize);
	this->text.setFont(Font);
	this->text.setString(Text);
	this->text.setPosition(PosX,PosY);
	this->text.setFillColor(sf::Color(Color.r,Color.g,Color.b,0));

	this->appearT = AppperT;
	this->disappearT = DisappearT;
	this->totalT = TotalT;
	this->currentT = 0;
	this->color = Color;
	this->alpha = 0;
}

DisappearingText::DisappearingText(std::string Text, sf::Font& Font, sf::Color Color, int FontSize, sf::Vector2i ScreenSize, int AppperT, int DisappearT, int TotalT)
{
	this->text.setCharacterSize(FontSize);
	this->text.setFont(Font);
	this->text.setString(Text);

	//center

	this->text.setPosition(
		ScreenSize.x / 2 - this->text.getGlobalBounds().width / 2,
		ScreenSize.y / 2 - this->text.getGlobalBounds().height
	);

	this->text.setFillColor(sf::Color(Color.r, Color.g, Color.b, 0));

	this->appearT = AppperT;
	this->disappearT = DisappearT;
	this->totalT = TotalT;
	this->currentT = 0;
	this->color = Color;
	this->alpha = 0;

	this->loopTime = clock();
}

DisappearingText::~DisappearingText()
{
	
}

bool DisappearingText::update()
{
	if (this->active == false) {
		this->loopTime = clock();
		this->active = true;
	}
	float msPerLoop = float(clock() - this->loopTime) / CLOCKS_PER_SEC;
	this->loopTime = clock();
	this->currentT += msPerLoop;

	if (this->currentT <= this->appearT) {
		this->alpha += 100 * msPerLoop*this->appearT;
		if (alpha > 100) alpha = 100;
		this->text.setFillColor(sf::Color(this->color.r, this->color.g, this->color.b, (int)this->alpha));

	}
	else if (this->currentT >= this->totalT-this->disappearT) {
		this->alpha -= 100 * msPerLoop;
		if (alpha < 0) alpha = 0;
		this->text.setFillColor(sf::Color(this->color.r, this->color.g, this->color.b, (int)this->alpha));
	}

	if (this->currentT > this->totalT) return true;
	return false;
}

//Render and update
void DisappearingText::render(sf::RenderTarget& Target)
{
	Target.draw(this->text);
}

sf::FloatRect DisappearingText::GetGlobalBounds()
{
	return this->text.getGlobalBounds();
}