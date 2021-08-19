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
		int imgy;
		int imgx;
		int width;
		int height;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;

		Animation(sf::Sprite& sprite, sf::Texture& texture_Sheet, sf::Vector2f scale,
			float animationTimer,
			int stFrameX,int stFrameY,int frameX,int frameY, int imgx,int imgy)
			:sprite(sprite), textureSheet(texture_Sheet), 
			animationTimer(animationTimer), imgx(imgx), imgy(imgy)
		{
			this->width = this->textureSheet.getSize().x / imgx;
			this->height = this->textureSheet.getSize().y / imgy;
			this->timer = 0.f;
			this->startRect = sf::IntRect(stFrameX * width, stFrameY * height, width, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(frameX * width, frameY * height, width, height);
			
			this->sprite.setOrigin(float(width)/2.f, float(height)/2.f);
			this->sprite.setScale(scale);
			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
		}
		
		//function
		void play(const float& deltaTime) {
			//Update timer
			this->timer += 100.f * deltaTime;
			if (this->timer >= this->animationTimer) {
				//reset timer
				this->timer = 0.f;
				if (this->currentRect != this->endRect) {
					this->currentRect.left += this->width;
				}
				else {
					this->currentRect.left = this->startRect.left;
				}

				this->sprite.setTextureRect(this->currentRect);
			}
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

public:
	AnimationComponent(sf::Sprite& sprite,sf::Texture& texture_Sheet, sf::Vector2f scale, int imgx, int imgy);
	virtual ~AnimationComponent();

	//function
	void addAnimation(const std::string key,
		float animationTimer,
		int stFrameX,int stFrameY, int frameX,  int frameY);

	void play(const std::string key,const float& deltaTime);
};

