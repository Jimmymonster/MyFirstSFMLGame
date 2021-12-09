#pragma once
#include "LeaderBoard.h"
#include "Slime.h"
#include "ItemDrop.h"
#include "PauseMenu.h"
#include "NameInput.h"
#include "SlimeSplash.h"
class GameState :
    public State
{
private:

    PauseMenu *pauseMenu;
    NameInput *Nameinput;
    sf::Font pauseMenufont;

    //GUI
    gui::textbox* Time;
    std::string time_text;
    unsigned int hour, minutes, second;
    gui::textbox* status[5]; //<-- 0 = Hp/MaxHp 1 = Atk  2 = defense 3 = rampage
    
    gui::textbox* Score;
    sf::RectangleShape Frame;
    unsigned int scoretime, scoreenemy;

    gui::damageNumber* dmgNum[1000];
    gui::damageNumber* playerdmgNum;

    //Shader
    sf::Shader core_shader;

    //For player death delay
    sf::Clock clock;
    sf::Time elapsed = sf::seconds(0.f);
    sf::Time temp = sf::seconds(0.f);
    sf::Time pauseTime = sf::seconds(0.f);

    //entities
    Player* player;
    sf::Time slimeDelayTime[1000];
    Slime* slime[1000];
    sf::Time ItemDelayTime[1000];
    ItemDrop* Item[1000];
    //Particles

    //Spawner
    int spawnnum;
    float hp, defense, atk, crirate, cridamage;
    sf::Time spawnTime = sf::seconds(0.f);
    sf::Time spawnTimer = sf::seconds(3.f);
    sf::Time statUpTimer = sf::seconds(0.f);
    sf::Time spawnnumTimer = sf::seconds(0.f);

    //background
    sf::RectangleShape background;
    sf::Texture backgroundTexture, backgroundTextureSheet;
    sf::Sprite backgroundSprite;
    AnimationComponent* backgroundAnimation;
    pFirefly* pfirefly;

    //Sounds
    sf::Music bgm;
    sf::Sound ItemSound;
    sf::SoundBuffer ItemSoundBuffer;
    sf::Sound slimeSound[3];
    sf::SoundBuffer slimeSoundBuffer[3];

    //checkStuff
    bool backtoMenu;
    bool entername;
    bool Enter;
    int slimecou;
    bool forceEndgame;
    //bool isSlimeBeingHit;

    //functions
    void initKeybinds();
    void initFonts();
    void initTextures();
    void initMenu();
    void initPlayers();
    void initShaders();
    void initEntities();
    void initGUI();
    void initBackground();
    void initSounds();
    

public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    //Utility
    void checkEndgame();

    //functions
    void spawner();
    void UpdateInput(const float& deltaTime);
    void UpdatePlayerInput(const float& deltaTime);
    void UpdatePauseMenuButtons();
    void UpdateNameInputButtons();
    void UpdateGUI(const float& deltaTime);
    void Update(const float& deltaTime);
    void Render(sf::RenderTarget* target = nullptr);
};

