#include "header.h"
#include "fireball.h"

Fireball::Fireball(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, int direction) :
    animation(texture, sf::Vector2u(1, 1), 0.2f)
{
    body.setSize(size);
    body.setOrigin(size / 2.0f);
    body.setPosition(position);
    body.setTexture(texture);
    this->direction = direction;
    this->exploded = false;
    this->row = 0;
}

Fireball::~Fireball()
{
    //dtor
}

float Fireball::DistanceToGround()
{
    float distance = 999999.0f;
    sf::Vector2f blockPos;
    int location;
    int index = 0;

    for (int i = 0; i < breakableBlocks.size(); i++)
    {
        blockPos = breakableBlocks[i].GetPosition();
        bool isBlock = false;

        if (blockPos.y - 16 >= body.getPosition().y + 16)
        {
            ///Left
            if (body.getPosition().x - 12 < blockPos.x + 16 && body.getPosition().x - 12 > blockPos.x - 16)
            {
                isBlock = true;
            }
            ///Right
            if (body.getPosition().x + 12 > blockPos.x - 16 && body.getPosition().x + 12 < blockPos.x + 16)
            {
                isBlock = true;
            }

            if (isBlock)
            {
                if (blockPos.y - 16 - (body.getPosition().y + 16) < distance)
                {
                    distance = blockPos.y - 16 - (body.getPosition().y + 16);
                    location = i;
                    index = 1;
                }
            }
        }
    }

    for (int i = 0; i < unbreakableBlocks.size(); i++)
    {
        blockPos = unbreakableBlocks[i].GetPosition();
        bool isBlock = false;

        if (blockPos.y - 16 >= body.getPosition().y + 16)
        {
            ///Left
            if (body.getPosition().x - 12 < blockPos.x + 16 && body.getPosition().x - 12 > blockPos.x - 16)
            {
                isBlock = true;
            }
            ///Right
            if (body.getPosition().x + 12 > blockPos.x - 16 && body.getPosition().x + 12 < blockPos.x + 16)
            {
                isBlock = true;
            }

            if (isBlock)
            {
                if (blockPos.y - 16 - (body.getPosition().y + 16) < distance)
                {
                    distance = blockPos.y - 16 - (body.getPosition().y + 16);
                    location = i;
                    index = 2;
                }
            }
        }
    }

    for (int i = 0; i < questionBlocks.size(); i++)
    {
        blockPos = questionBlocks[i].GetPosition();
        bool isBlock = false;

        if (blockPos.y - 16 >= body.getPosition().y + 16)
        {
            ///Left
            if (body.getPosition().x - 12 < blockPos.x + 16 && body.getPosition().x - 12 > blockPos.x - 16)
            {
                isBlock = true;
            }
            ///Right
            if (body.getPosition().x + 12 > blockPos.x - 16 && body.getPosition().x + 12 < blockPos.x + 16)
            {
                isBlock = true;
            }

            if (isBlock)
            {
                if (blockPos.y - 16 - (body.getPosition().y + 16) < distance)
                {
                    distance = blockPos.y - 16 - (body.getPosition().y + 16);
                    location = i;
                    index = 3;
                }
            }
        }
    }

    for (int i = 0; i < pipes.size(); i++)
    {
        blockPos = pipes[i].GetPosition();
        bool isBlock = false;

        if (blockPos.y - 16 >= body.getPosition().y + 16)
        {
            ///Left
            if (body.getPosition().x - 12 < blockPos.x + 16 && body.getPosition().x - 12 > blockPos.x - 16)
            {
                isBlock = true;
            }
            ///Right
            if (body.getPosition().x + 12 > blockPos.x - 16 && body.getPosition().x + 12 < blockPos.x + 16)
            {
                isBlock = true;
            }

            if (isBlock)
            {
                if (blockPos.y - 16 - (body.getPosition().y + 16) < distance)
                {
                    distance = blockPos.y - 16 - (body.getPosition().y + 16);
                    location = i;
                    index = 4;
                }
            }
        }
    }

    if (distance == 999999.0f)
    {
        return 999999.0f;
    }
    else
    {
        if (index == 1)
        {
            return breakableBlocks[location].GetPosition().y - 16 - (body.getPosition().y + 16);
        }
        else if (index == 2)
        {
            return unbreakableBlocks[location].GetPosition().y - 16 - (body.getPosition().y + 16);
        }
        else if (index == 3)
        {
            return questionBlocks[location].GetPosition().y - 16 - (body.getPosition().y + 16);
        }
        else if (index == 4)
        {
            return pipes[location].GetPosition().y - 16 - (body.getPosition().y + 16);
        }
    }
}

