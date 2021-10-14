#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite,
	float offset_x, float offset_y,
	float width, float height)
	: sprite(sprite), offsetX(offset_x), offsetY(offset_y), width(width), height(height), moveX(0), moveY(0), sizeX(0), sizeY(0)
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{
}

sf::RectangleShape* HitboxComponent::getHitbox()
{
	return &this->hitbox;
}


bool HitboxComponent::checkIntersect(const sf::FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::movepos(float x, float y,float sizeX,float sizeY)
{
	this->moveX = x;
	this->moveY = y;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}

void HitboxComponent::setpos(float x, float y)
{
	this->hitbox.setPosition(x, y);
}

void HitboxComponent::Update()
{
	//bug fix if my entity struck on floor
	if (this->hitbox.getPosition().y + this->hitbox.getGlobalBounds().height > 735.f) {
		this->sprite.setPosition(this->sprite.getPosition().x,730.f - height - offsetX - moveX);
	}
	//========================
	this->hitbox.setPosition(this->sprite.getPosition().x + offsetX + moveX, this->sprite.getPosition().y + offsetY + moveY);
	this->hitbox.setSize(sf::Vector2f(this->width + sizeX, this->height + sizeY));
	this->moveX = this->moveY = this->sizeX = this->sizeY = 0;
}

void HitboxComponent::Render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
