#include "Player.h"

void Player::initVariables()
{

}

void Player::initComponents()
{
	//this->createMovementComponent(200.f,15.f,4.f);
	//this->createAnimationComponent(this->sprite, this->textureSheet);
	//this->animationComponent->addAnimation("IDLE_LEFT", 100.f, 1, 1, 3, 1, 23, 11);
}

Player::Player(float x, float y, sf::Texture& textureSheet, sf::Vector2f scale, int imgx, int imgy)
{
	this->initVariables();
	this->scale = scale;
	 
//	this->setTexture(textureSheet);
	this->spriteSetPosition(x, y);

	this->createHitboxComponent(this->sprite,x-70,y-78,40.f,81.f);
	this->createMovementComponent(300.f, 20.f, 10.f);
	this->createAnimationComponent(textureSheet ,scale,imgx,imgy);

	this->animationComponent->addAnimation("RUN", 15.f, 23, 1, 28, 1);
	this->animationComponent->addAnimation("IDLE", 15.f, 11, 1, 14, 1);
	this->animationComponent->addAnimation("JUMP", 10.f, 19, 1, 22, 1);
	this->animationComponent->addAnimation("DROP", 5.f, 6, 1, 7, 1);
}

Player::~Player()
{
}

//function
void Player::Update(const float& deltaTime)
{
	this->movementComponent->Update(deltaTime);
	//flip
	if (this->movementComponent->getState(MOVING_RIGHT)) {
		this->hitboxComponent->movepos(10, 0);
		this->sprite.setScale(this->scale);
	}
	else if (this->movementComponent->getState(MOVING_LEFT)) {
		this->hitboxComponent->movepos(-10, 0);
		this->sprite.setScale(-this->scale.x, this->scale.y);
	}

	//play
	if (this->movementComponent->getState(IDLE)) {
		this->hitboxComponent->movepos(0, 0);
		this->animationComponent->play("IDLE", deltaTime);
	}
	else if (this->movementComponent->getState(DROP)) {
		this->animationComponent->play("DROP", deltaTime);
	}
	else if (this->movementComponent->getState(JUMP)) {
		this->animationComponent->play("JUMP", deltaTime);
	}
	else if(this->movementComponent->getState(MOVING_RIGHT)){
		this->animationComponent->play("RUN", deltaTime);
	}
	else if (this->movementComponent->getState(MOVING_LEFT)) {
		this->animationComponent->play("RUN", deltaTime);
	}
	

	this->hitboxComponent->Update();
}
