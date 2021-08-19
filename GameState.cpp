#include "GameState.h"

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestateKeybinds.ini.txt");
	if (ifs.is_open()) {
		std::string key = "" , key2 = "";
		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void GameState::initTextures()
{
	this->textures["PLAYER_SHEET"].loadFromFile("Resources/Sprites/Player/spriteSheet.png");
}

void GameState::initPlayers()
{
	this->player = new Player(50, 50, this->textures["PLAYER_SHEET"],sf::Vector2f(3,3),31,2);
}

GameState::GameState(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys, std::stack<State*>* states) : State(window,supportedKeys,states)
{
	this->initKeybinds();
	this->initTextures();
	this->initPlayers();
}

GameState::~GameState()
{
	delete this->player;
}

//functions
void GameState::UpdateInput(const float& deltaTime)
{
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move( -1.f, 0.f,deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move( 1.f, 0.f,deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("JUMP1")))|| sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("JUMP2"))))
		this->player->move( 0.f, -500.f,deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DROP"))))
		this->player->move( 0.f, 1.f,deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
		this->endState();
	}
}

void GameState::Update(const float& deltaTime)
{
	this->UpdateMousePositions();
	this->UpdateInput(deltaTime);

	this->player->Update(deltaTime);
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	this->player->Render(*target);
}
