#include "header.h"
#include "blockparticle.h"

BlockParticle::BlockParticle(sf::Vector2f position, int index)
{
    body.setPosition(position);
    body.setSize(sf::Vector2f(16.0f, 16.0f));
    body.setOrigin(body.getSize() / 2.0f);

    if (index == 0 || index == 2)
    {
        velocity.x = -981.0f / 4;
        body.rotate(0);
    }
    else if (index == 1 || index == 3)
    {
        velocity.x = 981.0f / 4;
        body.rotate(90);
    }

    if (index == 0 || index == 1)
    {
        velocity.y = -sqrt(981.0f * 981.0f);
    }
    else if (index == 2 || index == 3)
    {
        velocity.y = -sqrt(981.0f * 981.0f / 4.0f);
    }

    this->isOutside = false;
}

BlockParticle::~BlockParticle()
{
    //dtor
}

void BlockParticle::Update(float deltaTime)
{
    sf::Vector2f bodyPos = body.getPosition();

    ///Limit gravity
    if (velocity.y < 981.0f)
    {
        velocity.y += 3433.5f * deltaTime;
    }
    else
    {
        velocity.y = 981.0f;
    }

    ///Check if body is below the map
    if (bodyPos.y >= 656.0f)
    {
        isOutside = true;
    }

    ///Move body
    body.move(velocity * deltaTime);

    ///Set texture
    body.setTexture(&blockParticle);
}

///Custom draw to screen function
void BlockParticle::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
