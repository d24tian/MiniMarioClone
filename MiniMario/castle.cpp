#include "header.h"
#include "castle.h"

Castle::Castle(sf::Vector2f position)
{
    body.setSize(sf::Vector2f(160.0f, 160.0f));
    body.setOrigin(sf::Vector2f(body.getSize().x / 2.0f, body.getSize().y));
    body.setPosition(sf::Vector2f(position.x, position.y + 16.0f));
    door.setSize(sf::Vector2f(32.0f, 64.0f));
    door.setOrigin(door.getSize() / 2.0f);
    door.setPosition(sf::Vector2f(body.getPosition().x, body.getPosition().y - (door.getSize().y / 2.0f)));
    flag.setSize(sf::Vector2f(32.0f, 32.0f));
    flag.setOrigin(flag.getSize() / 2.0f);
    flag.setPosition(sf::Vector2f(body.getPosition().x, body.getPosition().y - body.getSize().y + flag.getSize().y));
    this->levelFinished = false;
    this->finishTimer = -1.0f;
    this->fireworksLaunched = 0;
}

Castle::~Castle()
{
    //dtor
}

void Castle::SetSprite()
{
    body.setTexture(&castle);
    door.setTexture(&castleDoor);
    flag.setTexture(&castleFlag);
}

void Castle::Update(float deltaTime)
{
    if (levelFinished)
    {
        if (timeLimit > 0.0f)
        {
            timeLimit -= 1.0f;
            score += 50;
        }
        else
        {
            timeLimit = 0.0f;
            finishTimer -= deltaTime;

            if (flag.getPosition().y > body.getPosition().y - body.getSize().y  - (flag.getSize().y / 2.0f))
            {
                flag.move(0.0f, -100.0f * deltaTime);
            }
            else
            {
                flag.setPosition(sf::Vector2f(flag.getPosition().x, body.getPosition().y - body.getSize().y  - (flag.getSize().y / 2.0f)));
            }

            if (finishTimer <= 3.25f && fireworksLaunched < 1)
            {
                explosions.push_back(Explosion(&explosion, sf::Vector2f(body.getPosition().x + rand() % 160 - 80, body.getPosition().y - rand() % 160 - 160)));
                fireworksLaunched++;
            }
            else if (finishTimer <= 2.5f && fireworksLaunched < 2)
            {
                explosions.push_back(Explosion(&explosion, sf::Vector2f(body.getPosition().x + rand() % 160 - 80, body.getPosition().y - rand() % 160 - 160)));
                fireworksLaunched++;
            }
            else if (finishTimer <= 1.75f && fireworksLaunched < 3)
            {
                explosions.push_back(Explosion(&explosion, sf::Vector2f(body.getPosition().x + rand() % 160 - 80, body.getPosition().y - rand() % 160 - 160)));
                fireworksLaunched++;
            }
            else if (finishTimer <= 0.0f)
            {
                finishTimer = 0.0f;

                ///Change level
                if (level == 11)
                {
                    level = 12;
                }
                else if (level == 12)
                {
                    level = 13;
                }
                else if (level == 13)
                {
                    level = 14;
                }
                else if (level == 14)
                {
                    level = 21;
                }

                loadTimer = 3.0f;
                inGame = 1;
            }
        }
    }
}

///Custom draw to screen function
void Castle::Draw(sf::RenderWindow& window)
{
    window.draw(flag);
    window.draw(body);
}

///Custom draw to screen function
void Castle::DrawDoor(sf::RenderWindow& window)
{
    window.draw(door);
}

