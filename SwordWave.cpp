#include "SwordWave.h"

SwordWave::SwordWave(float x, float y, float velocity, sf::Texture& sheet, sf::Vector2f scale)
	:x(x), y(y), velocity(velocity)
{
	this->spriteSetPosition(x, y);
	this->createHitboxComponent(this->sprite, -20.f, -50.f, 40.f, 100.f);
	this->createMovementComponent(10000.f, 0.f, 0.f);
	this->createAnimationComponent(sheet, scale, 1, 1);
	this->animationComponent->addAnimation("slash", 100.f, 0, 0, 0, 0);
}

SwordWave::~SwordWave()
{
}

HitboxComponent& SwordWave::getHitboxcomponent()
{
	return *this->hitboxComponent;
}

void SwordWave::Update(const float& deltaTime)
{
	this->animationComponent->play("slash",deltaTime);
	this->movementComponent->Update(deltaTime);
	this->movementComponent->setveclocity(sf::Vector2f(this->velocity, -9.80665f * 3.f));
}

void SwordWave::Render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	//this->hitboxComponent->Render(target);
}
