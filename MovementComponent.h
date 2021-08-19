#pragma once
#include"include.h"

enum movementState{IDLE=0,MOVING_LEFT,MOVING_RIGHT,JUMP,DROP};

class MovementComponent
{
private:
	sf::Sprite& sprite;
	
	float maxVelocity;
	float acceleration;
	float deceleration;
	bool jump;
	float jumpHeight;
	
	sf::Vector2f velocity;
	

	//function

public:
	MovementComponent(sf::Sprite& sprite,
		float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors

	//function
	const bool getState(const short unsigned state) const;

	void move(const float x, const float y,const float deltaTime);
	void Update(const float& deltaTime);
};

