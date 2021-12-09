#include "Player.h"

void Player::initVariables()
{
	this->attacking = false;
	this->Isattacked = false;
	for (int i = 0; i < 5; i++) this->attackhitboxComponent[i] = nullptr;
	this->animationComponent = nullptr;
	this->hitboxComponent = nullptr;
	this->knockback = false;
	this->finishdeath = false;
	this->disableInput = false;
	this->onrampage = false;
	this->swordwaving = false;
	this->swordwaved = false;
	this->slide = false;
	this->attackIdx = 0;
	this->swordfalling = false;
	this->swordFall = nullptr;
	for (int i = 0; i < 3; i++) this->attackPlayed[i] = false;
	
	this->hpbar.left = this->hpbar.top = 40.f;
	this->hpbar.width = 500.f;
	this->hpbar.height = 30.f;
	this->rampagebar.left = 40.f;
	this->rampagebar.top = 80.f;
	this->rampagebar.width = 500.f;
	this->rampagebar.height = 30.f;
	this->swordskillbar.left = this->swordskillbar.top = 0.f;
	this->swordskillbar.width = 40.f;
	this->swordskillbar.height = 5.f;
	this->slidebar.left = this->slidebar.top = 0.f;
	this->slidebar.width = 40.f;
	this->slidebar.height = 5.f;

	bar.loadFromFile("Resources/UI/Bar/hpmanabar.png");
}

void Player::initGUI()
{
	this->HPbar = new gui::bar(this->hpbar.left, this->hpbar.top, this->hpbar.width, this->hpbar.height, this->stat["HP"], this->stat["MAXHP"], &this->font, 26, sf::Color::Black, sf::Color::Red, sf::Color::White, &bar);
	this->Rampagebar = new gui::bar(this->rampagebar.left, this->rampagebar.top, this->rampagebar.width, this->rampagebar.height, 0, 100, &this->font, 26, sf::Color::Black, sf::Color::Magenta, sf::Color::White, &bar);
	this->swordskill = new gui::bar(this->swordskillbar.left, this->swordskillbar.top, this->swordskillbar.width , this->swordskillbar.height, this->WaveSwordCooldown.asSeconds(), this->WaveSwordCooldown.asSeconds(), &this->font, 26, sf::Color::Black, sf::Color::Blue, sf::Color::White);
	this->slideBar = new gui::bar(this->slidebar.left, this->slidebar.top, this->slidebar.width, this->slidebar.height, 20.f, 20.f, &this->font, 26, sf::Color::Black, sf::Color(200,200,0,255), sf::Color::White);
}

void Player::initComponents()
{
	//this->createMovementComponent(200.f,15.f,4.f);
	//this->createAnimationComponent(this->sprite, this->textureSheet);
	//this->animationComponent->addAnimation("IDLE_LEFT", 100.f, 1, 1, 3, 1, 23, 11);
}
void Player::AddAnimations()
{
	this->animationComponent->addAnimation("RUN", 15.f, 25, 1, 30, 1);
	this->animationComponent->addAnimation("JUMP", 15.f, 21, 1, 24, 1);
	this->animationComponent->addAnimation("DROP", 5.f, 8, 1, 9, 1);
	this->animationComponent->addAnimation("CROUCH", 15.f, 30, 0, 0, 1);
	this->animationComponent->addAnimation("SLIDE", 10.f, 31, 1, 32, 1);
	this->animationComponent->addAnimation("DIE", 30.f, 1, 1, 7, 1);
	this->animationComponent->addAnimation("ATTACK1", 15.f, 13, 0, 17, 0);
	this->animationComponent->addAnimation("ATTACK2", 15.f, 18, 0, 23, 0);
	this->animationComponent->addAnimation("WAVE_SWORD", 15.f, 18, 0, 23, 0);
	this->animationComponent->addAnimation("ATTACK3", 15.f, 24, 0, 29, 0);
	this->animationComponent->addAnimation("AIR_ATTACK1", 15.f, 3, 0, 6, 0);
	this->animationComponent->addAnimation("AIR_ATTACK2", 15.f, 7, 0, 9, 0);
	this->animationComponent->addAnimation("AIR_ATTACK3", 15.f, 0, 0, 2, 0);
	this->animationComponent->addAnimation("AIR_ATTACK_DROP", 15.f, 10, 0, 11, 0);
	this->animationComponent->addAnimation("AIR_ATTACK_DROP_END", 15.f, 12, 0, 12, 0);
	this->animationComponent->addAnimation("HURT", 30.f, 1, 1, 3, 1);
	//make sure idle is last added animation
	this->animationComponent->addAnimation("IDLE", 15.f, 13, 1, 16, 1);
}

