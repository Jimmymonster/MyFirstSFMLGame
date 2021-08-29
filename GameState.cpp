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
void GameState::initFonts()
{
	if (!this->pauseMenufont.loadFromFile("Fonts/angsana.ttc")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initTextures()
{
	this->textures["PLAYER_SHEET"].loadFromFile("Resources/Sprites/Player/spriteSheet.png");
	this->textures["RED_SLIME_SHEET"].loadFromFile("Resources/Sprites/Slime/Slime_Medium_Red.png");
}

void GameState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->pauseMenufont);
	this->pauseMenu->addButton("QUIT", 600.f, "Quit");
	this->pauseMenu->addButton("RESUME", 400.f, "Resume");
}

void GameState::initPlayers()
{
	this->player = new Player(800, 669, this->textures["PLAYER_SHEET"],sf::Vector2f(3,3),33,2,1000,10,10,5,50);
}
void GameState::initEntities()
{
	this->slimeRed = new Slime(300, 300, this->textures["RED_SLIME_SHEET"], sf::Vector2f(20, 20),4,4,100,2,0,5,50);
}
void GameState::initGUI()
{
	this->Time = new gui::textbox(1100, 30, 200, 50, sf::Color::White,
		"Time : "+std::to_string((int)this->clock.getElapsedTime().asSeconds()),
		&this->pauseMenufont, 30, sf::Color::Black);
	this->Score = new gui::textbox(1300, 30, 200, 50, sf::Color::White,
		"Score :" + std::to_string(this->scoretime + this->scoreenemy),
		&this->pauseMenufont, 30, sf::Color::Black);
}
void GameState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	if (!this->backgroundTexture.loadFromFile("Resources/BackGround/GamestateBackground.png")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD BACKGROUND TEXTURE");
	}
	this->background.setTexture(&backgroundTexture);
}

void GameState::checkEndgame()
{
	if (this->player->checkDeath()) {
		this->elapsed = this->clock.getElapsedTime();
		if (this->temp == sf::seconds(0.f)) this->temp = this->elapsed;
		if (this->elapsed - this->temp >= sf::seconds(5.f)) {
			this->endState(); //<--- go to leaderboard
		}
	}
}

GameState::GameState(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys, std::stack<State*>* states) 
	: State(window,supportedKeys,states),hour(0),minutes(0),second(0),scoretime(0),scoreenemy(0)
{
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
	this->initEntities();
	this->initGUI();
	this->initBackground();

}

GameState::~GameState()
{
	delete this->slimeRed;
	delete this->player;
	delete this->pauseMenu;
}



//functions
void GameState::UpdateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime()) {
		if (!this->pause)	this->pauseState();
		else				this->unpauseState();
	}
}

void GameState::UpdatePlayerInput(const float& deltaTime)
{
	if (this->player->DisableInput()) return;
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move( -1.f, 0.f,deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move( 1.f, 0.f,deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("JUMP1"))) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("JUMP2"))))
		this->player->move(0.f, -400.f, deltaTime);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CROUCH"))))
		this->player->move(0.f, 1.f, deltaTime);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->player->Attack();
	}
	// check if hp works
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) && this->getKeytime()) {
		this->player->setstat("MAXHP",this->player->getstat("MAXHP") + 10);
		this->player->Attacked();
	}
}

void GameState::UpdatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT")) {
		this->endState();
	}
	else if (this->pauseMenu->isButtonPressed("RESUME")) {
		this->unpauseState();
	}
}

void GameState::UpdateGUI(const float& deltaTime)
{
	hour = (int)this->clock.getElapsedTime().asSeconds() / 3600;
	minutes = (int)this->clock.getElapsedTime().asSeconds() / 60;
	second = (int)(this->clock.getElapsedTime().asSeconds()) % 60;
	this->time.clear();
	if (hour >= 10) this->time += std::to_string(hour);
	else this->time += "0" + std::to_string(hour);
	this->time += ":";
	if (minutes >= 10) this->time += std::to_string(minutes);
	else this->time += "0" + std::to_string(minutes);
	this->time += ":";
	if (second >= 10) this->time += std::to_string(second);
	else this->time += "0" + std::to_string(second);

	this->Time->settext("Time : " + time);

	this->scoretime = (int)this->clock.getElapsedTime().asSeconds() * 5;
	this->Score->settext("Score : " + std::to_string(this->scoretime + this->scoreenemy));
}

void GameState::Update(const float& deltaTime)
{
	this->UpdateMousePositions();
	this->UpdateInput(deltaTime);
	this->UpdateKeytime(deltaTime);
	this->UpdateGUI(deltaTime);
	
	if (!this->pause) { // Update game state
		this->UpdatePlayerInput(deltaTime);

		// =================== slime hit player ========================
		if (this->slimeRed->intersect(this->player->getHitboxGlobalbound())) {
			this->player->setstat("HP", this->player->getstat("HP") - this->slimeRed->getstat("ATK"));
			this->player->Attacked();
			this->checkEndgame();
		}
		// player hit slime
		if (this->slimeRed->intersect(this->player->getAttackHitboxGlobalbound())) {
			this->slimeRed->setstat("HP", this->slimeRed->getstat("HP") - this->player->getstat("ATK"));
			this->slimeRed->Attacked();
			if (this->slimeRed->checkDeath()) {
				this->scoreenemy += 100;

			}
		}
		// ==============================================================
		this->player->Update(deltaTime);
		if(this->slimeRed) this->slimeRed->Update(deltaTime,this->player->getPosition());

	}
	else {// Update pause state
		this->pauseMenu->Update(this->mousePosView);
		this->UpdatePauseMenuButtons();
	}
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	target->draw(this->background);

	this->player->Render(*target,true);
	if(this->slimeRed) this->slimeRed->Render(*target,true);

	this->Time->Render(*target);
	this->Score->Render(*target);

	if (this->pause) {
		this->pauseMenu->Render(*target);
	}
}
