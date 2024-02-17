#include "SwipeField.h"

SwipeField::SwipeField(std::string Text[], int Amount, sf::Font& Font, int FontSize, sf::Color Color, int PosX, int PosY,int active)
{
	//Setting options
	this->activeText = active;
	this->textSpace = 20;
	this->amount = Amount;
	this->leftTextState = IDLE;
	this->rightTextState = IDLE;
	this->middleTextState = IDLE;
	this->color = Color;
	this->mousePressedOutLeft = false;
	this->mousePressedOutMiddle = false;
	this->mousePressedOutRight = false;

//Setting text objects
	//Making array with text objects
	this->text = new sf::Text[Amount];
	//Go throw all objects
	for (int i = 0;i<Amount;i++) {
		//Same setting for all objects
		this->text[i].setFont(Font);
		this->text[i].setCharacterSize(FontSize);
		this->text[i].setString(Text[i]);
		this->text[i].setOrigin(this->text[i].getGlobalBounds().width / 2, this->text[i].getGlobalBounds().height / 2);
		this->text[i].setPosition(PosX, PosY);
		this->text[i].setFillColor(sf::Color(Color.r, Color.g, Color.b, 0));
	}
	//Text in center
		this->text[this->activeText].setFillColor(sf::Color(Color.r,Color.g,Color.b,255));
	//Text from left side
		int leftTextNum = this->activeText - 1 < 0 ? this->amount-1 : this->activeText - 1;
		this->text[leftTextNum].setPosition(PosX - this->text[this->activeText].getGlobalBounds().width / 2 - this->text[leftTextNum].getGlobalBounds().width / 2 - this->textSpace, PosY);
		this->text[leftTextNum].setFillColor(sf::Color(Color.r, Color.g, Color.b, 100));
	//Text from right side
		int rightTextNum = this->activeText >= this->amount-1 ? 0 : this->activeText+1;
		this->text[rightTextNum].setPosition(PosX + this->text[this->activeText].getGlobalBounds().width / 2 + this->text[rightTextNum].getGlobalBounds().width / 2 + this->textSpace, PosY);
		this->text[rightTextNum].setFillColor(sf::Color(Color.r, Color.g, Color.b, 100));
}

void SwipeField::render(sf::RenderTarget& Target)
{
	Target.draw(this->text[this->activeText]);
	int leftTextNum = this->activeText - 1 < 0 ? this->amount - 1 : this->activeText - 1;
	Target.draw(this->text[leftTextNum]);
	int rightTextNum = this->activeText >= this->amount-1 ? 0 : this->activeText + 1;
	Target.draw(this->text[rightTextNum]);
}

int SwipeField::update(sf::RenderWindow & Window)
{
int leftTextNum = this->activeText - 1 < 0 ? this->amount - 1 : this->activeText - 1;
int rightTextNum = this->activeText >= this->amount - 1 ? 0 : this->activeText + 1;
//Text in left side
if (this->leftTextState != PRESSED) {
	//Mouse inside text
	if (this->text[leftTextNum].getGlobalBounds()
		.contains(sf::Mouse::getPosition(Window).x, sf::Mouse::getPosition(Window).y)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->mousePressedOutLeft) {
			this->leftTextState = ACTIVE;
			this->text[leftTextNum].setFillColor(sf::Color(this->color.r, this->color.g, this->color.b, 200));
		}
		else if (this->leftTextState == ACTIVE && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->leftTextState = PRESSED;
			this->move(0);
		}
		else {
			this->leftTextState = HOVER;
			this->text[leftTextNum].setFillColor(sf::Color(this->color.r, this->color.g, this->color.b, 150));
		}
		
	}
	//Mouse outside text
	else {
		this->leftTextState = IDLE;
		this->text[leftTextNum].setFillColor(sf::Color(this->color.r, this->color.g, this->color.b, 100));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->mousePressedOutLeft = true;
		}
		else {
			this->mousePressedOutLeft = false;
		}
	}
}
//Text in right side
if (this->rightTextState != PRESSED) {
	//Mouse inside text
	if (this->text[rightTextNum].getGlobalBounds()
		.contains(sf::Mouse::getPosition(Window).x, sf::Mouse::getPosition(Window).y)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->mousePressedOutRight) {
			this->rightTextState = ACTIVE;
			this->text[rightTextNum].setFillColor(sf::Color(this->color.r, this->color.g, this->color.b, 200));
		}
		else if (this->rightTextState == ACTIVE && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->rightTextState = PRESSED;
			this->move(1);
		}
		else {
			this->rightTextState = HOVER;
			this->text[rightTextNum].setFillColor(sf::Color(this->color.r, this->color.g, this->color.b, 150));
		}

	}
	//Mouse outside text
	else {
		this->rightTextState = IDLE;
		this->text[rightTextNum].setFillColor(sf::Color(this->color.r, this->color.g, this->color.b, 100));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->mousePressedOutRight = true;
		}
		else {
			this->mousePressedOutRight = false;
		}
	}
}
//Middle text
	//Mouse inside text
	if (this->text[this->activeText].getGlobalBounds()
		.contains(sf::Mouse::getPosition(Window).x, sf::Mouse::getPosition(Window).y)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->mousePressedOutMiddle) {
			this->middleTextState = ACTIVE;
		}
		else if (this->middleTextState == ACTIVE && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			return this->activeText;
		}

	}
	//Mouse outside text
	else {
		this->middleTextState = IDLE;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->mousePressedOutMiddle = true;
		}
		else {
			this->mousePressedOutMiddle = false;
		}
	}