void Player::initSounds()
{
	this->buffer["SwordMiss"].loadFromFile("Resources/Sounds/Player/Sword/mixkit-fast-sword-whoosh-2792.wav");
	this->buffer["Walking"].loadFromFile("Resources/Sounds/Player/Walk/mixkit-footsteps-in-the-forest-ground-1230.wav");
	this->buffer["Hurt"].loadFromFile("Resources/Sounds/Player/BeingHit/minecraft_hit_soundmp3converter.wav");
	this->walksound.setBuffer(this->buffer["Walking"]);
	this->walksound.setVolume(30.f);
	//this->soundDelay["SwordMiss"] = sf::seconds(0.75f);
	this->swordFallSoundBuffer.loadFromFile("Resources/Sounds/Player/Sword/Knife-Stab-A10-www.fesliyanstudios.com.wav");
	this->swordFallSound.setBuffer(this->swordFallSoundBuffer);
	
	this->sound.setVolume(30.f);
}
Player::Player(float x, float y, sf::Texture& textureSheet, sf::Vector2f scale, int imgx, int imgy,
	float maxhp, float atk, float defense, float criRate, float cridamage)
	: x(x),y(y),scale(scale)
{
	this->initVariables();
	this->stat["HP"] = maxhp;
	this->stat["MAXHP"] = maxhp;
	this->stat["DEFENSE"] = defense;
	this->stat["ATK"] = atk;
	this->stat["CRIRATE"] = criRate;
	this->stat["CRIDAMAGE"] = cridamage;

	this->initfont();
	this->initGUI();
	this->initSounds();

//	this->setTexture(textureSheet);
	this->flame.loadFromFile("Resources/Sprites/Player/flame.png");
	this->flameAnima = new AnimationComponent(this->flameSprite,this->flame,sf::Vector2f(0.5f,0.5f),4,1);
	this->flameAnima->addAnimation("FLAME", 10.f, 0, 0, 3, 0);

	this->swordwavesheet.loadFromFile("Resources/Sprites/Player/SwordBeam.png");
	this->swordFallsheet.loadFromFile("Resources/Sprites/Player/SwordFall.png");

	this->spriteSetPosition(x, y);

	this->createHitboxComponent(this->sprite,-15.f,-20.f,30.f,70.f);
	//this->attackhitboxComponent = new HitboxComponent(this->sprite, 1000, 1000, 55.f, 100.f);
	this->createMovementComponent(300.f, 20.f, 10.f);
	this->createAnimationComponent(textureSheet ,scale,imgx,imgy);
	this->AddAnimations();
	
	
}

Player::~Player()
{
	for (int i = 0; i < 3; i++) {
		delete this->attackhitboxComponent[i];
	}
	delete this->Rampagebar;
}

//================================ function ==============================

void Player::flip() // <-- suppose to be update function
{
	//flip
	if (this->movementComponent->getState(MOVING_RIGHT)) {
		this->hitboxComponent->movepos(10, 0, 0, 0);
		this->sprite.setScale(this->scale);
	}
	else if (this->movementComponent->getState(MOVING_LEFT)) {
		this->hitboxComponent->movepos(-10, 0, 0, 0);
		this->sprite.setScale(-this->scale.x, this->scale.y);
	}
}

void Player::Attacked()
{
	if (this->invincible) return;
	this->Isattacked = true;
	this->invincible = true;
}

void Player::Attack()
{
	this->attacking = true;
}

void Player::playSound(std::string key)
{
	this->sound.stop();
	this->sound.resetBuffer();
	this->sound.setBuffer(this->buffer[key]);
	this->sound.play();

}
void Player::swordwave()
{
	if (this->movementComponent->getState(MID_AIR)) return;
	this->swordwaving = true;
}
void Player::swordfall()
{
	this->swordfalling = true;
}
void Player::Slide()
{
	if (this->movementComponent->getState(MID_AIR)) return;
	if (this->Isattacked) return;
	if (this->attacking) return;
	if (this->swordwaving) return;
	if (this->slide) return;
	this->slide = true;
}
//===========================================================================
const bool& Player::getSwordFallFloor() const
{
	if (!this->swordFall) return false;
	return this->swordFall->getFloor();
}

