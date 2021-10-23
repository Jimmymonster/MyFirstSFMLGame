#pragma once

#include "GameState.h"
#include "EditorState.h"
#include "HowtoPlayState.h"
#include "GUI.h"
#include "pFirefly.h"

class MainMenuState : public State
{
private:
    //variables
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    sf::Font font;

    pFirefly *pfirefly;

    std::map<std::string, gui::ButtonForMainmenu*> buttons;

    //bgm & sound stuff
    sf::Music bgm;

    //functions
    void initVariable();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
    void initBGM();

public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~MainMenuState();

    //functions
    void UpdateInput(const float& deltaTime);
    void UpdateBTN();
    void UpdateBGM();
    void Update(const float& deltaTime);
    void RenderBTN(sf::RenderTarget& target);
    void Render(sf::RenderTarget* target = nullptr);
};

