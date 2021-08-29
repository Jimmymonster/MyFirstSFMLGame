#pragma once
#include "Entity.h"
class Player:
	public Entity
{
private:
	//variables
	sf::Vector2f scale;
	bool attacking;
	bool Isattacked;
	bool knockback;
	bool finishdeath;
	bool disableInput;
	float x, y;

	sf::Clock clock;
    sf::Time elapsed;
	sf::Time time1 = sf::seconds(0);
	
	//function
	void initVariables();
	void initGUI();
	void initComponents();
	void AddAnimations();
public:
	//function
	Player(float x, float y, sf::Texture& textureSheet,sf::Vector2f scale,int imgx, int imgy,
		float maxhp,float atk,float defense,float criRate,float cridamage);
	virtual ~Player();

	//functions
	void flip();
	void Attacked();
	void Attack();

	//Accessor
	const float getRampage()const;
	const bool DisableInput()const;
	//Modifier
	void setRampage(float value);
	//Update stuff
	void UpdateAnimation(const float& deltaTime);
	void UpdateGUI(const float& deltaTime);
	virtual void Update(const float& deltaTime);
};