return -1;
}

void SwipeField::move(int direction)
{
	int leftTextNum = this->activeText - 1 < 0 ? this->amount - 1 : this->activeText - 1;
	int rightTextNum = this->activeText >= this->amount - 1 ? 0 : this->activeText + 1;
	if (direction == 0) {
		//left
		this->leftTextState = IDLE;
		this->text[rightTextNum].setFillColor(sf::Color(this->color.r, this->color.g, this->color.b, 0));
		int PosX = this->text[this->activeText].getPosition().x;
		int PosY = this->text[this->activeText].getPosition().y;
		this->activeText = this->activeText - 1 < 0 ? this->amount - 1 : this->activeText - 1;
		//Text in center
		this->text[this->activeText].setFillColor(sf::Color(this->color.r, this->color.g, this->color.b, 255));
		this->text[this->activeText].setPosition(PosX, PosY);
		//Text from left side
		leftTextNum = this->activeText - 1 < 0 ? this->amount - 1 : this->activeText - 1;
		this->text[leftTextNum].setPosition(PosX - this->text[this->activeText].getGlobalBounds().width / 2 - this->text[leftTextNum].getGlobalBounds().width / 2 - this->textSpace, PosY);
		this->text[leftTextNum].setFillColor(sf::Color(this->color.r, this->color.g, this->color.b, 100));
		//Text from right side
		rightTextNum = this->activeText >= this->amount - 1 ? 0 : this->activeText + 1;
		this->text[rightTextNum].setPosition(PosX + this->text[this->activeText].getGlobalBounds().width / 2 + this->text[rightTextNum].getGlobalBounds().width / 2 + this->textSpace, PosY);
		this->text[rightTextNum].setFillColor(sf::Color(this->color.r, this->color.g, this->color.b, 100));
	}
	else {
		//right
		this->rightTextState = IDLE;
		this->text[leftTextNum].setFillColor(sf::Color(this->color.r, this->color.g, this->color.b, 0));
		int PosX = this->text[this->activeText].getPosition().x;
		int PosY = this->text[this->activeText].getPosition().y;
		this->activeText = this->activeText >= this->amount - 1 ? 0 : this->activeText + 1;;
		//Text in center
		this->text[this->activeText].setFillColor(sf::Color(this->color.r, this->color.g, this->color.b, 255));
		this->text[this->activeText].setPosition(PosX, PosY);
		//Text from left side
		leftTextNum = this->activeText - 1 < 0 ? this->amount - 1 : this->activeText - 1;
		this->text[leftTextNum].setPosition(PosX - this->text[this->activeText].getGlobalBounds().width / 2 - this->text[leftTextNum].getGlobalBounds().width / 2 - this->textSpace, PosY);
		this->text[leftTextNum].setFillColor(sf::Color(this->color.r, this->color.g, this->color.b, 100));
		//Text from right side
		rightTextNum = this->activeText >= this->amount - 1 ? 0 : this->activeText + 1;
		this->text[rightTextNum].setPosition(PosX + this->text[this->activeText].getGlobalBounds().width / 2 + this->text[rightTextNum].getGlobalBounds().width / 2 + this->textSpace, PosY);
		this->text[rightTextNum].setFillColor(sf::Color(this->color.r, this->color.g, this->color.b, 100));
	}
}
