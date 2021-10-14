#pragma once

#include"Entity.h"

class SwordWave:
	public Entity
{
private:
	float x, y;
	float velocity;

public:
	SwordWave(float x,float y,float velocity,sf::Texture& sheet,sf::Vector2f scale);
	virtual ~SwordWave();
	//Accessor
	HitboxComponent &getHitboxcomponent();

	//function
	void Update(const float& deltaTime);
	void Render(sf::RenderTarget& target);
};

