#include "board.h"

board::board(int x, int y, sf::Color Color, int mode,sf::Font &Font)
{
	int width=300,height=300;
	int lineThickness = 6;
	this->isWin = false;
	this->WinLine = NULL;
	std::srand(time(NULL));
	this->WhoseTurn = rand()%2;
	this->isPressedOut = false;

	for (int i = 0;i<4;i++) {
		this->Lines[i].setFillColor(Color);
		if (i < 2) {
			this->Lines[i].setSize(sf::Vector2f(lineThickness, height));
		}
		else {
			this->Lines[i].setSize(sf::Vector2f(width, lineThickness));
		}
		this->Lines[i].setOrigin(this->Lines[i].getSize().x / 2, this->Lines[i].getSize().y / 2);
	}

	this->Lines[0].setPosition(sf::Vector2f(x - width / 6, y));
	this->Lines[1].setPosition(sf::Vector2f(x + width / 6, y));
	this->Lines[2].setPosition(sf::Vector2f(x, y - height / 6));
	this->Lines[3].setPosition(sf::Vector2f(x, y + height / 6));

	for (int i = 0;i<9;i++) {
		this->Squares[i].setSize(sf::Vector2f(width/3,height/3));
	}
	this->Squares[0].setPosition(x - width / 2,y - height/2);
	this->Squares[1].setPosition(x - width / 6, y - height / 2);
	this->Squares[2].setPosition(x + width / 6, y - height / 2);
	this->Squares[3].setPosition(x - width / 2, y - height / 6);
	this->Squares[4].setPosition(x - width / 6, y - height / 6);
	this->Squares[5].setPosition(x + width / 6, y - height / 6);
	this->Squares[6].setPosition(x - width / 2, y + height / 6);
	this->Squares[7].setPosition(x - width / 6, y + height / 6);
	this->Squares[8].setPosition(x + width / 6, y + height / 6);

	for (int i = 0;i<9;i++) {
		this->state[i] = 0;
	}

	switch (mode) {
		//easy
	case 0:
		this->Bot = new BotLogicEasy(this->state);
		break;
		//hard
	case 1:
		this->Bot = new BotLogicHard(this->state);
		break;
		//Impossible
	case 2:
		this->Bot = new BotLogicHard(this->state);
		break;
		//Learning
	case 3:
		this->Bot = new BotLogicEasy(this->state);
		break;
	}

	this->Shadow.setFillColor(sf::Color(49, 153, 158,200));
	this->Shadow.setSize(sf::Vector2f(600,600));

	this->EndInfo.setFont(Font);
	this->EndInfo.setFillColor(sf::Color::White);
	this->EndInfo.setCharacterSize(100);

	this->EndInfo1.setFont(Font);
	this->EndInfo1.setFillColor(sf::Color::White);
	this->EndInfo1.setCharacterSize(40);
	this->EndInfo1.setString("Press enter to try again");
}

void board::update(sf::RenderWindow& Window) {
	if (this->isWin == false)
	{
		if (this->WhoseTurn)
			this->updatePlayerMove(Window);
		else
			this->insert(this->Bot->move(), sf::Color());
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			this->isWin = false;
			delete this->WinLine;
			this->WinLine = NULL;
			std::srand(time(NULL));
			this->WhoseTurn = rand() % 2;
			this->isPressedOut = false;
			for (int i = 0;i<9;i++) {
				this->state[i] = 0;
				this->SuqaresState[0] = IDLE;
			}
			this->O.clear();
			this->X.clear();
		}
	}
}
void board::updatePlayerMove(sf::RenderWindow& Window) {
	if (this->WhoseTurn) {
		for (int i = 0;i<9;i++) {
			if (this->Squares[i].getGlobalBounds().contains(sf::Mouse::getPosition(Window).x, sf::Mouse::getPosition(Window).y)) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					this->SuqaresState[i] = ACTIVE;
				}
				else if(this->SuqaresState[i] == ACTIVE) {
					this->insert(i, sf::Color(255, 255, 255));
				}
				else {
					this->SuqaresState[i] = IDLE;
				}
				break;
			}
			else {
				this->SuqaresState[i] = IDLE;
			}
		}
	}
};