float Fireball::DistanceToWall(int direction)
{
    float distance = 999999.0f;
    sf::Vector2f blockPos;
    int location;
    int index = 0;

    ///LEFT
    if (direction == 0)
    {
        for (int i = 0; i < breakableBlocks.size(); i++)
        {
            blockPos = breakableBlocks[i].GetPosition();
            if (blockPos.x + 16 <= body.getPosition().x - 12 && blockPos.y - 16 < body.getPosition().y + 16 && blockPos.y + 16 > body.getPosition().y - 16)
            {
                if ((body.getPosition().x - 12) - (blockPos.x + 16) < distance)
                {
                    distance = (body.getPosition().x - 12) - (blockPos.x + 16);
                    location = i;
                    index = 1;
                }
            }
        }

        for (int i = 0; i < unbreakableBlocks.size(); i++)
        {
            blockPos = unbreakableBlocks[i].GetPosition();
            if (blockPos.x + 16 <= body.getPosition().x - 12 && blockPos.y - 16 < body.getPosition().y + 16 && blockPos.y + 16 > body.getPosition().y - 16)
            {
                if ((body.getPosition().x - 12) - (blockPos.x + 16) < distance)
                {
                    distance = (body.getPosition().x - 12) - (blockPos.x + 16);
                    location = i;
                    index = 2;
                }
            }
        }

        for (int i = 0; i < questionBlocks.size(); i++)
        {
            blockPos = questionBlocks[i].GetPosition();
            if (blockPos.x + 16 <= body.getPosition().x - 12 && blockPos.y - 16 < body.getPosition().y + 16 && blockPos.y + 16 > body.getPosition().y - 16)
            {
                if ((body.getPosition().x - 12) - (blockPos.x + 16) < distance)
                {
                    distance = (body.getPosition().x - 12) - (blockPos.x + 16);
                    location = i;
                    index = 3;
                }
            }
        }

        for (int i = 0; i < pipes.size(); i++)
        {
            blockPos = pipes[i].GetPosition();
            if (blockPos.x + 16 <= body.getPosition().x - 12 && blockPos.y - 16 < body.getPosition().y + 16 && blockPos.y + 16 > body.getPosition().y - 16)
            {
                if ((body.getPosition().x - 12) - (blockPos.x + 16) < distance)
                {
                    distance = (body.getPosition().x - 12) - (blockPos.x + 16);
                    location = i;
                    index = 4;
                }
            }
        }
    }
    ///RIGHT
    else if (direction == 1)
    {
        for (int i = 0; i < breakableBlocks.size(); i++)
        {
            blockPos = breakableBlocks[i].GetPosition();
            if (blockPos.x - 16 >= body.getPosition().x + 12 && blockPos.y - 16 < body.getPosition().y + 16 && blockPos.y + 16 > body.getPosition().y - 16)
            {
                if ((blockPos.x - 16) - (body.getPosition().x + 12) < distance)
                {
                    distance = (blockPos.x - 16) - (body.getPosition().x + 12);
                    location = i;
                    index = 1;
                }
            }
        }

        for (int i = 0; i < unbreakableBlocks.size(); i++)
        {
            blockPos = unbreakableBlocks[i].GetPosition();
            if (blockPos.x - 16 >= body.getPosition().x + 12 && blockPos.y - 16 < body.getPosition().y + 16 && blockPos.y + 16 > body.getPosition().y - 16)
            {
                if ((blockPos.x - 16) - (body.getPosition().x + 12) < distance)
                {
                    distance = (blockPos.x - 16) - (body.getPosition().x + 12);
                    location = i;
                    index = 2;
                }
            }
        }

        for (int i = 0; i < questionBlocks.size(); i++)
        {
            blockPos = questionBlocks[i].GetPosition();
            if (blockPos.x - 16 >= body.getPosition().x + 12 && blockPos.y - 16 < body.getPosition().y + 16 && blockPos.y + 16 > body.getPosition().y - 16)
            {
                if ((blockPos.x - 16) - (body.getPosition().x + 12) < distance)
                {
                    distance = (blockPos.x - 16) - (body.getPosition().x + 12);
                    location = i;
                    index = 3;
                }
            }
        }

        for (int i = 0; i < pipes.size(); i++)
        {
            blockPos = pipes[i].GetPosition();
            if (blockPos.x - 16 >= body.getPosition().x + 12 && blockPos.y - 16 < body.getPosition().y + 16 && blockPos.y + 16 > body.getPosition().y - 16)
            {
                if ((blockPos.x - 16) - (body.getPosition().x + 12) < distance)
                {
                    distance = (blockPos.x - 16) - (body.getPosition().x + 12);
                    location = i;
                    index = 4;
                }
            }
        }
    }

    if (direction == 0)
    {
        if (index == 1)
        {
            return (body.getPosition().x - 12) - (breakableBlocks[location].GetPosition().x + 16);
        }
        else if (index == 2)
        {
            return (body.getPosition().x - 12) - (unbreakableBlocks[location].GetPosition().x + 16);
        }
        else if (index == 3)
        {
            return (body.getPosition().x - 12) - (questionBlocks[location].GetPosition().x + 16);
        }
        else if (index == 4)
        {
            return (body.getPosition().x - 12) - (pipes[location].GetPosition().x + 16);
        }
    }
    else if (direction == 1)
    {
        if (index == 1)
        {
            return (breakableBlocks[location].GetPosition().x - 16) - (body.getPosition().x + 12);
        }
        else if (index == 2)
        {
            return (unbreakableBlocks[location].GetPosition().x - 16) - (body.getPosition().x + 12);
        }
        else if (index == 3)
        {
            return (questionBlocks[location].GetPosition().x - 16) - (body.getPosition().x + 12);
        }
        else if (index == 4)
        {
            return (pipes[location].GetPosition().x - 16) - (body.getPosition().x + 12);
        }
    }
}

