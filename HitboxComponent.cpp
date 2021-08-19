#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite,
	float offset_x, float offset_y,
	float width, float height)
	: sprite(sprite), offsetX(offset_x), offsetY(offset_y)
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

bool HitboxComponent::checkIntersect(const sf::FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::movepos(float x, float y)
{
	this->moveX = x;
	this->moveY = y;
}

void HitboxComponent::Update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offsetX + moveX, this->sprite.getPosition().y + offsetY + moveY);
}

void HitboxComponent::Render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
