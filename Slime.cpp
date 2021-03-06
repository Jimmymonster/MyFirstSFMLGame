#include "Slime.h"

void Slime::initVariables()
{
	this->isattacked = false;
	this->knockback = false;
	this->temp = false;
	this->jump = false;
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
		this->time += 7.5*deltaTime;
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
	
	this->createHitboxComponent(this->sprite, -20.f/3.f*scale.x, -20.f/3.f*scale.y, 40.f/3.f*scale.x, 35.f/3.f*scale.y);
	this->createMovementComponent(800.f, 800.f, 400.f);
	this->createAnimationComponent(textureSheet, scale, imgx, imgy);
	barx = this->sprite.getPosition().x - this->sprite.getGlobalBounds().width / 2.f;
	bary = this->getHitboxGlobalbound().top - 10;
	this->createHpbar(barx,bary ,scale);
	this->AddAnimations();
	
}
Slime::~Slime()
{

}

void Slime::Attacked(float x,float y)
{
	this->isattacked = true;
	this->knockbackX = x;
	this->knockbackY = y;
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

const bool Slime::getJump() const
{
	return this->jump;
}

void Slime::UpdateGUI()
{
	barx = this->sprite.getPosition().x - 5 * this->scale.x;
	bary = this->getHitboxGlobalbound().top - 10;
	this->HPbar->Update();
	
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
	if (!this->movementComponent->getState(MID_AIR)) {
		this->jump = false;
	}

	if (!this->isattacked)
		this->flip();
	if (this->isattacked) {
		this->time = 0;
		if (!this->invincible) this->elapsed = this->clock.getElapsedTime();
		this->invincible = true;
		if (playerPos.x < this->sprite.getPosition().x) {
			if (!this->knockback) {
				this->movementComponent->setveclocity(sf::Vector2f(knockbackX, -knockbackY));
				//this->move(1, -200, deltaTime);
				this->knockback = true;
			}
			if (!this->movementComponent->getState(MID_AIR)) {
				this->isattacked = false;
				this->knockback = false;
			}
		}
		else {
			if (!this->knockback) {
				this->movementComponent->setveclocity(sf::Vector2f(-knockbackX, -knockbackY));
				//this->move(-1, -200, deltaTime);
				this->knockback = true;
			}
			if (!this->movementComponent->getState(MID_AIR)) {
				this->isattacked = false;
				this->knockback = false;
			}
		}
	}
	if (this->clock.getElapsedTime() - this->elapsed >= sf::seconds(0.3)) {
		this->invincible = false;
	}
	this->UpdateAnimation(deltaTime);
	if (!this->death) {
		this->hitboxComponent->Update();
		if (playerPos.x > this->sprite.getPosition().x && !this->movementComponent->getState(MID_AIR) && this->getdelay()) {
			this->move(1, -300, deltaTime);
			if (this->sprite.getPosition().x > 0 && this->sprite.getPosition().x < 1600) {
				this->jump = true;
			}
		}
		else if (playerPos.x < this->sprite.getPosition().x && !this->movementComponent->getState(MID_AIR) && this->getdelay()) {
			this->move(-1, -300, deltaTime);
			if (this->sprite.getPosition().x > 0 && this->sprite.getPosition().x < 1600) {
				this->jump = true;
			}
		}
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
void Slime::Render(sf::RenderTarget& target, sf::Shader* shader, bool showhitbox)
{
	shader->setUniform("hasTexture", true);
	target.draw(this->sprite, shader);

	if (this->hitboxComponent && showhitbox)
		hitboxComponent->Render(target);

	if (this->HPbar && this->stat["HP"] < this->stat["MAXHP"])
		HPbar->Render(target);
}