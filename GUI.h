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

		//sound
		sf::Sound BTNsound;
		sf::SoundBuffer hoversound;
		sf::SoundBuffer clicksound;
		sf::Clock clock;
		sf::Time soundDelay;

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
			sf::Color outlineidleColor = sf::Color::Transparent, sf::Color outlinehoverColor = sf::Color::Transparent, sf::Color outlineactiveColor = sf::Color::Transparent,
			sf::Texture *texture = nullptr,
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
	class ButtonForMainmenu
	{
	private:
		short unsigned buttonState;
		unsigned hover_size;
		unsigned character_size;

		bool pressed;
		bool hover;

		sf::RectangleShape shape;

		sf::Font* font;
		sf::Text text;

		//texture
		sf::Color text_idle_color;
		sf::Texture glow;

		//sound
		sf::Sound BTNsound;
		sf::SoundBuffer clicksound;
		sf::Clock clock;
		sf::Time soundDelay;
	public:
		ButtonForMainmenu(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color,unsigned hover_size
		);
		~ButtonForMainmenu();
		//Accessors
		const bool isPressed() const;

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
		float &x;
		float &y;
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
		sf::RectangleShape texture;

	public:
		bar(float &x, float &y, float width, float height,
			float value, float Max_value,
			sf::Font* font, unsigned textsize, sf::Color text_color,
			sf::Color value_color, sf::Color Max_value_color, sf::Texture *texture = nullptr,
			bool showtext = false
		);
		~bar();
		//Accessor
		const float& getValue()const;
		const float& getMaxValue()const;
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
		sf::Color Outlinecolor;
		sf::Font* font;
		sf::Text text;
		sf::RectangleShape box;
		sf::Texture* texture;
		bool left;
	public:
		textbox(float x, float y, float width, float height,
			sf::Color box_color, std::string text,
			sf::Font* font, unsigned textsize, sf::Color text_color,
			sf::Texture* texture = nullptr, bool left = false,
			sf::Color Outlinecolor = sf::Color::Transparent, float outlineSize = 0.f
		);
		~textbox();
		//Accessor

		//Modifier
		void settext(std::string text);
		//function
		void Update();
		void Render(sf::RenderTarget& target);
	};
	class damageNumber
	{
	private:
		float x, y;
		float fade;
		sf::Color textColor;
		sf::Color OutlineTextColor;
		sf::Font* font;
		sf::Text text;
		sf::Clock clock;
		sf::Time delay;
	public:
		damageNumber(float x,float y,float damage,sf::Font* font,unsigned characterSize,unsigned outlineSize,
			sf::Color textColor,sf::Color OutlineTextColor);
		~damageNumber();
		//Accessor
		const bool remove();

		//function
		void Update(const float& deltaTime);
		void Render(sf::RenderTarget& target);
	};
}

