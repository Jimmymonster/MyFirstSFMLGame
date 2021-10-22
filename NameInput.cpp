#include "NameInput.h"

NameInput::NameInput(sf::RenderWindow& window, sf::Font& font)
	:font(font)
{
	//backgrond
	this->background.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y)));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	//container
	this->container.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x) - 60.f,
		static_cast<float>(window.getSize().y) - 60.f));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(
		static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
		30.f);

	//Init text
	this->text.setFont(font);
	this->text.setFillColor(sf::Color(255, 255, 255, 200));
	this->text.setCharacterSize(50);
	this->text.setString("Enter your name");
	this->text.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 80.f);

	this->name = "";
	this->inputname = new gui::textbox(500, 200, 600, 50, sf::Color::White,
		name,
		&this->font, 20, sf::Color::Black
	);
	this->texture.loadFromFile("Resources/UI/Btn2.png");
}

NameInput::~NameInput()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

void NameInput::setstring(std::string name)
{
	this->name = name;
}

std::map<std::string, gui::Button*>& NameInput::getButtons()
{
	return this->buttons;
}

std::string& NameInput::getstring()
{
	return this->name;
}

const bool NameInput::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void NameInput::addButton(const std::string key, float x,float y, const std::string text)
{
	float width = 70.f;
	float height = 70.f;
	this->buttons[key] = new gui::Button(x, y, width, height,
		&this->font, text, 20,
		sf::Color::Black, sf::Color::Black, sf::Color::Black,
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 220), sf::Color(200, 200, 200, 200),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
		&this->texture);
}

void NameInput::Update(const sf::Vector2f& mousePos)
{
	for (auto& it : this->buttons) {
		it.second->Update(mousePos);
	}
	this->inputname->settext(name);
}

void NameInput::Render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& i : this->buttons) {
		i.second->Render(target);
	}

	target.draw(this->text);
	inputname->Render(target);
}