///Update function------------------------------------------------------------------------------------------
void Fireball::Update(float deltaTime)
{
    if (!exploded)
    {
        ///Limit gravity
        if (velocity.y < 981.0f)
        {
            velocity.y += 3433.5f * deltaTime;//9.81f;
        }
        else
        {
            velocity.y = 981.0f;
        }

        ///Vertical collision
        if (DistanceToGround() < velocity.y * deltaTime)
        {
            velocity.y = -sqrt(981.0f * 122.625f);
            body.move(0.0f, DistanceToGround());
        }

        ///Backup collision engines
        for (int i = 0; i < breakableBlocks.size(); i++)
        {
            sf::Vector2f thisPos = GetPosition();
            sf::Vector2f otherPos = breakableBlocks[i].GetPosition();
            sf::Vector2f thisHalfSize = GetHalfSize();
            sf::Vector2f otherHalfSize = breakableBlocks[i].GetHalfSize();

            float deltaX = otherPos.x - thisPos.x;
            float deltaY = otherPos.y - thisPos.y;

            float intersectX = abs(deltaX) - (thisHalfSize.x + otherHalfSize.x);
            float intersectY = abs(deltaY) - (thisHalfSize.y + otherHalfSize.y);

            if (intersectX < 0.0f && intersectY < 0.0f)
            {
                ///Top
                if (deltaY > 0.0f)
                {
                    body.move(0.0f, intersectY);
                    velocity.y = -sqrt(981.0f * 122.625f);
                }
                ///Bottom
                else if (deltaY < 0.0f)
                {
                    body.move(0.0f, -intersectY);
                    velocity.y = -sqrt(981.0f * 122.625f);
                }
            }
        }

        for (int i = 0; i < unbreakableBlocks.size(); i++)
        {
            sf::Vector2f thisPos = GetPosition();
            sf::Vector2f otherPos = unbreakableBlocks[i].GetPosition();
            sf::Vector2f thisHalfSize = GetHalfSize();
            sf::Vector2f otherHalfSize = unbreakableBlocks[i].GetHalfSize();

            float deltaX = otherPos.x - thisPos.x;
            float deltaY = otherPos.y - thisPos.y;

            float intersectX = abs(deltaX) - (thisHalfSize.x + otherHalfSize.x);
            float intersectY = abs(deltaY) - (thisHalfSize.y + otherHalfSize.y);

            if (intersectX < 0.0f && intersectY < 0.0f)
            {
                ///Top
                if (deltaY > 0.0f)
                {
                    body.move(0.0f, intersectY);
                    velocity.y = -sqrt(981.0f * 122.625f);
                }
                ///Bottom
                else if (deltaY < 0.0f)
                {
                    body.move(0.0f, -intersectY);
                    velocity.y = -sqrt(981.0f * 122.625f);
                }
            }
        }

        for (int i = 0; i < questionBlocks.size(); i++)
        {
            sf::Vector2f thisPos = GetPosition();
            sf::Vector2f otherPos = questionBlocks[i].GetPosition();
            sf::Vector2f thisHalfSize = GetHalfSize();
            sf::Vector2f otherHalfSize = questionBlocks[i].GetHalfSize();

            float deltaX = otherPos.x - thisPos.x;
            float deltaY = otherPos.y - thisPos.y;

            float intersectX = abs(deltaX) - (thisHalfSize.x + otherHalfSize.x);
            float intersectY = abs(deltaY) - (thisHalfSize.y + otherHalfSize.y);

            if (intersectX < 0.0f && intersectY < 0.0f)
            {
                ///Top
                if (deltaY > 0.0f)
                {
                    body.move(0.0f, intersectY);
                    velocity.y = -sqrt(981.0f * 122.625f);
                }
                ///Bottom
                else if (deltaY < 0.0f)
                {
                    body.move(0.0f, -intersectY);
                    velocity.y = -sqrt(981.0f * 122.625f);
                }
            }
        }

        for (int i = 0; i < pipes.size(); i++)
        {
            sf::Vector2f thisPos = GetPosition();
            sf::Vector2f otherPos = pipes[i].GetPosition();
            sf::Vector2f thisHalfSize = GetHalfSize();
            sf::Vector2f otherHalfSize = pipes[i].GetHalfSize();

            float deltaX = otherPos.x - thisPos.x;
            float deltaY = otherPos.y - thisPos.y;

            float intersectX = abs(deltaX) - (thisHalfSize.x + otherHalfSize.x);
            float intersectY = abs(deltaY) - (thisHalfSize.y + otherHalfSize.y);

            if (intersectX < 0.0f && intersectY < 0.0f)
            {
                ///Top
                if (deltaY > 0.0f)
                {
                    body.move(0.0f, intersectY);
                    velocity.y = -sqrt(981.0f * 122.625f);
                }
                ///Bottom
                else if (deltaY < 0.0f)
                {
                    body.move(0.0f, -intersectY);
                    velocity.y = -sqrt(981.0f * 122.625f);
                }
            }
        }

        ///Check collision with goombas
        for (int i = 0; i < goombas.size(); i++)
        {
            if (!goombas[i].isFlipping)
            {
                sf::Vector2f thisPos = GetPosition();
                sf::Vector2f otherPos = goombas[i].GetPosition();
                sf::Vector2f thisHalfSize = GetHalfSize();
                sf::Vector2f otherHalfSize = goombas[i].GetHalfSize();

                float deltaX = otherPos.x - thisPos.x;
                float deltaY = otherPos.y - thisPos.y;

                float intersectX = abs(deltaX) - (thisHalfSize.x + otherHalfSize.x);
                float intersectY = abs(deltaY) - (thisHalfSize.y + otherHalfSize.y);

                if (intersectX < 0.0f && intersectY < 0.0f)
                {
                    goombas[i].Flip(1);
                    Explode();
                }
            }
        }

        ///Check collision with koopas
        for (int i = 0; i < koopas.size(); i++)
        {
            if (!koopas[i].isFlipping)
            {
                sf::Vector2f thisPos = GetPosition();
                sf::Vector2f otherPos = koopas[i].GetPosition();
                sf::Vector2f thisHalfSize = GetHalfSize();
                sf::Vector2f otherHalfSize = koopas[i].GetHalfSize();

                float deltaX = otherPos.x - thisPos.x;
                float deltaY = otherPos.y - thisPos.y;

                float intersectX = abs(deltaX) - (thisHalfSize.x + otherHalfSize.x);
                float intersectY = abs(deltaY) - (thisHalfSize.y + otherHalfSize.y);

                if (intersectX < 0.0f && intersectY < 0.0f)
                {
                    koopas[i].Flip(1);
                    Explode();
                }
            }
        }

        if (body.getPosition().y >= 656.0f)
        {
            exploded = true;
        }

        ///Rotate and move
        if (direction == 0)
        {
            velocity.x = -588.6f;
            body.rotate(-1000 * deltaTime);
        }
        else
        {
            velocity.x = 588.6;
            body.rotate(1000 * deltaTime);
        }
        body.move(velocity * deltaTime);
    }

    ///Update animations
    if (direction == 0)
    {
        animation.Update(row, 0, 0, deltaTime, false);
    }
    else if (direction == 1)
    {
        animation.Update(row, 0, 0, deltaTime, true);
    }
    body.setTextureRect(animation.uvRect);
}

void Fireball::Explode()
{
    explosions.push_back(Explosion(&explosion, body.getPosition()));
    exploded = true;
}

///Custom draw to screen function
void Fireball::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
