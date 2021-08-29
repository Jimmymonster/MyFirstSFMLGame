#pragma once
#include"include.h"

enum movementState{IDLE=0,MOVING_LEFT,MOVING_RIGHT,JUMP,DROP,CROUCH,SLIDE,MID_AIR};

class MovementComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape *hitbox;
	
	float maxVelocity;
	float acceleration;
	float deceleration;

	bool jump;
	bool crouch;
	bool onfloor;

	float jumpHeight;
	
	sf::Vector2f velocity;

	//function

public:
	MovementComponent(sf::Sprite& sprite,sf::RectangleShape *hitbox,
		float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const sf::Vector2f& getVeclocity() const;
	const float& getMaxVeclocity() const;
	//Modifier
	void setveclocity(sf::Vector2f veclocity);
	
	//function
	const bool getState(const short unsigned state) const;

	void push(const float x, const float y);
	void move(const float x, const float y,const float deltaTime);
	void Update(const float& deltaTime);
};

