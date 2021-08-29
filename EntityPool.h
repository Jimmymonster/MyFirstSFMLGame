#pragma once
#include "Slime.h"
class EntityPool
{
private:
	sf::Texture textrue;
	std::string type;
	float hp, atk, def, criTate, cridamage;

	static const int max_entities = 1e6;
	Entity entities[max_entities];
	Entity* first_var;
public:
	//need (texture type hp atk def criRate cridamage) 
	EntityPool();
	virtual ~EntityPool();

	//function
	void Update(const float& deltaTime);
	void Render(sf::RenderTarget& target);
};

