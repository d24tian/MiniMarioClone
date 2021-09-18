#include "header.h"
#include "coinicon.h"

CoinIcon::CoinIcon() :
    animation(&tilesheet, sf::Vector2u(29, 28), 0.125f)
{
    body.setSize(sf::Vector2f(32.0f, 32.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setTexture(&tilesheet);
    this->row = 24;
    this->columnBegin = 19;
    this->columnEnd = 24;
}

CoinIcon::~CoinIcon()
{
    //dtor
}

void CoinIcon::SetSprite()
{
    animation.SetTexture(&tilesheet);
    body.setTexture(&tilesheet);
}

void CoinIcon::Update(float deltaTime)
{
    ///Update animation
    body.setTexture(&tilesheet);
    animation.SetTexture(&tilesheet);
    if (inGame == 2)
    {
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
        columnBegin = 19;
        columnEnd = 24;
    }
    else
    {
        columnBegin = 19;
        columnEnd = 19;
    }
    animation.Update(row, columnBegin, columnEnd, deltaTime, true);
    body.setTextureRect(animation.uvRect);
}

///Custom draw to screen function
void CoinIcon::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
