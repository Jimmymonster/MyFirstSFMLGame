#include "LeaderBoard.h"
void LeaderBoard::initKeybinds()
{
	std::ifstream ifs("Config/LeaderboardKeybinds.ini.txt");
	if (ifs.is_open()) {
		std::string key = "", key2 = "";
		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}
void LeaderBoard::initFonts()
{
	if (!this->font.loadFromFile("Fonts/angsana.ttc")) {
		throw("ERROR::Leaderboard::COULD NOT LOAD FONT");
	}
}
void LeaderBoard::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	if (!this->backgroundTexture.loadFromFile("Resources/BackGround/LeaderboardBackground.jpg")) {
		throw("ERROR::Leaderboard::COULD NOT LOAD BACKGROUND TEXTURE");
	}
	this->background.setTexture(&backgroundTexture);
}

void LeaderBoard::initGUI()
{
	this->leaderboard = new gui::textbox(600,100,400,100,sf::Color(255,255,255,100),
		"Leader Board",
		&this->font,70,sf::Color::Black
		);
	this->quitBTN= new gui::Button(650, 750, 300.f, 75.f,
		&this->font, "Quit", 50,
		sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

void LeaderBoard::initScore()
{
	std::ifstream ifs("Config/LeaderBoardScore.txt");
	if (ifs.is_open()) {
		std::string name;
		unsigned int score;
		for (int i = 0; i < 5; i++) {
			if (!(ifs >> name >> score)) return;
			this->playerscore[i] = new gui::textbox(300, 200+i*100, 1000, 100, sf::Color(255, 255, 255, 200),
				std::to_string(i+1) + "." + name + "    Score:" + std::to_string(score),
				&this->font, 50, sf::Color::Black
			);
		}
	}
	ifs.close();
}

LeaderBoard::LeaderBoard(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initFonts();
	this->initBackground();
	this->initGUI();
	this->initBackground();
	this->initScore();
}

LeaderBoard::~LeaderBoard()
{
	delete this->leaderboard;
	for (int i = 0; i < 5; i++)
		delete this->playerscore[i];
}

void LeaderBoard::UpdateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime()) {
		this->endState();
	}
}

void LeaderBoard::UpdateGUI(const float& deltaTime)
{
	//button
	this->quitBTN->Update(this->mousePosView);
	if (this->quitBTN->isPressed()) {
		this->endState();
	}
}

void LeaderBoard::Update(const float& deltaTime)
{
	this->UpdateMousePositions();
	this->UpdateKeytime(deltaTime);
	this->UpdateInput(deltaTime);
	this->UpdateGUI(deltaTime);
}

void LeaderBoard::Render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	target->draw(this->background);

	this->leaderboard->Render(*target);
	for (int i = 0; i < 5; i++) {
		if(this->playerscore[i])
			this->playerscore[i]->Render(*target);
	}

	this->quitBTN->Render(*target);
}
