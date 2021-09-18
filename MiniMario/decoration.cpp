#include "header.h"
#include "decoration.h"

Decoration::Decoration(sf::Vector2f position, int type) :
    animation(&tilesheet, sf::Vector2u(29, 28), 0.0f)
{
    body.setSize(sf::Vector2f(32.0f, 32.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setTexture(&tilesheet);
    body.setPosition(position);
    this->row = 0;
    this->column = 0;
    this->type = type;
}

Decoration::~Decoration()
{
    //dtor
}

///Set sprite based on type
void Decoration::SetSprite()
{
    animation.SetTexture(&tilesheet);
    body.setTexture(&tilesheet);
}

///Update----------------------------------------------------------------------------------------------------
void Decoration::Update(float deltaTime)
{
    ///Update animations
    body.setTexture(&tilesheet);
    animation.SetTexture(&tilesheet);
    if (areaType == 0)
    {
        if (type == 0)
        {
            row = 8;
            column = 8;
        }
        else if (type == 1)
        {
            row = 9;
            column = 8;
        }
        else if (type == 2)
        {
            row = 9;
            column = 10;
        }
        else if (type == 3)
        {
            row = 9;
            column = 9;
        }
        else if (type == 4)
        {
            row = 8;
            column = 9;
        }
        else if (type == 5)
        {
            row = 8;
            column = 10;
        }
        else if (type == 6)
        {
            row = 9;
            column = 11;
        }
        else if (type == 7)
        {
            row = 9;
            column = 12;
        }
        else if (type == 8)
        {
            row = 9;
            column = 13;
        }
        else if (type == 9)
        {
            row = 21;
            column = 0;
        }
        else if (type == 10)
        {
            row = 21;
            column = 1;
        }
        else if (type == 11)
        {
            row = 20;
            column = 1;
        }
        else if (type == 12)
        {
            row = 21;
            column = 2;
        }
    }
    /*
    else if (areaType == 1)
    {

    }
    else if (areaType == 2)
    {

    }
    else if (areaType == 3)
    {
        row = 6;
    }
    */
    animation.Update(row, column, column, 0.0f, true);
    body.setTextureRect(animation.uvRect);
}

///Custom draw to screen function
void Decoration::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
