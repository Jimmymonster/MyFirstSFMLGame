#pragma once
#include "Entity.h"
#include "SwordWave.h"
class Player:
	public Entity
{
private:
	//variables
	sf::Vector2f scale;
	bool attacking;
	bool swordwaving;
	bool swordwaved;
	bool Isattacked;
	bool knockback;
	bool finishdeath;
	bool disableInput;
	bool onrampage;
	float x, y;

	int attackIdx;
	bool attackPlayed[3];
	//float saveAtk;

	HitboxComponent* attackhitboxComponent[4];
	gui::bar* Rampagebar;
	gui::bar* swordskill;
	sf::Time WaveSwordCooldown = sf::seconds(8.f);

	sf::Texture flame;
	sf::Sprite flameSprite;
	AnimationComponent* flameAnima;

	SwordWave* swordWave;
	sf::Texture swordwavesheet;

	sf::Clock clock;
    sf::Time elapsed;
	sf::Time attackdelayTime = sf::seconds(0);
	sf::Time swordWavedelayTime = sf::seconds(0);
	sf::Time time2 = sf::seconds(0);
	sf::Time rampageDelay = sf::seconds(0);

	//sound
	sf::Sound sound;
	sf::Sound walksound;
	std::map<std::string, sf::SoundBuffer> buffer;
	
	//function
	void initVariables();
	void initGUI();
	void initComponents();
	void initSounds();
	void AddAnimations();
public:
	//function
	Player(float x, float y, sf::Texture& textureSheet,sf::Vector2f scale,int imgx, int imgy,
		float maxhp,float atk,float defense,float criRate,float cridamage);
	virtual ~Player();

	//functions
	void flip();
	void Attacked();
	void Attack();
	void swordwave();
	void playSound(std::string key);

	//Accessor
	const float& getRampage()const;
	const bool& DisableInput()const;
	const bool& onRampage()const;
	const sf::FloatRect getAttackHitboxGlobalbound(int idx)const;
	//Modifier
	void setRampage(float value);
	//Update stuff
	void UpdateAnimation(const float& deltaTime);
	void UpdateGUI(const float& deltaTime);
	virtual void Update(const float& deltaTime);
	virtual void Render(sf::RenderTarget& target, bool showhitbox = false);
};

