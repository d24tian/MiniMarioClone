#include "header.h"
#include "goomba.h"

Goomba::Goomba(sf::Texture* texture, sf::Vector2f position) :
    animation(texture, sf::Vector2u(2, 3), 0.125f)
{
    body.setSize(sf::Vector2f(32.0f, 32.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(position);
    body.setTexture(texture);
    this->direction = direction;
    this->squishTimer = 0;
    this->isFlipping = false;
    this->startPos = position;
    this->faceRight = false;
    body.move(sf::Vector2f(0.0f, -0.01f));
}

Goomba::~Goomba()
{
    //dtor
}

float Goomba::DistanceToGround ()
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

float Goomba::DistanceToWall (int direction)
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

///Set sprite based on type
void Goomba::SetSprite()
{
    animation.SetTexture(&goomba);
    row = 0;
    body.setTexture(&goomba);
}

///Update----------------------------------------------------------------------------------------------------
void Goomba::Update(float deltaTime)
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

    if (!isFlipping)
    {
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

        ///Vertical
        if (DistanceToGround() < velocity.y * deltaTime)
        {
            velocity.y = 0.0f;
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
                        velocity.x = -1.0f;
                        direction = 0;
                    }
                    ///Right
                    else if (deltaX < 0.0f)
                    {
                        body.move(-intersectX, 0.0f);
                        velocity.x = 1.0f;
                        direction = 1;
                    }
                }
                else
                {
                    ///Top
                    if (deltaY > 0.0f)
                    {
                        body.move(0.0f, intersectY);
                        velocity.y = -1.0f;
                    }
                    ///Bottom
                    else if (deltaY < 0.0f)
                    {
                        body.move(0.0f, -intersectY);
                        velocity.y = 1.0f;
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
                        velocity.x = -1.0f;
                        direction = 0;
                    }
                    ///Right
                    else if (deltaX < 0.0f)
                    {
                        body.move(-intersectX, 0.0f);
                        velocity.x = 1.0f;
                        direction = 1;
                    }
                }
                else
                {
                    ///Top
                    if (deltaY > 0.0f)
                    {
                        body.move(0.0f, intersectY);
                        velocity.y = -1.0f;
                    }
                    ///Bottom
                    else if (deltaY < 0.0f)
                    {
                        body.move(0.0f, -intersectY);
                        velocity.y = 1.0f;
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
                        velocity.x = -1.0f;
                        direction = 0;
                    }
                    ///Right
                    else if (deltaX < 0.0f)
                    {
                        body.move(-intersectX, 0.0f);
                        velocity.x = 1.0f;
                        direction = 1;
                    }
                }
                else
                {
                    ///Top
                    if (deltaY > 0.0f)
                    {
                        body.move(0.0f, intersectY);
                        velocity.y = -1.0f;
                    }
                    ///Bottom
                    else if (deltaY < 0.0f)
                    {
                        body.move(0.0f, -intersectY);
                        velocity.y = 1.0f;
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
                        velocity.x = -1.0f;
                        direction = 0;
                    }
                    ///Right
                    else if (deltaX < 0.0f)
                    {
                        body.move(-intersectX, 0.0f);
                        velocity.x = 1.0f;
                        direction = 1;
                    }
                }
                else
                {
                    ///Top
                    if (deltaY > 0.0f)
                    {
                        body.move(0.0f, intersectY);
                        velocity.y = -1.0f;
                    }
                    ///Bottom
                    else if (deltaY < 0.0f)
                    {
                        body.move(0.0f, -intersectY);
                        velocity.y = 1.0f;
                    }
                }
            }
        }

        if (squishTimer == 0)
        {
            if (direction == 0)
            {
                velocity.x = -61.3125f;
            }
            else
            {
                velocity.x = 61.3125f;
            }

            ///Check collision with other goombas
            for (int i = 0; i < goombas.size(); i++)
            {
                if (goombas[i].GetPosition().x != GetPosition().x || goombas[i].GetPosition().y != GetPosition().y)
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
                        if (intersectX > intersectY)
                        {
                            ///Left
                            if (deltaX > 0.0f)
                            {
                                direction = 0;
                            }
                            ///Right
                            else if (deltaX < 0.0f)
                            {
                                direction = 1;
                            }
                        }
                    }
                }
            }

            ///Check collision with koopas
            for (int i = 0; i < koopas.size(); i++)
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
                    if (intersectX > intersectY)
                    {
                        ///Left
                        if (deltaX > 0.0f)
                        {
                            direction = 0;
                        }
                        ///Right
                        else if (deltaX < 0.0f)
                        {
                            direction = 1;
                        }
                    }
                }
            }

            ///If off screen, go back to spawn
            if (abs(body.getPosition().x - players[0].GetPosition().x) > (15 * 32.0f) && abs(startPos.x - players[0].GetPosition().x) > (15 * 32.0f))
            {
                body.setPosition(startPos);
                velocity.x = 0.0f;
                velocity.y = 0.0f;
                direction = 0;
            }
        }
        else if (squishTimer > 0)
        {
            velocity.x = 0.0f;
            squishTimer += deltaTime;
        }
    }

    ///Move
    body.move(velocity * deltaTime);

    ///Update animations
    if (direction == 0)
    {
        faceRight = false;
    }
    else if (direction == 1)
    {
        faceRight = true;
    }
    body.setTexture(&goomba);
    animation.Update(row, 0, 1, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);
}

void Goomba::Squish(int otherStreak)
{
    row = 1;
    squishTimer = 1;
    audioManager.PlayAudio("kick");
    if (otherStreak > 0)
    {
        int streakScore = GetStreakScore(otherStreak);
        score += streakScore;
        if (streakScore == 0)
        {
            lives++;
            audioManager.PlayAudio("oneUp");
        }
        else
        {
            scoreNumbers.push_back(ScoreNumber(&pressStart2P, body.getPosition(), streakScore));
        }
    }
}

void Goomba::Flip(int otherStreak)
{
    row = 2;
    isFlipping = true;
    velocity.x = 0.0f;
    velocity.y = -sqrt(981.0f * 981.0f / 4);
    audioManager.PlayAudio("kick");
    if (otherStreak > 0)
    {
        int streakScore = GetStreakScore(otherStreak);
        score += streakScore;
        if (streakScore == 0)
        {
            lives++;
            audioManager.PlayAudio("oneUp");
        }
        else
        {
            scoreNumbers.push_back(ScoreNumber(&pressStart2P, body.getPosition(), streakScore));
        }
    }
}

///Custom draw to screen function
void Goomba::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
