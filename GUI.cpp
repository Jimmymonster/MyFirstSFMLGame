#include "GUI.h"

gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
	sf::Color outlineidleColor, sf::Color outlinehoverColor, sf::Color outlineactiveColor,
	short unsigned id
	)
{
	this->id = id;
	this->hover = false;
	this->pressed = false;
	this->buttonState = BTN_IDLE;

	//shape
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	//text
	this->text_idle_color = text_idle_color;
	this->text_hover_color = text_hover_color;
	this->text_active_color = text_active_color;

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	sf::FloatRect textRect = this->text.getLocalBounds();
	this->text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	this->text.setPosition(
		x+(width/2.f),
		y+(height/2.f)	);

	//texture
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->outlineidleColor = outlineidleColor;
	this->outlinehoverColor = outlinehoverColor;
	this->outlineactiveColor = outlineactiveColor;
	
	this->shape.setFillColor(this->idleColor);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outlineidleColor);
}

gui::Button::~Button()
{
}

//Accessors
const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE) {
		return true;
	}
	return false;
}

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned& gui::Button::getId() const
{
	return this->id;
}

//Modifiers
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

//function
void gui::Button::Update(sf::Vector2f mousePos)
{
	//Update booleans for hover and pressed

	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->buttonState = BTN_HOVER;

		//Click
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = BTN_ACTIVE;
		}
	}
	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->text_idle_color);
		this->shape.setOutlineColor(this->outlineidleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->text_hover_color);
		this->shape.setOutlineColor(this->outlinehoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->text_active_color);
		this->shape.setOutlineColor(this->outlineactiveColor);
		break;
	//default:
	//	break;
	}
}

void gui::Button::Render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}


//=============================  DROP DOWN LIST  ===================================

gui::dropdownlist::dropdownlist(float x,float y,float width,float height,
	sf::Font &font,std::string list[], 
	unsigned nrOfElements,unsigned default_index)
	:font(font) ,showList(false),keytimeMax(10.f),keytime(0.f)
{
	//unsigned nrOfElements = sizeof(list) / sizeof(std::string);
	this->activeElement = new gui::Button(x, y , width, height,
		&this->font, list[default_index], 40,
		sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 20)
	);

	for (size_t i = 0; i < nrOfElements; i++) {
		this->list.push_back(
			new gui::Button(x, y + ((i+1)*height), width, height,
				&this->font, list[i], 40,
				sf::Color::White, sf::Color::White, sf::Color::White,
				sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
				sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
				i
			));
	}
	
}

gui::dropdownlist::~dropdownlist()
{
	delete this->activeElement;
	for (size_t i = 0; i < this->list.size(); i++) {
		delete this->list[i];
	}
}

const bool gui::dropdownlist::getkeyTime()
{
	if (this->keytime >= this->keytimeMax) {
		this->keytime = 0.f;
		return true;
	}
	return false;
}

void gui::dropdownlist::UpdateKeytime(const float& deltaTime)
{
	if (this->keytime < this->keytimeMax) {
		this->keytime += 50.f * deltaTime;
	}
}

void gui::dropdownlist::Update(sf::Vector2f mousePos, const float& deltaTime)
{
	this->UpdateKeytime(deltaTime);

	this->activeElement->Update(mousePos);
	
	if (this->activeElement->isPressed() && this->getkeyTime()) {
		if (this->showList == false) this->showList = true;
		else if(this->showList == true) this->showList = false;
	}

	if (this->showList) {
		for (auto& it : this->list) {
			it->Update(mousePos);
			if (it->isPressed() && this - getkeyTime()) {
				this->showList = false;
				this->activeElement->setText(it->getText());
				this->activeElement->setId(it->getId());
			}
		}
	}
}

void gui::dropdownlist::Render(sf::RenderTarget& target)
{
	this->activeElement->Render(target);

	if (this->showList) {
		for (auto &i:this->list) {
			i->Render(target);
		}
	}
}