void board::render(sf::RenderTarget& Target)
{
	for (int i = 0; i < 4; i++) {
		Target.draw(this->Lines[i]);
	}
	for (auto &i: this->X) {
		i->render(Target);
	}
	for (auto& i : this->O) {
		Target.draw(*i);
	}
	if(this->isWin){
		if(this->WinLine != NULL)
		Target.draw(*this->WinLine);
		Target.draw(this->Shadow);
		Target.draw(this->EndInfo);
		Target.draw(this->EndInfo1);
	}
}

bool board::insert(int pos,sf::Color Color)
{
	if (this->state[pos] !=0 ) { 
		return 0;
	}
	//X - gracz - 1
	if (this->WhoseTurn) {
		this->X.push_back(new cross(this->Squares[pos].getPosition().x+ this->Squares[pos].getSize() .x/2,
									this->Squares[pos].getPosition().y+ this->Squares[pos].getSize().y/2,
									Color)
						 );
		this->WhoseTurn = false;
		this->state[pos] = 1;
		this->checkWin();
		return 1;
	}
	//O - bot - 2
	else {
		this->O.push_back(new sf::CircleShape);
		this->O.back()->setOutlineColor(Color);
		this->O.back()->setFillColor(sf::Color(0,0,0,0));
		this->O.back()->setOutlineThickness(7);
		this->O.back()->setRadius(30);
		this->O.back()->setOrigin(this->O.back()->getGlobalBounds().width / 2, this->O.back()->getGlobalBounds().height / 2);
		this->O.back()->setPosition(this->Squares[pos].getPosition().x + this->Squares[pos].getSize().x/2 +7, this->Squares[pos].getPosition().y + this->Squares[pos].getSize().y/2 +7);
		this->WhoseTurn = true;
		this->state[pos] = 2;
		this->checkWin();
		return 1;
	}
	return 0;
}
void board::checkWin() {


	if (this->state[0] != 0 && this->state[0] == this->state[1] && this->state[1] == this->state[2]) {
		this->isWin = true;
		bool playerWon = true;
		if (this->state[0] == 1)
			playerWon = false;
		this->drawWinLine(0,2,playerWon);
	}
	else if (this->state[3] != 0 && this->state[3] == this->state[4] && this->state[4] == this->state[5]) {
		this->isWin = true;
		bool playerWon = true;
		if (this->state[3] == 1)
			playerWon = false;
		this->drawWinLine(3, 4, playerWon);
	}
	else if (this->state[6] != 0 && this->state[6] == this->state[7] && this->state[7] == this->state[8]) {
		this->isWin = true;
		bool playerWon = true;
		if (this->state[6] == 1)
			playerWon = false;
		this->drawWinLine(6, 8, playerWon);
	}
	else if (this->state[0] != 0 && this->state[0] == this->state[3] && this->state[3] == this->state[6]) {
		this->isWin = true;
		bool playerWon = true;
		if (this->state[0] == 1)
			playerWon = false;
		this->drawWinLine(0, 6, playerWon);
	}
	else if (this->state[1] != 0 && this->state[1] == this->state[4] && this->state[4] == this->state[7]) {
		this->isWin = true;
		bool playerWon = true;
		if (this->state[1] == 1)
			playerWon = false;
		this->drawWinLine(1, 7, playerWon);
	}
	else if (this->state[2] != 0 && this->state[2] == this->state[5] && this->state[5] == this->state[8]) {
		this->isWin = true;
		bool playerWon = true;
		if (this->state[2] == 1)
			playerWon = false;
		this->drawWinLine(2, 8, playerWon);
	}

	else if (this->state[2] != 0 && this->state[2] == this->state[4] && this->state[4] == this->state[6]) {
		this->isWin = true;
		bool playerWon = true;
		if (this->state[2] == 1)
			playerWon = false;
		this->drawWinLine(2, 6, playerWon);
	}
	else if (this->state[0] != 0 && this->state[0] == this->state[4] && this->state[4] == this->state[8]) {
		this->isWin = true;
		bool playerWon = true;
		if (this->state[0] == 1)
			playerWon = false;
		this->drawWinLine(0, 8, playerWon);
	}
	else {
		bool end = true;
		for (int i = 0;i<9; i++) {
			if (this->state[i] == 0) {
				end = false;
			}
		}
		if (end) {
			this->isWin = true;
			this->EndInfo.setString("Nobody won");
			this->EndInfo.setPosition(300 - this->EndInfo.getGlobalBounds().width / 2,
				300 - this->EndInfo.getGlobalBounds().height);
			this->EndInfo1.setPosition(100,
				350);
		}
	}
}
void board::drawWinLine(int SquareNum1, int SquareNum2, bool playerWon) {
	int width = 8;
	this->WinLine = new sf::RectangleShape();

	if (playerWon) {
		this->WinLine->setFillColor(sf::Color(0, 0, 0, 200));
		this->EndInfo.setString("You're Loser");
	}
	else{
	this->WinLine->setFillColor(sf::Color(255, 255, 255, 200));
	this->EndInfo.setString("You're Winner");
	}
	this->EndInfo.setPosition(300-this->EndInfo.getGlobalBounds().width/2,
		300 - this->EndInfo.getGlobalBounds().height);
	this->EndInfo1.setPosition(100,
		350);

	if (this->Squares[SquareNum1].getPosition().y == this->Squares[SquareNum2].getPosition().y) {
		this->WinLine->setSize(sf::Vector2f(this->Lines[2].getSize().x,width));
		this->WinLine->setPosition(this->Squares[SquareNum1].getPosition().x, this->Squares[SquareNum1].getPosition().y + this->Squares[SquareNum1].getSize().y/2 - this->WinLine->getSize().y/2);
	}
	else if (this->Squares[SquareNum1].getPosition().x == this->Squares[SquareNum2].getPosition().x) {
		this->WinLine->setSize(sf::Vector2f(width, this->Lines[0].getSize().y));
		this->WinLine->setPosition(this->Squares[SquareNum1].getPosition().x + this->Squares[SquareNum1].getSize().x / 2 - this->WinLine->getSize().x / 2, this->Squares[SquareNum1].getPosition().y);
	}
	else if (this->Squares[SquareNum1].getPosition().x > this->Squares[SquareNum2].getPosition().x) {
		int length = std::sqrt(std::pow(this->Lines[2].getSize().x,2) + std::pow(this->Lines[0].getSize().y,2));
		this->WinLine->setSize(sf::Vector2f(length,width));
		this->WinLine->setOrigin(0,width/2);
		this->WinLine->setRotation(-45);
		this->WinLine->setPosition(this->Squares[SquareNum2].getPosition().x, this->Squares[SquareNum2].getPosition().y+ this->Squares[SquareNum2].getSize().y);
	}
	else {
		int length = std::sqrt(std::pow(this->Lines[2].getSize().x, 2) + std::pow(this->Lines[0].getSize().y, 2));
		this->WinLine->setSize(sf::Vector2f(length, width));
		this->WinLine->setOrigin(0, width / 2);
		this->WinLine->setRotation(45);
		this->WinLine->setPosition(this->Squares[SquareNum1].getPosition().x, this->Squares[SquareNum1].getPosition().y);

	}
}
//Class X
cross::cross(int x, int y, sf::Color Color) {
	for (int i = 0; i < 2; i++) {
		this->line[i].setFillColor(Color);
		this->line[i].setSize(sf::Vector2f(7,80));
		this->line[i].setOrigin(this->line[i].getSize().x/2,this->line[i].getSize().y/2);
		this->line[i].setPosition(x,y);
	}
	this->line[0].setRotation(45);
	this->line[1].setRotation(-45);
}

void cross::render(sf::RenderTarget& Target) {
	Target.draw(this->line[0]);
	Target.draw(this->line[1]);
};
