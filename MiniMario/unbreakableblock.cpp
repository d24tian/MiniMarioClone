#include "header.h"
#include "unbreakableblock.h"

UnbreakableBlock::UnbreakableBlock(sf::Vector2f position, int type) :
    animation(&tilesheet, sf::Vector2u(29, 28), 0.0f)
{
    body.setSize(sf::Vector2f(32.0f, 32.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(position);
    body.setTexture(&tilesheet);
    this->row = 1;
    this->column = 0;
    this->type = type;
}

UnbreakableBlock::~UnbreakableBlock()
{
    //dtor
}

///Set sprite based on type
void UnbreakableBlock::SetSprite()
{
    animation.SetTexture(&tilesheet);
    body.setTexture(&tilesheet);
}

void UnbreakableBlock::Update(float deltaTime)
{
    ///Check collision with fireball
    for (int i = 0; i < fireballs.size(); i++)
    {
        sf::Vector2f otherPos = fireballs[i].GetPosition();
        sf::Vector2f otherHalfSize = fireballs[i].GetHalfSize();
        sf::Vector2f thisPos = GetPosition();
        sf::Vector2f thisHalfSize = GetHalfSize();

        float deltaX = otherPos.x - thisPos.x;
        float deltaY = otherPos.y - thisPos.y;

        float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x + 2);
        float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

        if (intersectX < 0.0f && intersectY < 0.0f)
        {
            if (intersectX > intersectY)
            {
                if (!fireballs[i].exploded)
                {
                    fireballs[i].Explode();
                }
            }
        }
    }

    ///Update animation
    body.setTexture(&tilesheet);
    animation.SetTexture(&tilesheet);
    if (areaType == 0)
    {
        row = 1;
    }
    else if (areaType == 1)
    {
        row = 3;
    }
    else if (areaType == 2)
    {
        row = 5;
    }
    else if (areaType == 3)
    {
        row = 7;
    }

    if (type == 0)
    {
        column = 0;
    }
    else if (type == 1)
    {
        column = 1;
    }
    animation.Update(row, column, column, deltaTime, true);
    body.setTextureRect(animation.uvRect);
}

///Custom draw to screen function
void UnbreakableBlock::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
