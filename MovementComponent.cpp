#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite,
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), 
	maxVelocity(maxVelocity),acceleration(acceleration), deceleration(deceleration)
{
	this->jump = false;
}
MovementComponent::~MovementComponent()
{
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
	}
	return false;
}

void MovementComponent::move(const float x, const float y,const float deltaTime)
{
	//Acceleration
	this->velocity.x += this->acceleration*x;
	if (y < 0 && velocity.y==0) this->jump = true;
	this->jumpHeight = y;
}

//function
void MovementComponent::Update(const float& deltaTime)
{
	//X Positive
	if (this->velocity.x > 0.f) {
		//Max Velocity Check
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = maxVelocity;
		//Deceleration
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f) this->velocity.x = 0;
	}
	//X Negative
	else if (this->velocity.x < 0.f) {
		//Max Velocity Check
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -maxVelocity;
		//Deceleration
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f) this->velocity.x = 0;
	}

	//gravity (acceleration * scale)
	this->velocity.y += 9.80665f*3;
	if (this->sprite.getPosition().y>=500) this->velocity.y = 0;
	if (this->jump && velocity.y == 0) {
		this->jump = false;
		this->velocity.y = -sqrtf(6*9.80665f  * -this->jumpHeight*100);
	}

	//Final move
	this->sprite.move(this->velocity * deltaTime);
}
