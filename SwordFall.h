#pragma once
#include "Entity.h"
class SwordFall :
    public Entity
{
private:
    float angle=270.f;
    float x, y, velocity;
    sf::Vector2f Velocity;
    sf::Vector2f scale;
    float chargeUpScale=0.f;
    std::map<std::string, bool> state;

    bool ready = false;
    bool fall = false;
    bool floor = false;
    bool first = true;
    bool first2 = true;
    bool playsound = false;

    sf::Clock clock;
    sf::Time elapse;
    sf::Time chargeUpTime = sf::seconds(0.f);
public:
    SwordFall(float x,float y,float velocity,sf::Texture& sheet);
    virtual ~SwordFall();
    //Modifier
    void Fall();

    //Accessor
    HitboxComponent& getHitboxcomponent();
    const bool& getReady()const;
    const bool& getFall()const;
    const bool& getPlaysound();
    const bool& getFloor();

    //function
    void Update(const float& deltatime, sf::Vector2f &mousePosView);
    void Render(sf::RenderTarget& target);
};

