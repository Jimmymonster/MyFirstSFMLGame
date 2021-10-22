#include "Game.h"

//Private function
void Game::initializeVariables()
{	//set up var
	this->window = nullptr;
	this->deltaTime = 0.f;
}

void Game::initializeWindow() 
{	//set up window

	std::ifstream ifs("Config/window.ini.txt");
	this->videoModes = sf::VideoMode::getFullscreenModes();

	this->videoMode = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	std::string title = "None";
	unsigned framerate_limit = 144;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0;

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> videoMode.height >> videoMode.width;
		ifs >> fullscreen;
		ifs >> framerate_limit;
		ifs >> antialiasing_level;
	}
	ifs.close();

	this->window_settings.antialiasingLevel = antialiasing_level;
	if(fullscreen)
		this->window = new sf::RenderWindow(sf::VideoMode(this->videoMode), title, sf::Style::Fullscreen, window_settings);
	else
		this->window = new sf::RenderWindow(sf::VideoMode(this->videoMode), title, sf::Style::Titlebar|sf::Style::Close, window_settings);

	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supportedKeys.ini.txt");
	if (ifs.is_open()) {
		std::string key = "";
		int key_value = 0;
		while (ifs >> key >> key_value) {
			this->supportedKeys[key] = key_value;
		}
	}
	ifs.close();
}

void Game::initializeStates()
{
	this->states.push(new MainMenuState(this->window,&this->supportedKeys,&this->states));
}
void Game::initMouse()
{
	this->MouseTexture.loadFromFile("Resources/UI/Mouse.png");
	this->Mouse.setTexture(&this->MouseTexture);
	this->Mouse.setSize(sf::Vector2f(40, 40));
}
Game::Game()
{
	this->initializeVariables();
	this->initializeWindow();
	this->initKeys();
	this->initializeStates();
	this->initMouse();
	this->window->setMouseCursorVisible(false);
	this->font.loadFromFile("Fonts/Minecraft.ttf");
	this->StudentID = new gui::textbox(1100, 100, 200, 30, sf::Color::Transparent,
		"64010324	Thanapob Parinyarat",
		&this->font, 30, sf::Color::White,
		nullptr, false,
		sf::Color::Black,3.f);
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
}

//Accessors
const bool Game::isWindowOpen() const
{
	return this->window->isOpen();
}

//function

void Game::endGame()
{
	std::cout << "Game End!!!\n";
	this->window->close();
}

void Game::UpdateDeltaTime()
{
	// Update the deltatime with the time is takes to update and render one frame
	this->deltaTime = this->deltaTimeClock.restart().asSeconds();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->endGame();
			break;
		}

	}
}
void Game::UpdateMouse()
{
	sf::Vector2f mousePosView;
	mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->Mouse.setPosition(mousePosView.x, mousePosView.y);
}

void Game::Update()
{
	/*
		Update game event
	*/
	this->pollEvents();

	if (!this->states.empty()) {
		this->states.top()->Update(this->deltaTime);
		this->UpdateMouse();
		//getQuit
		if (this->states.top()->getQuit()) {
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	//Game End
	else {
		this->endGame();
	}
}

void Game::Render()
{
	/*
		clear old frame
		render game objects
		display frame in window
	*/

	this->window->clear(sf::Color::Black);

	//Draw game objects
	if (!this->states.empty()) {
		this->states.top()->Render();

		window->draw(this->Mouse);
		this->StudentID->Render(*window);
	}

	this->window->display();
}

void Game::Framerate()
{
	std::cout << 1.f / deltaTime << std::endl;
}

