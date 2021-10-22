#pragma once

#include<iostream>
#include<ctime>
#include<cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float width;
	float height;
	float offsetX;
	float offsetY;
	float moveX;
	float moveY;
	float sizeX;
	float sizeY;
	bool floor = true;

public:
	HitboxComponent(sf::Sprite& sprite,
		float offset_x,float offset_y,
		float width,float height);
	virtual ~HitboxComponent();
	//Accessors
	sf::RectangleShape *getHitbox();

	//Modifier
	void setpos(float x, float y);
	void rotate(float degree);
	void setcenter(); //for sword fall
	//function
	bool checkIntersect(const sf::FloatRect& frect);
	void movepos(float x, float y,float sizeX,float sizeY);

	void Update();
	void Render(sf::RenderTarget& target);
};

