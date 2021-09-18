#include "header.h"
#include "pipe.h"

Pipe::Pipe(sf::Vector2f position, int type) :
    animation(&tilesheet, sf::Vector2u(29, 28), 0.0f)
{
    body.setSize(sf::Vector2f(32.0f, 32.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setTexture(&tilesheet);
    body.setPosition(position);
    this->row = 8;
    this->column = 0;
    this->faceLeft = true;
    /**
    0 = topLeft
    1 = topRight
    2 = shaftLeft
    3 = shaftRight
    4 = leftTopTop
    5 = leftTopBottom
    6 = leftShaftTop
    7 = leftShaftBottom
    8 = leftConnectTop
    9 = leftConnectBottom
    10 = rightTopTop
    11 = rightTopBottom
    12 = rightShaftTop
    13 = rightShaftBottom
    14 = rightConnectTop
    15 = rightConnectBottom
    */
    this->type = type;
}

Pipe::~Pipe()
{
    //dtor
}

///Set sprite based on type
void Pipe::SetSprite()
{
    animation.SetTexture(&tilesheet);
    body.setTexture(&tilesheet);
}

void Pipe::Update(float deltaTime)
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
        if (type == 0)
        {
            row = 8;
            column = 0;
            faceLeft = true;
        }
        else if (type == 1)
        {
            row = 8;
            column = 1;
            faceLeft = true;
        }
        else if (type == 2)
        {
            row = 9;
            column = 0;
            faceLeft = true;
        }
        else if (type == 3)
        {
            row = 9;
            column = 1;
            faceLeft = true;
        }
        else if (type == 4)
        {
            row = 8;
            column = 2;
            faceLeft = true;
        }
        else if (type == 5)
        {
            row = 9;
            column = 2;
            faceLeft = true;
        }
        else if (type == 6)
        {
            row = 8;
            column = 3;
            faceLeft = true;
        }
        else if (type == 7)
        {
            row = 9;
            column = 3;
            faceLeft = true;
        }
        else if (type == 8)
        {
            row = 8;
            column = 4;
            faceLeft = true;
        }
        else if (type == 9)
        {
            row = 9;
            column = 4;
            faceLeft = true;
        }
        else if (type == 10)
        {
            row = 8;
            column = 2;
            faceLeft = false;
        }
        else if (type == 11)
        {
            row = 9;
            column = 2;
            faceLeft = false;
        }
        else if (type == 12)
        {
            row = 8;
            column = 3;
            faceLeft = false;
        }
        else if (type == 13)
        {
            row = 9;
            column = 3;
            faceLeft = false;
        }
        else if (type == 14)
        {
            row = 8;
            column = 4;
            faceLeft = false;
        }
        else if (type == 15)
        {
            row = 9;
            column = 4;
            faceLeft = false;
        }
    }
    else if (areaType == 1)
    {
        if (type == 0)
        {
            row = 10;
            column = 0;
            faceLeft = true;
        }
        else if (type == 1)
        {
            row = 10;
            column = 1;
            faceLeft = true;
        }
        else if (type == 2)
        {
            row = 11;
            column = 0;
            faceLeft = true;
        }
        else if (type == 3)
        {
            row = 11;
            column = 1;
            faceLeft = true;
        }
        else if (type == 4)
        {
            row = 10;
            column = 2;
            faceLeft = true;
        }
        else if (type == 5)
        {
            row = 11;
            column = 2;
            faceLeft = true;
        }
        else if (type == 6)
        {
            row = 10;
            column = 3;
            faceLeft = true;
        }
        else if (type == 7)
        {
            row = 11;
            column = 3;
            faceLeft = true;
        }
        else if (type == 8)
        {
            row = 10;
            column = 4;
            faceLeft = true;
        }
        else if (type == 9)
        {
            row = 11;
            column = 4;
            faceLeft = true;
        }
        else if (type == 10)
        {
            row = 10;
            column = 2;
            faceLeft = false;
        }
        else if (type == 11)
        {
            row = 11;
            column = 2;
            faceLeft = false;
        }
        else if (type == 12)
        {
            row = 10;
            column = 3;
            faceLeft = false;
        }
        else if (type == 13)
        {
            row = 11;
            column = 3;
            faceLeft = false;
        }
        else if (type == 14)
        {
            row = 10;
            column = 4;
            faceLeft = false;
        }
        else if (type == 15)
        {
            row = 11;
            column = 4;
            faceLeft = false;
        }
    }
    /*
    else if (areaType == 2)
    {
        row = 4;
    }
    else if (areaType == 3)
    {
        row = 6;
    }
    */
    animation.Update(row, column, column, deltaTime, faceLeft);
    body.setTextureRect(animation.uvRect);
}

///Custom draw to screen function
void Pipe::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
