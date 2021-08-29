#pragma once
#include "Entity.h"
class Slime :
    public Entity
{
private:
	//variables
	sf::Vector2f scale;
	float x, y;
	float time, timeMax;

	sf::Clock clock;
	sf::Time elapsed;
	sf::Time time1 = sf::seconds(0);

	bool isattacked;
	bool knockback;
	bool temp;

	//function
	void initVariables();
	void initComponents();
	void AddAnimations();
	const bool getdelay();
	void Updatedelay(const float &deltaTime);
public:
    Slime(float x, float y, sf::Texture& textureSheet, sf::Vector2f scale, int imgx, int imgy,
		float maxhp, float atk, float defense, float criRate, float cridamage);
    virtual ~Slime();
	//function
	void Attacked();
	void flip();

	//Update stuff
	void UpdateGUI();
	void UpdateAnimation(const float& deltaTime);
	virtual void Update(const float& deltaTime, sf::Vector2f playerPos);
};

