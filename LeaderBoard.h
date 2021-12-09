#pragma once
#include "State.h"
#include "GUI.h"
#include "pFirefly.h"
class LeaderBoard :
    public State
{
private:
    sf::Font font;

    //gui stuff
    gui::textbox* leaderboard;
    gui::textbox* playerscore[5];
    
    gui::Button* quitBTN;
    pFirefly* pfirefly;
    
    //background
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    sf::RectangleShape squre;

    //function
    void initKeybinds();
    void initFonts();
    void initBackground();
    void initGUI();
    void initScore();
public:
    LeaderBoard(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~LeaderBoard();

    //function
    void UpdateInput(const float& deltaTime);
    void UpdateGUI(const float& deltaTime);
    void Update(const float& deltaTime);
    void Render(sf::RenderTarget* target = nullptr);
};

