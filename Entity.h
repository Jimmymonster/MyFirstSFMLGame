#pragma once

#include"HitboxComponent.h"
#include"MovementComponent.h"
#include"AnimationComponent.h"
class Entity
{
private:
	void initVariables();

protected:
	sf::Sprite sprite;

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
public:
	Entity();
	virtual ~Entity();

	//Component function
	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite,float offset_x,float offset_y,float width,float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& textureSheet, sf::Vector2f scale, int imgx, int imgy);

	//function
	virtual void spriteSetPosition(const float x, const float y);
	virtual void move(const float x, const float y, const float& deltaTime);

	virtual void Update(const float& deltaTime);
	virtual void Render(sf::RenderTarget& target);
};
