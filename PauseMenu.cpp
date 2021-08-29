#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	:font(font)
{
	//backgrond
	this->background.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x), 
		static_cast<float>(window.getSize().y)));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	//container
	this->container.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x)/4.f,
		static_cast<float>(window.getSize().y)-60.f));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(
		static_cast<float>(window.getSize().x)/2.f-this->container.getSize().x/2.f,
		30.f);

	//Init text
	this->pauseMenuText.setFont(font);
	this->pauseMenuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->pauseMenuText.setCharacterSize(100);
	this->pauseMenuText.setString("PAUSED");
	this->pauseMenuText.setPosition(
		this->container.getPosition().x+this->container.getSize().x/2.f-this->pauseMenuText.getGlobalBounds().width/2.f,
		this->container.getPosition().y+40.f);
}

PauseMenu::~PauseMenu()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

//function
const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, float y, const std::string text)
{
	float width = 250.f;
	float height = 50.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;
	this->buttons[key] = new gui::Button(x, y, width, height,
		&this->font, text , 50,
		sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

void PauseMenu::Update(const sf::Vector2f& mousePos)
{
	for (auto& it : this->buttons) {
		it.second->Update(mousePos);
	}
}

void PauseMenu::Render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& i : this->buttons) {
		i.second->Render(target);
	}

	target.draw(this->pauseMenuText);
}
