#pragma once

#include"State.h"
#include "GUI.h"
class EditorState : public State
{
private:
    //variables
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;

    //functions
    void initVariable();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~EditorState();

    //functions

    void UpdateInput(const float& deltaTime);
    void UpdateBTN();
    void Update(const float& deltaTime);
    void RenderBTN(sf::RenderTarget& target);
    void Render(sf::RenderTarget* target = nullptr);
};