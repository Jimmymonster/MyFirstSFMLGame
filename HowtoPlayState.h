#pragma once
#include "State.h"
#include "AnimationComponent.h"
#include "pFirefly.h"
class HowtoPlayState :
    public State
{
private:
    sf::Font font;

    //background
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    pFirefly* pfirefly;

    AnimationComponent* animationComponent[3];
    sf::Sprite sprite[5];
    sf::RectangleShape squre;

    std::map<std::string, gui::textbox*> text;
    gui::Button* quitBTN;

    //function
    void initKeybinds();
    void initFonts();
    void initBackground();
    void initGUI();
public:
    HowtoPlayState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~HowtoPlayState();

     //function
    void UpdateInput(const float& deltaTime);
    void UpdateGUI(const float& deltaTime);
    void Update(const float& deltaTime);
    void Render(sf::RenderTarget* target = nullptr);
};

