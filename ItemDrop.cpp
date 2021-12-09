#include "ItemDrop.h"

void ItemDrop::initVariables()
{
	this->pickUp = false;
	this->moved = false;
}

void ItemDrop::initComponents()
{
}

ItemDrop::ItemDrop(float x, float y, sf::Texture& textrueSheet, sf::Vector2f scale, std::string type, float percent)
	:x(x), y(y), scale(scale), type(type), percent(percent)
{
	this->initVariables();
	this->initComponents();
	this->setTexture(textrueSheet);

	this->spriteSetPosition(x-50, y-50);
	this->sprite.setScale(this->scale);

	this->createHitboxComponent(this->sprite, 0, 0, 37, 37);
	this->createMovementComponent(100000.f, 100.f, 50.f);
	
}

ItemDrop::~ItemDrop()
{

}

const std::string& ItemDrop::getType() const
{
	return this->type;
}

const float& ItemDrop::getpercent() const
{
	return this->percent;
}

void ItemDrop::setpickUp(bool value)
{
	this->pickUp = value;
}

void ItemDrop::Update(const float& deltaTime)
{
	this->movementComponent->Update(deltaTime);
	this->hitboxComponent->Update();

	if (!this->moved) {
		if (rand() % 2 == 1) {
			this->movementComponent->setveclocity(sf::Vector2f(-300,-600));
		}
		else {
			this->movementComponent->setveclocity(sf::Vector2f(300, -600));
		}
		this->moved = true;
	}

	//Check collistion for item
	if (this->sprite.getPosition().x < 30) {
		this->sprite.setPosition(30, this->sprite.getPosition().y);
	}
	else if (this->sprite.getPosition().x > 1570) {
		this->sprite.setPosition(1570, this->sprite.getPosition().y);
	}

	if (this->pickUp) {
		this->hitboxComponent = nullptr;
	}
}

void ItemDrop::Render(sf::RenderTarget& target, sf::Shader* shader, bool showhitbox)
{
	shader->setUniform("hasTexture", true);
	target.draw(this->sprite, shader);

	if (this->hitboxComponent && showhitbox)
		hitboxComponent->Render(target);

	if (this->HPbar && this->stat["HP"] < this->stat["MAXHP"])
		HPbar->Render(target);
}