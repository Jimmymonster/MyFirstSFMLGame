#include "GameState.h"

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestateKeybinds.ini.txt");
	if (ifs.is_open()) {
		std::string key = "" , key2 = "";
		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}
void GameState::initFonts()
{
	if (!this->pauseMenufont.loadFromFile("Fonts/Minecraft.ttf")) {
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initTextures()
{
	this->textures["PLAYER_SHEET"].loadFromFile("Resources/Sprites/Player/spriteSheet.png");
	this->textures["RED_SLIME_SHEET"].loadFromFile("Resources/Sprites/Slime/Slime_Medium_Red.png");
	this->textures["GREEN_SLIME_SHEET"].loadFromFile("Resources/Sprites/Slime/Slime_Medium_Green.png");
	this->textures["BLUE_SLIME_SHEET"].loadFromFile("Resources/Sprites/Slime/Slime_Medium_Blue.png");
	this->textures["WHITE_SLIME_SHEET"].loadFromFile("Resources/Sprites/Slime/Slime_Medium_White.png");
	this->textures["AttackUp"].loadFromFile("Resources/Item/AttackUp.jpg");
	this->textures["DefenseUp"].loadFromFile("Resources/Item/DefenseUp.jpg");
	this->textures["HealthUp"].loadFromFile("Resources/Item/HealthUp.jpg");
	this->textures["RampageUp"].loadFromFile("Resources/Item/RampageUp.jpg");
	this->textures["UI_texture"].loadFromFile("Resources/UI/panel_Example1.png");
}

void GameState::initMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->pauseMenufont);
	this->pauseMenu->addButton("QUIT", 600.f, "Quit");
	this->pauseMenu->addButton("RESUME", 400.f, "Resume");

	//===================input after death==========================
	this->Nameinput = new NameInput(*this->window, this->pauseMenufont);
	
	// add alphabet button
	for (int i = 0; i < 15; i++) {
		char a = 'a' + i;
		std::string b;
		b.push_back(a);
		this->Nameinput->addButton(b, 50.f * (i + 1) + 50.f * (i) + 10, 300.f, b);
	}
	for (int i = 0; i < 11; i++) {
		char a = 'a' + i + 15;
		std::string b;
		b.push_back(a);
		this->Nameinput->addButton(b, 50.f * (i + 1) + 50.f * (i) + 10, 400.f, b);
	}
	for (int i = 0; i < 15; i++) {
		char a = 'A' + i;
		std::string b;
		b.push_back(a);
		this->Nameinput->addButton(b, 50.f * (i + 1) + 50.f * (i) + 10, 500.f, b);
	}
	for (int i = 0; i < 11; i++) {
		char a = 'A' + i + 15;
		std::string b;
		b.push_back(a);
		this->Nameinput->addButton(b, 50.f * (i + 1) + 50.f * (i) + 10, 600.f, b);
	}
	//delete
	this->Nameinput->addButton("DELETE", 50.f, 700.f, "Del");
	this->Nameinput->addButton("ENTER", 150.f, 700.f, "Enter");
}

