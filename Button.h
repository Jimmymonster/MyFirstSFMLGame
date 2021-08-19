#pragma once
#include"include.h"

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button
{
private:
	short unsigned buttonState;

	bool pressed;
	bool hover;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	//texture
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;
	sf::Color text_idle_color;
	sf::Color text_hover_color;
	sf::Color text_active_color;

public:
	Button(float x,float y,float width,float height,
		sf::Font* font,std::string text, unsigned character_size,
		sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
		sf::Color idleColor,sf::Color hoverColor,sf::Color activeColor);
	~Button();

	//Accessors
	const bool isPressed() const;

	//function
	void Update(sf::Vector2f mousePos);
	void Render(sf::RenderTarget& target);
};

