#pragma once

#include "State.h"
#include "GUI.h"

class SettingState :
    public State
{
private:
    //variables
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::dropdownlist*> dropdownlists;

    //functions
    void initVariable();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initGUI();

public:
    SettingState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~SettingState();
    
    //Accessor

    //Function
    void UpdateInput(const float& deltaTime);
    void UpdateGUI(const float& deltaTime);
    void Update(const float& deltaTime);
    void RenderGUI(sf::RenderTarget& target);
    void Render(sf::RenderTarget* target = nullptr);
};

