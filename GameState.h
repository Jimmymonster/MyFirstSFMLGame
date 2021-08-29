#pragma once
#include "State.h"
#include "Slime.h"
#include "PauseMenu.h"
class GameState :
    public State
{
private:

    PauseMenu *pauseMenu;
    sf::Font pauseMenufont;

    gui::textbox* Time;
    std::string time;
    unsigned int hour, minutes, second;
    
    gui::textbox* Score;
    unsigned int scoretime, scoreenemy;

    //For player death delay
    sf::Clock clock;
    sf::Time elapsed;
    sf::Time temp = sf::seconds(0.f);

    Player* player;
    Slime* slimeRed;

    sf::RectangleShape background;
    sf::Texture backgroundTexture;

    //functions
    void initKeybinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initPlayers();
    void initEntities();
    void initGUI();
    void initBackground();
    //Utility
    void checkEndgame();

public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    //functions
    void UpdateInput(const float& deltaTime);
    void UpdatePlayerInput(const float& deltaTime);
    void UpdatePauseMenuButtons();
    void UpdateGUI(const float& deltaTime);
    void Update(const float& deltaTime);
    void Render(sf::RenderTarget* target = nullptr);
};

