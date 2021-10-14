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
	bool pause;
	float keytime;
	float keytimeMax;

	bool shaking;
	int cou;
	sf::View saveView;
	sf::View view;
	sf::Clock clock;
	sf::Time temp;

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

	//Accessor
	const bool& getQuit() const;
	const bool getKeytime();

	//function
	void endState();
	void pauseState();
	void unpauseState();
	void shakeScreen();

	//virtual
	virtual void UpdateMousePositions();
	virtual void UpdateKeytime(const float deltaTime);
	
	//pure virtual <-- make sure to add this in each state
	virtual void UpdateInput(const float& deltaTime) = 0;
	virtual void Update(const float& deltaTime) = 0;
	virtual void Render(sf::RenderTarget* target=nullptr) = 0;
};