void GameState::initPlayers()
{
	//																					maxhp atk def crirate cridamage
	this->player = new Player(800, 669, this->textures["PLAYER_SHEET"], sf::Vector2f(3, 3), 33, 2, 100, 5, 5, 5, 50);
	//this->player = new Player(800, 669, this->textures["PLAYER_SHEET"], sf::Vector2f(3, 3), 33, 2, 1, 5, 1, 5, 50);
}
void GameState::initEntities()
{
	for (int i = 0; i < 999; i++) slimeDelayTime[i] = sf::seconds(0);
}
void GameState::initGUI()
{
	//Time
	this->Time = new gui::textbox(900, 30, 300, 50, sf::Color::White,
		"Time : "+std::to_string((int)this->clock.getElapsedTime().asSeconds()),
		&this->pauseMenufont, 25, sf::Color::Black,&this->textures["UI_texture"]);
	this->Score = new gui::textbox(1200, 30, 300, 50, sf::Color::White,
		"Score :" + std::to_string(this->scoretime + this->scoreenemy),
		&this->pauseMenufont, 25, sf::Color::Black, &this->textures["UI_texture"]);
	//status
	this->Frame.setTexture(&this->textures["UI_texture"]);
	this->Frame.setPosition(sf::Vector2f(30.f,145.f));
	this->Frame.setSize(sf::Vector2f(350,250));
	this->status[0] = new gui::textbox(40, 170, 350, 50, sf::Color::Transparent,
		"Health  : " + std::to_string((int)this->player->getstat("HP")) + "/" + std::to_string((int)this->player->getstat("MAXHP")),
		&this->pauseMenufont, 30, sf::Color::Black, nullptr, true);
	this->status[1] = new gui::textbox(40, 220, 350, 50, sf::Color::Transparent,
		"Attack  : " + std::to_string((int)this->player->getstat("ATK")),
		&this->pauseMenufont, 30, sf::Color::Black, nullptr, true);
	this->status[2] = new gui::textbox(40, 270, 350, 50, sf::Color::Transparent,
		"Defense : " + std::to_string((int)this->player->getstat("DEFENSE")),
		&this->pauseMenufont, 30, sf::Color::Black, nullptr, true);
	this->status[3] = new gui::textbox(40, 320, 350, 50, sf::Color::Transparent,
		"Rampage : " + std::to_string((int)this->player->getRampage()) + "/100" ,
		&this->pauseMenufont, 30, sf::Color::Black, nullptr, true);
}
void GameState::initBackground()
{
	this->background[0].setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	this->backgroundTexture[0].loadFromFile("Resources/BackGround/GamestateBackground.png");
	this->background[0].setTexture(&backgroundTexture[0]);
	this->background[1].setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	this->backgroundTexture[1].loadFromFile("Resources/BackGround/GamestateBackground1.png");
	this->background[1].setTexture(&backgroundTexture[1]);
}
void GameState::initSounds()
{
	/*if (!this->bgm.openFromFile("")) {
		throw("")
	}*/
	this->slimeSoundBuffer[0].loadFromFile("Resources/Sounds/Slime/BeingHit/mixkit-sword-cutting-flesh-2788.wav");
	this->slimeSoundBuffer[1].loadFromFile("Resources/Sounds/Slime/BeingHit/mixkit-sword-gore-slash-hit-2796.wav");
	this->slimeSoundBuffer[2].loadFromFile("Resources/Sounds/Slime/Jump/72f20b1d-7a21-492e-a7e3-bfdaea90e33d.wav");
	for (int i = 0; i < 3; i++) {
		this->slimeSound->setBuffer(this->slimeSoundBuffer[i]);
		this->slimeSound[i].setVolume(30.f);
	}
	this->ItemSoundBuffer.loadFromFile("Resources/Sounds/Item/345297__scrampunk__itemize.wav");
	this->ItemSound.setBuffer(this->ItemSoundBuffer);
	this->ItemSound.setVolume(30.f);

	this->bgm.openFromFile("Resources/Sounds/Ingame/bgm.wav");
	this->bgm.setVolume(25.f);
	this->bgm.setLoop(true);
	this->bgm.play();
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states), hour(0), minutes(0), second(0), scoretime(0), scoreenemy(0), backtoMenu(false), entername(false), Enter(false),
	hp(10),defense(3),atk(10),crirate(5),cridamage(50),spawnnum(1)
{
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initMenu();
	this->initPlayers();
	this->initEntities();
	this->initGUI();
	this->initBackground();
	this->initSounds();

	
	this->slimecou = 0;
	//Set Seed <-- need to fix
	srand(time(0));
}

