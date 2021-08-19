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
	float offsetX;
	float offsetY;
	float moveX;
	float moveY;

public:
	HitboxComponent(sf::Sprite& sprite,
		float offset_x,float offset_y,
		float width,float height);
	virtual ~HitboxComponent();

	//function
	bool checkIntersect(const sf::FloatRect& frect);
	void movepos(float x, float y);

	void Update();
	void Render(sf::RenderTarget& target);
};

