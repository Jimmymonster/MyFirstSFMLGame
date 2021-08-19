#pragma once
#include "Player.h"

class State
{
private:

protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;

	//MousePos
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resource
	std::map<std::string, sf::Texture> textures;

	//function
	virtual void initKeybinds() = 0;

public:
	State(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;

	//virtual
	virtual void UpdateMousePositions();
	//pure virtual
	void endState();
	virtual void UpdateInput(const float& deltaTime) = 0;
	virtual void Update(const float& deltaTime) = 0;
	virtual void Render(sf::RenderTarget* target=nullptr) = 0;
};
