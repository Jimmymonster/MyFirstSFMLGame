#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite,sf::RectangleShape *hitbox,
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), hitbox(hitbox),
	maxVelocity(maxVelocity),acceleration(acceleration), deceleration(deceleration)
{
	this->onfloor = false;
	this->jump = false;
	this->crouch = false;
	this->jumpHeight = 0;
}
MovementComponent::~MovementComponent()
{
}

//Accessor
const sf::Vector2f& MovementComponent::getVeclocity() const
{
	return this->velocity;
}

const float& MovementComponent::getMaxVeclocity() const
{
	return this->maxVelocity;
}

void MovementComponent::setveclocity(sf::Vector2f veclocity)
{
	this->velocity = veclocity;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0.f) {
			return true;
		}
		break;
	case MOVING_LEFT:
		if (this->velocity.x < 0.f) {
			return true;
		}
		break;
	case MOVING_RIGHT:
		if (this->velocity.x > 0.f) {
			return true;
		}
		break;
	case JUMP:
		if (this->velocity.y < 0.f) {
			return true;
		}
		break;
	case DROP:
		if (this->velocity.y > 0.f) {
			return true;
		}
		break;
	case CROUCH:
		if (this->crouch) {
			return true;
		}
		break;
	case MID_AIR:
		if (!this->onfloor) {
			return true;
		}
		break;
	}
	return false;
}

void MovementComponent::push(const float x, const float y)
{
	this->velocity.x += this->acceleration * x;
	this->velocity.y = y * 3;
}

void MovementComponent::move(const float x, const float y,const float deltaTime)
{
	//Acceleration
	this->velocity.x += this->acceleration*x;
	if (y < 0) this->jump = true;
	else if (y > 0) {
		this->crouch = true;
	}
	this->jumpHeight = y;
}

//function
void MovementComponent::Update(const float& deltaTime)
{
	//gravity (acceleration * scale)
	this->velocity.y += 9.80665f*3;
	//floor
	if (this->hitbox->getPosition().y + this->hitbox->getGlobalBounds().height >= 705.f) {
		this->velocity.y = 0;
	}
	//check if on floor
	if (this->velocity.y != 0) this->onfloor = false;
	else this->onfloor = true;

	//crouch
	if (!this->onfloor || velocity.x) this->crouch = false;
	//slide
	if (this->crouch) {
	}

	//jump
	if (!this->onfloor) this->jump = false;
	if (this->jump) {
		this->jump = false;
		this->crouch = false;
		this->velocity.y = jumpHeight* 3;
	}

	//X Positive
	
	if (this->velocity.x > 0.f) {
		//Max Velocity Check
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = maxVelocity;
		//Deceleration
		if(this->onfloor)
			this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f) this->velocity.x = 0;
	}
	//X Negative
	else if (this->velocity.x < 0.f) {
		//Max Velocity Check
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -maxVelocity;
		//Deceleration
		if (this->onfloor)
			this->velocity.x += deceleration;
		if (this->velocity.x > 0.f) this->velocity.x = 0;
	}
	
	//Final move
	this->sprite.move(this->velocity * deltaTime);
}