#include "header.h"
#include "coin.h"

Coin::Coin(sf::Vector2f position) :
    animation(&tilesheet, sf::Vector2u(29, 28), 0.03125f)
{
    body.setSize(sf::Vector2f(32.0f, 32.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setTexture(&tilesheet);
    body.setPosition(sf::Vector2f(position.x, position.y - 32.0f));
    this->movement = 0;
    this->moveTimer = 0.0f;
    this->row = 24;
    this->columnBegin = 25;
    this->columnEnd = 28;
    this->originalY = position.y - 32.0f;
    this->velocity.y = -sqrt(981.0f * 981.0f / 1.5f);
}

Coin::~Coin()
{
    //dtor
}

void Coin::Update(float deltaTime)
{
    if (movement == 0)
    {
        if (velocity.y > 0.0f)
        {
            movement = 1;
        }
    }
    else if (movement == 1)
    {
        if (body.getPosition().y > originalY)
        {
            movement = 2;
        }
    }

    velocity.x = 0.0f;

    ///Limit gravity
    if (velocity.y < 981.0f)
    {
        velocity.y += 3433.5f * deltaTime;
    }
    else
    {
        velocity.y = 981.0f;
    }

    ///Move
    body.move(velocity * deltaTime);

    ///Update animation
    body.setTexture(&tilesheet);
    animation.SetTexture(&tilesheet);
    if (areaType == 0)
    {
        row = 24;
    }
    else if (areaType == 1)
    {
        row = 25;
    }
    else if (areaType == 2)
    {
        row = 26;
    }
    else if (areaType == 3)
    {
        row = 27;
    }
    columnBegin = 25;
    columnEnd = 28;
    animation.Update(row, columnBegin, columnEnd, deltaTime, true);
    body.setTextureRect(animation.uvRect);
}

///Custom draw to screen function
void Coin::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