GameState::~GameState()
{
	for (int i = 0; i < 999; i++)
		delete this->slime[i];
	for (int i = 0; i < 999; i++)
		delete this->Item[i];
	delete this->player;
	delete this->pauseMenu;
}

//functions
void GameState::checkEndgame()
{
	if (this->player->checkDeath()) {
		if (this->temp == sf::seconds(0.f)) {
			this->temp = this->elapsed;
			this->player->stopWalkSound();
			if (this->bgm.getStatus() == sf::Music::Playing) {
				this->bgm.stop();
			}
			this->bgm.openFromFile("Resources/Sounds/Ingame/Snail_s-House-Pixel-Galaxy-_Official-MV_ (1).wav");
			this->bgm.play();
		}
		if (this->elapsed - this->temp >= sf::seconds(5.f)) {

			this->entername = true;
			if (this->Nameinput->getstring() == "") this->Enter = false;
			/*
			add scoretime+scoreenemy to leaderboard here!!!
			make sure to do it
			*/
			//=====================Load Score form file============================
			if (!this->backtoMenu) {
				std::ifstream ifs("Config/LeaderBoardScore.txt");
				std::string name[6];
				unsigned int score[6] = { 0,0,0,0,0,0 };
				int cou = 1;
				if (ifs.is_open()) {
					for (int i = 0; i < 6; i++) {
						if (!(ifs >> name[i] >> score[i])) { cou = i + 1; break; }
					}
					for (int i = 0; i < cou; i++) {
						if (this->scoretime + this->scoreenemy > score[i]) {
							if (cou > 5) cou = 5;
							for (int j = cou - 1; j > i; j--) {
								score[j] = score[j - 1];
								name[j] = name[j - 1];
							}
							name[i] = this->Nameinput->getstring();
							score[i] = this->scoretime + this->scoreenemy;
							break;
						}
					}
				}
				ifs.close();

				//std::cout << cou << std::endl;
				//for (int i = 0; i < cou; i++) std::cout << name[i] << " " << score[i] << std::endl;

				if (this->Enter) {
					std::ofstream ofs("Config/LeaderBoardScore.txt");
					if (ofs.is_open()) {
						for (int i = 0; i < cou; i++) {
							ofs << name[i] << " " << score[i] << std::endl;
						}
					}
					ofs.close();
				}
			}
			//===============================================================
			if (!this->backtoMenu && this->Enter) {
				this->states->push(new LeaderBoard(this->window, this->supportedKeys, this->states));
				this->backtoMenu = true;
			}
			if(this->backtoMenu)
				this->endState();
		}
	}
}
void GameState::spawner() 
{
	if (this->elapsed - this->spawnTime >= this->spawnTimer || this->spawnTime == sf::seconds(0.f)) {
		int cou = 0;
		float scale;
		std::string col[4] = {"RED_SLIME_SHEET","GREEN_SLIME_SHEET","BLUE_SLIME_SHEET","WHITE_SLIME_SHEET"};
		for (int i = 0; i <= 999; i++) {
			scale = 3 + rand() % 5;
			if (this->slime[i]) continue;
			if (!this->slime[i]) {
				/*if (this->forceEndgame) {
					this->spawnnum = 1;
					this->slime[i] = new Slime(-400.f + rand() % 300, 300.f + rand() % 600, this->textures[col[rand() % 4]], sf::Vector2f(30, 30), 4, 4,
						999999999,
						999999999,
						999999999,
						100,
						999999999
					);
				}*/
				if (rand() % 2 == 1) {
					this->slime[i] = new Slime(-400.f + rand() % 300, 300.f+ rand() % 3000, this->textures[col[rand()%4]], sf::Vector2f(scale, scale), 4, 4,
						this->hp - rand()%(((int)this->hp + 1)/2), 
						this->atk - rand() % (((int)this->atk + 1)/ 2),
						this->defense - rand() % (((int)this->defense + 1)/ 2),
						this->crirate ,
						this->cridamage
					);
				}
				else {
					this->slime[i] = new Slime(2000.f + rand() % 300, 300.f + rand() % 3000, this->textures[col[rand() % 4]], sf::Vector2f(scale, scale), 4, 4,
						this->hp - rand() % (((int)this->hp + 1) / 2),
						this->atk - rand() % (((int)this->atk + 1) / 2),
						this->defense - rand() % (((int)this->defense + 1) / 2),
						this->crirate,
						this->cridamage
					);
				}
				cou++;
				if (cou >= this->spawnnum) {
					break;
				}
			}
		}
		this->spawnTime = this->elapsed;
		this->spawnTimer += sf::seconds(1.f);
	}
	if (this->elapsed - this->statUpTimer >= sf::seconds(10.f)) {
		float value;
		value = this->hp * 0.1f;
		//if (value > 1000.f) value = 1000.f;
		if (this->player->getstat("ATK") > this->hp * 0.4) value += this->player->getstat("ATK") / 2.f;
		if (this->forceEndgame) value += this->hp * 0.1f;
		this->hp += value;

		value = this->defense * 0.08f;
		if (value > 100.f) value = 100.f;
		this->defense += value;

		value = this->atk * 0.1f;
		//if (value > 100.f) value = 100.f;
		if (this->player->getstat("MAXHP") / 15 > this->atk) value += this->player->getstat("MAXHP") / 15;
		if (this->forceEndgame) value += this->atk * 0.2f;
		this->atk += value;
		this->statUpTimer = this->elapsed;
	}
	if (this->elapsed - this->spawnnumTimer >= sf::seconds(15.f)) {
		this->spawnnum++;
		this->spawnnumTimer = this->elapsed;
	}
}

