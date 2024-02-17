#pragma once
#include "state.h"
#include "DisappearingText.h"
#include "SwipeField.h"
#include "GameState.h"

class MainMenuState :
    public state
{
protected:
    DisappearingText* Text;
    DisappearingText* TextInfo;
    SwipeField* GameModes;
public:
    //Constructors and destructors
    MainMenuState(sf::RenderWindow& Window, sf::Event& Event, std::stack<state*>& States);
    ~MainMenuState();
    //Render and update state
    void render();
    void update();
};

