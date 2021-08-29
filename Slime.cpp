#include "Slime.h"

void Slime::initVariables()
{
	this->isattacked = false;
	this->knockback = false;
	this->temp = false;
}

void Slime::initComponents()
{
}

void Slime::AddAnimations()
{
	this->animationComponent->addAnimation("JUMP", 10.f, 0, 1, 3, 1);
	this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 3, 0);
}

const bool Slime::getdelay()
{
	if (this->time >= this->timeMax) {
		this->time = 0;
		return true;
	}
	return false;
}

void Slime::Updatedelay(const float& deltaTime)
{
	if (this->time < this->timeMax) {
		this->time += 10*deltaTime;
	}
}

Slime::Slime(float x, float y, sf::Texture& textureSheet, sf::Vector2f scale, int imgx, int imgy,
	float maxhp, float atk, float defense, float criRate, float cridamage)
	:x(x),y(y),scale(scale),time(0.f),timeMax(10.f)
{
	this->initVariables();
	this->initfont();
	this->stat["HP"] = maxhp;
	this->stat["MAXHP"] = maxhp;
	this->stat["DEFENSE"] = defense;
	this->stat["ATK"] = atk;
	this->stat["CRIRATE"] = criRate;
	this->stat["CRIDAMAGE"] = cridamage;

	this->spriteSetPosition(x, y);
	
	this->createHitboxComponent(this->sprite, -20.f/3.f*scale.x, -20/3.f*scale.y, 40.f/3.f*scale.x, 35.f/3.f*scale.y);
	this->createMovementComponent(800.f, 800.f, 400.f);
	this->createAnimationComponent(textureSheet, scale, imgx, imgy);
	this->createHpbar(this->sprite.getPosition().x - this->sprite.getGlobalBounds().width / 2.f, this->getHitboxGlobalbound().top - 10,scale);
	this->AddAnimations();
	
}
Slime::~Slime()
{
	
}

void Slime::Attacked()
{
	this->isattacked = true;
}

void Slime::flip()
{
	//flip
	if (this->movementComponent->getState(MOVING_RIGHT)) {
		this->sprite.setScale(this->scale);
	}
	else if (this->movementComponent->getState(MOVING_LEFT)) {
		this->sprite.setScale(-this->scale.x, this->scale.y);
	}
}

void Slime::UpdateGUI()
{
	this->HPbar->Update();
	this->HPbar->setPosition(this->sprite.getPosition().x - 5 * this->scale.x, this->getHitboxGlobalbound().top-10);
}

void Slime::UpdateAnimation(const float& deltaTime)
{
	//======================== not priority animation ========================
	if (this->movementComponent->getState(IDLE)) {
		this->animationComponent->play("JUMP", deltaTime);
	}
	else if (this->movementComponent->getState(JUMP)) {
		this->animationComponent->play("JUMP", deltaTime);
	}
}

void Slime::Update(const float& deltaTime,sf::Vector2f playerPos)
{
	this->Updatedelay(deltaTime);
	this->UpdateGUI();
	this->movementComponent->Update(deltaTime);

	if (!this->isattacked)
		this->flip();
	if (this->isattacked) {
		this->time = 0;
		if (playerPos.x < this->sprite.getPosition().x) {
			if (!this->knockback) {
				this->movementComponent->setveclocity(sf::Vector2f(0, 0));
				this->move(1, -500, deltaTime);
				this->knockback = true;
			}
			if (this->animationComponent->play("JUMP", deltaTime, true)) {
				this->isattacked = false;
				this->knockback = false;
			}
		}
		else {
			if (!this->knockback) {
				this->movementComponent->setveclocity(sf::Vector2f(0, 0));
				this->move(-1, -500, deltaTime);
				this->knockback = true;
			}
			if (this->animationComponent->play("JUMP", deltaTime, true)) {
				this->isattacked = false;
				this->knockback = false;
			}
		}
	}
	this->UpdateAnimation(deltaTime);
	if (!this->death) {
		this->hitboxComponent->Update();
		if (playerPos.x > this->sprite.getPosition().x && !this->movementComponent->getState(MID_AIR) && this->getdelay()) this->move(1, -310, deltaTime);
		else if (playerPos.x < this->sprite.getPosition().x && !this->movementComponent->getState(MID_AIR) && this->getdelay()) this->move(-1, -310, deltaTime);
	}

	else if (this->death) {
		if (!this->temp) {
			this->hitboxComponent->setpos(0, 0);
			this->temp = true;
		}
		//std::cout << this->hitboxComponent->getHitbox()->getPosition().y << std::endl; <--- for dubuging
		//make sure to delete all component
	 	this->hitboxComponent = nullptr;
	}
	
}
