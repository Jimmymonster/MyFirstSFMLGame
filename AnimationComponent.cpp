#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_Sheet, sf::Vector2f scale, int imgx, int imgy)
	: sprite(sprite), textrueSheet(texture_Sheet), scale(scale), imgx(imgx), imgy(imgy), lastAnimation(nullptr)
{
}

AnimationComponent::~AnimationComponent()
{
	for (auto& it : this->animations) {
		delete it.second;
	}
}

void AnimationComponent::addAnimation(const std::string key,
	float animationTimer,
	int stFrameX, int stFrameY,int frameX,  int frameY)
{
	this->animations[key] = new Animation(
		this->sprite, this->textrueSheet, this->scale,
		animationTimer,
		stFrameX,stFrameY,frameX,frameY,imgx,imgy
	);
}

void AnimationComponent::play(const std::string key,const float& deltaTime)
{
	//check if need to reset animation form last animation
	if (this->lastAnimation != this->animations[key]) {
		if (this->lastAnimation == nullptr) {
			this->lastAnimation = this->animations[key];
		}
		else{
			this->lastAnimation->reset();
			this->lastAnimation = this->animations[key];
		}
	}
	this->animations[key]->play(deltaTime);
}
