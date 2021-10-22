#pragma once

#include"HitboxComponent.h"
#include"MovementComponent.h"
#include"AnimationComponent.h"
#include"GUI.h"
class Entity
{
private:
	void initVariables();

protected:
		sf::Sprite sprite;

		std::map<std::string, float> stat;

		sf::Font font;

		bool death;
		bool invincible;

		HitboxComponent* hitboxComponent;
		MovementComponent* movementComponent;
		AnimationComponent* animationComponent;
		gui::bar* HPbar;
		
		
public:
	Entity();
	virtual ~Entity();

	//Component function
	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite,float offset_x,float offset_y,float width,float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& textureSheet, sf::Vector2f scale, int imgx, int imgy);
	void initfont();
	void createHpbar(float &x,float &y,sf::Vector2f scale);
	//Accessor
	virtual const sf::Vector2f &getPosition()const;
	const float getstat(std::string key);
	const bool checkDeath();
	const bool Invincible();
	const sf::FloatRect getHitboxGlobalbound()const;
	bool intersect(const sf::FloatRect& frect);
	//Modifier
	void setstat(std::string key, float value);
	//function
	virtual void spriteSetPosition(const float x, const float y);
	virtual void move(const float x, const float y, const float& deltaTime);

	virtual void Update(const float& deltaTime);
	virtual void Render(sf::RenderTarget& target, bool showhitbox = false);
};

