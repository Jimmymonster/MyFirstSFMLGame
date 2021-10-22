#include "MainMenuState.h"

void MainMenuState::initVariable()
{
}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),static_cast<float>(this->window->getSize().y)));
	if (!this->backgroundTexture.loadFromFile("Resources/BackGround/Mainmenu.jpg")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD BACKGROUND TEXTURE");
	}
	this->background.setTexture(&backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Minecraft.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustateKeybinds.ini.txt");
	if (ifs.is_open()) {
		std::string key = "", key2 = "";
		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE_BTN"] = new gui::ButtonForMainmenu(110.f, 300.f, 300.f, 75.f,
		&this->font, "Start Game",30,
		sf::Color::White, 40);

/*	this->buttons["Setting_STATE_BTN"] = new gui::Button(70.f, 450.f, 300.f, 75.f,
		&this->font, "Settings",50,
		sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["EDITOR_STATE_BTN"] = new gui::Button(70.f, 550.f, 300.f, 75.f,
		&this->font, "Editor",50,
		sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));*/

	this->buttons["LEADERBOARD_STATE_BTN"] = new gui::ButtonForMainmenu(110.f, 400.f, 300.f, 75.f,
		&this->font, "Leader Board", 30,
		sf::Color::White,40);

	this->buttons["HOWTOPLAY_STATE_BTN"] = new gui::ButtonForMainmenu(110.f, 500.f, 300.f, 75.f,
		&this->font, "How to play", 30,
		sf::Color::White, 40);

	this->buttons["EXIT_STATE_BTN"] = new gui::ButtonForMainmenu(110.f, 600.f, 300.f, 75.f,
		&this->font, "Quit",30,
		sf::Color::White, 40);
}

void MainMenuState::initBGM()
{
	if (!this->bgm.openFromFile("Resources/Sounds/Mainmenu/Mili-Vulnerability.wav")) {
		throw("CANNOT LOAD BGM IN MAINMENU STATE");
	}
	this->bgm.setVolume(30.f);
	this->bgm.setLoop(true);
	this->bgm.play();
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariable();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initBackground();
	this->initBGM();
}
MainMenuState::~MainMenuState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
	
}

//functions

void MainMenuState::UpdateInput(const float& deltaTime)
{

}

void MainMenuState::UpdateBTN()
{
	//Update BTN and handle their function
	for (auto& it:this->buttons) {
		it.second->Update(this->mousePosView);
	}

	if (this->buttons["GAME_STATE_BTN"]->isPressed()) {
		this->states->push(new GameState(this->window, this->supportedKeys,this->states));
		this->bgm.stop();
	}

/*	if (this->buttons["Setting_STATE_BTN"]->isPressed()) {
		this->states->push(new SettingState(this->window, this->supportedKeys, this->states));
	}

	if (this->buttons["EDITOR_STATE_BTN"]->isPressed()) {
		this->states->push(new EditorState(this->window, this->supportedKeys, this->states));
	}*/

	if (this->buttons["LEADERBOARD_STATE_BTN"]->isPressed()) {
		this->states->push(new LeaderBoard(this->window, this->supportedKeys, this->states));
	}

	if (this->buttons["HOWTOPLAY_STATE_BTN"]->isPressed()) {
		this->states->push(new HowtoPlayState(this->window, this->supportedKeys, this->states));
	}

	if (this->buttons["EXIT_STATE_BTN"]->isPressed()) {
		this->endState();
	}
}

void MainMenuState::UpdateBGM()
{
	if (this->bgm.getStatus() == this->bgm.Stopped) {
		this->bgm.play();
	}
}


void MainMenuState::Update(const float& deltaTime)
{
	this->UpdateMousePositions();
	this->UpdateInput(deltaTime);
	this->UpdateBGM();
	this->UpdateBTN();
}

void MainMenuState::RenderBTN(sf::RenderTarget& target)
{
	for (auto& it : this->buttons) {
		it.second->Render(target);
	}
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	target->draw(this->background);

	this->RenderBTN(*target);


	
	//temporary check for mouse position
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x+10,this->mousePosView.y);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(20);
	std::stringstream ss;
	ss << this->mousePosView.x << " , " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);*/
}