const float& Player::getRampage() const
{
	return this->Rampagebar->getValue();
}

const bool& Player::DisableInput() const
{
	return this->disableInput;
}
const bool& Player::onRampage()const
{
	return this->onrampage;
}
const sf::FloatRect Player::getAttackHitboxGlobalbound(int idx) const
{
	if (this->attackhitboxComponent[idx]) return this->attackhitboxComponent[idx]->getHitbox()->getGlobalBounds();
	else return sf::FloatRect(0, 0, 0, 0);
}
void Player::setRampage(float value)
{
	this->Rampagebar->setValue(value);
}
void Player::stopWalkSound()
{
	if (this->walksound.getStatus() == sf::Sound::Playing) {
		this->walksound.stop();
	}
}

const bool& Player::getSlide() const
{
	return this->slide;
}

//========================= Update stuff ====================================
void Player::UpdateAnimation(const float& deltaTime)
{
	if (this->onrampage) this->flameAnima->play("FLAME", deltaTime);

	if (this->death) {
		this->disableInput = true;
		this->attacking = false;
		for (int i = 0; i < 3; i++) this->attackhitboxComponent[i] = nullptr;

		if (this->finishdeath) { 
			this->sprite.setTextureRect(sf::IntRect(350,37,50,37));
			return; 
		}
		else if (this->animationComponent->play("DIE", deltaTime, true)) {
			this->finishdeath = true;
		}
		if (this->finishdeath) {
			this->sprite.setTextureRect(sf::IntRect(350, 37, 50, 37));
		}
		return;
	}

	if(!Isattacked)
		this->flip();

	if (clock.getElapsedTime() - this->time2 >= sf::seconds(1.3f)) {
		this->sprite.setColor(sf::Color::White);
		this->invincible = false;
	}
	//=============================================== Sword Falling ===========================================
	if (this->swordfalling && this->swordFall == nullptr) {
		this->swordFall = new SwordFall(this->sprite.getPosition().x, this->sprite.getPosition().y - 400, 3000.f, this->swordFallsheet);
	}
	if (this->attacking && this->swordFall && this->swordFall->getReady() && !this->swordFall->getFall()) {
		this->swordFall->Fall();
		this->swordFalldelayTime = this->elapsed;
		this->attackhitboxComponent[4] = &this->swordFall->getHitboxcomponent();
	}
	if (this->swordFall && this->swordFall->getFall()) {
		if (this->elapsed - this->swordFalldelayTime >= sf::seconds(2.f)) {
			this->swordFall = nullptr;
			this->swordfalling = false;
			this->attackhitboxComponent[4] = nullptr;
		}
	}
	//=============================================== Sword waving =====================================================================================
	if (this->swordwaving) {
		if (this->elapsed - this->swordWavedelayTime >= this->WaveSwordCooldown || (this->elapsed < this->WaveSwordCooldown && this->swordWavedelayTime == sf::seconds(0.f))) {
			this->attacking = false;
			this->disableInput = true;
			this->invincible = true;
			this->swordWavedelayTime = this->elapsed;
			this->playSound("SwordMiss");
		}
		if (this->disableInput) {
			if (this->animationComponent->play("WAVE_SWORD", deltaTime, true)) {
				this->disableInput = false;
				this->invincible = false;
				this->swordwaving = false;
			}
		}
		if (this->elapsed - this->swordWavedelayTime >= sf::seconds(0.4f)&&!this->swordwaved) {
			if (this->sprite.getScale().x > 0) this->swordWave = new SwordWave(this->sprite.getPosition().x, this->sprite.getPosition().y, 1000.f, this->swordwavesheet, sf::Vector2f(0.2f, 0.2f));
			else  this->swordWave = new SwordWave(this->sprite.getPosition().x, this->sprite.getPosition().y, -1000.f, this->swordwavesheet, sf::Vector2f(-0.2f, 0.2f));
			this->attackhitboxComponent[3] = &this->swordWave->getHitboxcomponent();
			this->swordwaved = true;
		}
	}
	
	if (this->elapsed - this->swordWavedelayTime >= sf::seconds(3.f)) {
		this->swordWave = nullptr;
		this->attackhitboxComponent[3] = nullptr;
		this->swordwaving = false;
		this->swordwaved = false;
	}
	//===================================================================================================================================================

	// Attacked
	if (this->Isattacked) {
		for(int i=0;i<3;i++) this->attackhitboxComponent[i] = nullptr;
		this->attacking = false;
		this->swordwaving = false;
		this->attackdelayTime = sf::seconds(0);
		this->time2 = this->clock.getElapsedTime();

		this->invincible = true;

		this->sprite.setColor(sf::Color(0, 0, 0, 100));
		if (this->sprite.getScale().x<0) {
			if (!this->knockback) { // knockback variable make sure to knockback 1 time
				this->movementComponent->setveclocity(sf::Vector2f(0, 0));
				this->move(10, -200, deltaTime);
				this->knockback = true;
				this->disableInput = true;
				this->playSound("Hurt");
			}
			for (int i = 0; i < 3; i++) this->attackhitboxComponent[i] = nullptr;
			if (this->animationComponent->play("HURT", deltaTime, true)) {
				this->Isattacked = false;
				this->knockback = false;
				this->disableInput = false;
			}
		}
		else {
			if (!this->knockback) {
				this->movementComponent->setveclocity(sf::Vector2f(0, 0));
				this->move(-10, -200, deltaTime);
				this->knockback = true;
				this->disableInput = true;
				this->playSound("Hurt");
			}
			for (int i = 0; i < 3; i++) this->attackhitboxComponent[i] = nullptr;
			if (this->animationComponent->play("HURT", deltaTime, true)) {
				this->Isattacked = false;
				this->knockback = false;
				this->disableInput = false;
			}
		}
	}
	//Attack
	else if (this->attacking) {
		this->hitboxComponent->movepos(0, 0, 0, 0);
		if(!this->movementComponent->getState(MID_AIR)) this->disableInput = true;

		if (attackdelayTime == sf::seconds(0)) {
			this->playSound("SwordMiss");
			attackdelayTime = elapsed;
		}

//		std::cout << this->time1.asSeconds()<<" "<< this->elapsed.asSeconds() << std::endl;

		//check if attack 1 is done
		if (attackIdx == 0) {
			if (elapsed - attackdelayTime >= sf::seconds(0.2f)) {
				this->invincible = true;
				if (sprite.getScale().x < 0) this->attackhitboxComponent[0] = new HitboxComponent(this->sprite, -20, -55, -50.f, 100.f);
				else this->attackhitboxComponent[0] = new HitboxComponent(this->sprite, 20, -55, 50.f, 100.f);
			}
			if (elapsed - attackdelayTime >= sf::seconds(0.4f)) {
				this->attackhitboxComponent[0] = nullptr;
				this->disableInput = false;
			}
			if(!this->attackPlayed[0]){
				if (this->animationComponent->play("ATTACK1", deltaTime, true)) {
					this->attacking = false;
					this->attackPlayed[0] = true;
					this->invincible = false;
				}
			}
			else {
				attackdelayTime = sf::seconds(0.f);
				this->attackIdx++;
			}
		}
		if (attackIdx == 1) {
			if (elapsed - attackdelayTime >= sf::seconds(0.3f)) {
				this->invincible = true;
				if (sprite.getScale().x < 0) this->attackhitboxComponent[1] = new HitboxComponent(this->sprite, -20, -35, -52.f, 80.f);
				else this->attackhitboxComponent[1] = new HitboxComponent(this->sprite, 20, -35, 52.f, 80.f);
			}
			if (elapsed - attackdelayTime >= sf::seconds(0.55f)) {
				this->attackhitboxComponent[1] = nullptr;
				this->disableInput = false;
			}
			if (!this->attackPlayed[1]) {
				if (this->animationComponent->play("ATTACK2", deltaTime, true)) {
					this->attacking = false;
					this->attackPlayed[1] = true;
					this->invincible = false;
				}
			}
			else {
				attackdelayTime = sf::seconds(0.f);
				this->attackIdx++;
			}
		}
		if (attackIdx == 2) {
			if (elapsed - attackdelayTime >= sf::seconds(0.2f)) {
				this->invincible = true;
				if (sprite.getScale().x < 0) this->attackhitboxComponent[2] = new HitboxComponent(this->sprite, 60, -10, -140.f, 55.f);
				else this->attackhitboxComponent[2] = new HitboxComponent(this->sprite, -60, -10, 140.f, 55.f);
			}
			if (elapsed - attackdelayTime >= sf::seconds(0.4f)) {
				this->attackhitboxComponent[2] = nullptr;
				this->disableInput = false;
			}
			if (!this->attackPlayed[2]) {
				if (this->animationComponent->play("ATTACK3", deltaTime, true)) {
					this->attacking = false;
					this->attackPlayed[2] = true;
					this->invincible = false;
				}
			}
			else {
				this->attacking = false;
				attackdelayTime = sf::seconds(0.f);
				this->attackIdx = 0;
				for (int i = 0; i < 3; i++) this->attackPlayed[i] = false;
			}
		}
	}
	if (elapsed - attackdelayTime >= sf::seconds(0.9f) && !this->attacking) {
		attackdelayTime = sf::seconds(0.f);
		this->attackIdx = 0;
		for (int i = 0; i < 3; i++) this->attackPlayed[i] = false;
	}
	
	//================================ not priority animation =================================
	if (this->movementComponent->getState(CROUCH)) {
		this->hitboxComponent->movepos(0, 20, 0, -20);
		this->animationComponent->play("CROUCH", deltaTime);
		this->flameSprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y);
	}
	else if (this->movementComponent->getState(IDLE)) {
		this->hitboxComponent->movepos(0, 0, 0, 0);
		this->animationComponent->play("IDLE", deltaTime);
		this->flameSprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y - 25);
	}
	else if (this->movementComponent->getState(DROP)) {
		this->hitboxComponent->movepos(0, 0, 0, 0);
		this->animationComponent->play("DROP", deltaTime);
		this->flameSprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y - 25);
	}
	else if (this->movementComponent->getState(JUMP)) {
		this->hitboxComponent->movepos(0, 0, 0, 0);
		this->animationComponent->play("JUMP", deltaTime);
		this->flameSprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y - 25);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT)) {
		this->animationComponent->play("RUN", deltaTime, this->movementComponent->getVeclocity().x, this->movementComponent->getMaxVeclocity());
		this->flameSprite.setPosition(this->sprite.getPosition().x+10, this->sprite.getPosition().y - 25);

		if (this->walksound.getStatus() != sf::Sound::Playing) {
			this->walksound.play();
		}
	}
	else if (this->movementComponent->getState(MOVING_LEFT)) {
		this->animationComponent->play("RUN", deltaTime, this->movementComponent->getVeclocity().x, this->movementComponent->getMaxVeclocity());
		this->flameSprite.setPosition(this->sprite.getPosition().x-10, this->sprite.getPosition().y - 25);

		if (this->walksound.getStatus() != sf::Sound::Playing) {
			this->walksound.play();
		}
	}
	//================================ Slide ==================================================
	if (this->slide) {
		if ((this->elapsed - this->slideCooldown >= sf::seconds(20.f) || (this->elapsed < sf::seconds(20.f) && this->slideCooldown == sf::seconds(0.f)))) {
			this->slideCooldown = this->elapsed;
			this->slideTime = this->elapsed;
			this->invincible = true;
			this->disableInput = true;
		}
		if (this->disableInput) {
			if (this->sprite.getScale().x > 0) this->sprite.move(sf::Vector2f(1000.f * deltaTime, 0)), this->flameSprite.setPosition(this->sprite.getPosition().x - 15, this->sprite.getPosition().y + 10);
			else this->sprite.move(sf::Vector2f(-1000.f * deltaTime, 0)), this->flameSprite.setPosition(this->sprite.getPosition().x + 15, this->sprite.getPosition().y + 10);
			this->animationComponent->play("SLIDE", deltaTime);
			if (this->elapsed - this->slideTime >= sf::seconds(0.5f)) {
				this->slide = false;
				this->invincible = false;
				this->disableInput = false;
			}
		}
	}
	//Sound
	if ((!this->movementComponent->getState(MOVING_LEFT) && !this->movementComponent->getState(MOVING_RIGHT)) || this->movementComponent->getState(MID_AIR) || this->checkDeath()) this->walksound.stop();
}

