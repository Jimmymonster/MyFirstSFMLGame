#include "Entity.h"

void Entity::initVariables()
{
	this->hitboxComponent = nullptr;
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
	this->death = false;
	this->invincible = false;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->HPbar;
}

//Component function
//===============================================================================================
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(sf::Sprite& sprite,float offset_x,float offset_y,float width,float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity,const float acceleration,const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, this->hitboxComponent->getHitbox(),maxVelocity,acceleration,deceleration);
}

void Entity::createAnimationComponent( sf::Texture& textureSheet, sf::Vector2f scale, int imgx, int imgy)
{
	this->animationComponent = new AnimationComponent(this->sprite, textureSheet, scale,imgx,imgy);
}

void Entity::initfont()
{
	if (!this->font.loadFromFile("Fonts/angsana.ttc")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}
void Entity::createHpbar(float x,float y,sf::Vector2f scale)
{
	this->HPbar = new gui::bar(x, y, 10*scale.x, 10, this->stat["HP"], this->stat["MAXHP"], &this->font, 26, sf::Color::Black, sf::Color::Red, sf::Color::White);
}

//========================================================================================
const sf::Vector2f &Entity::getPosition() const
{
	return this->sprite.getPosition();
}

const float Entity::getstat(std::string key)
{
	return this->stat[key];
}


const bool Entity::checkDeath()
{
	if (this->stat["HP"]<=0) {
		this->death = true;
		return true;
	}
	return false;
}
const bool Entity::Invincible()
{
	return this->invincible;
}
const sf::FloatRect Entity::getHitboxGlobalbound() const
{
	if (this->hitboxComponent) return this->hitboxComponent->getHitbox()->getGlobalBounds();
	else return sf::FloatRect(0, 0, 0, 0);
}
bool Entity::intersect(const sf::FloatRect& frect)
{
	if(this->hitboxComponent) return this->hitboxComponent->checkIntersect(frect);
	return false;
}

//=======================================================================================
void Entity::setstat(std::string key, float value)
{
	this->stat[key] = value;
	if(!key.compare("HP")) this->HPbar->setValue(value);
	else if(!key.compare("MAXHP")) this->HPbar->setMaxValue(value);

	if (this->stat[key] <= 0) this->stat[key] = 0;
}

void Entity::spriteSetPosition(const float x, const float y)
{
	this->sprite.setPosition(x,y);
}

//================================================================================
//function
void Entity::move(const float x, const float y,const float &deltaTime)
{
	if (this->movementComponent) {
		this->movementComponent->move(x, y, deltaTime);
	}
}

void Entity::Update(const float& deltaTime)
{

}

void Entity::Render(sf::RenderTarget& target, bool showhitbox)
{
	target.draw(this->sprite);

	if (this->hitboxComponent && showhitbox)
		hitboxComponent->Render(target);

	if (this->HPbar) 
		HPbar->Render(target);
}