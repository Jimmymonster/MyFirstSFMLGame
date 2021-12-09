#include "pFirefly.h"
pFirefly::pFirefly(unsigned int count, int adjust)
	:particles(count), lifeTime(sf::seconds(2.5f)), fireflies(count), adjust(adjust)
{
	texture.loadFromFile("Resources/UI/Particles/Firefly.png");
	for (std::size_t i = 0; i < particles.size(); ++i) {
		fireflies[i].setRadius(rand()%6+3);
		fireflies[i].setTexture(&texture);
	}
	
}

pFirefly::~pFirefly()
{
}

void pFirefly::resetParticle(std::size_t i)
{
	sf::Vector2i position(rand() % 1600, rand() % 400 + 500);
	if (position.x >= 400 && position.x <= 1200 && position.y<=700-adjust) position.x %= 400;
	particles[i].position = sf::Vector2f(position);
	particles[i].lifetime = sf::milliseconds(rand()%6000+4000);
	particles[i].speed = rand() % 25 + 25;
	fireflies[i].setRadius(rand() % 6 + 3);
}

void pFirefly::Update(const float& deltatime)
{
	for (std::size_t i = 0; i < particles.size(); ++i) {
		Particle& p = particles[i];
		p.lifetime -= sf::seconds(deltatime);
		if (p.lifetime <= sf::Time::Zero) {
			resetParticle(i);
		}
		
		float angle = rand() % 30 - 15 + p.previousAngle;
		particles[i].previousAngle = angle;
		particles[i].position.x += cos(angle * 22.f / 7.f / 180.f) * p.speed * deltatime;
		particles[i].position.y += sin(angle * 22.f / 7.f / 180.f) * p.speed * deltatime;
		fireflies[i].setPosition(particles[i].position);
		float ratio = p.lifetime / this->lifeTime;
		fireflies[i].setFillColor(sf::Color(255, 255, 255, 255 * ratio));
	}
}

void pFirefly::Render(sf::RenderTarget* target)
{
	for (std::size_t i = 0; i < particles.size(); ++i) {
		target->draw(this->fireflies[i]);
	}
}