void Player::UpdateGUI(const float& deltaTime)
{
	this->HPbar->Update();
	this->Rampagebar->Update();
	if (this->elapsed - this->swordWavedelayTime <= this->WaveSwordCooldown && this->swordWavedelayTime != sf::seconds(0.f)) {
		this->swordskill->setValue((this->elapsed-this->swordWavedelayTime).asSeconds());
	}
	this->swordskillbar.left = this->getHitboxGlobalbound().left - 5;
	this->swordskillbar.top = this->getHitboxGlobalbound().top - 15;
	if (this->elapsed - this->slideCooldown <= sf::seconds(20.f) || (this->elapsed < this->slideCooldown && this->slideCooldown == sf::seconds(0.f))) {
		this->slideBar->setValue((this->elapsed - this->slideCooldown).asSeconds());
	}
	this->slidebar.left = this->getHitboxGlobalbound().left - 5;
	this->slidebar.top = this->getHitboxGlobalbound().top - 20;
	this->swordskill->Update();
	this->slideBar->Update();
}
void Player::UpdateSound()
{
	if (this->swordFall && this->swordFall->getPlaysound()) {
		this->swordFallSound.play();
	}
}

void Player::Update(const float& deltaTime, sf::Vector2f &mousePosView)
{
	this->movementComponent->Update(deltaTime);
	this->elapsed = clock.getElapsedTime();
	this->UpdateGUI(deltaTime);
	//Check collistion for player
	if (this->sprite.getPosition().x < 30) {
		this->sprite.setPosition(30, this->sprite.getPosition().y);
	}
	else if (this->sprite.getPosition().x > 1570) {
		this->sprite.setPosition(1570, this->sprite.getPosition().y);
	}
	//play
	this->UpdateAnimation(deltaTime);
	//sounds
	this->UpdateSound();

	//============================Rampage stuff==================================
	if (this->getRampage() >= 100) {
		this->onrampage = true;
	}
	if (this->onrampage) {
		this->invincible = true;
		if (this->rampageDelay == sf::seconds(0.f)) {
		//	this->saveAtk = this->stat["ATK"];
		//	this->stat["ATK"] = 999999;
		}
		if (clock.getElapsedTime() - this->rampageDelay >= sf::seconds(0.1f)) {
			this->rampageDelay = this->clock.getElapsedTime();
			this->setRampage(this->getRampage() - 0.5);
		}
		if (this->getRampage() <= 0) {
		//	this->stat["ATK"] = saveAtk;
			this->rampageDelay = sf::seconds(0.f);
			this->setRampage(0);
			this->invincible = false;
			this->onrampage = false;
		}
	}
	//======================================================================
	this->hitboxComponent->Update();
	
	if (this->swordWave) this->swordWave->Update(deltaTime);
	if (this->swordFall) this->swordFall->Update(deltaTime, mousePosView);
	
	for (int i = 0; i < 5; i++) {
		if (this->attackhitboxComponent[i] != nullptr) {
			this->attackhitboxComponent[i]->Update();
		}
	}
	
}

void Player::Render(sf::RenderTarget& target, sf::Shader* shader, bool showhitbox)
{
	
	shader->setUniform("hasTexture", true);
	shader->setUniform("lightPos", this->getCenter());

	if(this->onrampage) target.draw(this->flameSprite, shader);
	target.draw(this->sprite, shader);

	if (this->hitboxComponent && showhitbox)
		hitboxComponent->Render(target);

	for (int i = 0; i < 5; i++) {
		if (this->attackhitboxComponent[i] && showhitbox)
			attackhitboxComponent[i]->Render(target);
	}
	if (this->swordFall) {
		this->swordFall->Render(target, shader);
	}
	if (this->swordWave) {
		this->swordWave->Render(target, shader);
	}

	if (this->HPbar)
		HPbar->Render(target);

	if (this->Rampagebar)
		Rampagebar->Render(target);
	if (this->swordskill && this->elapsed - this->swordWavedelayTime < this->WaveSwordCooldown && this->swordWavedelayTime != sf::seconds(0.f) )
		this->swordskill->Render(target);
	if (this->elapsed - this->slideCooldown < sf::seconds(20.f) && this->slideCooldown != sf::seconds(0.f) )
		this->slideBar->Render(target);
}