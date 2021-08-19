#pragma once
#include"MainMenuState.h"
/*
	Game Engine class(Something like that)
*/

class Game
{
private:
	//Varables
	sf::RenderWindow* window;
	sf::Event ev;
	std::vector<sf::VideoMode> videoModes;
	sf::VideoMode videoMode; // <-- default
	sf::ContextSettings window_settings;

	float deltaTime;
	sf::Clock deltaTimeClock;

	std::stack<State*> states;
	
	std::map<std::string, int> supportedKeys;

	//Game objects

	//Private function
	void initializeVariables();
	void initializeWindow();
	void initKeys();
	void initializeStates();

public:

	//construct
	Game();

	//desctruct
	virtual ~Game();

	//Accessors
	const bool isWindowOpen() const;

	//function
	//Regular
	void endGame();

	//UPDATE
	void UpdateDeltaTime();
	void pollEvents();
	void Update();

	//RENDER
	void Render();
	void Framerate();
};