//========================== BAR ===========================

gui::bar::bar(float x, float y, float width, float height,
	float value, float Max_value, 
	sf::Font* font,unsigned textsize, sf::Color text_color,
	sf::Color value_color, sf::Color Max_value_color, bool showtext
)
	:value_color(value_color),Max_value_color(Max_value_color),value(value),Max_value(Max_value),width(width),height(height),x(x),y(y),showtext(showtext)
{
	this->percent = value / Max_value;

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setCharacterSize(textsize);
	this->text.setFillColor(text_color);
	this->text.setString(std::to_string(int(value)) + "/" + std::to_string(int(Max_value)));
	sf::FloatRect textRect = this->text.getLocalBounds();
	this->text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	this->text.setPosition(
		x + (width / 2.f),
		y + (height / 2.f));

	this->value_shape.setPosition(x, y);
	this->value_shape.setFillColor(this->value_color);
	this->value_shape.setSize(sf::Vector2f(width*this->percent,height));

	this->Max_value_shape.setPosition(x + this->percent * width, y);
	this->Max_value_shape.setFillColor(this->Max_value_color);
	this->Max_value_shape.setSize(sf::Vector2f(width*(1-this->percent),height));
}

gui::bar::~bar()
{
}

const float &gui::bar::getValue() const
{
	return this->value;
}

const float &gui::bar::getMaxValue() const
{
	return this->Max_value;
}

void gui::bar::setPosition(float x, float y)
{
	this->value_shape.setPosition(x, y);
	this->x = x;
	this->y = y;
}

void gui::bar::setValue(float x)
{
	this->value = x;
}

void gui::bar::setMaxValue(float x)
{
	this->Max_value = x;
}

void gui::bar::Update()
{
	if (this->value <= 0) this->value = 0;
	if (this->value > this->Max_value) this->value = this->Max_value;
	this->percent = this->value / this->Max_value;
	this->value_shape.setSize(sf::Vector2f(this->width * this->percent, this->height));
	this->Max_value_shape.setSize(sf::Vector2f(this->width * (1 - this->percent), this->height));
	this->Max_value_shape.setPosition(this->x + this->percent * width, this->y);

	this->text.setString(std::to_string(int(value)) + "/" + std::to_string(int(Max_value)));
	sf::FloatRect textRect = this->text.getLocalBounds();
	this->text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	this->text.setPosition(
		x + (width / 2.f),
		y + (height / 2.f));
}

void gui::bar::Render(sf::RenderTarget& target)
{
	target.draw(this->value_shape);
	target.draw(this->Max_value_shape);
	if(this->showtext)
		target.draw(this->text);
}

//============================== TEXTBOX ============================

gui::textbox::textbox(float x, float y, float width, float height,
	sf::Color box_color, std::string text,
	sf::Font* font, unsigned textsize, sf::Color text_color)
	:x(x),y(y),width(width),height(height),box_color(box_color),font(font),text_color(text_color)
{
	this->box.setPosition(x, y);
	this->box.setSize(sf::Vector2f(width, height));
	this->box.setFillColor(box_color);

	this->text.setFont(*this->font);
	this->text.setCharacterSize(textsize);
	this->text.setFillColor(text_color);
	this->text.setString(text);
	sf::FloatRect textRect = this->text.getLocalBounds();
	this->text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	this->text.setPosition(
		x + (width / 2.f),
		y + (height / 2.f));

}

gui::textbox::~textbox()
{
}

void gui::textbox::settext(std::string text)
{
	this->text.setString(text);
	sf::FloatRect textRect = this->text.getLocalBounds();
	this->text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	this->text.setPosition(
		x + (width / 2.f),
		y + (height / 2.f));
}

void gui::textbox::Update()
{
}

void gui::textbox::Render(sf::RenderTarget& target)
{
	target.draw(this->box);
	target.draw(this->text);
}
