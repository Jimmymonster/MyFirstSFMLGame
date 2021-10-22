#pragma once
#include"include.h"
#include"GUI.h"

class NameInput
{
private:
	sf::Font& font;
	sf::Text text;

	sf::RectangleShape background;
	sf::RectangleShape container;

	sf::Texture texture;

	std::string name;

	std::map<std::string, gui::Button*> buttons;
	gui::textbox *inputname;

public:
	NameInput(sf::RenderWindow& window, sf::Font& font);
	virtual ~NameInput();
	//Modifier
	void setstring(std::string name);

	//Accessor
	std::map<std::string, gui::Button*>& getButtons();
	std::string& getstring();

	//function
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key,float x, float y, const std::string text);
	void Update(const sf::Vector2f& mousePos);
	void Render(sf::RenderTarget& target);
};

