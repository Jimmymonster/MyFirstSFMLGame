#pragma once
#include "Entity.h"
class Player:
	public Entity
{
private:
	//variables
	sf::Vector2f scale;

	//function
	void initVariables();
	void initComponents();
public:
	//function
	Player(float x, float y, sf::Texture& textureSheet,sf::Vector2f scale,int imgx, int imgy);
	virtual ~Player();

	//functions
	virtual void Update(const float& deltaTime);
};

