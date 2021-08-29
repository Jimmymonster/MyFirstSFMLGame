#include "SettingState.h"

void SettingState::initVariable()
{
}

void SettingState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	if (!this->backgroundTexture.loadFromFile("Resources/BackGround/Mainmenu.jpg")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD BACKGROUND TEXTURE");
	}
	this->background.setTexture(&backgroundTexture);
}

void SettingState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/angsana.ttc")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void SettingState::initKeybinds()
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

void SettingState::initGUI()
{
	this->buttons["APPLY"] = new gui::Button(800, 700, 200.f, 75.f,
		&this->font, "Apply", 50,
		sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE_BTN"] = new gui::Button(1050, 700, 200.f, 75.f,
		&this->font, "Back", 50,
		sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	std::string li[] = { "1920x1080" , "1600x900"  ,"1280x720" };
	this->dropdownlists["RESOLUTION"] = new gui::dropdownlist(700, 300, 200, 50, this->font, li, 3);

}

SettingState::SettingState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window,supportedKeys,states)
{
	this->initVariable();
	this->initFonts();
	this->initKeybinds();
	this->initGUI();
	this->initBackground();
}

SettingState::~SettingState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
	for (auto it = this->dropdownlists.begin(); it != this->dropdownlists.end(); ++it) {
		delete it->second;
	}
}

void SettingState::UpdateInput(const float& deltaTime)
{

}

void SettingState::UpdateGUI(const float& deltaTime)
{
	//Update BTN and handle their function
	for (auto& it : this->buttons) {
		it.second->Update(this->mousePosView);
	}

	if (this->buttons["APPLY"]->isPressed()) {
		
	}

	if (this->buttons["EXIT_STATE_BTN"]->isPressed()) {
		this->endState();
	}

	//dropdownlist
	for (auto &it :this->dropdownlists) {
		it.second->Update(mousePosView, deltaTime);
	}
}

void SettingState::Update(const float& deltaTime)
{
	this->UpdateMousePositions();
	this->UpdateInput(deltaTime);
	
	this->UpdateGUI(deltaTime);
}

void SettingState::RenderGUI(sf::RenderTarget& target)
{
	for (auto& it : this->buttons) {
		it.second->Render(target);
	}

	for (auto& it : this->dropdownlists) {
		it.second->Render(target);
	}
}

void SettingState::Render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	target->draw(this->background);

	this->RenderGUI(*target);

	//temporary check for mouse position
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x+10,this->mousePosView.y);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(20);
	std::stringstream ss;
	ss << this->mousePosView.x << " , " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}
