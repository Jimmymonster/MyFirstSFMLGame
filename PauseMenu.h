#pragma once
#include"include.h"
#include"GUI.h"
class PauseMenu
{
private:
	sf::Font& font;
	sf::Text pauseMenuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

	//Private Functions
public:
	PauseMenu(sf::RenderWindow& window,sf::Font& font);
	virtual ~PauseMenu();

	//Accessor
	std::map<std::string, gui::Button*>& getButtons();

	//function
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key,float y, const std::string text);
	void Update(const sf::Vector2f& mousePos);
	void Render(sf::RenderTarget& target);
};