void GameState::UpdateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime()) {
		if (!this->pause) {
			this->temp = this->elapsed;
			this->pauseState();
		}
		else {
			this->pauseTime += this->elapsed - this->temp;
			this->temp = sf::seconds(0.f);
			this->unpauseState();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ENTER")))) {
		this->Enter = true;
	}
}

void GameState::UpdatePlayerInput(const float& deltaTime)
{
	if (this->player->DisableInput()) return;
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move( -1.f, 0.f,deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move( 1.f, 0.f,deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("JUMP1"))) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("JUMP2"))))
		this->player->move(0.f, -400.f, deltaTime);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CROUCH"))))
		this->player->move(0.f, 1.f, deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SWORDFALL")))) {
		this->player->swordfall();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->player->Attack();
		//if (!this->isSlimeBeingHit) this->player->playSound("SwordMiss");
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		this->player->swordwave();
	}
	// check if hp works
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) && this->getKeytime()) {
		this->player->setstat("MAXHP",this->player->getstat("MAXHP") + 10);
		this->player->Attacked();
	}*/
}

void GameState::UpdatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT")) {
		this->endState();
	}
	else if (this->pauseMenu->isButtonPressed("RESUME")) {
		this->pauseTime += this->elapsed - this->temp;
		this->temp = sf::seconds(0.f);
		this->bgm.play();
		this->unpauseState();
	}
}

void GameState::UpdateNameInputButtons()
{
	for (auto it : this->Nameinput->getButtons()) {
		if (it.second->isPressed() && getKeytime()) {
			if (it.first == "DELETE") {
				std::string a = this->Nameinput->getstring();
				if (a.length() > 0) {
					a.pop_back();
					this->Nameinput->setstring(a);
				}
			}
			else if (it.first == "ENTER") {
				if (this->Nameinput->getstring() != "") {
					if (this->bgm.getStatus() == sf::Music::Playing) {
						this->bgm.stop();
					}
					this->Enter = true;
				}
			}
			else {
				if(this->Nameinput->getstring().length()<=20)
					this->Nameinput->setstring(this->Nameinput->getstring() + it.first);
			}
		}
	}
}

