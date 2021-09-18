#include "header.h"
#include "questionblock.h"

QuestionBlock::QuestionBlock(sf::Vector2f position, int type, int param) :
    animation(&tilesheet, sf::Vector2u(29, 28), 0.125f)
{
    body.setSize(sf::Vector2f(32.0f, 32.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setTexture(&tilesheet);
    body.setPosition(position);
    this->row = 0;
    this->columnBegin = 23;
    this->columnEnd = 28;
    this->type = type;
    this->param = param;
    this->collideCounter = 0;
    this->originalY = position.y;
}

QuestionBlock::~QuestionBlock()
{
    //dtor
}

int QuestionBlock::GetItem()
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].GetPosition().y + 16 <= GetPosition().y - 16 && items[i].GetPosition().y + 16 >= GetPosition().y - 18)
        {
            ///Left
            if (GetPosition().x - 12 < items[i].GetPosition().x + 16 && GetPosition().x - 12 > items[i].GetPosition().x - 16)
            {
                return i;
            }
            ///Right
            if (GetPosition().x + 12 > items[i].GetPosition().x - 16 && GetPosition().x + 12 < items[i].GetPosition().x + 16)
            {
                return i;
            }
        }
    }

    return -1;
}

int QuestionBlock::GetGoomba()
{
    for (int i = 0; i < goombas.size(); i++)
    {
        if (goombas[i].GetPosition().y + 16 <= GetPosition().y - 16 && goombas[i].GetPosition().y + 16 >= GetPosition().y - 18)
        {
            ///Left
            if (GetPosition().x - 12 < goombas[i].GetPosition().x + 16 && GetPosition().x - 12 > goombas[i].GetPosition().x - 16)
            {
                return i;
            }
            ///Right
            if (GetPosition().x + 12 > goombas[i].GetPosition().x - 16 && GetPosition().x + 12 < goombas[i].GetPosition().x + 16)
            {
                return i;
            }
        }
    }

    return -1;
}

int QuestionBlock::GetKoopa()
{
    for (int i = 0; i < koopas.size(); i++)
    {
        if (koopas[i].GetPosition().y + 16 <= GetPosition().y - 16 && koopas[i].GetPosition().y + 16 >= GetPosition().y - 18)
        {
            ///Left
            if (GetPosition().x - 12 < koopas[i].GetPosition().x + 16 && GetPosition().x - 12 > koopas[i].GetPosition().x - 16)
            {
                return i;
            }
            ///Right
            if (GetPosition().x + 12 > koopas[i].GetPosition().x - 16 && GetPosition().x + 12 < koopas[i].GetPosition().x + 16)
            {
                return i;
            }
        }
    }

    return -1;
}

///Set sprite based on type
void QuestionBlock::SetSprite()
{
    animation.SetTexture(&tilesheet);
    body.setTexture(&tilesheet);
}

void QuestionBlock::Update(float deltaTime)
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

    if (collideCounter > 0)
    {
        if (body.getPosition().y - (128 * deltaTime) > originalY - 8.0f)
        {
            body.move(0.0f, -128 * deltaTime);
            collideCounter -= deltaTime;
        }
        else if (body.getPosition().y - (128 * deltaTime) <= originalY - 8.0f)
        {
            body.setPosition(sf::Vector2f(body.getPosition().x, originalY - 8.0f));
            collideCounter = 0.0f;
        }
    }
    else if (GetPosition().y + (128 * deltaTime) < originalY)
    {
        body.move(0.0f, 128 * deltaTime);
    }
    else if (GetPosition().y + (128 * deltaTime) >= originalY)
    {
        body.setPosition(GetPosition().x, originalY);
    }

    ///Update animation
    body.setTexture(&tilesheet);
    animation.SetTexture(&tilesheet);
    if (areaType == 0)
    {
        row = 0;
    }
    else if (areaType == 1)
    {
        row = 2;
    }
    else if (areaType == 2)
    {
        row = 4;
    }
    else if (areaType == 3)
    {
        row = 6;
    }

    if (type == 0)
    {
        columnBegin = 23;
        columnEnd = 28;
    }
    else if (type == 1)
    {
        columnBegin = 2;
        columnEnd = 2;
    }
    animation.Update(row, columnBegin, columnEnd, deltaTime, true);
    body.setTextureRect(animation.uvRect);
}

///Move and create item when player collides
void QuestionBlock::OnCollision(int isBig)
{
    if (type == 0)
    {
        if (param == 0)
        {
            coins.push_back(Coin(body.getPosition()));
            audioManager.PlayAudio("coin");
            score += 200;
            coinCounter++;
        }
        else if (param == 1)
        {
            if (isBig != 0)
            {
                items.push_back(Item(body.getPosition(), 1));
            }
            else
            {
                items.push_back(Item(body.getPosition(), 0));
            }
            audioManager.PlayAudio("powerupAppears");
        }

        if (GetItem() != -1)
        {
            items[GetItem()].Bump();
        }
        if (GetGoomba() != -1)
        {
            goombas[GetGoomba()].Flip(1);
        }
        if (GetKoopa() != -1)
        {
            koopas[GetKoopa()].Flip(1);
        }

        collideCounter = 0.1f;
    }
    else
    {
        audioManager.PlayAudio("bump");
    }

    ///Deactivate
    type = 1;
}

///Custom draw to screen function
void QuestionBlock::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
