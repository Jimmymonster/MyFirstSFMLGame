#pragma once
#include "State.h"
class GameState :
    public State
{
private:
    Player* player;

    //functions
    void initKeybinds();
    void initTextures();
    void initPlayers();

public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    //functions

    void UpdateInput(const float& deltaTime);
    void Update(const float& deltaTime);
    void Render(sf::RenderTarget* target = nullptr);
};