void GameState::UpdateGUI(const float& deltaTime)
{
	hour = (int)this->elapsed.asSeconds() / 3600;
	minutes = (int)this->elapsed.asSeconds()  / 60;
	second = (int)this->elapsed.asSeconds()  % 60;
	this->time_text.clear();
	if (hour >= 10) this->time_text += std::to_string(hour);
	else this->time_text += "0" + std::to_string(hour);
	this->time_text += ":";
	if (minutes >= 10) this->time_text += std::to_string(minutes);
	else this->time_text += "0" + std::to_string(minutes);
	this->time_text += ":";
	if (second >= 10) this->time_text += std::to_string(second);
	else this->time_text += "0" + std::to_string(second);
	this->Time->settext("Time : " + time_text);

	this->scoretime = (int)(this->elapsed.asSeconds()) * 5;
	this->Score->settext("Score : " + std::to_string(this->scoretime + this->scoreenemy));

	this->status[0]->settext("Health  : " + std::to_string((int)this->player->getstat("HP")) + "/" + std::to_string((int)this->player->getstat("MAXHP")));
	this->status[1]->settext("Attack  : " + std::to_string((int)this->player->getstat("ATK")));
	this->status[2]->settext("Defense : " + std::to_string((int)this->player->getstat("DEFENSE")));
	this->status[3]->settext("Rampage : " + std::to_string((int)this->player->getRampage()) + "/100");
}

