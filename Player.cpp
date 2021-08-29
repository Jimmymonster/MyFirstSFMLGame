#include "Player.h"

void Player::initVariables()
{
	this->attacking = false;
	this->Isattacked = false;
	this->attackhitboxComponent = nullptr;
	this->animationComponent = nullptr;
	this->hitboxComponent = nullptr;
	this->knockback = false;
	this->finishdeath = false;
	this->disableInput = false;
}

void Player::initGUI()
{
	this->HPbar = new gui::bar(40, 40, 200, 20, this->stat["HP"], this->stat["MAXHP"], &this->font, 26, sf::Color::Black, sf::Color::Red, sf::Color::White, true);
	this->Rampagebar = new gui::bar(40, 61, 200, 20, 0, 100, &this->font, 26, sf::Color::Black, sf::Color::Magenta, sf::Color::White);
}

void Player::initComponents()
{
	//this->createMovementComponent(200.f,15.f,4.f);
	//this->createAnimationComponent(this->sprite, this->textureSheet);
	//this->animationComponent->addAnimation("IDLE_LEFT", 100.f, 1, 1, 3, 1, 23, 11);
}
void Player::AddAnimations()
{
	this->animationComponent->addAnimation("RUN", 15.f, 25, 1, 30, 1);
	this->animationComponent->addAnimation("JUMP", 12.f, 21, 1, 24, 1);
	this->animationComponent->addAnimation("DROP", 5.f, 8, 1, 9, 1);
	this->animationComponent->addAnimation("CROUCH", 15.f, 30, 0, 0, 1);
	this->animationComponent->addAnimation("SLIDE", 10.f, 31, 1, 32, 1);
	this->animationComponent->addAnimation("DIE", 30.f, 1, 1, 7, 1);
	this->animationComponent->addAnimation("ATTACK1", 15.f, 13, 0, 17, 0);
	this->animationComponent->addAnimation("ATTACK2", 15.f, 18, 0, 23, 0);
	this->animationComponent->addAnimation("ATTACK3", 15.f, 24, 0, 29, 0);
	this->animationComponent->addAnimation("AIR_ATTACK1", 15.f, 3, 0, 6, 0);
	this->animationComponent->addAnimation("AIR_ATTACK2", 15.f, 7, 0, 9, 0);
	this->animationComponent->addAnimation("AIR_ATTACK3", 15.f, 0, 0, 2, 0);
	this->animationComponent->addAnimation("AIR_ATTACK_DROP", 15.f, 10, 0, 11, 0);
	this->animationComponent->addAnimation("AIR_ATTACK_DROP_END", 15.f, 12, 0, 12, 0);
	this->animationComponent->addAnimation("HURT", 30.f, 1, 1, 3, 1);
	//make sure idle is last added animation
	this->animationComponent->addAnimation("IDLE", 15.f, 13, 1, 16, 1);
}

Player::Player(float x, float y, sf::Texture& textureSheet, sf::Vector2f scale, int imgx, int imgy,
	float maxhp, float atk, float defense, float criRate, float cridamage)
	: x(x),y(y),scale(scale)
{
	this->initVariables();
	this->stat["HP"] = maxhp;
	this->stat["MAXHP"] = maxhp;
	this->stat["DEFENSE"] = defense;
	this->stat["ATK"] = atk;
	this->stat["CRIRATE"] = criRate;
	this->stat["CRIDAMAGE"] = cridamage;

	this->initfont();
	this->initGUI();

//	this->setTexture(textureSheet);
	this->spriteSetPosition(x, y);

	this->createHitboxComponent(this->sprite,-15,-23,30.f,73.f);
	//this->attackhitboxComponent = new HitboxComponent(this->sprite, 1000, 1000, 55.f, 100.f);
	this->createMovementComponent(300.f, 20.f, 10.f);
	this->createAnimationComponent(textureSheet ,scale,imgx,imgy);
	this->AddAnimations();
	
}

Player::~Player()
{
	delete this->attackhitboxComponent;
}

//================================ function ==============================

void Player::flip() // <-- suppose to be update function
{
	//flip
	if (this->movementComponent->getState(MOVING_RIGHT)) {
		this->hitboxComponent->movepos(10, 0, 0, 0);
		this->sprite.setScale(this->scale);
	}
	else if (this->movementComponent->getState(MOVING_LEFT)) {
		this->hitboxComponent->movepos(-10, 0, 0, 0);
		this->sprite.setScale(-this->scale.x, this->scale.y);
	}
}

void Player::Attacked()
{
	this->Isattacked = true;
}

void Player::Attack()
{
	this->attacking = true;
}
//===========================================================================

const float Player::getRampage() const
{
	return this->Rampagebar->getValue();
}

const bool Player::DisableInput() const
{
	return this->disableInput;
}

