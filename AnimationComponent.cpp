#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_Sheet, sf::Vector2f scale, int imgx, int imgy)
	: sprite(sprite), textrueSheet(texture_Sheet), scale(scale), imgx(imgx), imgy(imgy), lastAnimation(nullptr), priorityAnimation(nullptr)
{
}

AnimationComponent::~AnimationComponent()
{
	for (auto& it : this->animations) {
		delete it.second;
	}
}

//Accessors
const bool& AnimationComponent::isDone(const std::string key)
{
	return this->animations[key]->isDone();
}

//function
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

const bool& AnimationComponent::play(const std::string key,const float& deltaTime,const bool priority)
{
	if (priority) {
		this->priorityAnimation = this->animations[key];
	}
	if (this->priorityAnimation) { //If there is priority animation
		if (this->priorityAnimation == this->animations[key]) {
			//check if need to reset animation form last animation
			if (this->lastAnimation != this->animations[key]) {
				if (this->lastAnimation == nullptr) {
					this->lastAnimation = this->animations[key];
				}
				else {
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}
			// remove priorityAnimation
			if (this->animations[key]->play(deltaTime)) {
				this->priorityAnimation = nullptr;
			}
		}
	}
	else {
		//check if need to reset animation form last animation
		if (this->lastAnimation != this->animations[key]) {
			if (this->lastAnimation == nullptr) {
				this->lastAnimation = this->animations[key];
			}
			else {
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(deltaTime);
	}

	return this->animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float& deltaTime, const float& modifier, const float& modifier_max, const bool priority)
{
	if (priority) {
		this->priorityAnimation = this->animations[key];
	}
	if (this->priorityAnimation) { //If there is priority animation
		if (this->priorityAnimation == this->animations[key]) {
			//check if need to reset animation form last animation
			if (this->lastAnimation != this->animations[key]) {
				if (this->lastAnimation == nullptr) {
					this->lastAnimation = this->animations[key];
				}
				else {
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}
			// remove priorityAnimation
			if (this->animations[key]->play(deltaTime, (modifier / modifier_max))) {
				this->priorityAnimation = nullptr;
			}
		}
	}
	else {
		if (this->lastAnimation != this->animations[key]) {
			if (this->lastAnimation == nullptr) {
				this->lastAnimation = this->animations[key];
			}
			else {
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(deltaTime, (modifier / modifier_max));
	}
	return this->animations[key]->isDone();
}
