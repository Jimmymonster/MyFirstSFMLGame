#include "Entity.h"

void Entity::initVariables()
{
	this->hitboxComponent = nullptr;
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
}

//Component function
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(sf::Sprite& sprite,float offset_x,float offset_y,float width,float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity,const float acceleration,const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity,acceleration,deceleration);
}

void Entity::createAnimationComponent( sf::Texture& textureSheet, sf::Vector2f scale, int imgx, int imgy)
{
	this->animationComponent = new AnimationComponent(this->sprite, textureSheet, scale,imgx,imgy);
}

void Entity::spriteSetPosition(const float x, const float y)
{
	this->sprite.setPosition(x,y);
}

//function
void Entity::move(const float x, const float y,const float &deltaTime)
{
	if (this->movementComponent) {
		this->movementComponent->move(x, y, deltaTime);
	}
}

void Entity::Update(const float& deltaTime)
{

}

void Entity::Render(sf::RenderTarget& target)
{

	target.draw(this->sprite);

	if (this->hitboxComponent)
		hitboxComponent->Render(target);
}