void Player::setRampage(float value)
{
	this->Rampagebar->setValue(value);
}

//========================= Update stuff ====================================
void Player::UpdateAnimation(const float& deltaTime)
{
	if (this->death) {
		if (this->finishdeath) { 
			this->sprite.setTextureRect(sf::IntRect(350,37,50,37));
			return; 
		}
		else if (this->animationComponent->play("DIE", deltaTime, true)) {
			this->finishdeath = true;
		}
		if (this->finishdeath) {
			this->sprite.setTextureRect(sf::IntRect(350, 37, 50, 37));
		}
		return;
	}

	if(!Isattacked)
		this->flip();

	// Attacked
	if (this->Isattacked) {
		this->attackhitboxComponent = nullptr;
		this->attacking = false;
		this->time1 = sf::seconds(0);
		this->clock.restart();
		if (this->sprite.getScale().x<0) {
			if (!this->knockback) { // knockback variable make sure to knockback 1 time
				this->movementComponent->setveclocity(sf::Vector2f(0, 0));
				this->move(10, -200, deltaTime);
				this->knockback = true;
				this->disableInput = true;
			}
			this->attackhitboxComponent = nullptr;
			if (this->animationComponent->play("HURT", deltaTime, true)) {
				this->Isattacked = false;
				this->knockback = false;
				this->disableInput = false;
			}
		}
		else {
			if (!this->knockback) {
				this->movementComponent->setveclocity(sf::Vector2f(0, 0));
				this->move(-10, -200, deltaTime);
				this->knockback = true;
				this->disableInput = true;
			}
			this->attackhitboxComponent = nullptr;
			if (this->animationComponent->play("HURT", deltaTime, true)) {
				this->Isattacked = false;
				this->knockback = false;
				this->disableInput = false;
			}
		}
	}
	//Attack
	else if (this->attacking) {
		this->hitboxComponent->movepos(0, 0, 0, 0);
		if(!this->movementComponent->getState(MID_AIR)) this->disableInput = true;
		elapsed = clock.getElapsedTime();

		if (time1 == sf::seconds(0)) time1 = elapsed;

//		std::cout << this->time1.asSeconds()<<" "<< this->elapsed.asSeconds() << std::endl;

		if (elapsed-time1 >= sf::seconds(0.2f)) {
			if (sprite.getScale().x < 0) this->attackhitboxComponent = new HitboxComponent(this->sprite, -20, -55, -55.f, 100.f);
			else this->attackhitboxComponent = new HitboxComponent(this->sprite, 20, -55, 55.f, 100.f);
		}
		if (elapsed - time1 >= sf::seconds(0.4f)) {
			this->attackhitboxComponent = nullptr;
			this->disableInput = false;
		}
		//check if attack is done
		if (this->animationComponent->play("ATTACK1", deltaTime, true)) {
			this->attacking = false;
			this->time1 = sf::seconds(0);
		}
	}
	//================================ not priority animation =================================
	if (this->movementComponent->getState(CROUCH)) {
		this->hitboxComponent->movepos(0, 20, 0, -20);
		this->animationComponent->play("CROUCH", deltaTime);
	}
	else if (this->movementComponent->getState(IDLE)) {
		this->hitboxComponent->movepos(0, 0, 0, 0);
		this->animationComponent->play("IDLE", deltaTime);
	}
	else if (this->movementComponent->getState(DROP)) {
		this->hitboxComponent->movepos(0, 0, 0, 0);
		this->animationComponent->play("DROP", deltaTime);
	}
	else if (this->movementComponent->getState(JUMP)) {
		this->hitboxComponent->movepos(0, 0, 0, 0);
		this->animationComponent->play("JUMP", deltaTime);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT)) {
		this->animationComponent->play("RUN", deltaTime, this->movementComponent->getVeclocity().x, this->movementComponent->getMaxVeclocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT)) {
		this->animationComponent->play("RUN", deltaTime, this->movementComponent->getVeclocity().x, this->movementComponent->getMaxVeclocity());
	}

}

void Player::UpdateGUI(const float& deltaTime)
{
	this->HPbar->Update();
	this->Rampagebar->Update();
}

void Player::Update(const float& deltaTime)
{
	this->movementComponent->Update(deltaTime);
	this->UpdateGUI(deltaTime);
	//Check collistion for player
	if (this->sprite.getPosition().x < 30) {
		this->sprite.setPosition(30, this->sprite.getPosition().y);
	}
	else if (this->sprite.getPosition().x > 1570) {
		this->sprite.setPosition(1570, this->sprite.getPosition().y);
	}
	//play

	this->UpdateAnimation(deltaTime);

	this->hitboxComponent->Update();
	if (this->attackhitboxComponent != nullptr) {
		this->attackhitboxComponent->Update();
	}
}
