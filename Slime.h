#pragma once
#include "Entity.h"
class Slime :
    public Entity
{
private:
	//variables
	sf::Vector2f scale;
	float x, y;
	float barx, bary;
	float time, timeMax;

	sf::Clock clock;
	sf::Time elapsed;
	sf::Time time1 = sf::seconds(0);

	bool isattacked;
	bool knockback;
	bool temp;
	bool jump;
	float knockbackX, knockbackY;

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
	void Attacked(float x, float y);
	void flip();
	//Accessor
	const bool getJump() const;

	// Modifier
	
	//Update stuff
	void UpdateGUI();
	void UpdateAnimation(const float& deltaTime);
	virtual void Update(const float& deltaTime, sf::Vector2f playerPos);

	//Render
	void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr, bool showhitbox = false);
};

