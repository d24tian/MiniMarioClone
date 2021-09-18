#include "header.h"
#include "breakableblock.h"

BreakableBlock::BreakableBlock(sf::Vector2f position, int type, int param) :
    animation(&tilesheet, sf::Vector2u(29, 28), 0.0f)
{
    body.setSize(sf::Vector2f(32.0f, 32.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(position);
    body.setTexture(&tilesheet);
    this->row = 0;
    this->column = 1;
    this->type = type;
    this->param = param;
    this->collideCounter = 0;
    this->originalY = position.y;
    this->coinTimer = -1.0f;
    this->isBroken = false;
}

BreakableBlock::~BreakableBlock()
{
    //dtor
}

int BreakableBlock::GetItem()
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

int BreakableBlock::GetGoomba()
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

int BreakableBlock::GetKoopa()
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
void BreakableBlock::SetSprite()
{
    animation.SetTexture(&tilesheet);
    body.setTexture(&tilesheet);
}

void BreakableBlock::Update(float deltaTime)
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

    if (coinTimer > 0.0f)
    {
        coinTimer -= deltaTime;
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
        column = 0;
    }
    else if (type == 1)
    {
        column = 1;
    }
    else if (type == 2)
    {
        column = 2;
    }
    animation.Update(row, column, column, deltaTime, true);
    body.setTextureRect(animation.uvRect);
}

///Move and detect for objects above when player collides
void BreakableBlock::OnCollision(int isBig)
{
    if (type != 2)
    {
        ///Nothing
        if (param == 0)
        {
            if (isBig == 0)
            {
                collideCounter = 0.1f;
                audioManager.PlayAudio("bump");
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    blockParticles.push_back(BlockParticle(GetPosition(), i));
                }
                audioManager.PlayAudio("breakBlock");
                isBroken = true;
            }
        }
        ///Coins for 4 seconds
        else if (param == 1)
        {
            if (coinTimer == -1.0f)
            {
                coinTimer = 4.0f;
            }
            else if (coinTimer <= 0.0f)
            {
                ///Deactivate
                type = 2;
                column = 3;
            }

            coins.push_back(Coin(body.getPosition()));
            audioManager.PlayAudio("coin");
            collideCounter = 0.1f;
            coinCounter++;
            score += 200;
        }
        ///Star
        else if (param == 2)
        {
            items.push_back(Item(body.getPosition(), 2));
            collideCounter = 0.1f;
            audioManager.PlayAudio("powerupAppears");

            ///Deactivate
            type = 2;
            column = 3;
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
    }
    else
    {
        audioManager.PlayAudio("bump");
    }
}

///Custom draw to screen function
void BreakableBlock::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
