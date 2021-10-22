#include "SwordFall.h"

SwordFall::SwordFall(float x, float y, float velocity, sf::Texture& sheet)
	: x(x),y(y),velocity(velocity)
{
	this->scale = sf::Vector2f(0.0f, 0.0f);
	this->sprite.setTexture(sheet);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width/2.f,this->sprite.getGlobalBounds().height/2.f);
	this->sprite.setScale(this->scale);
	this->spriteSetPosition(x, y);
	this->createHitboxComponent(this->sprite, 0.f, 0.f, 50.f, 100.f);
	this->hitboxComponent->setcenter();
}

SwordFall::~SwordFall()
{
}

void SwordFall::Fall()
{
	this->Velocity.x = this->velocity * cos(this->angle * 22.f / 7.f / 180.f);
	this->Velocity.y = this->velocity * sin(this->angle * 22.f / 7.f / 180.f);
	this->fall = true;
}

HitboxComponent& SwordFall::getHitboxcomponent()
{
	return *this->hitboxComponent;
}

const bool& SwordFall::getReady() const
{
	return this->ready;
}

const bool& SwordFall::getFall() const
{
	return this->fall;
}

const bool& SwordFall::getPlaysound()
{
	if (this->playsound) {
		if (!this->first2) return false;
		this->first2 = false;
		return true;
	}
	return false;
}

const bool& SwordFall::getFloor()
{
	if (this->floor) {
		if (!this->first) return false;
		this->first = false;
		return true;
	}
	return false;
}
void SwordFall::Update(const float& deltatime, sf::Vector2f& mousePosView)
{
	this->elapse = this->clock.getElapsedTime();
	if (!ready) {
		if (this->elapse - this->chargeUpTime >= sf::seconds(0.02)) {
			this->chargeUpTime = this->elapse;
			this->chargeUpScale += 0.002;
			this->sprite.setScale(sf::Vector2f(this->chargeUpScale, this->chargeUpScale));
			if (this->chargeUpScale >= 0.15) {
				this->ready = true;
			}
		}
	}
	if (!fall) {
		this->sprite.rotate(360 - this->angle);
		this->hitboxComponent->rotate(360 - this->angle);
		this->angle = - (atan2((this->y - mousePosView.y), (mousePosView.x - this->x)) * 180.f * 7.f / 22.f);
		this->sprite.rotate(this->angle);
		this->hitboxComponent->rotate(this->angle);
	}
	if (fall) {
		if (this->sprite.getPosition().y <= 700) this->sprite.move(this->Velocity * deltatime);
		else this->floor = true;
		if (this->sprite.getPosition().y >= 300) this->playsound = true;
	}
}

void SwordFall::Render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	//this->hitboxComponent->Render(target);
}
