#pragma once
#include<iostream>
#include<string>
#include<map>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
class AnimationComponent
{
private:
	class Animation
	{
	public:
		//variable
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		float timer;
		bool done;
		int imgy;
		int imgx;
		int width;
		int height;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;

		Animation(sf::Sprite& sprite, sf::Texture& texture_Sheet, sf::Vector2f scale,
			float animationTimer,
			int stFrameX, int stFrameY, int frameX, int frameY, int imgx, int imgy)
			:sprite(sprite), textureSheet(texture_Sheet),
			animationTimer(animationTimer), imgx(imgx), imgy(imgy), timer(0.f), done(false)
		{
			this->width = this->textureSheet.getSize().x / imgx;
			this->height = this->textureSheet.getSize().y / imgy;
			this->startRect = sf::IntRect(stFrameX * width, stFrameY * height, width, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(frameX * width, frameY * height, width, height);
			
			this->sprite.setOrigin(float(width)/2.f, float(height)/2.f);
			this->sprite.setScale(scale);
			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
		}
		
		//Accessor
		const bool& isDone()const { return this->done; }

		//function
		const bool &play(const float& deltaTime) {
			//Update timer
			this->done = false;
			this->timer += 100.f * deltaTime;
			if (this->timer >= this->animationTimer) {
				//reset timer
				this->timer = 0.f;
				if (this->currentRect != this->endRect) {
					this->currentRect.left += this->width;
				}
				else {
					this->currentRect = this->startRect;
					this->done = true;
				}

				this->sprite.setTextureRect(this->currentRect);

				//change row
				if (this->currentRect.left == (imgx - 1) * width && this->currentRect != this->endRect) {
					this->currentRect.left = 0;
					this->currentRect.top += height;
				}
				//std::cout << currentRect.left << " " << currentRect.top << std::endl;
			}
			return this->done;
		}
		const bool &play(const float& deltaTime, float percentage) {
			//Update timer
			this->done = false;
			percentage = abs(percentage);
			if (percentage < 0.5f) percentage = 0.5f;
			this->timer += percentage * 100.f * deltaTime;
			if (this->timer >= this->animationTimer) {
				//reset timer
				this->timer = 0.f;
				if (this->currentRect != this->endRect) {
					this->currentRect.left += this->width;
				}
				else {
					this->currentRect = this->startRect;
					this->done = true;
				}

				this->sprite.setTextureRect(this->currentRect);

				//change row
				if (this->currentRect.left == (imgx - 1) * width && this->currentRect != this->endRect) {
					this->currentRect.left = 0;
					this->currentRect.top += height;
				}
				//std::cout << currentRect.left << " " << currentRect.top << std::endl;
			}
			return this->done;
		}
		void reset() {
			this->timer = this->animationTimer;
			this->currentRect = this->startRect;
		}
	};

	sf::Sprite& sprite;
	sf::Texture& textrueSheet;
	sf::Vector2f scale;
	int imgx, imgy;
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;
	Animation* priorityAnimation;

public:
	AnimationComponent(sf::Sprite& sprite,sf::Texture& texture_Sheet, sf::Vector2f scale, int imgx, int imgy);
	virtual ~AnimationComponent();
	//Accessor
	const bool& isDone(const std::string key);
	//function
	void addAnimation(const std::string key,
		float animationTimer,
		int stFrameX,int stFrameY, int frameX,  int frameY);

	const bool& play(const std::string key,const float& deltaTime, const bool priority = false);
	const bool& play(const std::string key,const float& deltaTime,const float& modifier,const float& modifier_max, const bool priority = false);
};

