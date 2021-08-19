#pragma once
#include "GameState.h"
#include "EditorState.h"
#include "Button.h"
class MainMenuState : public State
{
private:
    //variables
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    sf::Font font;

    std::map<std::string, Button*> buttons;

    //functions
    void initVariable();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~MainMenuState();

    //functions

    void UpdateInput(const float& deltaTime);
    void UpdateBTN();
    void Update(const float& deltaTime);
    void RenderBTN(sf::RenderTarget& target);
    void Render(sf::RenderTarget* target = nullptr);
};

