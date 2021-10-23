#pragma once
#include"include.h"
class pFirefly
{
private:
	struct Particle
	{
		sf::Vector2f position;
		float speed;
		sf::Time lifetime;
		float previousAngle;
	};
	sf::Time lifeTime;
	std::vector<Particle> particles;
	std::vector<sf::CircleShape> fireflies;
	sf::Texture texture;

public:
	pFirefly(unsigned int count);
	~pFirefly();
	void resetParticle(std::size_t i);

	//Update
	void Update(const float deltatime);

	//Render
	void Render(sf::RenderTarget* target);
};


