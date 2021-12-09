#pragma once
#include "Entity.h"
class ItemDrop :
    public Entity
{
private:
    //variables
    sf::Vector2f scale;
    float x, y;
    float percent;
    
    std::string type;

    bool pickUp;
    bool moved;

    //function
    void initVariables();
    void initComponents();
public:
    //need parameter typeOfStatus and rand()%
    ItemDrop(float x, float y, sf::Texture& textrueSheet, sf::Vector2f scale, std::string type, float percent);
    virtual ~ItemDrop();
    //Accessor
    const std::string& getType()const;
    const float& getpercent()const;
    //Modifier
    void setpickUp(bool value);
    //Update stuff
    virtual void Update(const float& deltaTime);

    //Render
    void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr, bool showhitbox = false);
};

