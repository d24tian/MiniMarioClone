#include "header.h"
#include "item.h"

Item::Item(sf::Vector2f position, int type) :
    animation(&tilesheet, sf::Vector2u(29, 28), 1.0f / 6.0f)
{
    body.setSize(sf::Vector2f(32.0f, 32.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setTexture(&tilesheet);
    body.setPosition(position);
    this->row = 8;
    this->columnBegin = 25;
    this->columnEnd = 25;
    this->spawnTimer = 1.0f;
    this->direction = 1;
    this->type = type;
}

Item::~Item()
{
    //dtor
}

float Item::DistanceToGround()
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

float Item::DistanceToWall(int direction)
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

///Update function----------------------------------------------------------------------------------------------------
void Item::Update(float deltaTime)
{
    if (spawnTimer > 0.0f)
    {
        body.move(0.0f, -32.0f * deltaTime);
        spawnTimer -= deltaTime;
    }
    else
    {
        if (type == 0 || type == 2)
        {
            if (direction == 0)
            {
                velocity.x = -122.625f;
            }
            else
            {
                velocity.x = 122.625f;
            }
        }

        ///Collision
        ///Horizontal
        if (direction == 0)
        {
            if (DistanceToWall(0) < abs(velocity.x) * deltaTime)
            {
                velocity.x = 0.0f;
                body.move(-DistanceToWall(0), 0.0f);
                direction = 1;
            }
        }
        else if (direction == 1)
        {
            if (DistanceToWall(1) < velocity.x * deltaTime)
            {
                velocity.x = 0.0f;
                body.move(DistanceToWall(1), 0.0f);
                direction = 0;
            }
        }

        ///Limit gravity
        if (velocity.y < 981.0f)
        {
            velocity.y += 1962.0f * deltaTime;//3433.5f * deltaTime;//9.81f;
        }
        else
        {
            velocity.y = 981.0f;
        }

        ///Vertical
        if (DistanceToGround() < velocity.y * deltaTime)
        {
            if (type == 2)
            {
                velocity.y = -sqrt(981.0f * 981.0f / 2.0f);
            }
            else
            {
                velocity.y = 0.0f;
            }
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
                if (intersectX > intersectY)
                {
                    ///Left
                    if (deltaX > 0.0f)
                    {
                        body.move(intersectX, 0.0f);
                        direction = 0;
                    }
                    ///Right
                    else if (deltaX < 0.0f)
                    {
                        body.move(-intersectX, 0.0f);
                        direction = 1;
                    }
                }
                else
                {
                    ///Top
                    if (deltaY > 0.0f)
                    {
                        body.move(0.0f, -intersectY);
                    }
                    ///Bottom
                    else if (deltaY < 0.0f)
                    {
                        body.move(0.0f, -intersectY);
                    }
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
                if (intersectX > intersectY)
                {
                    ///Left
                    if (deltaX > 0.0f)
                    {
                        body.move(intersectX, 0.0f);
                        direction = 0;
                    }
                    ///Right
                    else if (deltaX < 0.0f)
                    {
                        body.move(-intersectX, 0.0f);
                        direction = 1;
                    }
                }
                else
                {
                    ///Top
                    if (deltaY > 0.0f)
                    {
                        body.move(0.0f, -intersectY);
                    }
                    ///Bottom
                    else if (deltaY < 0.0f)
                    {
                        body.move(0.0f, -intersectY);
                    }
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
                if (intersectX > intersectY)
                {
                    ///Left
                    if (deltaX > 0.0f)
                    {
                        body.move(intersectX, 0.0f);
                        direction = 0;
                    }
                    ///Right
                    else if (deltaX < 0.0f)
                    {
                        body.move(-intersectX, 0.0f);
                        direction = 1;
                    }
                }
                else
                {
                    ///Top
                    if (deltaY > 0.0f)
                    {
                        body.move(0.0f, -intersectY);
                    }
                    ///Bottom
                    else if (deltaY < 0.0f)
                    {
                        body.move(0.0f, -intersectY);
                    }
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
                if (intersectX > intersectY)
                {
                    ///Left
                    if (deltaX > 0.0f)
                    {
                        body.move(intersectX, 0.0f);
                        direction = 0;
                    }
                    ///Right
                    else if (deltaX < 0.0f)
                    {
                        body.move(-intersectX, 0.0f);
                        direction = 1;
                    }
                }
                else
                {
                    ///Top
                    if (deltaY > 0.0f)
                    {
                        body.move(0.0f, -intersectY);
                    }
                    ///Bottom
                    else if (deltaY < 0.0f)
                    {
                        body.move(0.0f, -intersectY);
                    }
                }
            }
        }

        if (bumpCooldown)
        {
            bumpCooldown = false;
        }

        ///Move
        body.move(velocity * deltaTime);
    }

    ///Update animations
    body.setTexture(&tilesheet);
    animation.SetTexture(&tilesheet);
    if (areaType == 0)
    {
        ///Mushroom
        if (type == 0)
        {
            row = 8;
            columnBegin = 25;
            columnEnd = 25;
        }
        ///Fire flower
        else if (type == 1)
        {
            row = 10;
            columnBegin = 25;
            columnEnd = 28;
        }
        ///Star
        else if (type == 2)
        {
            row = 11;
            columnBegin = 25;
            columnEnd = 28;
        }
        ///1-Up
        else if (type == 3)
        {
            row = 8;
            columnBegin = 26;
            columnEnd = 26;
        }
    }
    else if (areaType == 1)
    {
        ///Mushroom
        if (type == 0)
        {
            row = 8;
            columnBegin = 25;
            columnEnd = 25;
        }
        ///Fire flower
        else if (type == 1)
        {
            row = 14;
            columnBegin = 25;
            columnEnd = 28;
        }
        ///Star
        else if (type == 2)
        {
            row = 15;
            columnBegin = 25;
            columnEnd = 28;
        }
        ///1-Up
        else if (type == 3)
        {
            row = 8;
            columnBegin = 26;
            columnEnd = 26;
        }
    }
    else if (areaType == 2)
    {
        ///Mushroom
        if (type == 0)
        {
            row = 8;
            columnBegin = 25;
            columnEnd = 25;
        }
        ///Fire flower
        else if (type == 1)
        {
            row = 18;
            columnBegin = 25;
            columnEnd = 28;
        }
        ///Star
        else if (type == 2)
        {
            row = 19;
            columnBegin = 25;
            columnEnd = 28;
        }
        ///1-Up
        else if (type == 3)
        {
            row = 8;
            columnBegin = 26;
            columnEnd = 26;
        }
    }
    else if (areaType == 3)
    {
        ///Mushroom
        if (type == 0)
        {
            row = 8;
            columnBegin = 25;
            columnEnd = 25;
        }
        ///Fire flower
        else if (type == 1)
        {
            row = 22;
            columnBegin = 25;
            columnEnd = 28;
        }
        ///Star
        else if (type == 2)
        {
            row = 23;
            columnBegin = 25;
            columnEnd = 28;
        }
        ///1-Up
        else if (type == 3)
        {
            row = 8;
            columnBegin = 26;
            columnEnd = 26;
        }
    }
    animation.Update(row, columnBegin, columnEnd, deltaTime, true);
    body.setTextureRect(animation.uvRect);
}

void Item::Bump()
{
    if (!bumpCooldown)
    {
        if (direction == 0)
        {
            direction = 1;
        }
        else if (direction == 1)
        {
            direction = 0;
        }

        velocity.y = -sqrt(981.0f * 981.0f / 4);

        bumpCooldown = true;
    }
}

///Custom draw to screen function
void Item::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
