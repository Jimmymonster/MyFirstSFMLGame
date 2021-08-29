#pragma once
#include"include.h"

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

namespace gui {
	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;

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
		sf::Color outlineidleColor;
		sf::Color outlinehoverColor;
		sf::Color outlineactiveColor;

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
			sf::Color outlineidleColor = sf::Color::Transparent, sf::Color outlinehoverColor = sf::Color::Transparent, sf::Color outlineactiveColor = sf::Color::Transparent, 
			short unsigned id = 0
		);
		~Button();

		//Accessors
		const bool isPressed() const;
		const std::string getText()const;
		const short unsigned& getId() const;

		//Modifiers
		void setText(const std::string text);
		void setId(const short unsigned id);

		//function
		void Update(sf::Vector2f mousePos);
		void Render(sf::RenderTarget& target);
	};

	//=============================  DROP DOWN LIST  ===================================

	class dropdownlist
	{
	private:
		float keytime;
		float keytimeMax;
		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;
	public:
		dropdownlist(float x, float y, float width, float height,
			sf::Font& font, std::string list[],
			unsigned nrOfElements, unsigned default_index = 0);
		~dropdownlist();
		//Accessor
		const bool getkeyTime();
		//function
		void UpdateKeytime(const float& deltaTime);
		void Update(sf::Vector2f mousePos, const float& deltaTime);
		void Render(sf::RenderTarget& target);
	};

	//========================== BAR ===========================

	class bar
	{
	private:
		float x;
		float y;
		float percent;
		float value;
		float Max_value;
		float width;
		float height;
		bool showtext;
		sf::Font* font;
		sf::Text text;
		sf::Color value_color;
		sf::Color Max_value_color;
		sf::RectangleShape Max_value_shape;
		sf::RectangleShape value_shape;

	public:
		bar(float x, float y, float width, float height,
			float value, float Max_value,
			sf::Font* font, unsigned textsize, sf::Color text_color,
			sf::Color value_color, sf::Color Max_value_color, bool showtext = false
		);
		~bar();
		//Accessor
		const float &getValue()const;
		const float &getMaxValue()const;
		//Modifier
		void setPosition(float x, float y);
		void setValue(float x);
		void setMaxValue(float x);
		//function
		void Update();
		void Render(sf::RenderTarget& target);
	};
	class textbox
	{
	private:
		float x;
		float y;
		float width;
		float height;
		sf::Color box_color;
		sf::Color text_color;
		sf::Font* font;
		sf::Text text;
		sf::RectangleShape box;
	public:
		textbox(float x, float y, float width, float height,
			sf::Color box_color, std::string text,
			sf::Font* font,unsigned textsize, sf::Color text_color);
		~textbox();
		//Accessor

		//Modifier
		void settext(std::string text);
		//function
		void Update();
		void Render(sf::RenderTarget& target);
	};
}

