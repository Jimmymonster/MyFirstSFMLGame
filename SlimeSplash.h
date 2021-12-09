#pragma once
#include"include.h"
class SlimeSplash : public sf::Drawable
{
private:
	struct Particle{
		sf::Time lifeTime;
		sf::Vector2f velocity;
	};
	std::vector<Particle> particlesInfo;
	sf::VertexArray particles;
	float MaxSpeed;
	float MinSpeed;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
public:
	SlimeSplash(unsigned int count,sf::Color color,float MaxSpeed,float MinSpeed,bool faceRight);
	~SlimeSplash();

	//Update
	void Update(const float deltaTime);

	//Render
	//void Render(sf::RenderTarget* target);
};