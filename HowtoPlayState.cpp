#include "HowtoPlayState.h"

void HowtoPlayState::initKeybinds()
{
	std::ifstream ifs("Config/HowtoPlayState.ini.txt");
	if (ifs.is_open()) {
		std::string key = "", key2 = "";
		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void HowtoPlayState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/angsana.ttc")) {
		throw("ERROR::Leaderboard::COULD NOT LOAD FONT");
	}
}

void HowtoPlayState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	if (!this->backgroundTexture.loadFromFile("Resources/BackGround/LeaderboardBackground.jpg")) {
		throw("ERROR::Leaderboard::COULD NOT LOAD BACKGROUND TEXTURE");
	}
	this->background.setTexture(&backgroundTexture);
}

void HowtoPlayState::initGUI()
{
	this->text["HOWTOPLAY"] = new gui::textbox(600, 50, 400, 100,
		sf::Color(255, 255, 255, 255), "How to play",
		&this->font, 50, sf::Color::Black,
		nullptr, false);
	this->text["WASD"] = new gui::textbox(800, 200, 500, 75,
		sf::Color(255, 255, 255, 200), "Use W A S D to control player",
		&this->font, 30, sf::Color::Black,
		nullptr, false);
	this->text["SPACEBAR"] = new gui::textbox(800, 300, 500, 75,
		sf::Color(255, 255, 255, 200), "Press spacebar to jump",
		&this->font, 30, sf::Color::Black,
		nullptr, false);
	this->text["ATTACK"] = new gui::textbox(800, 400, 500, 75,
		sf::Color(255, 255, 255, 200), "Left click to attack up to 3 combos",
		&this->font, 30, sf::Color::Black,
		nullptr, false);
	this->text["WAVE"] = new gui::textbox(800, 500, 500, 75,
		sf::Color(255, 255, 255, 200), "Right click to unleash sword enegy with 8 sec cooldown",
		&this->font, 30, sf::Color::Black,
		nullptr, false);
	this->quitBTN = new gui::Button(650, 750, 300.f, 75.f,
		&this->font, "Quit", 50,
		sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

HowtoPlayState::HowtoPlayState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initFonts();
	this->initBackground();
	this->initGUI();
	this->textureSheet.loadFromFile("Resources/Sprites/Player/spriteSheet.png");
	for(int i=0;i<3;i++)	this->animationComponent[i] = new AnimationComponent(this->sprite[i], this->textureSheet, sf::Vector2f(3, 3), 33, 2);
	this->animationComponent[0]->addAnimation("RUN", 15.f, 25, 1, 30, 1);
	this->animationComponent[1]->addAnimation("JUMP", 15.f, 21, 1, 24, 1);
	this->animationComponent[2]->addAnimation("ATTACK", 15.f, 13 ,0, 29, 0);
	this->sprite[0].setPosition(sf::Vector2f(600, 220));
	this->sprite[1].setPosition(sf::Vector2f(600, 320));
	this->sprite[2].setPosition(sf::Vector2f(600, 420));
	this->Swordwave.loadFromFile("Resources/Sprites/Player/SwordBeam.png");
	this->sprite[3].setTexture(this->Swordwave);
	this->sprite[3].setScale(sf::Vector2f(0.2, 0.2));
	this->sprite[3].setPosition(sf::Vector2f(600, 500));

	this->squre.setFillColor(sf::Color(255,255,255,150));
	this->squre.setPosition(100, 100);
	this->squre.setSize(sf::Vector2f(1400, 600));
}

HowtoPlayState::~HowtoPlayState()
{
}

void HowtoPlayState::UpdateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime()) {
		this->endState();
	}
}

void HowtoPlayState::UpdateGUI(const float& deltaTime)
{
	this->quitBTN->Update(this->mousePosView);
	if (this->quitBTN->isPressed()) {
		this->endState();
	}
}

void HowtoPlayState::Update(const float& deltaTime)
{
	this->UpdateMousePositions();
	this->UpdateKeytime(deltaTime);
	this->UpdateInput(deltaTime);
	this->UpdateGUI(deltaTime);
	this->animationComponent[0]->play("RUN",deltaTime);
	this->animationComponent[1]->play("JUMP", deltaTime);
	this->animationComponent[2]->play("ATTACK", deltaTime);
}

void HowtoPlayState::Render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	target->draw(this->background);
	target->draw(this->squre);

	for (int i = 0; i < 4; i++) target->draw(this->sprite[i]);

	for (auto& it : this->text) {
		it.second->Render(*target);
	}
	this->quitBTN->Render(*target);
}