void GameState::Update(const float& deltaTime)
{
	this->elapsed = this->clock.getElapsedTime() - this->pauseTime;

	this->UpdateMousePositions();
	this->UpdateInput(deltaTime);
	this->UpdateKeytime(deltaTime);

	if (this->entername) {
		this->Nameinput->Update(this->mousePosView);
		this->UpdateNameInputButtons();
	}
	else if (!this->pause) { // Update game state
		this->slimecou = 0;

		this->spawner();
		this->UpdatePlayerInput(deltaTime);
		this->player->Update(deltaTime,this->mousePosView);

		//================ Death =======================================
		if (!this->player->checkDeath())
			this->UpdateGUI(deltaTime);
		if (this->playerdmgNum) {
			this->playerdmgNum->Update(deltaTime);
			if (this->playerdmgNum->remove()) this->playerdmgNum = nullptr;
		}
		//================================================================
		//=================== Sword Fall Shake =============================
		if (this->player->getSwordFallFloor()) {
			this->shaking = true;
		}
		//================================================================
		for (int i = 0; i < 999; i++) {
			if (!this->slime[i]) continue;
			this->slime[i]->Update(deltaTime, this->player->getPosition());
		}
		for (int i = 0; i < 999; i++) {
			if (this->Item[i]) this->Item[i]->Update(deltaTime);
			if (this->dmgNum[i]) {
				this->dmgNum[i]->Update(deltaTime);
				if (this->dmgNum[i]->remove()) this->dmgNum[i] = nullptr;
			}
 		}
		for (int i = 0; i < 999; i++) {
			//delay 3 sec after slime death clear the memory
			if (slimeDelayTime[i]!=sf::seconds(0.f) && this->elapsed - slimeDelayTime[i] >= sf::seconds(2.f)) {
				this->slimeDelayTime[i] = sf::seconds(0);
				this->slime[i] = nullptr;
				//std::cout << i << std::endl;
			}
			if (!this->slime[i]) continue;
			this->slimecou++;
			if (this->slimecou > 70 || this->elapsed>=sf::seconds(300)) this->forceEndgame = true;
			//slime jump sound
			if (this->slime[i]->getJump()) {
				this->slimeSound[2].setBuffer(this->slimeSoundBuffer[2]);
				this->slimeSound[2].play();
			}

			// player hit slime
			for(int j=0;j<5;j++){
				if (this->slime[i]->intersect(this->player->getAttackHitboxGlobalbound(j)) && !slime[i]->Invincible()) {
					float diff;
					if (j == 0) diff = this->player->getstat("ATK") - this->slime[i]->getstat("DEFENSE");
					if (j == 1) diff = this->player->getstat("ATK") * 1.1f - this->slime[i]->getstat("DEFENSE");
					if (j == 2) diff = this->player->getstat("ATK") * 1.5f; // ignore def
					if (j == 3) diff = this->player->getstat("ATK") - this->slime[i]->getstat("DEFENSE");
					if (j == 4) diff = this->player->getstat("ATK") * 0.2f;
					if (diff <= 1) diff = 1.f;

					if (this->player->onRampage()) {
						this->slime[i]->setstat("HP", 0);
						this->dmgNum[i] = new gui::damageNumber(
							this->slime[i]->getPosition().x,this->slime[i]->getPosition().y - 50,999999.f,&this->pauseMenufont,
							40,1,
							sf::Color::White,sf::Color::Black);
					}
					else {
						this->slime[i]->setstat("HP", this->slime[i]->getstat("HP") - diff);
						this->dmgNum[i] = new gui::damageNumber(
							this->slime[i]->getPosition().x, this->slime[i]->getPosition().y - 50, diff, &this->pauseMenufont,
							40, 1,
							sf::Color::White, sf::Color::Black);
					}
					if (j == 0) this->slime[i]->Attacked(1000, 500);
					if (j == 1) this->slime[i]->Attacked(1000, 500);
					if (j == 2) this->slime[i]->Attacked(2000, 1000);
					if (j == 3) this->slime[i]->Attacked(1000, 500);
					if (j == 4) this->slime[i]->Attacked(0, 0);

					if (this->slime[i]->checkDeath()) {
						this->slimeSound[1].setBuffer(this->slimeSoundBuffer[1]);
						this->slimeSound[1].play();
						if (this->slime[i]->getstat("ATk") == 999999999.f) this->scoreenemy = 999999999.f;
						else this->scoreenemy += 100;
						//do one time when slime die and Update delay time
						if (slimeDelayTime[i] == sf::seconds(0)) {
							//Update slime death
							slimeDelayTime[i] = this->elapsed;
							//Update player Ramage
							if (!this->player->onRampage())
								this->player->setRampage(this->player->getRampage() + 1);
							else if (this->player->onRampage()) {
								float sum = this->player->getstat("MAXHP") / 25.f + this->player->getstat("HP");
								if (sum > this->player->getstat("MAXHP")) sum = this->player->getstat("MAXHP");
								this->player->setstat("HP", sum);
							}
							//Item drop
							if (rand() % 3 == 0) {  //<-- Item drop 33 percent
								int random = (rand()/3) % 100;
								//basicly i want attackup and healthup rate is 35% defense and rampage rate is 15%
								int idx;
								if (random < 35) idx = 0;
								else if (random < 70) idx = 1;
								else if (random < 85) idx = 2;
								else if (random < 100) idx = 3;
								std::string type[4] = { "AttackUp","HealthUp","DefenseUp","RampageUp" };
								for (int j = 0; j < 99999; j++) {
									if (this->Item[j] == nullptr) {
										this->ItemDelayTime[j] = sf::seconds(0);
										this->Item[j] = new ItemDrop(slime[i]->getPosition().x, this->slime[i]->getPosition().y, this->textures[type[idx]], sf::Vector2f(0.5, 0.5), type[idx], 0.25);
										break;
									}
								}
							}
						}
					}
					else {
						this->slimeSound[0].setBuffer(this->slimeSoundBuffer[0]);
						this->slimeSound[0].play();
					}
				}
			}
			// Slime hit player
			if (this->slime[i]->intersect(this->player->getHitboxGlobalbound()) && !player->Invincible()) {
				this->shaking = true;
				float diff;
				diff = this->slime[i]->getstat("ATK") - this->player->getstat("DEFENSE");
				if (diff <= 1) diff = 1.f;
				this->playerdmgNum = new gui::damageNumber(
					this->player->getPosition().x, this->player->getPosition().y - 50, diff, &this->pauseMenufont,
					40, 1,
					sf::Color::Red, sf::Color::Black);
				this->player->setstat("HP", this->player->getstat("HP") - diff);
				this->player->Attacked();
				this->checkEndgame();
			}
		}

		for (int i = 0; i < 999; i++) {
			// player pickup item and update item timer
			if (this->Item[i]) {
				if (this->ItemDelayTime[i] == sf::seconds(0)) {
					this->ItemDelayTime[i] = this->elapsed;
				}
				if (this->Item[i]->intersect(this->player->getHitboxGlobalbound())) {
					this->ItemSound.play();
					//std::cout << this->Item[i]->getType() << std::endl;
					float value;
					if (!this->Item[i]->getType().compare("AttackUp")) {
						value = this->player->getstat("ATK") * this->Item[i]->getpercent();
						if (value > 100.f) value = 100.f;
						this->player->setstat("ATK", this->player->getstat("ATK") + value);
					}
					else if (!this->Item[i]->getType().compare("DefenseUp")) {
						value = this->player->getstat("DEFENSE") * this->Item[i]->getpercent();
						if (value > 100.f) value = 100.f;
						this->player->setstat("DEFENSE", this->player->getstat("DEFENSE") + value);
					}
					else if (!this->Item[i]->getType().compare("HealthUp")) {
						value = this->player->getstat("MAXHP") * this->Item[i]->getpercent();
						if (value > 1000.f) value = 1000.f;
						this->player->setstat("MAXHP", this->player->getstat("MAXHP") + value);

						value = this->player->getstat("HP") * this->Item[i]->getpercent();
						if (value > 1000.f) value = 1000.f;
						this->player->setstat("HP", this->player->getstat("HP") + value);
					}
					else if (!this->Item[i]->getType().compare("RampageUp")) {
						float plus = this->player->getRampage() + 10;
						if (plus > 100) plus = 100;
						this->player->setRampage(plus);
					}
					this->Item[i]->setpickUp(true);
					this->Item[i] = nullptr;
				}
				//delete item after 20 second
				if (this->elapsed - this->ItemDelayTime[i] >= sf::seconds(20)) {
					this->ItemDelayTime[i] = sf::seconds(0);
					this->Item[i]->setpickUp(true);
					this->Item[i] = nullptr;
				}
			}
			// ==============================================================
		}
	}
	else {// Update pause state
		if (this->bgm.getStatus() == sf::Music::Playing) {
			this->bgm.stop();
		}
		this->pauseMenu->Update(this->mousePosView);
		this->UpdatePauseMenuButtons();
		this->player->stopWalkSound();
	}
	this->checkEndgame();
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	if (this->shaking&&!this->player->checkDeath()) this->shakeScreen();

	target->draw(this->background[0]);

	//this->player->Render(*target,true); //<---for hit block check
	this->player->Render(*target);

	for (int i = 0; i < 999; i++) {
		if (!this->slime[i]) continue;
		//if (this->slime[i]) this->slime[i]->Render(*target, true); //<---for hit block check
		if (this->slime[i]) this->slime[i]->Render(*target);
	}
	for (int i = 0; i < 999; i++) {
		if (this->Item[i]) this->Item[i]->Render(*target);
		if (this->dmgNum[i]) this->dmgNum[i]->Render(*target);
	}
	if (this->playerdmgNum) this->playerdmgNum->Render(*target);

	target->draw(this->Frame);
	for (int i = 0; i < 5; i++) {
		if (status[i]) status[i]->Render(*target);
	}

	this->Time->Render(*target);
	this->Score->Render(*target);

	target->draw(this->background[1]);

	if (this->entername) {
		this->Nameinput->Render(*target);
	}
	else if (this->pause) {
		this->pauseMenu->Render(*target);
	}
}
