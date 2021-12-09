#include "SlimeSplash.h"

void SlimeSplash::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = NULL;
	target.draw(particles, states);
}

SlimeSplash::SlimeSplash(unsigned int count, sf::Color color, float MaxSpeed, float MinSpeed,bool faceRight)
	:particles(sf::Points, count),particlesInfo(count),MaxSpeed(MaxSpeed),MinSpeed(MinSpeed)
{
	for (size_t i = 0; i < count; i++) {
		float angle = rand()%60;
		if (!faceRight) angle = 180 - angle;
		angle *= 22.f / 7.f / 180.f;
		float speed = (rand()%int(this->MaxSpeed-this->MinSpeed))+this->MinSpeed;
		particlesInfo[i].velocity = sf::Vector2f(cos(angle) * speed, sin(angle) * speed);
		particlesInfo[i].lifeTime = sf::microseconds(rand()%3000+2000);
	}
}

SlimeSplash::~SlimeSplash()
{
}

void SlimeSplash::Update(const float deltaTime)
{
	for (size_t i = 0; i < particlesInfo.size() ; i++) {
		Particle p = particlesInfo[i];
		p.lifeTime -= sf::seconds(deltaTime);
		if (p.lifeTime <= sf::Time::Zero) p.lifeTime = sf::Time::Zero;
		if (p.lifeTime <= sf::seconds(1.5f)) {
			float ratio = p.lifeTime.asSeconds() / 1.5f;
			particles[i].color.a = static_cast<sf::Uint8>(255*ratio);
		}
		particles[i].position += particlesInfo[i].velocity*deltaTime;
		particles[i].position.y += 9.80665f * 3;
	}
}

/*void SlimeSplash::Render(sf::RenderTarget* target)
{
	target->draw(particles);
}*/
