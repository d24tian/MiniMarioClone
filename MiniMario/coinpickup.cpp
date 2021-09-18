#include "header.h"
#include "coinpickup.h"

CoinPickup::CoinPickup(sf::Texture* texture, sf::Vector2f position) :
    animation(texture, sf::Vector2u(4, 2), 1.0f / 6.0f)
{
    body.setSize(sf::Vector2f(32.0f, 32.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setTexture(texture);
    body.setPosition(position);
}

CoinPickup::~CoinPickup()
{
    //dtor
}

///Set sprite based on type
void CoinPickup::SetSprite()
{
    animation.SetTexture(&coinPickup);
    body.setTexture(&coinPickup);
}

///Update function----------------------------------------------------------------------------------------------------
void CoinPickup::Update(float deltaTime)
{
    ///Update animations
    body.setTexture(&coinPickup);
    if (level == 11)
    {
        if (area == 0)
        {
            animation.Update(0, 0, 3, deltaTime, true);
        }
        else if (area == 1)
        {
            animation.Update(1, 0, 3, deltaTime, true);
        }
    }
    else
    {

    }
    body.setTextureRect(animation.uvRect);
}

///Custom draw to screen function
void CoinPickup::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
